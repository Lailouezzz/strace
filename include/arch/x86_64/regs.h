#ifndef  ARCH_X86_64_REGS_H
# define ARCH_X86_64_REGS_H

// ---
// Includes
// ---

# include <stdint.h>
# include <sys/user.h>

// ---
// Defines
// ---

// ---
// Typedefs
// ---

/**
 * @typedef i386_user_regs_s
 * @brief Define the i386 user regs
 *
 */
typedef struct i386_user_regs_s {
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;
	uint32_t eax;
	uint32_t xds;
	uint32_t xes;
	uint32_t xfs;
	uint32_t xgs;
	uint32_t orig_eax;
	uint32_t eip;
	uint32_t xcs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t xss;
}	i386_user_regs_t;

/**
 * @typedef x86_regs_u
 * @brief Unified x86 regs
 *
 */
typedef union x86_regs_u {
	struct user_regs_struct		x86_64_r;
	struct i386_user_regs_s		i386_r;
}	x86_regs_t;

typedef x86_regs_t	user_regs_t;

// ---
// Function declartions
// ---

#endif
