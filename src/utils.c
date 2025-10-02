/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:07:54 by ale-boud          #+#    #+#             */
/*   Updated: 2025/09/11 16:20:39 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ---
// Includes
// ---

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "strace.h"

#include "utils.h"

// ---
// Defines
// ---

#define ERRNO_NAME_ENTRY(name, idx) [idx] = #name,

// ---
// Local variable
// ---

static const char	*_errno_names[] = {
ERRNO_NAME_ENTRY(EPERM, 1)
ERRNO_NAME_ENTRY(ENOENT, 2)
ERRNO_NAME_ENTRY(ESRCH, 3)
ERRNO_NAME_ENTRY(EINTR, 4)
ERRNO_NAME_ENTRY(EIO, 5)
ERRNO_NAME_ENTRY(ENXIO, 6)
ERRNO_NAME_ENTRY(E2BIG, 7)
ERRNO_NAME_ENTRY(ENOEXEC, 8)
ERRNO_NAME_ENTRY(EBADF, 9)
ERRNO_NAME_ENTRY(ECHILD, 10)
ERRNO_NAME_ENTRY(EAGAIN, 11)
ERRNO_NAME_ENTRY(ENOMEM, 12)
ERRNO_NAME_ENTRY(EACCES, 13)
ERRNO_NAME_ENTRY(EFAULT, 14)
ERRNO_NAME_ENTRY(ENOTBLK, 15)
ERRNO_NAME_ENTRY(EBUSY, 16)
ERRNO_NAME_ENTRY(EEXIST, 17)
ERRNO_NAME_ENTRY(EXDEV, 18)
ERRNO_NAME_ENTRY(ENODEV, 19)
ERRNO_NAME_ENTRY(ENOTDIR, 20)
ERRNO_NAME_ENTRY(EISDIR, 21)
ERRNO_NAME_ENTRY(EINVAL, 22)
ERRNO_NAME_ENTRY(ENFILE, 23)
ERRNO_NAME_ENTRY(EMFILE, 24)
ERRNO_NAME_ENTRY(ENOTTY, 25)
ERRNO_NAME_ENTRY(ETXTBSY, 26)
ERRNO_NAME_ENTRY(EFBIG, 27)
ERRNO_NAME_ENTRY(ENOSPC, 28)
ERRNO_NAME_ENTRY(ESPIPE, 29)
ERRNO_NAME_ENTRY(EROFS, 30)
ERRNO_NAME_ENTRY(EMLINK, 31)
ERRNO_NAME_ENTRY(EPIPE, 32)
ERRNO_NAME_ENTRY(EDOM, 33)
ERRNO_NAME_ENTRY(ERANGE, 34)
ERRNO_NAME_ENTRY(EDEADLK, 35)
ERRNO_NAME_ENTRY(ENAMETOOLONG, 36)
ERRNO_NAME_ENTRY(ENOLCK, 37)
ERRNO_NAME_ENTRY(ENOSYS, 38)
ERRNO_NAME_ENTRY(ENOTEMPTY, 39)
ERRNO_NAME_ENTRY(ELOOP, 40)
ERRNO_NAME_ENTRY(EWOULDBLOCK, 41)
ERRNO_NAME_ENTRY(ENOMSG, 42)
ERRNO_NAME_ENTRY(EIDRM, 43)
ERRNO_NAME_ENTRY(ECHRNG, 44)
ERRNO_NAME_ENTRY(EL2NSYNC, 45)
ERRNO_NAME_ENTRY(EL3HLT, 46)
ERRNO_NAME_ENTRY(EL3RST, 47)
ERRNO_NAME_ENTRY(ELNRNG, 48)
ERRNO_NAME_ENTRY(EUNATCH, 49)
ERRNO_NAME_ENTRY(ENOCSI, 50)
ERRNO_NAME_ENTRY(EL2HLT, 51)
ERRNO_NAME_ENTRY(EBADE, 52)
ERRNO_NAME_ENTRY(EBADR, 53)
ERRNO_NAME_ENTRY(EXFULL, 54)
ERRNO_NAME_ENTRY(ENOANO, 55)
ERRNO_NAME_ENTRY(EBADRQC, 56)
ERRNO_NAME_ENTRY(EBADSLT, 57)
ERRNO_NAME_ENTRY(EDEADLOCK, 58)
ERRNO_NAME_ENTRY(EBFONT, 59)
ERRNO_NAME_ENTRY(ENOSTR, 60)
ERRNO_NAME_ENTRY(ENODATA, 61)
ERRNO_NAME_ENTRY(ETIME, 62)
ERRNO_NAME_ENTRY(ENOSR, 63)
ERRNO_NAME_ENTRY(ENONET, 64)
ERRNO_NAME_ENTRY(ENOPKG, 65)
ERRNO_NAME_ENTRY(EREMOTE, 66)
ERRNO_NAME_ENTRY(ENOLINK, 67)
ERRNO_NAME_ENTRY(EADV, 68)
ERRNO_NAME_ENTRY(ESRMNT, 69)
ERRNO_NAME_ENTRY(ECOMM, 70)
ERRNO_NAME_ENTRY(EPROTO, 71)
ERRNO_NAME_ENTRY(EMULTIHOP, 72)
ERRNO_NAME_ENTRY(EDOTDOT, 73)
ERRNO_NAME_ENTRY(EBADMSG, 74)
ERRNO_NAME_ENTRY(EOVERFLOW, 75)
ERRNO_NAME_ENTRY(ENOTUNIQ, 76)
ERRNO_NAME_ENTRY(EBADFD, 77)
ERRNO_NAME_ENTRY(EREMCHG, 78)
ERRNO_NAME_ENTRY(ELIBACC, 79)
ERRNO_NAME_ENTRY(ELIBBAD, 80)
ERRNO_NAME_ENTRY(ELIBSCN, 81)
ERRNO_NAME_ENTRY(ELIBMAX, 82)
ERRNO_NAME_ENTRY(ELIBEXEC, 83)
ERRNO_NAME_ENTRY(EILSEQ, 84)
ERRNO_NAME_ENTRY(ERESTART, 85)
ERRNO_NAME_ENTRY(ESTRPIPE, 86)
ERRNO_NAME_ENTRY(EUSERS, 87)
ERRNO_NAME_ENTRY(ENOTSOCK, 88)
ERRNO_NAME_ENTRY(EDESTADDRREQ, 89)
ERRNO_NAME_ENTRY(EMSGSIZE, 90)
ERRNO_NAME_ENTRY(EPROTOTYPE, 91)
ERRNO_NAME_ENTRY(ENOPROTOOPT, 92)
ERRNO_NAME_ENTRY(EPROTONOSUPPORT, 93)
ERRNO_NAME_ENTRY(ESOCKTNOSUPPORT, 94)
ERRNO_NAME_ENTRY(EOPNOTSUPP, 95)
ERRNO_NAME_ENTRY(EPFNOSUPPORT, 96)
ERRNO_NAME_ENTRY(EAFNOSUPPORT, 97)
ERRNO_NAME_ENTRY(EADDRINUSE, 98)
ERRNO_NAME_ENTRY(EADDRNOTAVAIL, 99)
ERRNO_NAME_ENTRY(ENETDOWN, 100)
ERRNO_NAME_ENTRY(ENETUNREACH, 101)
ERRNO_NAME_ENTRY(ENETRESET, 102)
ERRNO_NAME_ENTRY(ECONNABORTED, 103)
ERRNO_NAME_ENTRY(ECONNRESET, 104)
ERRNO_NAME_ENTRY(ENOBUFS, 105)
ERRNO_NAME_ENTRY(EISCONN, 106)
ERRNO_NAME_ENTRY(ENOTCONN, 107)
ERRNO_NAME_ENTRY(ESHUTDOWN, 108)
ERRNO_NAME_ENTRY(ETOOMANYREFS, 109)
ERRNO_NAME_ENTRY(ETIMEDOUT, 110)
ERRNO_NAME_ENTRY(ECONNREFUSED, 111)
ERRNO_NAME_ENTRY(EHOSTDOWN, 112)
ERRNO_NAME_ENTRY(EHOSTUNREACH, 113)
ERRNO_NAME_ENTRY(EALREADY, 114)
ERRNO_NAME_ENTRY(EINPROGRESS, 115)
ERRNO_NAME_ENTRY(ESTALE, 116)
ERRNO_NAME_ENTRY(EUCLEAN, 117)
ERRNO_NAME_ENTRY(ENOTNAM, 118)
ERRNO_NAME_ENTRY(ENAVAIL, 119)
ERRNO_NAME_ENTRY(EISNAM, 120)
ERRNO_NAME_ENTRY(EREMOTEIO, 121)
ERRNO_NAME_ENTRY(EDQUOT, 122)
ERRNO_NAME_ENTRY(ENOMEDIUM, 123)
ERRNO_NAME_ENTRY(EMEDIUMTYPE, 124)
ERRNO_NAME_ENTRY(ECANCELED, 125)
ERRNO_NAME_ENTRY(ENOKEY, 126)
ERRNO_NAME_ENTRY(EKEYEXPIRED, 127)
ERRNO_NAME_ENTRY(EKEYREVOKED, 128)
ERRNO_NAME_ENTRY(EKEYREJECTED, 129)
ERRNO_NAME_ENTRY(EOWNERDEAD, 130)
ERRNO_NAME_ENTRY(ENOTRECOVERABLE, 131)
ERRNO_NAME_ENTRY(ERFKILL, 132)
ERRNO_NAME_ENTRY(ERESTARTSYS, 512)
ERRNO_NAME_ENTRY(ERESTARTNOINTR, 513)
ERRNO_NAME_ENTRY(ERESTARTNOHAND, 514)
ERRNO_NAME_ENTRY(ERESTART_RESTARTBLOCK, 516)
};

static const char *_kstrerror_table[] = {
[ERESTARTSYS] = "To be restarted if SA_RESTART is set",
[ERESTARTNOINTR] = "Restart syscall (ignore EINTR)",
[ERESTARTNOHAND] = "Restart if no signal handler",
[ERESTART_RESTARTBLOCK] = "Restart via restart_syscall",
};

// ---
// Static function declarations
// ---

/**
 * @brief Check if the absolute path s is a regular file
 *
 * @param s the absolute path
 * @return 1 if exist 0 otherwise
 */
static int	_search_exec_exist(
				const char *s
				);

// ---
// Extern function definitions
// ---

void	error_msg(const char *fmt, ...) {
	va_list	args;

	fprintf(stderr, "%s: ", g_ctx.pn);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

void	perror_msg(const char *fmt, ...) {
	va_list	args;

	fprintf(stderr, "%s: ", g_ctx.pn);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, ": %s\n", strerror(errno));
}

void	verbose(const char *fmt, ...) {
	va_list	args;

	if (!g_ctx.verbose)
		return ;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

char	*search_exec(
			char *s,
			char *envpath
			) {
	char	*spath;
	char	*envpath_copy;

	if (s == NULL)
		return (NULL);
	if (envpath == NULL || (envpath_copy = strdup(envpath)) == NULL)
		return (strdup(s));
	if (strchr(s, '/') != NULL)
		return (free(envpath_copy), strdup(s));
	for (char *path = strtok(envpath_copy, ":"); path != NULL; path = strtok(NULL, ":")) {
		spath = malloc((strlen(s) + strlen(path) + 2) * sizeof(char));
		strcpy(spath, path);
		strcat(spath, "/");
		strcat(spath, s);
		if (_search_exec_exist(spath))
			return (free(envpath_copy), spath);
		free(spath);
	}
	return (free(envpath_copy), strdup(s));
}

const char	*errno_name(int err) {
	const char	*ret = NULL;

	if (err > 0 && (unsigned int)err < ELEM_COUNT(_errno_names))
		ret = _errno_names[err];
	if (ret == NULL)
		ret = "EUNK";
	return (ret);
}

const char	*kstrerror(int err) {
	switch (err) {
		case ERESTARTSYS:
		case ERESTARTNOINTR:
		case ERESTARTNOHAND:
		case ERESTART_RESTARTBLOCK:
			return (_kstrerror_table[err]);
		default:
			return (strerror(err));
	}
}

// ---
// Static function definitions
// ---

static int	_search_exec_exist(
				const char *s
				) {
	struct stat	st;

	if (stat(s, &st) == -1 || S_ISDIR(st.st_mode))
		return (0);
	if (access(s, X_OK) == -1)
		return (0);
	return (1);
}
