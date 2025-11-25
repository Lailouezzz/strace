// ---
// Includes
// ---

#include <linux/mman.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Local variables
// ---

/**
 * @brief Mapping of mmap() flags to their string names.
 */
static const bitmap_mapping_t _flags_bm[] = {
BITMAP_MAPPING_ENTRY(MAP_FIXED),
BITMAP_MAPPING_ENTRY(MAP_ANONYMOUS),
BITMAP_MAPPING_ENTRY(MAP_32BIT),
BITMAP_MAPPING_ENTRY(MAP_GROWSDOWN),
BITMAP_MAPPING_ENTRY(MAP_DENYWRITE),
BITMAP_MAPPING_ENTRY(MAP_EXECUTABLE),
BITMAP_MAPPING_ENTRY(MAP_LOCKED),
BITMAP_MAPPING_ENTRY(MAP_NORESERVE),
BITMAP_MAPPING_ENTRY(MAP_POPULATE),
BITMAP_MAPPING_ENTRY(MAP_NONBLOCK),
BITMAP_MAPPING_ENTRY(MAP_STACK),
BITMAP_MAPPING_ENTRY(MAP_HUGETLB),
BITMAP_MAPPING_ENTRY(MAP_SYNC),
BITMAP_MAPPING_ENTRY(MAP_FIXED_NOREPLACE),
BITMAP_MAPPING_ENTRY(MAP_UNINITIALIZED),
};

LOG_FUNC_impl(MMAP_FLAGS) {
	UNUSED(sci);
	UNUSED(sys_type);
	int						ret = 0;
	int						tmp;
	int						flags;
	const bitmap_mapping_t	*flag;

	flags = value;
	switch (flags & MAP_TYPE) {
		case MAP_SHARED_VALIDATE:
			TRY_SILENT(tmp = LOG_PRINT("MAP_SHARED_VALIDATE"));
			ret += tmp;
			break ;
		case MAP_SHARED:
			TRY_SILENT(tmp = LOG_PRINT("MAP_SHARED"));
			ret += tmp;
			break ;
		case MAP_PRIVATE:
			TRY_SILENT(tmp = LOG_PRINT("MAP_PRIVATE"));
			ret += tmp;
			break ;
	}
	flags &= ~MAP_TYPE;
	array_foreach(_flags_bm, flag) {
		if ((flags & flag->bit) != 0) {
			TRY_SILENT(tmp = LOG_PRINT("|%s", flag->name));
			ret += tmp;
		}
	}
	return (ret);
}
