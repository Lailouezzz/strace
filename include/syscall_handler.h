/**
 * @file syscall_handler.h
 * @brief Syscall entry and exit handling.
 */

#ifndef  SYSCALL_HANDLER_H
# define SYSCALL_HANDLER_H

// ---
// Includes
// ---

#include <sys/types.h>
#include "statistic.h"
#include "syscall.h"

// ---
// Defines
// ---

// ---
// Typedefs
// ---

// ---
// Function declarations
// ---

/**
 * @brief Handle syscall entry.
 * @param pid Process ID.
 * @param sci Syscall information to populate.
 * @return 0 on success, -1 on error.
 */
int	syscall_handle_in(
		pid_t pid,
		syscall_info_t *sci
		);

/**
 * @brief Handle syscall exit.
 * @param pid Process ID.
 * @param sci Syscall information to update with return value.
 * @param time Syscall execution time in microseconds.
 * @return 0 on success, -1 on error.
 */
int	syscall_handle_out(
		pid_t pid,
		syscall_info_t *sci,
		long time
		);

#endif
