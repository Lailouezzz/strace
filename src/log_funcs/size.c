// ---
// Includes
// ---

#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(SIZE) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("%zu", (size_t)value));
	ret = tmp;
	return (ret);
}
