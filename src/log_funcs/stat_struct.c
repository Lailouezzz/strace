// ---
// Includes
// ---

#define _GNU_SOURCE
#include <fcntl.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Static function declarations
// ---

/**
 * @brief Get the file type string from mode.
 * @param mode The st_mode field from struct stat.
 * @return The file type constant name (e.g., "S_IFREG").
 */
static const char	*_get_ft(
						__mode_t mode
						);

LOG_FUNC_impl(STAT_STRUCT) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	struct stat	*stat;

	stat = read_process(sci->pid, value, sizeof(*stat));
	if (stat == NULL)
		return (log_func_PTR(value, sci, SYS_TYPE_PTR));
	TRY_SILENT(tmp = LOG_PRINT("{st_mode="));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT("%s|0%2o", _get_ft(stat->st_mode), stat->st_mode & 0777));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(", st_size="));
	ret += tmp;
	TRY_SILENT(tmp = log_func_OFF((uint64_t)stat->st_size, sci, SYS_TYPE_OFF));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(", ...}"));
	ret += tmp;
	free(stat);
	return (ret);
}

static const char	*_get_ft(
						__mode_t mode
						) {
	switch (mode & S_IFMT) {
		case S_IFREG:  return ("S_IFREG");
		case S_IFDIR:  return ("S_IFDIR");
		case S_IFLNK:  return ("S_IFLNK");
		case S_IFCHR:  return ("S_IFCHR");
		case S_IFBLK:  return ("S_IFBLK");
		case S_IFIFO:  return ("S_IFIFO");
		case S_IFSOCK: return ("S_IFSOCK");
		default:       return ("S_IFUNK");
	}
}
