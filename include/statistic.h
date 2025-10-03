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

typedef struct	stat_entry_s {
	long			time;
	syscall_info_t	sci;
}	stat_entry_t;

// ---
// Function declartions
// ---

/**
 * @brief Init the statistics
 *
 * @param should_save 
 * @return 
 */
int		stat_init(
			bool should_save
			);

/**
 * @brief Cleanup the statistics
 */
void	stat_cleanup(void);

int		stat_add(
			const stat_entry_t *se
			);

int		stat_print_summary(void);

#endif
