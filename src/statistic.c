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

TYPEDEF_LIST(stat_entry_t, list_stat_entry);
TYPEDEF_LIST(stat_t, list_stat);

// ---
// Local variable
// ---

static list_stat_entry_t	_sc_stat_entries[ELEM_COUNT(g_syscall_defs)] = { 0 };
static bool					_should_save = false;

// ---
// Static function declarations
// ---

static int	_stat_cmp(
				const void *a,
				const void *b
				);

static bool _stat_aggregate_stats(
				list_stat_t *stats,
				stat_t *total
				);

static int _stat_print_stat(
				const stat_t *stat,
				const stat_t *total
				);

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
	list_stat_entry_t	*stat_entries;

	array_foreach(_sc_stat_entries, stat_entries) {
		list_free(stat_entries);
	}
}

int		stat_add(
			const stat_entry_t *se
			) {
	BREAK_SHOULD_SAVE;

	return (list_push(&_sc_stat_entries[SCD_INDEX(se->sci.scd)], *se) ? 0 : -1);
}

int	stat_print_summary(void) {
	BREAK_SHOULD_SAVE;
	int			tmp;
	int			ret = 0;
	list_stat_t	stats = list_new();
	stat_t		*stat;
	stat_t		total;

	TRY_SILENT(_stat_aggregate_stats(&stats, &total) ? 0 : -1);
	qsort(stats.data, stats.len, sizeof(*stats.data), _stat_cmp);
	TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
				"% time", "seconds", "usecs/call", "calls", "errors", "syscall"));
	ret += tmp;
	TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
				"------", "-----------", "-----------", "---------", "---------", "----------------"));
	ret += tmp;
	list_foreach(&stats, stat) {
		TRY_SILENT(tmp = _stat_print_stat(stat, &total));
		ret += tmp;
	}
	TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
				"------", "-----------", "-----------", "---------", "---------", "----------------"));
	ret += tmp;
	TRY_SILENT(tmp = _stat_print_stat(&total, &total));
	ret += tmp;
	return (ret);
}

// ---
// Static function definitions
// ---

static int	_stat_cmp(
				const void *a,
				const void *b
				) {
	return (((const stat_t *)b)->time - ((const stat_t *)a)->time);
}

static int	_stat_print_stat(
				const stat_t *stat,
				const stat_t *total
				) {
	int	tmp;
	int	ret = 0;

	TRY_SILENT(tmp = logger_log("%6.2f %11.6f %11ld %9ld %9ld %s\n",
		total->time != 0 ? (stat->time / (float)total->time) * 100.f : 0.f,
		stat->time / 1000000.0,
		stat->time_per_call,
		stat->calls,
		stat->errors,
		stat->scd != NULL ? stat->scd->name : "total"));
	ret += tmp;
	return (ret);
}

static bool	_stat_aggregate_stats(
				list_stat_t *stats,
				stat_t *total
				) {
	list_stat_entry_t	*stat_entries;
	stat_entry_t		*stat_entry;
	stat_t				stat;

	total->scd = NULL;
	total->calls = 0;
	total->time = 0;
	total->errors = 0;
	array_foreach(_sc_stat_entries, stat_entries) {
		if (stat_entries->len == 0)
			continue ;
		stat.scd = &g_syscall_defs[stat_entries - _sc_stat_entries];
		stat.calls = 0;
		stat.errors = 0;
		stat.time = 0;
		stat.calls = stat_entries->len;
		total->calls += stat.calls;
		list_foreach(stat_entries, stat_entry) {
			if (stat_entry->sci.errnr != 0)
				++stat.errors;
			stat.time += stat_entry->time;
		}
		total->time += stat.time;
		total->errors += stat.errors;
		stat.time_per_call = stat.calls != 0 ? stat.time / stat.calls : 0;
		if (!list_push(stats, stat))
			return (false);
	}
	total->time_per_call = total->calls != 0 ? total->time / total->calls : 0;
	return (true);
}
