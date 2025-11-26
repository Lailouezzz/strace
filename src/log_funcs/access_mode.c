// ---
// Includes
// ---

#include <unistd.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Local variables
// ---

/**
 * @brief Mapping of access() mode flags to their string names.
 */
static const bitmap_mapping_t _modes_bm[] = {
	BITMAP_MAPPING_ENTRY(R_OK),
	BITMAP_MAPPING_ENTRY(W_OK),
	BITMAP_MAPPING_ENTRY(X_OK),
};

LOG_FUNC_impl(ACCESS_MODE) {
	UNUSED(sci);
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp = 0;
	bool	first = true;
	const bitmap_mapping_t	*it;

	if (value == F_OK)
		return (LOG_PRINT("F_OK"));
	array_foreach(_modes_bm, it) {
		if ((it->bit & value) != 0) {
			TRY_SILENT(tmp = LOG_PRINT("%s%s", first ? "" : "|", it->name));
			ret += tmp;
			first = false;
		}
	}
	return (ret);
}
