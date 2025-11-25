// ---
// Includes
// ---

#define _GNU_SOURCE
#include <fcntl.h>
#include "log_funcs.h"
#include "utils.h"

#include "log_custom.h"

LOG_CUSTOM_impl(openat, in) {
	int	ret = 0;
	int	tmp;

	TRY_SILENT(tmp = log_func_FD(sci->args[0], sci, SYS_TYPE_FD));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(", "));
	ret += tmp;
	TRY_SILENT(tmp = log_func_STRING(sci->args[1], sci, SYS_TYPE_STRING));
	ret += tmp;
	TRY_SILENT(tmp = LOG_PRINT(", "));
	ret += tmp;
	TRY_SILENT(tmp = log_func_OPEN_FLAGS(sci->args[2], sci, SYS_TYPE_OPEN_FLAGS));
	ret += tmp;
	if ((sci->args[2] & O_CREAT) != O_CREAT && (sci->args[2] & O_TMPFILE) != O_TMPFILE)
		return (ret);
	TRY_SILENT(tmp = LOG_PRINT(", "));
	ret += tmp;
	TRY_SILENT(tmp = log_func_OPEN_MODE(sci->args[3], sci, SYS_TYPE_OPEN_MODE));
	ret += tmp;
	return (ret);
}

LOG_CUSTOM_impl(openat, out) {
	UNUSED(sci);

	return (0);
}
