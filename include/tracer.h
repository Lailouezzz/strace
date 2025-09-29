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
// Function declartions
// ---

/**
 * @brief Attach to desired pid
 *
 * @param pid
 * @param wait_sigstop
 * @return -1 error 0 if attach success
 */
int	tracer_attach(
		pid_t pid,
		bool wait_sigstop
		);

/**
 * @brief Tracer loop on syscalls
 *
 * @return -1 error; 0 success
 */
int	tracer_loop(void);

#endif
