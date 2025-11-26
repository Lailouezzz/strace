// ---
// Includes
// ---

#include <asm/prctl.h>
#include "utils.h"

#include "log_funcs.h"

// ---
// Static function declarations
// ---

/**
 * @brief Get the arch_prctl code name.
 * @param code The arch_prctl code value.
 * @return The code name string, or NULL if unknown.
 */
static const char	*_get_code(
						uint64_t code
						);

LOG_FUNC_impl(ARCH_CODE) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	const char	*code = _get_code(value);

	if (code != NULL)
		return (LOG_PRINT("%s", code));
	TRY_SILENT(tmp = log_func_HEX(value, sci, SYS_TYPE_HEX));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(" /* ARCH_??? */"));
	ret += tmp;
	return (ret);
}

static const char	*_get_code(
						uint64_t code
						) {
	switch (code) {
		CASE_STR(ARCH_SET_CPUID);
		CASE_STR(ARCH_GET_CPUID);
		CASE_STR(ARCH_SET_FS);
		CASE_STR(ARCH_GET_FS);
		CASE_STR(ARCH_SET_GS);
		CASE_STR(ARCH_GET_GS);
		default: return (NULL);
	}
}
