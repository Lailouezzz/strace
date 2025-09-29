/**
 * @file
 * @brief 
 */

// ---
// Includes
// ---

#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "strace.h"
#include "utils.h"

#include "tracer.h"

// ---
// Local variables
// ---

/**
 * @brief Attached pid
 */
static pid_t	_pid = -1;

// ---
// Static function declarations
// ---

/**
 * @brief Wait pid SIGSTOP
 *
 * @param pid 
 * @return -1 error; 0 success
 */
static int	_tracer_attach_wait(
				pid_t pid
				);

// ---
// Extern function definitions
// ---

int	tracer_attach(
		pid_t pid,
		bool wait_sigstop
		) {
	_pid = pid;

	if (ptrace(PTRACE_SEIZE, pid, NULL, PTRACE_O_TRACESYSGOOD) == -1)
		return (perror_msg("attach: ptrace(PTRACE_SEIZE)"), -1);
	if (wait_sigstop && _tracer_attach_wait(pid) == -1)
		return (-1);
	return (0);
}

int	tracer_loop(void) {
	int	sig = 0;

	if (_pid < 0)
		return (-1);
	while (42 > 01) {
		ptrace(PTRACE_SYSCALL, _pid, NULL, sig);
		if (waitpid(_pid, &g_ctx.cstatus, __WALL) == -1)
			return (perror_msg("waitpid(%d)", _pid), -1);
		if (WIFEXITED(g_ctx.cstatus) || WIFSIGNALED(g_ctx.cstatus))
			break ;
		if (WIFSTOPPED(g_ctx.cstatus)) {
			sig = WSTOPSIG(g_ctx.cstatus);
			if ((sig & 0x7f) == SIGTRAP) {
				if ((sig & 0x80) == 0) // Not a syscall trap
					continue ;
				verbose("Syscall called\n");
				sig = 0;
			}
		}
	}
	return (0);
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
