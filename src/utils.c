/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:07:54 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 16:20:39 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ---
// Includes
// ---

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "strace.h"

#include "utils.h"

// ---
// Static function declarations
// ---

/**
 * @brief Check if the absolute path s is a regular file
 *
 * @param s the absolute path
 * @return 1 if exist 0 otherwise
 */
static int	_search_exec_exist(
				const char *s
				);

// ---
// Extern function definitions
// ---

void	error_msg(const char *fmt, ...) {
	va_list	args;

	fprintf(stderr, "%s: ", g_ctx.pn);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

void	perror_msg(const char *fmt, ...) {
	va_list	args;

	fprintf(stderr, "%s: ", g_ctx.pn);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, ": %s\n", strerror(errno));
}

void	verbose(const char *fmt, ...) {
	va_list	args;

	if (!g_ctx.verbose)
		return ;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

char	*search_exec(
			char *s,
			char *envpath
			) {
	char	*spath;
	char	*envpath_copy;

	if (s == NULL)
		return (NULL);
	if (envpath == NULL || (envpath_copy = strdup(envpath)) == NULL)
		return (strdup(s));
	if (strchr(s, '/') != NULL)
		return (free(envpath_copy), strdup(s));
	for (char *path = strtok(envpath_copy, ":"); path != NULL; path = strtok(NULL, ":")) {
		spath = malloc((strlen(s) + strlen(path) + 2) * sizeof(char));
		strcpy(spath, path);
		strcat(spath, "/");
		strcat(spath, s);
		if (_search_exec_exist(spath))
			return (free(envpath_copy), spath);
		free(spath);
	}
	return (free(envpath_copy), strdup(s));
}

// ---
// Static function definitions
// ---

static int	_search_exec_exist(
				const char *s
				) {
	struct stat	st;

	if (stat(s, &st) == -1 || S_ISDIR(st.st_mode))
		return (0);
	if (access(s, X_OK) == -1)
		return (0);
	return (1);
}
