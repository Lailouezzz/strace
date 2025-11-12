// ---
// Includes
// ---

#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include "utils.h"

#include "statistic.h"

// ---
// Define
// ---

#define BREAK_SHOULD_SAVE if (!_should_save) {return (0);}

// ---
// Typedef
// ---

TYPEDEF_LIST(stat_entry_t, list_stat);

// ---
// Local variable
// ---

static list_stat_t			_stats[ELEM_COUNT(g_syscall_defs)] = { 0 };
static size_t				_stats_len = 0;
static bool					_should_save = false;

// ---
// Static function declarations
// ---



// ---
// Extern function definitions
// ---


int	stat_init(
		bool should_save
		) {
	_should_save = should_save;
	BREAK_SHOULD_SAVE;

	return (0);
}

void	stat_cleanup(void) {
	list_stat_t	*sc_stats;

	array_foreach(_stats, sc_stats) {
		list_free(sc_stats);
	}
}

int		stat_add(
			const stat_entry_t *se
			) {
	BREAK_SHOULD_SAVE;

	return (list_push(&_stats[SCD_INDEX(se->sci.scd)], *se) ? 0 : -1);
}

int	stat_print_summary(void) {
	BREAK_SHOULD_SAVE;
	int	tmp;
	int	ret = 0;

	TRY_SILENT(tmp = logger_log("SUMMARY : %zu\n", _stats_len));
	ret += tmp;
	return (ret);
}

// ---
// Static function definitions
// ---
