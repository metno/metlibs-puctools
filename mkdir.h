/* $Id$ */
#ifndef MKDIR_H_INCLUDED
#define MKDIR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__MSVCRT__)

#include <io.h>

static inline int
pu_mkdir(const char *dn, long mode)
{
	return mkdir(dn);
}

#else

#include <sys/types.h>
#include <sys/stat.h>

static inline int
pu_mkdir(const char *dn, mode_t mode)
{
	return mkdir(dn, mode);
}

#endif

#ifdef __cplusplus
}
#endif

#endif
