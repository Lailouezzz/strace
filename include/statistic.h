/**
 * @file statistic.h
 * @brief Syscall statistics collection and reporting.
 */

#ifndef  STATISTIC_H
# define STATISTIC_H

// ---
// Includes
// ---

# include <stdbool.h>
# include "syscall.h"

// ---
// Defines
// ---

// ---
// Typedefs
// ---

/**
 * @typedef stat_entry_t
 * @brief Single syscall statistic entry.
 */
typedef struct	stat_entry_s {
	/**
	 * @brief Syscall execution time in microseconds.
	 */
	long			time;

	/**
	 * @brief Syscall information.
	 */
	syscall_info_t	sci;
}	stat_entry_t;

/**
 * @typedef stat_t
 * @brief Aggregated statistics for a syscall.
 */
typedef struct	stat_s {
	/**
	 * @brief Syscall definition.
	 */
	const syscall_def_t	*scd;

	/**
	 * @brief Total execution time in microseconds.
	 */
	long				time;

	/**
	 * @brief Total number of calls.
	 */
	long				calls;

	/**
	 * @brief Number of failed calls.
	 */
	long				errors;
}	stat_t;

// ---
// Function declarations
// ---

/**
 * @brief Initialize statistics collection.
 * @param should_save Enable statistics collection.
 * @return 0 on success, -1 on error.
 */
int		stat_init(
			bool should_save
			);

/**
 * @brief Enable or disable statistics collection.
 * @param should_save true to enable, false to disable.
 */
void	stat_should_save(
			bool should_save
			);

/**
 * @brief Cleanup statistics resources.
 */
void	stat_cleanup(void);

/**
 * @brief Add a syscall entry to statistics.
 * @param se Statistic entry to add.
 * @return 0 on success, -1 on error.
 */
int		stat_add(
			const stat_entry_t *se
			);

/**
 * @brief Print statistics summary.
 * @return 0 on success, -1 on error.
 */
int		stat_print_summary(void);

#endif
