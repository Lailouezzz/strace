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
LOG_FUNC_entry(SIZE)
LOG_FUNC_entry(SSIZE)
LOG_FUNC_entry(MMAP_PROT)
LOG_FUNC_entry(MMAP_FLAGS)
LOG_FUNC_entry(FD)
LOG_FUNC_entry(HEX)
LOG_FUNC_entry(STRING)
LOG_FUNC_entry(MEMSEG)
LOG_FUNC_entry(OPEN_FLAGS)
LOG_FUNC_entry(OPEN_MODE)
LOG_FUNC_entry(AT_FLAGS)
LOG_FUNC_entry(STAT_STRUCT)
LOG_FUNC_entry(OFF)
LOG_FUNC_entry(LONG)
LOG_FUNC_entry(ARCH_CODE)
LOG_FUNC_entry(ARGV)
LOG_FUNC_entry(ENVP)
LOG_FUNC_entry(ACCESS_MODE)
LOG_FUNC_entry(SIGNAL)
};
