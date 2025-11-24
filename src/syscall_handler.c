// ---
// Includes
// ---

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "personality.h"
#include "statistic.h"
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
static int	_cur_write = 0;

// ---
// Static function declarations
// ---

static void	_syscall_handle_pers_change(
				int new_pers,
				pid_t pid
				);

// ---
// Extern function definitions
// ---

int	syscall_handle_in(
		pid_t pid,
		syscall_info_t *sci
		) {
	TRY(pers_get_sci(pid, sci));
	_cur_scd = sci->scd;
	_syscall_handle_pers_change(sci->pers, pid);
	if (_cur_scd == &g_syscall_defs[SR_SYS_execve])
		(logger_should_log_event(true), stat_should_save(true));
	TRY(_cur_write = logger_log_syscall_in(sci));
	return (0);
}

int	syscall_handle_out(
		pid_t pid,
		syscall_info_t *sci,
		long time
		) {
	stat_entry_t	stat;

	if (WIFEXITED(g_ctx.cstatus) || WIFSIGNALED(g_ctx.cstatus))
		return (logger_log_syscall_out(NULL, _cur_write), 0);
	TRY(pers_get_sci(pid, sci));
	sci->scd = _cur_scd;
	TRY(logger_log_syscall_out(sci, _cur_write));
	if (!WIFEXITED(g_ctx.cstatus) && !WIFSIGNALED(g_ctx.cstatus) && sci->errnr <= ERRNO_MAX) {
		stat.sci = *sci;
		stat.time = time;
		TRY(stat_add(&stat));
	}
	if (sci->errnr != 0 && _cur_scd == &g_syscall_defs[SR_SYS_execve])
		(logger_should_log_event(false), stat_should_save(false));
	_syscall_handle_pers_change(sci->pers, pid);
	return (0);
}

// ---
// Static function definitions
// ---

static void	_syscall_handle_pers_change(
				int new_pers,
				pid_t pid
				) {
	if (new_pers == _cur_pers)
		return ;
	if (_cur_pers != -1)
		logger_log("[ Process PID=%d runs in %s mode. ]\n", pid, pers_get_name(new_pers));
	_cur_pers = new_pers;
}
