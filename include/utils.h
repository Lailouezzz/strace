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

/**
 * @file utils.h
 * @brief Utility macros and helper functions.
 */

#ifndef  UTILS_H
# define UTILS_H

// ---
// Includes
// ---

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <stdbool.h>

// ---
// Defines
// ---

/**
 * @brief Generic dynamic list structure.
 * @param T Element type.
 */
# define list(T) struct { T *data; size_t cap; size_t len; }

/**
 * @brief Typedef helper for list types.
 * @param T Element type.
 * @param name Type name prefix (creates name_t).
 */
# define TYPEDEF_LIST(T, name) typedef list(T) name##_t

/**
 * @brief Initialize an empty list.
 */
# define list_new() { .data = NULL, .cap = 0, .len = 0 }

/**
 * @brief Free a list and reset its state.
 * @param l Pointer to the list.
 */
# define list_free(l) do { \
	if ((l)->data != NULL) free((l)->data); \
	(l)->data = NULL; \
	(l)->cap = 0; \
	(l)->len = 0; \
} while (0)

/**
 * @brief Reserve capacity for list elements.
 * @param l Pointer to the list.
 * @param capacity New capacity.
 * @return true on success, false on allocation failure.
 */
# define list_reserve(l, capacity) ({ \
	void *__tmp = realloc((l)->data, (capacity) * sizeof(*(l)->data)); \
	if (__tmp != NULL) { \
		(l)->data = __tmp; \
		(l)->cap = (capacity); \
	} \
	(__tmp != NULL); \
	})

/**
 * @brief Push an element to the list.
 * @param l Pointer to the list.
 * @param v Value to push.
 * @return true on success, false on allocation failure.
 */
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

/**
 * @brief Iterate over list elements.
 * @param l Pointer to the list.
 * @param it Iterator variable (pointer to element).
 */
# define list_foreach(l, it) \
	for (size_t _i = 0; _i < (l)->len && ((it) = &(l)->data[_i], 1); _i++)

/**
 * @brief Iterate over array elements.
 * @param array Static array.
 * @param it Iterator variable (pointer to element).
 */
# define array_foreach(array, it) \
	for (size_t _i = 0; _i < ELEM_COUNT(array) && ((it) = &(array)[_i], 1); _i++)

/**
 * @brief Execute call and return -1 on failure with perror.
 * @param call Expression to evaluate.
 */
# define TRY(call) if ((call) < 0) { return (perror_msg(#call), -1); }

/**
 * @brief Execute call and return -1 on failure silently.
 * @param call Expression to evaluate.
 */
# define TRY_SILENT(call) if ((call) < 0) { return (-1); }

/**
 * @brief Return the maximum of two values.
 */
# define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Return the minimum of two values.
 */
# define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief Return the absolute value.
 */
# define ABS(a) (((a) < 0) ? (-(a)) : (a))

/**
 * @brief Get element count of a static array.
 */
# define ELEM_COUNT(container) (sizeof(container) / sizeof(*container))

# define CASE_STR(val) case val: return (#val)

/**
 * @brief Mark a variable as unused.
 */
# define UNUSED(var) ((void)var);

/* Extra errno values from kernel */

# define ERRNO_MAX             511

/** @brief Restart syscall. */
# define ERESTARTSYS           512

/** @brief Restart if no interrupt. */
# define ERESTARTNOINTR        513

/** @brief Restart if no handler. */
# define ERESTARTNOHAND        514

/** @brief Restart with restart block. */
# define ERESTART_RESTARTBLOCK 516

// ---
// Typedefs
// ---

TYPEDEF_LIST(char, bytes);

// ---
// Function declarations
// ---

/**
 * @brief Print error message with program name.
 * @param fmt printf-style format string.
 * @param ... Format arguments.
 */
void	error_msg(const char *fmt, ...);

/**
 * @brief Print error message with program name and errno.
 * @param fmt printf-style format string.
 * @param ... Format arguments.
 */
void	perror_msg(const char *fmt, ...);

/**
 * @brief Print verbose message if verbose mode is enabled.
 * @param fmt printf-style format string.
 * @param ... Format arguments.
 */
void	verbose(const char *fmt, ...);

/**
 * @brief Convert errno to its name.
 * @param err The errno value.
 * @return Errno name string (e.g., "EINVAL", "EPERM").
 */
const char	*errno_name(int err);

/**
 * @brief Custom strerror including ERESTART* errors.
 * @param err The errno value.
 * @return Error description string.
 */
const char	*kstrerror(int err);

/**
 * @brief Convert signal number to its name.
 * @param signo The signal number.
 * @return Signal name string (e.g., "SIGINT", "SIGQUIT").
 */
const char	*signal_name(int signo);

/**
 * @brief Search for executable in PATH.
 * @param s Executable name to search.
 * @param path The PATH environment variable.
 * @return Absolute path if found, s if contains '/' or not found.
 *         Must be freed. NULL on malloc error.
 */
char	*search_exec(
			char *s,
			char *path
			);

/**
 * @brief Read memory from a traced process.
 * @param pid The process ID to read from.
 * @param addr The memory address in the target process.
 * @param size The number of bytes to read.
 * @return Allocated buffer with the data, or NULL on error. Must be freed.
 */
void	*read_process(
			pid_t pid,
			uint64_t addr,
			size_t size
			);

/**
 * @brief Read memory string from a traced process.
 * @param pid The process ID to read from.
 * @param addr The memory address in the target process.
 * @return Allocated buffer with the data, or NULL on error. Must be freed.
 */
char	*read_process_str(
			pid_t pid,
			uint64_t addr
			);

/**
 * @brief Print escaped string to file.
 * @param fp The file pointer to write to.
 * @param data The data to print.
 * @param len The length of the data.
 * @return The number of characters printed.
 */
int	fprint_escaped(
		FILE *fp,
		const char *data,
		size_t len
		);

#endif
