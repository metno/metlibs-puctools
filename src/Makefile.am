lib_LTLIBRARIES = libpuCtools.la

libpuCtools_la_SOURCES=getopt.c\
	puMath.c\
	safety.c\
	stringmanip.c\
	timemanip.c

libpuCtools_la_LDFLAGS = ${VERSION_INFO}

INSTALL=install -p # tells install to preserve timestamp
DEFAULT_INCLUDES=-I${srcdir}/../include
