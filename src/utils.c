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
#include <sys/signal.h>
#include "strace.h"

#include "utils.h"

// ---
// Defines
// ---

#define NAME_IDX_ENTRY(name, idx) [idx] = #name,

// ---
// Local variable
// ---

static const char	*_errno_names[] = {
NAME_IDX_ENTRY(EPERM, 1)
NAME_IDX_ENTRY(ENOENT, 2)
NAME_IDX_ENTRY(ESRCH, 3)
NAME_IDX_ENTRY(EINTR, 4)
NAME_IDX_ENTRY(EIO, 5)
NAME_IDX_ENTRY(ENXIO, 6)
NAME_IDX_ENTRY(E2BIG, 7)
NAME_IDX_ENTRY(ENOEXEC, 8)
NAME_IDX_ENTRY(EBADF, 9)
NAME_IDX_ENTRY(ECHILD, 10)
NAME_IDX_ENTRY(EAGAIN, 11)
NAME_IDX_ENTRY(ENOMEM, 12)
NAME_IDX_ENTRY(EACCES, 13)
NAME_IDX_ENTRY(EFAULT, 14)
NAME_IDX_ENTRY(ENOTBLK, 15)
NAME_IDX_ENTRY(EBUSY, 16)
NAME_IDX_ENTRY(EEXIST, 17)
NAME_IDX_ENTRY(EXDEV, 18)
NAME_IDX_ENTRY(ENODEV, 19)
NAME_IDX_ENTRY(ENOTDIR, 20)
NAME_IDX_ENTRY(EISDIR, 21)
NAME_IDX_ENTRY(EINVAL, 22)
NAME_IDX_ENTRY(ENFILE, 23)
NAME_IDX_ENTRY(EMFILE, 24)
NAME_IDX_ENTRY(ENOTTY, 25)
NAME_IDX_ENTRY(ETXTBSY, 26)
NAME_IDX_ENTRY(EFBIG, 27)
NAME_IDX_ENTRY(ENOSPC, 28)
NAME_IDX_ENTRY(ESPIPE, 29)
NAME_IDX_ENTRY(EROFS, 30)
NAME_IDX_ENTRY(EMLINK, 31)
NAME_IDX_ENTRY(EPIPE, 32)
NAME_IDX_ENTRY(EDOM, 33)
NAME_IDX_ENTRY(ERANGE, 34)
NAME_IDX_ENTRY(EDEADLK, 35)
NAME_IDX_ENTRY(ENAMETOOLONG, 36)
NAME_IDX_ENTRY(ENOLCK, 37)
NAME_IDX_ENTRY(ENOSYS, 38)
NAME_IDX_ENTRY(ENOTEMPTY, 39)
NAME_IDX_ENTRY(ELOOP, 40)
NAME_IDX_ENTRY(EWOULDBLOCK, 41)
NAME_IDX_ENTRY(ENOMSG, 42)
NAME_IDX_ENTRY(EIDRM, 43)
NAME_IDX_ENTRY(ECHRNG, 44)
NAME_IDX_ENTRY(EL2NSYNC, 45)
NAME_IDX_ENTRY(EL3HLT, 46)
NAME_IDX_ENTRY(EL3RST, 47)
NAME_IDX_ENTRY(ELNRNG, 48)
NAME_IDX_ENTRY(EUNATCH, 49)
NAME_IDX_ENTRY(ENOCSI, 50)
NAME_IDX_ENTRY(EL2HLT, 51)
NAME_IDX_ENTRY(EBADE, 52)
NAME_IDX_ENTRY(EBADR, 53)
NAME_IDX_ENTRY(EXFULL, 54)
NAME_IDX_ENTRY(ENOANO, 55)
NAME_IDX_ENTRY(EBADRQC, 56)
NAME_IDX_ENTRY(EBADSLT, 57)
NAME_IDX_ENTRY(EDEADLOCK, 58)
NAME_IDX_ENTRY(EBFONT, 59)
NAME_IDX_ENTRY(ENOSTR, 60)
NAME_IDX_ENTRY(ENODATA, 61)
NAME_IDX_ENTRY(ETIME, 62)
NAME_IDX_ENTRY(ENOSR, 63)
NAME_IDX_ENTRY(ENONET, 64)
NAME_IDX_ENTRY(ENOPKG, 65)
NAME_IDX_ENTRY(EREMOTE, 66)
NAME_IDX_ENTRY(ENOLINK, 67)
NAME_IDX_ENTRY(EADV, 68)
NAME_IDX_ENTRY(ESRMNT, 69)
NAME_IDX_ENTRY(ECOMM, 70)
NAME_IDX_ENTRY(EPROTO, 71)
NAME_IDX_ENTRY(EMULTIHOP, 72)
NAME_IDX_ENTRY(EDOTDOT, 73)
NAME_IDX_ENTRY(EBADMSG, 74)
NAME_IDX_ENTRY(EOVERFLOW, 75)
NAME_IDX_ENTRY(ENOTUNIQ, 76)
NAME_IDX_ENTRY(EBADFD, 77)
NAME_IDX_ENTRY(EREMCHG, 78)
NAME_IDX_ENTRY(ELIBACC, 79)
NAME_IDX_ENTRY(ELIBBAD, 80)
NAME_IDX_ENTRY(ELIBSCN, 81)
NAME_IDX_ENTRY(ELIBMAX, 82)
NAME_IDX_ENTRY(ELIBEXEC, 83)
NAME_IDX_ENTRY(EILSEQ, 84)
NAME_IDX_ENTRY(ERESTART, 85)
NAME_IDX_ENTRY(ESTRPIPE, 86)
NAME_IDX_ENTRY(EUSERS, 87)
NAME_IDX_ENTRY(ENOTSOCK, 88)
NAME_IDX_ENTRY(EDESTADDRREQ, 89)
NAME_IDX_ENTRY(EMSGSIZE, 90)
NAME_IDX_ENTRY(EPROTOTYPE, 91)
NAME_IDX_ENTRY(ENOPROTOOPT, 92)
NAME_IDX_ENTRY(EPROTONOSUPPORT, 93)
NAME_IDX_ENTRY(ESOCKTNOSUPPORT, 94)
NAME_IDX_ENTRY(EOPNOTSUPP, 95)
NAME_IDX_ENTRY(EPFNOSUPPORT, 96)
NAME_IDX_ENTRY(EAFNOSUPPORT, 97)
NAME_IDX_ENTRY(EADDRINUSE, 98)
NAME_IDX_ENTRY(EADDRNOTAVAIL, 99)
NAME_IDX_ENTRY(ENETDOWN, 100)
NAME_IDX_ENTRY(ENETUNREACH, 101)
NAME_IDX_ENTRY(ENETRESET, 102)
NAME_IDX_ENTRY(ECONNABORTED, 103)
NAME_IDX_ENTRY(ECONNRESET, 104)
NAME_IDX_ENTRY(ENOBUFS, 105)
NAME_IDX_ENTRY(EISCONN, 106)
NAME_IDX_ENTRY(ENOTCONN, 107)
NAME_IDX_ENTRY(ESHUTDOWN, 108)
NAME_IDX_ENTRY(ETOOMANYREFS, 109)
NAME_IDX_ENTRY(ETIMEDOUT, 110)
NAME_IDX_ENTRY(ECONNREFUSED, 111)
NAME_IDX_ENTRY(EHOSTDOWN, 112)
NAME_IDX_ENTRY(EHOSTUNREACH, 113)
NAME_IDX_ENTRY(EALREADY, 114)
NAME_IDX_ENTRY(EINPROGRESS, 115)
NAME_IDX_ENTRY(ESTALE, 116)
NAME_IDX_ENTRY(EUCLEAN, 117)
NAME_IDX_ENTRY(ENOTNAM, 118)
NAME_IDX_ENTRY(ENAVAIL, 119)
NAME_IDX_ENTRY(EISNAM, 120)
NAME_IDX_ENTRY(EREMOTEIO, 121)
NAME_IDX_ENTRY(EDQUOT, 122)
NAME_IDX_ENTRY(ENOMEDIUM, 123)
NAME_IDX_ENTRY(EMEDIUMTYPE, 124)
NAME_IDX_ENTRY(ECANCELED, 125)
NAME_IDX_ENTRY(ENOKEY, 126)
NAME_IDX_ENTRY(EKEYEXPIRED, 127)
NAME_IDX_ENTRY(EKEYREVOKED, 128)
NAME_IDX_ENTRY(EKEYREJECTED, 129)
NAME_IDX_ENTRY(EOWNERDEAD, 130)
NAME_IDX_ENTRY(ENOTRECOVERABLE, 131)
NAME_IDX_ENTRY(ERFKILL, 132)
NAME_IDX_ENTRY(ERESTARTSYS, 512)
NAME_IDX_ENTRY(ERESTARTNOINTR, 513)
NAME_IDX_ENTRY(ERESTARTNOHAND, 514)
NAME_IDX_ENTRY(ERESTART_RESTARTBLOCK, 516)
};

static const char	*_signal_names[] = {
NAME_IDX_ENTRY(SIGHUP, 1)
NAME_IDX_ENTRY(SIGINT, 2)
NAME_IDX_ENTRY(SIGQUIT, 3)
NAME_IDX_ENTRY(SIGILL, 4)
NAME_IDX_ENTRY(SIGTRAP, 5)
NAME_IDX_ENTRY(SIGABRT, 6)
NAME_IDX_ENTRY(SIGBUS, 7)
NAME_IDX_ENTRY(SIGFPE, 8)
NAME_IDX_ENTRY(SIGKILL, 9)
NAME_IDX_ENTRY(SIGUSR1, 10)
NAME_IDX_ENTRY(SIGSEGV, 11)
NAME_IDX_ENTRY(SIGUSR2, 12)
NAME_IDX_ENTRY(SIGPIPE, 13)
NAME_IDX_ENTRY(SIGALRM, 14)
NAME_IDX_ENTRY(SIGTERM, 15)
NAME_IDX_ENTRY(SIGCHLD, 17)
NAME_IDX_ENTRY(SIGCONT, 18)
NAME_IDX_ENTRY(SIGSTOP, 19)
NAME_IDX_ENTRY(SIGTSTP, 20)
NAME_IDX_ENTRY(SIGTTIN, 21)
NAME_IDX_ENTRY(SIGTTOU, 22)
NAME_IDX_ENTRY(SIGURG, 23)
NAME_IDX_ENTRY(SIGXCPU, 24)
NAME_IDX_ENTRY(SIGXFSZ, 25)
NAME_IDX_ENTRY(SIGVTALRM, 26)
NAME_IDX_ENTRY(SIGPROF, 27)
NAME_IDX_ENTRY(SIGWINCH, 28)
NAME_IDX_ENTRY(SIGIO, 29)
NAME_IDX_ENTRY(SIGPWR, 30)
NAME_IDX_ENTRY(SIGSYS, 31)
};

static const char	*_kstrerror_table[] = {
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
	if (envpath == NULL)
		return (strdup(s));
	if ((envpath_copy = strdup(envpath)) == NULL)
		return (NULL);
	if (strchr(s, '/') != NULL)
		return (free(envpath_copy), strdup(s));
	for (char *path = strtok(envpath_copy, ":"); path != NULL; path = strtok(NULL, ":")) {
		spath = malloc((strlen(s) + strlen(path) + 2) * sizeof(char));
		if (spath == NULL)
			return (free(envpath_copy), NULL);
		strcpy(spath, path);
		strcat(spath, "/");
		strcat(spath, s);
		if (_search_exec_exist(spath))
			return (free(envpath_copy), spath);
		free(spath);
	}
	return (free(envpath_copy), strdup(""));
}

const char	*errno_name(int err) {
	const char	*ret = NULL;

	if (err > 0 && (unsigned int)err < ELEM_COUNT(_errno_names))
		ret = _errno_names[err];
	if (ret == NULL)
		ret = "SIG?";
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

const char	*signal_name(int signo) {
	const char	*ret = NULL;

	if (signo > 0 && (unsigned int)signo < ELEM_COUNT(_signal_names))
		ret = _signal_names[signo];
	if (ret == NULL)
		ret = "SIG?";
	return (ret);
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
