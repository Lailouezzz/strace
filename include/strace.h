/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strace.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:26:21 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 15:43:17 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  STRACE_H
# define STRACE_H

// ---
// Includes
// ---

#include <stdbool.h>
#include <stdnoreturn.h>
#include <sys/types.h>

// ---
// Typedefs
// ---

/**
 * @typedef strace_ctx_s
 * @brief Global context
 *
 */
typedef struct strace_ctx_s {
	/**
	 * @brief The program name (ex: "./strace")
	 */
	const char	*pn;

	/**
	 * @brief Child argc
	 */
	int			cargc;

	/**
	 * @brief Child argv
	 */
	char		**cargv;

	/**
	 * @brief main envp
	 */
	char		**envp;

	/**
	 * @brief Enable end summary
	 */
	bool		print_summary;

	/**
	 * @brief Enable syscalls print
	 */
	bool		print_syscalls;

	/**
	 * @brief -v flag
	 */
	bool		verbose;

	/**
	 * @brief Target PID
	 */
	pid_t		pid;

	/**
	 * @brief Child last waitpid(?, &cstatus)
	 */
	int			cstatus;

	/**
	 * @brief The strace process is signaled ?
	 */
	bool		signaled;
}	strace_ctx_t;

// ---
// Global variables
// ---

/**
 * @brief Global context
 */
extern strace_ctx_t	g_ctx;

// ---
// Function declarations
// ---

/**
 * @brief Initialization of the global context
 *
 * @param argc main argc
 * @param argv main argv
 * @param envp main envp
 * @return -1 if error 0 otherwise
 */
int	strace_init(
		int argc,
		char **argv,
		char **envp
		);

/**
 * @brief Run the child and trace it
 */
void	strace_run(void);

/**
 * @brief Cleanup global context etc.
 */
void	strace_cleanup(void);

/**
 * @brief Terminate the process with status code
 *
 * @param status_code 
 */
noreturn void	strace_terminate(
					int status_code
					);

#endif
