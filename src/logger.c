// ---
// Includes
// ---

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include "utils.h"
#include "log_funcs.h"

#include "logger.h"

// ---
// Define
// ---

#define SHOULD_LOG_EVENT (_should_log_event && !_disabled)

// ---
// Local variable
// ---

static bool		_should_log_event = false;
static bool		_disabled = false;
static uint64_t	_saved_args[MAX_SYSCALL_ARG_COUNT];

// ---
// Static function declarations
// ---



// ---
// Extern function definitions
// ---

void	logger_should_log_event(
			bool should_log_event
			) {
	_should_log_event = should_log_event;
}

void	logger_disabled(
			bool disabled
			) {
	_disabled = disabled;
}

int	logger_log_syscall_in(
			const syscall_info_t *sci
			) {
	int	ret = 0;
	int	tmp;

	if (!SHOULD_LOG_EVENT)
		return (0);
	memcpy(_saved_args, sci->args, sizeof(_saved_args));
	TRY_SILENT(tmp = fprintf(stderr, "%s(", sci->scd->name));
	ret += tmp;
	TRY_SILENT(tmp = logger_log_args(sci, sci->args, true));
	ret += tmp;
	fflush(stderr);
	return (ret);
}

int	logger_log_syscall_out(
			const syscall_info_t *sci,
			int cur_write
			) {
	int	ret = cur_write;
	int tmp;

	if (!SHOULD_LOG_EVENT)
		return (0);
	TRY_SILENT(tmp = logger_log_args(sci, _saved_args, false));
	ret += tmp;
	TRY_SILENT(tmp = fprintf(stderr, ")%*s", MAX(LOGGER_PADDING - ret - 2, 0), ""));
	ret += tmp;
	if (sci == NULL) {
		TRY_SILENT(tmp = fprintf(stderr, " = ?\n"));
		ret += tmp;
		return (ret);
	}
	if (sci->errnr != 0) {
		switch (sci->errnr) {
			case ERESTARTSYS:
			case ERESTARTNOINTR:
			case ERESTARTNOHAND:
			case ERESTART_RESTARTBLOCK:
				TRY_SILENT(tmp = fprintf(stderr, " = ?"));
				ret += tmp;
				break;
		default:
				TRY_SILENT(tmp = fprintf(stderr, " = -1"));
				ret += tmp;
		}
		TRY_SILENT(tmp = fprintf(stderr, " %s (%s)\n", errno_name(sci->errnr), kstrerror(sci->errnr)));
		ret += tmp;
	}
	else {
		TRY_SILENT(tmp = fprintf(stderr, " = "));
		ret += tmp;
		TRY_SILENT(tmp = logger_log_return(sci));
		ret += tmp;
		TRY_SILENT(tmp = fprintf(stderr, "\n"));
		ret += tmp;
	}
	return (ret);
}

int	logger_log_event(const char *fmt, ...) {
	va_list	args;
	int		ret;

	if (!SHOULD_LOG_EVENT)
		return (0);
	va_start(args, fmt);
	ret = vfprintf(stderr, fmt, args);
	va_end(args);
	return (ret);
}

int	logger_log(const char *fmt, ...) {
	va_list	args;
	int		ret;

	va_start(args, fmt);
	ret = vfprintf(stderr, fmt, args);
	va_end(args);
	return (ret);
}

int	logger_log_args(
		const syscall_info_t *sci,
		const uint64_t args[MAX_SYSCALL_ARG_COUNT],
		bool syscall_in
		) {
	int	begin;
	int	end;
	int	ret;
	int	tmp;
	log_func_t	log_func;

	if (sci == NULL)
		return (0);
	if (g_log_custom[SCD_INDEX(sci->scd)][syscall_in ? 0 : 1] != NULL)
		return (g_log_custom[SCD_INDEX(sci->scd)][syscall_in ? 0 : 1](sci));
	begin = 0;
	end = MAX_SYSCALL_ARG_COUNT;
	for (int k = 0; k < MAX_SYSCALL_ARG_COUNT; ++k) {
		*(syscall_in ? &end : &begin) = k;
		if ((int)sci->scd->arg_types[k] > 0)
			break ;
	}
	ret = 0;
	for (int k = begin; k < end && sci->scd->arg_types[k] != SYS_TYPE_NONE; ++k) {
		log_func = g_log_funcs[GET_SYS_TYPE((int)sci->scd->arg_types[k])];
		if (log_func != NULL) {
			TRY_SILENT(tmp = log_func(args[k], sci, sci->scd->arg_types[k]));
		}
		else {
			TRY_SILENT(tmp = LOG_FUNC_DEFAULT(args[k], sci, SYS_TYPE_DEFAULT));
		}
		ret += tmp;
		if (k != MAX_SYSCALL_ARG_COUNT - 1 && sci->scd->arg_types[k + 1] != SYS_TYPE_NONE) {
			TRY_SILENT(tmp = fprintf(stderr, ", "));
			ret += tmp;
		}
	}
	return (ret);
}

int	logger_log_return(
		const syscall_info_t *sci
		) {
	log_func_t	log_func;

	log_func = g_log_funcs[GET_SYS_TYPE((int)sci->scd->ret_type)];
	if (log_func != NULL)
		return (log_func(sci->ret, sci, sci->scd->ret_type));
	else
		return (LOG_FUNC_DEFAULT(sci->ret, sci, sci->scd->ret_type));
}

int	logger_log_signal(
		int pid,
		const siginfo_t *si
		) {
	UNUSED(pid);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = logger_log_event("--- %s {si_signo=%s si_code=%d",
										signal_name(si->si_signo),
										signal_name(si->si_signo),
										si->si_code));
	ret += tmp;
	switch (si->si_signo) {
		case SIGSEGV:
			TRY_SILENT(tmp = logger_log_event(" si_addr=%p", si->si_addr));
			break ;
		default:
			break ;
	}
	ret += tmp;
	TRY_SILENT(tmp = logger_log_event("} ---\n"));
	ret += tmp;
	return (ret);
}

// ---
// Static function definitions
// ---
