// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(PTR) {
	UNUSED(sci);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("0x%0*lx", SCI_REG_SIZE(*sci) * 2, value));
	ret = tmp;
	return (ret);
}
