// ---
// Includes
// ---

#include <sys/uio.h>
#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

/**
 * @brief Get the size of the memory segment to log.
 * @param sci The syscall information context.
 * @param sys_type The syscall type with encoded size argument.
 * @return The size of the memory segment in bytes.
 */
static uint64_t	_get_size(
					const syscall_info_t *sci,
					int sys_type
					);

LOG_FUNC_impl(MEMSEG) {
	int			ret = 0;
	int			tmp;
	uint64_t	size;
	char		*data;

	size = _get_size(sci, sys_type);
	data = read_process(sci->pid, value, size);
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
	if (data != NULL) {
		TRY_SILENT(tmp = fprint_escaped(LOG_FILE, data, size));
		ret += tmp;
	}
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
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
