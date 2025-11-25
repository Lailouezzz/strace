// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(SSIZE) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("%zd", SCI_REG_SIZE(*sci) == 4 ? (ssize_t)(int32_t)value : (ssize_t)value));
	ret = tmp;
	return (ret);
}
