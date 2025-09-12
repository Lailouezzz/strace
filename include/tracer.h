#ifndef  TRACER_H
# define TRACER_H

// ---
// Includes
// ---

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
 * @return -1 error 0 if attach success
 */
int	tracer_attach(
		pid_t pid
		);

/**
 * @brief Tracer loop on syscalls
 *
 * @return -1 error; 0 success
 */
int	tracer_loop(void);

#endif
