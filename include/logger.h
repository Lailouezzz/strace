/**
 * @file logger.h
 * @brief Syscall and signal logging utilities.
 */

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

/**
 * @brief Padding for log output alignment.
 */
# define LOGGER_PADDING (40)

/**
 * @brief Default log function for unknown types.
 */
# define LOG_FUNC_DEFAULT g_log_funcs[SYS_TYPE_DEFAULT]

/**
 * @brief Print to stderr.
 */
# define LOG_FILE stderr
# define LOG_PRINT(...) fprintf(LOG_FILE, __VA_ARGS__)

// ---
// Typedefs
// ---

/**
 * @typedef log_func_t
 * @brief Function pointer type for syscall argument logging.
 * @param value The argument value to log.
 * @param sci The syscall information context.
 * @return Number of characters written.
 */
typedef int	(*log_func_t)(uint64_t value, const syscall_info_t *sci, syscall_type_t sys_type);

/**
 * @typedef log_custom_t
 * @brief Function pointer type for custom syscall logging.
 * @param sci The syscall information context.
 * @return Number of characters written.
 */
typedef int	(*log_custom_t)(const syscall_info_t *sci);

// ---
// Global variable
// ---

/**
 * @brief Array of log functions indexed by syscall argument type.
 */
extern const log_func_t	g_log_funcs[SYS_TYPE__COUNT];

/**
 * @brief Array of custom log functions indexed by syscall definition.
 *        First element is for entry (in), second for exit (out).
 */
extern const log_custom_t	g_log_custom[ELEM_COUNT(g_syscall_defs)][2];

// ---
// Function declarations
// ---

/**
 * @brief Enable or disable event logging.
 * @param should_log_event true to enable, false to disable.
 */
void	logger_should_log_event(
			bool should_log_event
			);

/**
 * @brief Enable or disable the logger entirely.
 * @param disabled true to disable, false to enable.
 */
void	logger_disabled(
			bool disabled
			);

/**
 * @brief Log syscall event before execution.
 * @param sci The syscall information.
 * @return Number of characters written to stderr.
 */
int	logger_log_syscall_in(
		const syscall_info_t *sci
		);

/**
 * @brief Log syscall event after execution.
 * @param sci The syscall information.
 * @param cur_write Current number of characters already written.
 * @return Number of characters written to stderr.
 */
int	logger_log_syscall_out(
		const syscall_info_t *sci,
		int cur_write
		);

/**
 * @brief Log a signal event.
 * @param pid Process ID receiving the signal.
 * @param siginfo Signal information.
 * @return Number of characters written.
 */
int	logger_log_signal(
		int pid,
		const siginfo_t *siginfo
		);

/**
 * @brief Log syscall arguments.
 * @param sci The syscall information.
 * @param args Array of syscall arguments.
 * @param syscall_in true if logging before syscall, false after.
 * @return Number of characters written.
 */
int	logger_log_args(
		const syscall_info_t *sci,
		const uint64_t args[MAX_SYSCALL_ARG_COUNT],
		bool syscall_in
		);

/**
 * @brief Log syscall return value.
 * @param sci The syscall information.
 * @return Number of characters written.
 */
int	logger_log_return(
		const syscall_info_t *sci
		);

/**
 * @brief Log a formatted event message.
 * @param fmt printf-style format string.
 * @param ... Format arguments.
 * @return Number of characters written.
 */
int	logger_log_event(
		const char *fmt, ...
		);

/**
 * @brief Log a formatted message.
 * @param fmt printf-style format string.
 * @param ... Format arguments.
 * @return Number of characters written.
 */
int	logger_log(
		const char *fmt, ...
		);

#endif
