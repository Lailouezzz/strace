/**
 * @file log_funcs.h
 * @brief Syscall argument type logging functions.
 */

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

/**
 * @brief Log function table entry macro.
 * @param type Syscall type suffix.
 */
# define LOG_FUNC_entry(type) [SYS_TYPE_ ## type] = log_func_ ## type,

/**
 * @brief Log function declaration macro.
 * @param type Syscall type suffix.
 */
# define LOG_FUNC_def(type) int log_func_ ## type(uint64_t value, const syscall_info_t *sci, syscall_type_t sys_type);

/**
 * @brief Log function implementation macro.
 * @param type Syscall type suffix.
 */
# define LOG_FUNC_impl(type) int log_func_ ## type(uint64_t value, const syscall_info_t *sci, syscall_type_t sys_type)

/**
 * @brief Print to stderr.
 */
# define LOG_FILE stderr
# define LOG_PRINT(...) fprintf(LOG_FILE, __VA_ARGS__)

// ---
// Function declarations
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
