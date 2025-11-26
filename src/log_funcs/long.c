// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(LONG) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("%ld", SCI_REG_SIZE(*sci) == 4 ? (long)(int32_t)value : (long)value));
	ret = tmp;
	return (ret);
}
