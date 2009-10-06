# $Id: Makefile.am 2786 2009-09-23 11:39:02Z dages $

pkgname = puCtools

include $(top_srcdir)/metlibs.mk

lib_LTLIBRARIES = libpuCtools.la

libpuCtools_la_SOURCES = \
	getopt.c \
	puMath.c \
	safety.c \
	stringmanip.c \
	timemanip.c

libpuCtools_la_LDFLAGS = \
	${VERSION_INFO}

libpuCtools_la_LIBADD = \
	-lm

pkg_includedir = ${prefix}/include/puCtools

pkg_include_HEADERS = \
	bool.h \
	porttypes.h \
	puMath.h \
	stringmanip.h \
	getopt.h \
	puCtools.h \
	safety.h \
	timemanip.h

