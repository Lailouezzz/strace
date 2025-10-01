#ifndef  STATISTIC_H
# define STATISTIC_H

// ---
// Includes
// ---

# include <stdbool.h>

// ---
// Defines
// ---



// ---
// Typedefs
// ---

typedef struct	stat_entry_s {
	long	time;
	bool	is_error;
	int		pers;
}	stat_entry_t;

// ---
// Function declartions
// ---

/**
 * @brief Init the statistics
 *
 * @return 
 */
int		stat_init(void);

/**
 * @brief Cleanup the statistics
 */
void	stat_cleanup(void);

#endif
