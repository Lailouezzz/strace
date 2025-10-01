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
# define ELEM_COUNT(container) (sizeof(container) / sizeof(*container))

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
