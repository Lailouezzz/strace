// ---
// Includes
// ---

#define _GNU_SOURCE
#include <sys/mman.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Local variables
// ---

/**
 * @brief Mapping of mmap() protection flags to their string names.
 */
static const bitmap_mapping_t _flags_bm[] = {
	BITMAP_MAPPING_ENTRY(PROT_READ),
	BITMAP_MAPPING_ENTRY(PROT_WRITE),
	BITMAP_MAPPING_ENTRY(PROT_EXEC),
};

LOG_FUNC_impl(MMAP_PROT) {
	UNUSED(sci);
	UNUSED(sys_type);
	int		ret = 0;
	int		tmp;
	bool	first = true;
	const bitmap_mapping_t	*flag;

	if (value == PROT_NONE)
		return (LOG_PRINT("PROT_NONE"));
	array_foreach(_flags_bm, flag) {
		if ((value & flag->bit) != 0) {
			TRY_SILENT(tmp = LOG_PRINT("%s%s", first ? "" : "|", flag->name));
			ret += tmp;
			first = false;
		}
	}
	return (ret);
}
