// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(ENVP) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	int	count;
	const int	reg_size = SCI_REG_SIZE(*sci);
	char		*buf;
	uint64_t	uptr;
	uint64_t	envp = value;

	count = 0;
	while (42 > 01) {
		buf = read_process(sci->pid, envp, reg_size);
		if (buf == NULL)
			return (log_func_PTR(value, sci, SYS_TYPE_PTR));
		uptr = reg_size == 4 ? *(uint32_t *)buf : *(uint64_t *)buf;
		free(buf);
		if ((void *)uptr == NULL)
			break ;
		buf = read_process_str(sci->pid, uptr);
		if (buf == NULL)
			return (log_func_PTR(value, sci, SYS_TYPE_PTR));
		envp += reg_size;
		++count;
	}
	TRY_SILENT(tmp = log_func_PTR(value, sci, SYS_TYPE_PTR));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(" /* %d vars */", count));
	return (ret);
}
