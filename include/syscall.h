#ifndef  SYSCALL_H
# define SYSCALL_H

// ---
// Includes
// ---

# include <stdint.h>
# include <sys/types.h>

// ---
// Defines
// ---

# define MAX_SYSCALL_ARG_COUNT (6)

// ---
// Typedefs
// ---

typedef struct syscall_def_s {
	const char	*name;
}	syscall_def_t;

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

	int				pers;
}	syscall_info_t;

// ---
// Function declartions
// ---

#endif
