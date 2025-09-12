/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strace.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:21:24 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 15:59:20 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ---
// Includes
// ---

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <errno.h>
#include <getopt.h>
#include "runner.h"
#include "tracer.h"
#include "utils.h"

#include "strace.h"

// ---
// Extern variables
// ---

strace_ctx_t	g_ctx = { 0 };

// ---
// Local variables
// ---

/**
 * @brief Command line arguments definition
 */
static struct option long_opt[] = {
	{"summary-only", no_argument, 0, 'c'},
	{"summary", no_argument, 0, 'C'},
	{"help", no_argument, 0, 'h'},
	{"verbose", no_argument, 0, 'v'},
	{ 0, 0, 0, 0 },
};

// ---
// Static function declarations
// ---

/**
 * @brief Parse flags into the global context
 *
 * @param argc main argc
 * @param argv main argv
 */
static void	_strace_init_parse_args(
				int argc,
				char **argv
				);

/**
 * @brief Print the usage
 */
static void _strace_usage(void);

// ---
// Extern function definitions
// ---

int	strace_init(
			int argc,
			char **argv,
			char **envp
			) {
	g_ctx.pn = *argv;
	g_ctx.print_syscalls = true;
	g_ctx.envp = envp;
	g_ctx.cpid = -1;
	_strace_init_parse_args(argc, argv);
	return (0);
}

void	strace_run(void) {
	g_ctx.cpid = runner_spawn_child(g_ctx.cargv, g_ctx.envp);
	if (g_ctx.cpid < 0)
		strace_terminate(EXIT_FAILURE);
	verbose("Child pid: %d\n", g_ctx.cpid);
	if (tracer_attach(g_ctx.cpid) == -1)
		strace_terminate(EXIT_FAILURE);
	verbose("Pid: %d attached\nStarting tracer loop\n", g_ctx.cpid);
	if (tracer_loop() == -1)
		strace_terminate(EXIT_FAILURE);
}

void	strace_cleanup(void) {
	if (g_ctx.cpid != -1 && kill(g_ctx.cpid, SIGKILL) == -1 && errno != ESRCH)
		perror_msg("kill(%d, SIGKILL)", g_ctx.cpid);
}

noreturn void	strace_terminate(
					int status_code
					) {
	verbose("strace terminate code: %d\n", status_code);
	strace_cleanup();
	exit(status_code);
}

// ---
// Static function definitions
// ---


static void	_strace_init_parse_args(
				int argc,
				char **argv
				) {
	int	opt;
	bool summary_only_flag = false;
	bool summary_flag = false;

	while ((opt = getopt_long(argc, argv, "cChv", long_opt, NULL)) != -1) {
		switch (opt) {
			case 'c':
				g_ctx.print_syscalls = false;
				g_ctx.print_summary = true;
				summary_only_flag = true;
				break;
			case 'C':
				g_ctx.print_summary = true;
				g_ctx.print_syscalls = true;
				summary_flag = true;
				break;
			case 'h':
				_strace_usage();
				strace_terminate(EXIT_SUCCESS);
				break;
			case 'v':
				g_ctx.verbose = true;
				break;
			default:
				fprintf(stderr, "Try '%s -h' for more information.\n", g_ctx.pn);
				strace_terminate(EXIT_FAILURE);
				break;
		}
	}

	if (summary_flag && summary_only_flag) {
		error_msg("-c/--summary-only and -C/--summary are mutually exclusive");
		strace_terminate(EXIT_FAILURE);
	}

	g_ctx.cargc = argc - optind;
	g_ctx.cargv = argv + optind;
	if (g_ctx.cargc == 0) {
		error_msg("must have PROG [ARGS]");
		fprintf(stderr, "Try '%s -h' for more information.\n", g_ctx.pn);
		strace_terminate(EXIT_FAILURE);
	}
}

static void _strace_usage(void) {
	printf("Usage: %s [-Chv] PROG [ARGS]\n\
   or: %s [-chv] PROG [ARGS]\n\
\n\
Statistics:\n\
  -c, --summary-only\n\
                 count time, calls and errors for each syscall and report\n\
                 summary\n\
  -C, --summary  like -c, but also print the regular output\n\
  -h, --help     print this message\n\
  -v, --verbose  print debug message\n", g_ctx.pn, g_ctx.pn);
}
