// ---
// Includes
// ---

#include <fcntl.h>
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(FD) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;

	if ((int)value == AT_FDCWD) {
		TRY_SILENT(tmp = LOG_PRINT("AT_FDCWD"));
		ret = tmp;
	} else {
		TRY_SILENT(tmp = LOG_PRINT("%d", (int)value));
		ret = tmp;
	}
	return (ret);
}
