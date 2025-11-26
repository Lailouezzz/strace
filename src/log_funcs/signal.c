// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(SIGNAL) {
	UNUSED(sci);
	UNUSED(sys_type);

	return (LOG_PRINT("%s", signal_name(value)));
}
