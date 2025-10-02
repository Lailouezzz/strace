#ifndef  SYSCALL_H
# define SYSCALL_H

// ---
// Includes
// ---

# include <stdint.h>
# include <stdbool.h>
# include <sys/types.h>
# include"syscall_defs.h"

// ---
// Defines
// ---

# define MAX_SYSCALL_ARG_COUNT (6)

// ---
// Typedefs
// ---

/**
 * @typedef syscall_info_s
 * @brief Describe all information for a syscall event
 *
 */
typedef struct syscall_info_s {
	/**
	 * @brief Concerned syscall
	 */
	const syscall_def_t	*scd;

	/**
	 * @brief Syscall args (in only)
	 */
	uint64_t		args[MAX_SYSCALL_ARG_COUNT];

	/**
	 * @brief Return value of syscall (out only)
	 */
	uint64_t		ret;

	/**
	 * @brief Process PID
	 */
	pid_t			pid;

	/**
	 * @brief Personality
	 */
	int				pers;

	int				errnr;
}	syscall_info_t;

// ---
// Function declartions
// ---

#endif
