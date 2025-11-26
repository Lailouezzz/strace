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
 * @brief Mapping of *at() flags to their string names.
 */
static const bitmap_mapping_t _flags_bm[] = {
	BITMAP_MAPPING_ENTRY(AT_SYMLINK_NOFOLLOW),
	BITMAP_MAPPING_ENTRY(AT_SYMLINK_FOLLOW),
	BITMAP_MAPPING_ENTRY(AT_NO_AUTOMOUNT),
	BITMAP_MAPPING_ENTRY(AT_EMPTY_PATH),
	BITMAP_MAPPING_ENTRY(AT_STATX_FORCE_SYNC),
	BITMAP_MAPPING_ENTRY(AT_STATX_DONT_SYNC),
};

LOG_FUNC_impl(AT_FLAGS) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	int	flags = value;
	bool first = true;
	const bitmap_mapping_t	*flag_bm;

	if (value == 0)
		return (LOG_PRINT("0"));
	array_foreach(_flags_bm, flag_bm) {
		if ((flag_bm->bit & flags) != 0) {
			TRY_SILENT(tmp = LOG_PRINT("%s%s", first ? "" : "|", flag_bm->name));
			ret += tmp;
			flags &= ~flag_bm->bit;
			first = false;
		}
	}
	if (flags != 0) {
		TRY_SILENT(tmp = LOG_PRINT("|0x%x", flags));
		ret += tmp;
	}
	return (ret);
}
