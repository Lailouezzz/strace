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



// ---
// Defines
// ---

# define TRY(call) if ((call) < 0) { return (perror_msg(#call), -1); }
# define TRY_SILENT(call) if ((call) < 0) { return (-1); }
# define MAX(a, b) ((a) > (b) ? (a) : (b))
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
