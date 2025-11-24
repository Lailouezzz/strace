/**
 * @file tracer.h
 * @brief Process tracing and syscall interception.
 */

#ifndef  TRACER_H
# define TRACER_H

// ---
// Includes
// ---

#include <stdbool.h>
#include <sys/types.h>

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
 * @brief Attach to a process for tracing.
 * @param pid Target process ID.
 * @param wait_sigstop Wait for SIGSTOP before continuing.
 * @return 0 on success, -1 on error.
 */
int	tracer_attach(
		pid_t pid,
		bool wait_sigstop
		);

/**
 * @brief Main tracer loop intercepting syscalls.
 * @return 0 on success, -1 on error.
 */
int	tracer_loop(void);

#endif
