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
	if (str == NULL)
		return (log_func_PTR(value, sci, SYS_TYPE_PTR));
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
	TRY_SILENT(tmp = fprint_escaped(LOG_FILE, str, strlen(str)));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT("\""));
	ret += tmp;
	free(str);
	return (ret);
}
