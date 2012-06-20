# $Id$

pkgname = puCtools

include $(top_srcdir)/metlibs.mk

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

libpuCtools_la_CPPFLAGS = $(AM_CPPFLAGS) \
	${MILOGGER_CPPFLAGS} \
	${LOG4CPP_CPPFLAGS}

libpuCtools_la_LDFLAGS = ${VERSION_INFO}
#	${LOG4CPP_LDFLAGS}

#libpuCtools_la_LIBADD = \
#	-lm \
#	${MILOGGER_LIBS} \
#	${LOG4CPP_LIBS}

pkg_includedir = ${includedir}/puCtools

pkg_include_HEADERS = \
	bool.h \
	glob.h \
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

