# $Id$

pkgname = puCtools



lib_LTLIBRARIES = libpuCtools.la

libpuCtools_la_SOURCES = \
	getopt.c \
	glob.c \
	glob_cache.cc \
	puMath.c \
	safety.c \
	sleep.c \
	stringmanip.c \
	strlcpy.c \
	timemanip.c

libpuCtools_la_CPPFLAGS = $(AM_CPPFLAGS) ${MILOGGER_CPPFLAGS} 

libpuCtools_la_LDFLAGS = ${VERSION_INFO}

if ENABLE_SHARED_LIBRARY

libpuCtools_la_LDFLAGS += ${MILOGGER_LDFLAGS}
libpuCtools_la_LIBADD = ${MILOGGER_LIBS} -lm

endif

pkg_includedir = ${includedir}/puCtools

pkg_include_HEADERS = \
	bool.h \
	deprecated.h \
	puCglob.h \
	glob_cache.h \
	porttypes.h \
	puMath.h \
	stringmanip.h \
	getopt.h \
	mkdir.h \
	puCtools.h \
	safety.h \
	sleep.h \
	stat.h \
	strlcpy.h \
	timemanip.h

INSTALL=install -p # tells install to preserve timestamp