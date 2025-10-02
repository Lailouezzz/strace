// ---
// Includes
// ---

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"

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
	/* TODO: print in args */
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
	/* TODO: print out args */
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
		TRY_SILENT(tmp = fprintf(stderr, " = %ld\n", sci->ret));
		ret += tmp;
	}
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

// ---
// Static function definitions
// ---
