/**
 * @file tracer.c
 * @brief Process tracing and syscall interception implementation.
 */

// ---
// Includes
// ---

#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <signal.h>
#include <elf.h>
#include <time.h>
#include "logger.h"
#include "statistic.h"
#include "strace.h"
#include "syscall_handler.h"
#include "utils.h"

#include "tracer.h"

// ---
// Local variables
// ---

/**
 * @brief Currently attached process ID.
 */
static pid_t	_pid = -1;

/**
 * @brief Signal to deliver on next ptrace continue.
 */
static int		_cont_sig = 0;

// ---
// Static function declarations
// ---

/**
 * @brief Wait for the traced process to stop with SIGSTOP.
 * @param pid Process ID to wait for.
 * @return 0 on success, -1 on error.
 */
static int	_tracer_attach_wait(
				pid_t pid
				);

/**
 * @brief Handle a syscall entry/exit event.
 * @param start_ru Resource usage at syscall entry.
 * @return 0 on success, -1 on error.
 */
static int	_tracer_handle_syscall(
				const struct rusage *start_ru
				);

/**
 * @brief Log the traced process exit status.
 */
static void	_tracer_handle_exit(void);

/**
 * @brief Handle a signal received by the traced process.
 * @return 0 on success, -1 on error.
 */
static int _tracer_handle_sig(void);

// ---
// Extern function definitions
// ---

int	tracer_attach(
		pid_t pid,
		bool wait_sigstop
		) {
	_pid = pid;

	if (ptrace(PTRACE_SEIZE, pid, NULL, PTRACE_O_TRACESYSGOOD) < 0)
		return (perror_msg("attach: ptrace(PTRACE_SEIZE)"), -1);
	if (wait_sigstop && _tracer_attach_wait(pid) == -1)
		return (-1);
	return (0);
}

int	tracer_loop(void) {
	struct rusage	start_ru;

	if (_pid < 0)
		return (-1);
	while (!WIFEXITED(g_ctx.cstatus) && !WIFSIGNALED(g_ctx.cstatus) && g_ctx.signal == 0) {
		if (ptrace(PTRACE_SYSCALL, _pid, NULL, _cont_sig) < 0)
			return (perror_msg("ptrace(PTRACE_SYSCALL, %d)", _pid), -1);
		if (wait4(_pid, &g_ctx.cstatus, __WALL, &start_ru) == -1)
			return (perror_msg("waitpid(%d)", _pid), -1);
		if (WIFSTOPPED(g_ctx.cstatus)) {
			_cont_sig = WSTOPSIG(g_ctx.cstatus);
			if ((_cont_sig & 0x7f) == SIGTRAP && (_cont_sig & 0x80) != 0) {
				if (_tracer_handle_syscall(&start_ru) != 0)
					return (-1);
				_cont_sig = 0;
			} else {
				if (_tracer_handle_sig() != 0)
					return (-1);
			}
		}
	}
	return (_tracer_handle_exit(), 0);
}

// ---
// Static function definitions
// ---

static int	_tracer_attach_wait(
				pid_t pid
				) {
	if (waitpid(pid, &g_ctx.cstatus, 0) == -1)
		return (perror_msg("waitpid(%d)", pid), -1);
	if (WIFEXITED(g_ctx.cstatus) || WIFSIGNALED(g_ctx.cstatus))
		return (error_msg("Desired pid %d is terminated", pid), -1);
	if (!WIFSTOPPED(g_ctx.cstatus) || WSTOPSIG(g_ctx.cstatus) != SIGSTOP) {
		error_msg("Desired pid %d wasn't stopped by SIGSTOP (%d)", pid, WSTOPSIG(g_ctx.cstatus));
		return (-1);
	}
	return (0);
}

static int	_tracer_handle_syscall(
				const struct rusage *start_ru
				) {

	syscall_info_t	sci;
	stat_entry_t	stat;
	struct rusage	ru;

	syscall_handle_in(_pid, &sci);
	if (ptrace(PTRACE_SYSCALL, _pid, NULL, 0) < 0)
		return (perror_msg("ptrace(PTRACE_SYSCALL, %d)", _pid), -1);
	if (wait4(_pid, &g_ctx.cstatus, __WALL, &ru) == -1)
		return (errno == EINTR ? 0 : (perror_msg("waitpid(%d)", _pid), -1));
	stat.time = (ru.ru_stime.tv_usec + ru.ru_stime.tv_sec * 1000000L) - (start_ru->ru_stime.tv_usec + start_ru->ru_stime.tv_sec * 1000000L);
	syscall_handle_out(_pid, &sci);
	if (!WIFEXITED(g_ctx.cstatus) && !WIFSIGNALED(g_ctx.cstatus)) {
		stat.sci = sci;
		TRY(stat_add(&stat));
	}
	return (0);
}

static void	_tracer_handle_exit(void) {
	if (WIFEXITED(g_ctx.cstatus))
		logger_log_event("+++ exited with %d +++\n", WEXITSTATUS(g_ctx.cstatus));
	else if (WIFSIGNALED(g_ctx.cstatus)) {
		logger_log_event("+++ killed by %s", signal_name(WTERMSIG(g_ctx.cstatus)));
		switch (WTERMSIG(g_ctx.cstatus)) {
			case SIGSEGV:
			case SIGQUIT:
				logger_log_event(" (core dumped)");
				break ;
			default:
				break ;
		}
		logger_log_event(" +++\n");
	}
}

static int _tracer_handle_sig(void) {
	siginfo_t	siginfo;

	if (ptrace(PTRACE_GETSIGINFO, _pid, NULL, &siginfo) < 0)
		return (perror_msg("ptrace(PTRACE_GETSIGINFO, %d)", _pid), -1);
	if (WIFSTOPPED(g_ctx.cstatus)) {
		if (siginfo.si_signo == SIGTRAP)
			_cont_sig = 0;
		logger_log_signal(_pid, &siginfo);
	}
	return (0);
}
