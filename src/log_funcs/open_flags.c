// ---
// Includes
// ---

#define _GNU_SOURCE
#include <fcntl.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Local variables
// ---

/**
 * @brief Mapping of open() flags to their string names.
 */
static const bitmap_mapping_t _flags_bm[] = {
	{O_CREAT, "O_CREAT"},
	{O_EXCL, "O_EXCL"},
	{O_NOCTTY, "O_NOCTTY"},
	{O_TRUNC, "O_TRUNC"},
	{O_APPEND, "O_APPEND"},
	{O_NONBLOCK, "O_NONBLOCK"},
	{O_SYNC, "O_SYNC"},
	{O_DSYNC, "O_DSYNC"},
	{O_DIRECT, "O_DIRECT"},
	{O_NOATIME, "O_NOATIME"},
	{O_CLOEXEC, "O_CLOEXEC"},
	{O_DIRECTORY, "O_DIRECTORY"},
	{O_NOFOLLOW, "O_NOFOLLOW"},
	{O_PATH, "O_PATH"},
	{O_TMPFILE, "O_TMPFILE"},
};

LOG_FUNC_impl(OPEN_FLAGS) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	int	flags = value;
	const bitmap_mapping_t	*flag_bm;

	switch (flags & O_ACCMODE) {
		case O_RDONLY:
			TRY_SILENT(tmp = LOG_PRINT("O_RDONLY"));
			ret += tmp;
			break;
		case O_WRONLY:
			TRY_SILENT(tmp = LOG_PRINT("O_WRONLY"));
			ret += tmp;
			break;
		case O_RDWR:
			TRY_SILENT(tmp = LOG_PRINT("O_RDWR"));
			ret += tmp;
			break;
		default:
			break;
	}
	flags &= ~O_ACCMODE;
	array_foreach(_flags_bm, flag_bm) {
		if ((flag_bm->bit & flags) != 0) {
			TRY_SILENT(tmp = LOG_PRINT("|%s", flag_bm->name));
			ret += tmp;
			flags &= ~flag_bm->bit;
		}
	}
	if (flags != 0) {
		TRY_SILENT(tmp = LOG_PRINT("|0x%x", flags));
		ret += tmp;
	}
	return (ret);
}
