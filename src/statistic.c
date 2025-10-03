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
// Local variable
// ---

static stat_entry_t	*_stats = NULL;
static size_t		_stats_len = 0;
static size_t		_stats_alloced = 0;
static bool			_should_save = false;

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

	_stats = malloc(sizeof(*_stats));
	if (_stats == NULL)
		return (perror_msg("malloc()"), -1);
	_stats_alloced = 1;
	return (0);
}

void	stat_cleanup(void) {
	if (_stats != NULL)
		free(_stats);
	_stats = NULL;
}

int		stat_add(
			const stat_entry_t *se
			) {
	BREAK_SHOULD_SAVE;

	if (_stats_len >= _stats_alloced) {
		_stats = realloc(_stats, sizeof(*_stats) * (_stats_alloced << 1));
		if (_stats == NULL)
			return (perror_msg("realloc()"), -1);
		_stats_alloced <<= 1;
	}
	_stats[_stats_len++] = *se;
	return (0);
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
