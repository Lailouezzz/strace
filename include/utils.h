/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:01:28 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 16:18:45 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  UTILS_H
# define UTILS_H

// ---
// Includes
// ---

# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

// ---
// Defines
// ---

# define list(T) struct { T *data; size_t cap; size_t len; }
# define TYPEDEF_LIST(T, name) typedef list(T) name##_t

# define list_new() { .data = NULL, .cap = 0, .len = 0 }
# define list_free(l) do { \
	if ((l)->data != NULL) free((l)->data); \
	(l)->data = NULL; \
	(l)->cap = 0; \
	(l)->len = 0; \
} while (0)

# define list_reserve(l, capacity) ({ \
	void *__tmp = realloc((l)->data, (capacity) * sizeof(*(l)->data)); \
	if (__tmp != NULL) { \
		(l)->data = __tmp; \
		(l)->cap = (capacity); \
	} \
	(__tmp != NULL); \
	})

# define list_push(l, v) ({ \
	bool _success = true; \
	if ((l)->len >= (l)->cap) { \
		_success = list_reserve(l, (l)->cap != 0 ? (l)->cap << 1 : 8); \
	} \
	if (_success) { \
		(l)->data[(l)->len++] = (v); \
	} \
	_success; \
	})

# define list_foreach(l, it) \
	for (size_t _i = 0; _i < (l)->len && ((it) = &(l)->data[_i], 1); _i++)

# define array_foreach(array, it) \
	for (size_t _i = 0; _i < ELEM_COUNT(array) && ((it) = &(array)[_i], 1); _i++)

# define TRY(call) if ((call) < 0) { return (perror_msg(#call), -1); }
# define TRY_SILENT(call) if ((call) < 0) { return (-1); }
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define ABS(a) (((a) < 0) ? (-(a)) : (a))
# define ELEM_COUNT(container) (sizeof(container) / sizeof(*container))
# define UNUSED(var) ((void)var);

/* extra errno */
# define ERESTARTSYS           512
# define ERESTARTNOINTR        513
# define ERESTARTNOHAND        514
# define ERESTART_RESTARTBLOCK 516

// ---
// Function declartions
// ---

/**
 * @brief Print the program name followed by the message on stderr
 *
 * @param fmt printf format
 */
void	error_msg(const char *fmt, ...);

/**
 * @brief Print the program name followed by the message and errno on stderr
 *
 * @param fmt printf format
 */
void	perror_msg(const char *fmt, ...);

/**
 * @brief Print verbose messages if g_ctx.verbose
 *
 * @param fmt 
 */
void	verbose(const char *fmt, ...);

/**
 * @brief Int to errno name traduction
 *
 * @param err The errno
 * @return "EINVAL" "EPERM" for example
 */
const char	*errno_name(int err);

/**
 * @brief Custom strerror, including ERESTART* errors
 *
 * @param err errno
 * @return strerror() like
 */
const char	*kstrerror(int err);

/**
 * @brief Convert signo to the signo string
 *
 * @param signo 
 * @return "SIGINT" "SIGQUIT" for example
 */
const char	*signal_name(int signo);

/**
 * @brief Search path to executable
 *
 * @param s Executable to search
 * @param path The PATH environment variable
 * @return if s contain '/' return s otherwise the executable absolute path
 *            if not find return s. Must be free. NULL if malloc error
 */
char	*search_exec(
			char *s,
			char *path
			);

#endif
