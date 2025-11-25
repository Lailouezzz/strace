// ---
// Includes
// ---

#include <elf.h>
#include <sys/uio.h>
#include <sys/ptrace.h>
#include "regs.h"
#include "utils.h"
#include "syscall_defs.h"

#include "personality.h"

// ---
// Local variable
// ---

static const char	*_pers_names[] = {
[PERS_x86_64] = "64 bit",
[PERS_i386] = "32 bit",
};

static const int	_pers_sce_x86_64[] = {
#include "personality_sce_x86_64.h"
};

static const int	_pers_sce_i386[] = {
#include "personality_sce_i386.h"
};

// ---
// Static function declarations
// ---

/**
 * @brief Get the return value from user registers.
 * @param user_regs The user registers structure.
 * @param pers The architecture personality.
 * @return The syscall return value.
 */
static uint64_t	_pers_get_return(
					const user_regs_t *user_regs,
					arch_pers_t pers
					);

/**
 * @brief Get the syscall number from user registers.
 * @param user_regs The user registers structure.
 * @param pers The architecture personality.
 * @return The syscall number.
 */
static uint64_t	_pers_get_sysnr(
					const user_regs_t *user_regs,
					arch_pers_t pers
					);

/**
 * @brief Extract syscall arguments from user registers.
 * @param user_regs The user registers structure.
 * @param args Output array for the arguments.
 * @param pers The architecture personality.
 */
static void		_pers_get_args(
					const user_regs_t *user_regs,
					uint64_t *args,
					arch_pers_t pers
					);

// ---
// Extern function definitions
// ---

int	pers_get_sci(
		pid_t pid,
		syscall_info_t *sci
		) {
	struct iovec	iov;
	user_regs_t		user_regs;
	uint64_t		sysnr;
	int				scd_idx;
	int64_t			ret;

	iov.iov_base = &user_regs;
	iov.iov_len = sizeof(user_regs);
	if (ptrace(PTRACE_GETREGSET, pid, (void *)NT_PRSTATUS, &iov) < 0)
		return (perror_msg("ptrace(PTRACE_GETREGSET, %d)", pid), -1);
	sci->pers = (iov.iov_len == sizeof(i386_user_regs_t) ? PERS_i386 : PERS_x86_64);
	sci->pid = pid;
	sci->ret = _pers_get_return(&user_regs, sci->pers);
	_pers_get_args(&user_regs, sci->args, sci->pers);
	sysnr = _pers_get_sysnr(&user_regs, sci->pers);
	if (sci->pers == PERS_i386) {
		if (sysnr >= ELEM_COUNT(_pers_sce_i386))
			scd_idx = 0;
		else
			scd_idx = _pers_sce_i386[sysnr];
	} else {
		if (sysnr >= ELEM_COUNT(_pers_sce_x86_64))
			scd_idx = 0;
		else
			scd_idx = _pers_sce_x86_64[sysnr];
	}
	sci->scd = &g_syscall_defs[scd_idx];
	ret = (sci->pers == PERS_i386 ? (int32_t)sci->ret : (int64_t)sci->ret);
	if (ret < 0 && ret > -0x1000)
		sci->errnr = -ret;
	else
		sci->errnr = 0;
	return (0);
}

const char	*pers_get_name(
				arch_pers_t pers
				) {
	return (_pers_names[pers]);
}

// ---
// Static function definitions
// ---

static uint64_t	_pers_get_return(
					const user_regs_t *user_regs,
					arch_pers_t pers
					) {
	if (pers == PERS_x86_64) {
		return (user_regs->x86_64_r.rax);
	} else {
		return (user_regs->i386_r.eax);
	}
}

static uint64_t	_pers_get_sysnr(
					const user_regs_t *user_regs,
					arch_pers_t pers
					) {
	if (pers == PERS_x86_64) {
		return (user_regs->x86_64_r.orig_rax);
	} else {
		return (user_regs->i386_r.orig_eax);
	}
}

static void		_pers_get_args(
					const user_regs_t *user_regs,
					uint64_t *args,
					arch_pers_t pers
					) {
	if (pers == PERS_x86_64) {
		args[0] = user_regs->x86_64_r.rdi;
		args[1] = user_regs->x86_64_r.rsi;
		args[2] = user_regs->x86_64_r.rdx;
		args[3] = user_regs->x86_64_r.r10;
		args[4] = user_regs->x86_64_r.r8;
		args[5] = user_regs->x86_64_r.r9;
	} else {
		args[0] = user_regs->i386_r.ebx;
		args[1] = user_regs->i386_r.ecx;
		args[2] = user_regs->i386_r.edx;
		args[3] = user_regs->i386_r.esi;
		args[4] = user_regs->i386_r.edi;
		args[5] = user_regs->i386_r.ebp;
	}
}
