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

/**
 * @file runner.h
 * @brief Child process spawning and attachment.
 */

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
// Function declarations
// ---

/**
 * @brief Spawn a child process and attach the tracer.
 * @param cargv Child argument vector.
 * @param cenvp Child environment pointer.
 * @return Spawned child PID, or -1 on error.
 */
pid_t	runner_spawn_child(
			char **cargv,
			char **cenvp
			);

#endif
