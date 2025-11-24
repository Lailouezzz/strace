// ---
// Includes
// ---

#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdnoreturn.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include "utils.h"

#include "runner.h"

// ---
// Static function declarations
// ---

/**
 * @brief Child entry point.
 * @param exec_path The executable path to run.
 * @param cargv The argument vector.
 * @param cenvp The environment vector.
 */
static noreturn void	_runner_child_entry(
							const char *exec_path,
							char **cargv,
							char **cenvp
							);

// ---
// Extern function definitions
// ---

pid_t	runner_spawn_child(
			char **cargv,
			char **cenvp
			) {
	pid_t	cpid;
	char	*exec_path;
	struct stat	st;

	exec_path = search_exec(*cargv, getenv("PATH"));
	if (exec_path == NULL)
		return (-1);
	if (stat(exec_path, &st) == -1) {
		error_msg("Can't stat '%s': %s", *cargv, strerror(errno));
		return (free(exec_path), -1);
	}
	if ((cpid = fork()) < 0) {
		perror_msg("fork()");
		return (free(exec_path), -1);
	} else if (cpid == 0)
		_runner_child_entry(exec_path, cargv, cenvp);
	free(exec_path);
	return (cpid);
}

// ---
// Static function definitions
// ---

static noreturn void	_runner_child_entry(
							const char *exec_path,
							char **cargv,
							char **cenvp
							) {
	raise(SIGSTOP);
	execve(exec_path, cargv, cenvp);
	perror_msg("exec");
	_exit(EXIT_FAILURE);
}
