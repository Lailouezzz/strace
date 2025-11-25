// ---
// Includes
// ---

#include "logger.h"
#include "log_custom.h"

// ---
// Global variable
// ---

/**
 * @brief Custom log functions for specific syscalls.
 *        Index [syscall_idx][0] for entry, [syscall_idx][1] for exit.
 */
const log_custom_t	g_log_custom[ELEM_COUNT(g_syscall_defs)][2] = {
	LOG_CUSTOM_entry(openat)
	LOG_CUSTOM_entry(open)
};
