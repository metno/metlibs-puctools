# $Id$

pkgname = puCtools

include $(top_srcdir)/metlibs.mk

lib_LTLIBRARIES = libpuCtools.la

libpuCtools_la_SOURCES = \
	getopt.c \
	glob.c \
	puMath.c \
	safety.c \
	sleep.c \
	stringmanip.c \
	strlcpy.c \
	timemanip.c

libpuCtools_la_LDFLAGS = \
	${VERSION_INFO}

pkg_includedir = ${includedir}/puCtools

pkg_include_HEADERS = \
	bool.h \
	glob.h \
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

