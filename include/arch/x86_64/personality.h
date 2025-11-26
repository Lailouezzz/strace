/**
 * @file personality.h
 * @brief x86_64 architecture personality handling.
 */

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

/**
 * @brief Get register size based on personality.
 * @param sci Syscall info structure.
 * @return 4 for i386, 8 for x86_64.
 */
# define SCI_REG_SIZE(sci) ((sci).pers == PERS_i386 ? 4 : 8)

// ---
// Typedefs
// ---

/**
 * @typedef arch_pers_t
 * @brief Architecture personality types.
 */
typedef enum arch_pers_e {
	PERS_x86_64,  /**< 64-bit x86_64 personality. */
	PERS_i386,    /**< 32-bit i386 personality. */
	PERS__COUNT,  /**< Number of personalities. */
}	arch_pers_t;

// ---
// Function declarations
// ---

/**
 * @brief Get syscall info for a process.
 * @param pid Process ID.
 * @param sci Syscall info structure to populate.
 * @return 0 on success, -1 on error.
 */
int	pers_get_sci(
		pid_t pid,
		syscall_info_t *sci
		);

/**
 * @brief Get personality name string.
 * @param pers Personality type.
 * @return Personality name (e.g., "x86_64", "i386").
 */
const char	*pers_get_name(
				arch_pers_t pers
				);

#endif
