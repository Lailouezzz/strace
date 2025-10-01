// ---
// Includes
// ---

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "personality.h"
#include "strace.h"
#include "syscall.h"
#include "syscall_defs.h"
#include "utils.h"

#include "syscall_handler.h"

// ---
// Local variable
// ---

static int	_cur_pers = -1;
static const syscall_def_t	*_cur_scd = NULL;

// ---
// Static function declarations
// ---

static void	_syscall_handle_pers_change(
				int new_pers
				);

// ---
// Extern function definitions
// ---

int	syscall_handle_in(
		pid_t pid
		) {
	syscall_info_t	sci = { 0 };

	TRY(pers_get_sci(pid, &sci));
	_cur_scd = sci.scd;
	_syscall_handle_pers_change(sci.pers);
	if (_cur_scd == &g_syscall_defs[SR_SYS_execve])
		logger_should_log_event(true);
	logger_log_syscall_in(&sci);
	return (0);
}

int	syscall_handle_out(
		pid_t pid
		) {
	syscall_info_t	sci;

	if (WIFEXITED(g_ctx.cstatus) || WIFSIGNALED(g_ctx.cstatus))
		return (logger_log_syscall_out(NULL), 0);
	TRY(pers_get_sci(pid, &sci));
	logger_log_syscall_out(&sci);
	if ((int64_t)sci.ret < 0 && _cur_scd == &g_syscall_defs[SR_SYS_execve])
		logger_should_log_event(false);
	_syscall_handle_pers_change(sci.pers);
	return (0);
}

// ---
// Static function definitions
// ---

static void	_syscall_handle_pers_change(
				int new_pers
				) {
	if (new_pers == _cur_pers)
		return ;
	if (_cur_pers != -1)
		verbose("Changing mode to %s\n", pers_get_name(new_pers));
	_cur_pers = new_pers;
}
