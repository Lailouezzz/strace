#ifndef  LOGGER_H
# define LOGGER_H

// ---
// Includes
// ---

# include <bits/types/siginfo_t.h>
# include <stdbool.h>
# include "syscall.h"

// ---
// Defines
// ---

# define LOGGER_PADDING (40)
# define LOG_FUNC_DEFAULT g_log_funcs[SYS_TYPE_INT]

// ---
// Typedefs
// ---

typedef int	(*log_func_t)(uint64_t value, const syscall_info_t *sci);

// ---
// Global variable
// ---

/**
 * @brief All logger function for each type
 */
extern const log_func_t	g_log_funcs[SYS_TYPE__COUNT];

// ---
// Function declartions
// ---

/**
 * @brief Define if the logger should log event like syscall, signals
 *
 * @param should_log 
 */
void	logger_should_log_event(
			bool should_log_event
			);

/**
 * @brief Define if the logger is disabled or not
 *
 * @param disabled 
 */
void	logger_disabled(
			bool disabled
			);

/**
 * @brief Log syscall event before the syscall
 *
 * @param sci The syscall informations
 * @return Number of char written in stderr
 */
int	logger_log_syscall_in(
		const syscall_info_t *sci
		);

/**
 * @brief Log syscall event after the syscall
 *
 * @param sci The syscall informations
 * @param cur_write The current amount of char written to stderr
 * @return Number of char written in stderr
 */
int	logger_log_syscall_out(
		const syscall_info_t *sci,
		int cur_write
		);

int	logger_log_signal(
		int pid,
		const siginfo_t *siginfo
		);

int	logger_log_args(
		const syscall_info_t *sci,
		const uint64_t args[MAX_SYSCALL_ARG_COUNT],
		bool syscall_in
		);

int	logger_log_return(
		const syscall_info_t *sci
		);

int	logger_log_event(
		const char *fmt, ...
		);

int	logger_log(
		const char *fmt, ...
		);

#endif
