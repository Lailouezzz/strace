/**
 * @file regs.h
 * @brief x86 register structures for both 32-bit and 64-bit modes.
 */

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
 * @typedef i386_user_regs_t
 * @brief i386 user register structure.
 */
typedef struct i386_user_regs_s {
	uint32_t ebx;      /**< EBX register. */
	uint32_t ecx;      /**< ECX register. */
	uint32_t edx;      /**< EDX register. */
	uint32_t esi;      /**< ESI register. */
	uint32_t edi;      /**< EDI register. */
	uint32_t ebp;      /**< EBP register. */
	uint32_t eax;      /**< EAX register. */
	uint32_t xds;      /**< DS segment register. */
	uint32_t xes;      /**< ES segment register. */
	uint32_t xfs;      /**< FS segment register. */
	uint32_t xgs;      /**< GS segment register. */
	uint32_t orig_eax; /**< Original EAX (syscall number). */
	uint32_t eip;      /**< Instruction pointer. */
	uint32_t xcs;      /**< CS segment register. */
	uint32_t eflags;   /**< CPU flags. */
	uint32_t esp;      /**< Stack pointer. */
	uint32_t xss;      /**< SS segment register. */
}	i386_user_regs_t;

/**
 * @typedef x86_regs_t
 * @brief Unified x86 register union.
 */
typedef union x86_regs_u {
	struct user_regs_struct		x86_64_r; /**< x86_64 registers. */
	struct i386_user_regs_s		i386_r;   /**< i386 registers. */
}	x86_regs_t;

/**
 * @typedef user_regs_t
 * @brief Platform-specific user registers.
 */
typedef x86_regs_t	user_regs_t;

// ---
// Function declarations
// ---

#endif
