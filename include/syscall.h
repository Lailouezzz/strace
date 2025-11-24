/**
 * @file syscall.h
 * @brief Syscall information structures.
 */

#ifndef  SYSCALL_H
# define SYSCALL_H

// ---
// Includes
// ---

# include <stdint.h>
# include <stdbool.h>
# include <sys/types.h>
# include "syscall_defs.h"

// ---
// Defines
// ---

// ---
// Typedefs
// ---

/**
 * @typedef syscall_info_t
 * @brief Syscall event information.
 */
typedef struct syscall_info_s {
	/**
	 * @brief Syscall definition.
	 */
	const syscall_def_t	*scd;

	/**
	 * @brief Syscall arguments (input only).
	 */
	uint64_t		args[MAX_SYSCALL_ARG_COUNT];

	/**
	 * @brief Syscall return value (output only).
	 */
	uint64_t		ret;

	/**
	 * @brief Process ID.
	 */
	pid_t			pid;

	/**
	 * @brief Process personality.
	 */
	int				pers;

	/**
	 * @brief Error number if syscall failed.
	 */
	int				errnr;
}	syscall_info_t;

// ---
// Function declarations
// ---

#endif
