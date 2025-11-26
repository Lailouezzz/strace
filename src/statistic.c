/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:37:53 by ale-boud          #+#    #+#             */
/*   Updated: 2025/11/24 12:13:09 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ---
// Includes
// ---

#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include "personality.h"
#include "utils.h"

#include "statistic.h"

// ---
// Define
// ---

#define BREAK_SHOULD_SAVE if (!_should_save) {return (0);}

// ---
// Typedef
// ---

TYPEDEF_LIST(stat_t*, list_stat);

// ---
// Local variable
// ---

static stat_t	_sc_pers_stats[PERS__COUNT][ELEM_COUNT(g_syscall_defs)] = { 0 };
static bool		_should_save = false;

// ---
// Static function declarations
// ---

/**
 * @brief Compare two stat entries by time for sorting.
 * @param a First stat entry pointer.
 * @param b Second stat entry pointer.
 * @return Negative if a > b, positive if a < b, 0 if equal.
 */
static int	_stat_cmp(
				const void *a,
				const void *b
				);

/**
 * @brief Print a single stat entry.
 * @param stat The stat entry to print.
 * @param total The total stat for percentage calculation.
 * @return Number of characters printed, or -1 on error.
 */
static int _stat_print_stat(
				const stat_t *stat,
				const stat_t *total
				);

/**
 * @brief Process stats array into sorted list and compute totals.
 * @param stats The stats array to process.
 * @param stats_len Length of the stats array.
 * @param ordered_stats Output list for sorted stats.
 * @param total Output for total statistics.
 * @return 0 on success, -1 on error.
 */
static int	_stat_process(
				stat_t *stats,
				size_t stats_len,
				list_stat_t *ordered_stats,
				stat_t *total
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

void	stat_should_save(
			bool should_save
			) {
	_should_save = should_save;
}

void	stat_cleanup(void) {
}

int		stat_add(
			const stat_entry_t *se
			) {
	BREAK_SHOULD_SAVE;

	++_sc_pers_stats[se->sci.pers][SCD_INDEX(se->sci.scd)].calls;
	_sc_pers_stats[se->sci.pers][SCD_INDEX(se->sci.scd)].time += se->time;
	if (se->sci.errnr != 0)
		++_sc_pers_stats[se->sci.pers][SCD_INDEX(se->sci.scd)].errors;
	return (0);
}

int	stat_print_summary(void) {
	int			tmp;
	int			ret = 0;
	stat_t		(*pers_stats)[ELEM_COUNT(g_syscall_defs)];
	list_stat_t	stats = list_new();
	stat_t		**stat;
	stat_t		total;
	arch_pers_t	pers;

	array_foreach(_sc_pers_stats, pers_stats) {
		TRY_SILENT(_stat_process(*pers_stats, ELEM_COUNT(*_sc_pers_stats), &stats, &total));
		if (stats.len == 0)
			continue ;
		pers = pers_stats - _sc_pers_stats;
		if (pers != PERS_x86_64) {
			TRY_SILENT(tmp = logger_log("System call usage summary for %s mode:\n", pers_get_name(pers)));
			ret += tmp;
		}
		TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
					"% time", "seconds", "usecs/call", "calls", "errors", "syscall"));
		ret += tmp;
		TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
					"------", "-----------", "-----------", "---------", "---------", "----------------"));
		ret += tmp;
		list_foreach(&stats, stat) {
			TRY_SILENT(tmp = _stat_print_stat(*stat, &total));
			ret += tmp;
		}
		TRY_SILENT(tmp = logger_log("%6s %11s %11s %9s %9s %s\n",
					"------", "-----------", "-----------", "---------", "---------", "----------------"));
		ret += tmp;
		TRY_SILENT(tmp = _stat_print_stat(&total, &total));
		ret += tmp;
		list_free(&stats);
	}
	return (ret);
}

// ---
// Static function definitions
// ---

static int	_stat_cmp(
				const void *a,
				const void *b
				) {
	return ((*(const stat_t **)b)->time - (*(const stat_t **)a)->time);
}

static int	_stat_print_stat(
				const stat_t *stat,
				const stat_t *total
				) {
	int	tmp;
	int	ret = 0;

	TRY_SILENT(tmp = logger_log("%6.2f %11.6f %11ld %9ld",
		total->time != 0 ? (stat->time / (float)total->time) * 100.f : 0.f,
		stat->time / 1000000.0,
		stat->calls != 0 ? stat->time / stat->calls : 0,
		stat->calls));
	ret += tmp;
	if (stat->errors != 0) {
		TRY_SILENT(tmp = logger_log(" %9ld %s\n",
			stat->errors,
			stat->scd != NULL ? stat->scd->name : "total"));
		ret += tmp;
	} else {
		TRY_SILENT(tmp = logger_log(" %9s %s\n",
			"",
			stat->scd != NULL ? stat->scd->name : "total"));
		ret += tmp;
	}
	return (ret);
}

static int	_stat_process(
				stat_t *stats,
				size_t stats_len,
				list_stat_t *ordered_stats,
				stat_t *total
				) {
	total->calls = 0;
	total->errors = 0;
	total->scd = NULL;
	total->time = 0;
	for (size_t k = 0; k < stats_len; ++k) {
		if (stats[k].calls <= 0) {
			continue ;
		}
		stats[k].scd = &g_syscall_defs[(((char*)&stats[k] - (char*)_sc_pers_stats) / sizeof(*stats)) % ELEM_COUNT(*_sc_pers_stats)];
		if (!list_push(ordered_stats, &stats[k]))
			return (-1);
		total->calls += stats[k].calls;
		total->errors += stats[k].errors;
		total->time += stats[k].time;
	}
	qsort(ordered_stats->data, ordered_stats->len, sizeof(*ordered_stats->data), _stat_cmp);
	return (0);
}
