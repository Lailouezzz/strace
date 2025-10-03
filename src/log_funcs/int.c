// ---
// Includes
// ---

#include <stdio.h>
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(INT) {
	UNUSED(sci);
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = LOG_PRINT("%lu", value));
	ret = tmp;
	return (ret);
}
