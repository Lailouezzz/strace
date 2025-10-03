
// ---
// Includes
// ---

#include "logger.h"
#include "log_funcs.h"

// ---
// Global var
// ---

const log_func_t	g_log_funcs[SYS_TYPE__COUNT] = {
LOG_FUNC_entry(INT)
LOG_FUNC_entry(PTR)
};
