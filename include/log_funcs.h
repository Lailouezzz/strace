#ifndef  LOG_FUNCS_H
# define LOG_FUNCS_H

// ---
// Includes
// ---

# include <stdio.h>
# include "logger.h"

// ---
// Defines
// ---

# define LOG_FUNC_entry(type) [SYS_TYPE_ ## type] = log_func_ ## type,
# define LOG_FUNC_def(type) int log_func_ ## type(uint64_t value, const syscall_info_t *sci);
# define LOG_FUNC_impl(type) int log_func_ ## type(uint64_t value, const syscall_info_t *sci)
# define LOG_PRINT(...) fprintf(stderr, __VA_ARGS__)

// ---
// Function declartions
// ---

LOG_FUNC_def(INT)
LOG_FUNC_def(PTR)
LOG_FUNC_def(SIGNED_INT)
LOG_FUNC_def(HEX)
LOG_FUNC_def(STRING)
LOG_FUNC_def(MEMSEG)
LOG_FUNC_def(OPEN_FLAGS)
LOG_FUNC_def(OPEN_MODE)

#endif
