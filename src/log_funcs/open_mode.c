// ---
// Includes
// ---

#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(OPEN_MODE) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("0%02lo", value));
	ret = tmp;
	return (ret);
}
