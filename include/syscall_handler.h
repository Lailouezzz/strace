#ifndef  SYSCALL_HANDLER_H
# define SYSCALL_HANDLER_H

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

int	syscall_handle_in(
		pid_t pid
		);

int	syscall_handle_out(
		pid_t pid
		);

#endif
