// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

LOG_FUNC_impl(STRING) {
	UNUSED(sys_type);
	int		ret = 0;
	int		tmp;
	char	*str;

	str = read_process_str(sci->pid, value);
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
	if (str != NULL) {
		TRY_SILENT(tmp = fprint_escaped(LOG_FILE, str, strlen(str)));
		ret += tmp;
	}
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
	free(str);
	return (ret);
}
