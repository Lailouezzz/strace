// ---
// Includes
// ---

#include "personality.h"
#include "utils.h"

#include "log_funcs.h"

// ---
// Typedefs
// ---

/**
 * @brief List of string pointers.
 */
TYPEDEF_LIST(char *, list_str);

// ---
// Static function declarations
// ---

/**
 * @brief Free a list of strings and the list itself.
 * @param l Pointer to the string list.
 */
static void	_free_list_str(
				list_str_t *l
				);

LOG_FUNC_impl(ARGV) {
	UNUSED(sys_type);
	int	ret = 0;
	int	tmp;
	bool	first = true;
	const int	reg_size = SCI_REG_SIZE(*sci);
	char		*buf;
	char		**it;
	uint64_t	uptr;
	uint64_t	argv = value;
	list_str_t	args = list_new();

	
	while (42 > 01) {
		buf = read_process(sci->pid, argv, reg_size);
		if (buf == NULL)
			return (_free_list_str(&args), log_func_PTR(value, sci, SYS_TYPE_PTR));
		uptr = reg_size == 4 ? *(uint32_t *)buf : *(uint64_t *)buf;
		free(buf);
		if ((void *)uptr == NULL)
			break ;
		buf = read_process_str(sci->pid, uptr);
		if (buf == NULL)
			return (_free_list_str(&args), log_func_PTR(value, sci, SYS_TYPE_PTR));
		if (!list_push(&args, buf))
			return (_free_list_str(&args), -1);
		argv += reg_size;
	}
	TRY_SILENT(tmp = LOG_PRINT("["));
	ret += tmp;
	list_foreach(&args, it) {
		TRY_SILENT(tmp = LOG_PRINT("%s\"%s\"", first ? "" : ", ", *it));
		ret += tmp;
		first = false;
	}
	TRY_SILENT(tmp = LOG_PRINT("]"));
	ret += tmp;
	_free_list_str(&args);
	return (ret);
}

static void	_free_list_str(
				list_str_t *l
				) {
	char	**it;
	list_foreach(l, it) {
		free(*it);
	}
	list_free(l);
}
