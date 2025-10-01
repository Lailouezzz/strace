#ifndef  ARCH_X86_64_PERSONALITY_H
# define ARCH_X86_64_PERSONALITY_H

// ---
// Includes
// ---

# include <stdint.h>
# include <sys/types.h>
# include "syscall.h"

// ---
// Defines
// ---

// ---
// Typedefs
// ---

/**
 * @typedef arch_pers_e
 * @brief Define architectures personalities
 *
 */
typedef enum arch_pers_e {
	PERS_x86_64,
	PERS_i386,
	PERS__COUNT,
}	arch_pers_t;

// ---
// Function declartions
// ---

int	pers_get_sci(
		pid_t pid,
		syscall_info_t *sci
		);

const char	*pers_get_name(
				arch_pers_t pers
				);

#endif
