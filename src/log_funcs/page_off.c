// ---
// Includes
// ---

#include <unistd.h>
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(PAGE_OFF) {
	UNUSED(sci);
	UNUSED(sys_type);

	return (log_func_HEX(value * sysconf(_SC_PAGE_SIZE), sci, SYS_TYPE_HEX));
}
