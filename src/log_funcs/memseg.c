// ---
// Includes
// ---

#include <sys/uio.h>
#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

/**
 * @brief 
 *
 * @param sci 
 * @param sys_type 
 * @return 
 */
static uint64_t	_get_size(
					const syscall_info_t *sci,
					int sys_type
					);

LOG_FUNC_impl(MEMSEG) {
	UNUSED(sci);
	UNUSED(sys_type);
	int			ret = 0;
	int			tmp;
	uint64_t	size;
	char		*data;

	size = _get_size(sci, sys_type);
	data = read_process(sci->pid, value, size);
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret = tmp;
	if (data != NULL) {
		TRY_SILENT(tmp = fprint_escaped(LOG_FILE, data, size));
		ret = tmp;
	}
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret = tmp;
	free(data);
	return (ret);
}

static uint64_t	_get_size(
					const syscall_info_t *sci,
					int sys_type
					) {
	if (GET_SYS_TYPE_ARG(sys_type) == 0)
		return (sci->ret);
	return (sci->args[GET_SYS_TYPE_ARG(sys_type) - 1]);
}
