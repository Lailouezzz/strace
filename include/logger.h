#ifndef  LOGGER_H
# define LOGGER_H

// ---
// Includes
// ---

# include <stdbool.h>
# include "syscall.h"

// ---
// Defines
// ---

# define LOGGER_PADDING (40)

// ---
// Typedefs
// ---



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

void	logger_disabled(
			bool disabled
			);

int	logger_log_syscall_in(
			const syscall_info_t *sci
			);

int	logger_log_syscall_out(
			const syscall_info_t *sci,
			int cur_write
			);

int	logger_log(
			const char *fmt, ...
			);

#endif
