// ---
// Includes
// ---

#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "utils.h"

// ---
// Local variable
// ---

static bool		_should_log = false;
static uint64_t	_saved_args[MAX_SYSCALL_ARG_COUNT];

// ---
// Static function declarations
// ---



// ---
// Extern function definitions
// ---

void	logger_should_log_event(
			bool should_log
			) {
	_should_log = should_log;
}

void	logger_log_syscall_in(
			const syscall_info_t *sci
			) {
	if (!_should_log)
		return ;
	memcpy(_saved_args, sci->args, ELEM_COUNT(_saved_args));
	fprintf(stderr, "%s(...)", sci->scd->name);
}

void	logger_log_syscall_out(
			const syscall_info_t *sci
			) {
	if (!_should_log)
		return ;
	if (sci == NULL) {
		fprintf(stderr, " = ?\n");
		return ;
	}
	fprintf(stderr, " = %ld\n", (int64_t)sci->ret);
}

// ---
// Static function definitions
// ---
