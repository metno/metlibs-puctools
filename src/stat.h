/* $Id$ */
#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__MSVCRT__)

// Windows with Microsoft Visual C runtime: separate 64-bit functions

typedef struct _stati64 pu_struct_stat;

static inline int
pu_stat(const char *fn, pu_struct_stat *sb)
{
	return _stati64(fn, sb);
}

static inline int
pu_lstat(const char *fn, pu_struct_stat *sb)
{
	return _stati64(fn, sb);
}

#define S_ISLNK(sb) (0)

#else

/*
 * Everything else: either stat() / fstat() / lstat() support 64-bit sizes
 * directly (*BSD), or the library takes care of it transparently (GNU
 * with _FILE_OFFSET_BITS defined to 64, courtesy of AC_SYS_LARGEFILE).
 */
typedef struct stat pu_struct_stat;

static inline int
pu_stat(const char *fn, pu_struct_stat *sb)
{
	return stat(fn, sb);
}

static inline int
pu_lstat(const char *fn, pu_struct_stat *sb)
{
	return lstat(fn, sb);
}

#endif

#ifdef __cplusplus
}
#endif

#endif
