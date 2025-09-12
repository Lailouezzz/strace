#include <locale.h>
#include <stdlib.h>
#include "strace.h"

int main(int argc, char **argv, char **envp) {
	setlocale(LC_ALL, "");
	if (strace_init(argc, argv, envp) != 0)
		strace_terminate(EXIT_FAILURE);
	strace_run();
	if (WIFEXITED(g_ctx.cstatus))
		strace_terminate(WEXITSTATUS(g_ctx.cstatus));
	else if (WIFSIGNALED(g_ctx.cstatus))
		strace_terminate(WTERMSIG(g_ctx.cstatus) + 126);
	else
		strace_terminate(EXIT_FAILURE);
}
