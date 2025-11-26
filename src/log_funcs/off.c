// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(OFF) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("%jd", SCI_REG_SIZE(*sci) == 4 ? (intmax_t)(int32_t)value : (intmax_t)value));
	ret = tmp;
	return (ret);
}
