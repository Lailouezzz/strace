/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:12:58 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 15:59:09 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  RUNNER_H
# define RUNNER_H

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

/**
 * @brief Run and attach child to the tracer
 *
 * @param cargv child argv
 * @param cenvp child envp
 * @return The spawned child pid or -1 if error
 */
pid_t	runner_spawn_child(
			char **cargv,
			char **cenvp
			);

#endif
