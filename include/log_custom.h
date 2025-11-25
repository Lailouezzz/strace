/**
 * @file log_custom.h
 * @brief Syscall custom logging functions.
 */

#ifndef  LOG_CUSTOM_H
# define LOG_CUSTOM_H

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
 * @param sr_sys Syscall sr_sys suffix.
 */
# define LOG_CUSTOM_entry(sr_sys) [SR_SYS_ ## sr_sys] = { log_custom_ ## sr_sys ##_in, log_custom_ ## sr_sys ##_out },

/**
 * @brief Log function declaration macro.
 * @param sr_sys Syscall sr_sys suffix.
 */
# define LOG_CUSTOM_def(sr_sys) int log_custom_ ## sr_sys ##_in(const syscall_info_t *sci); \
                                int log_custom_ ## sr_sys ##_out(const syscall_info_t *sci);

/**
 * @brief Log function implementation macro.
 * @param sr_sys Syscall sr_sys suffix.
 */
# define LOG_CUSTOM_impl(sr_sys, in_out) int log_custom_ ## sr_sys ##_ ## in_out(const syscall_info_t *sci)

// ---
// Function declarations
// ---

LOG_CUSTOM_def(openat)
LOG_CUSTOM_def(open)

#endif
