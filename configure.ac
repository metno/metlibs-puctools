#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([puCtools], [4.0.0], [diana@met.no])
AM_INIT_AUTOMAKE
METNO_SET_VERSION_INFO


AC_CONFIG_SRCDIR([src/puMath.c])
AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Not available under pkg-config on all platforms:
# Make sure pkg-config also considers $prefix/lib/pkgconfig.
#export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$prefix/lib/pkgconfig
#PKG_CHECK_MODULES([HDF], [hdf])

# Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC

AC_CHECK_HEADERS([stdlib.h string.h stdarg.h ctype.h math.h], , 
	         AC_MSG_FAILURE(Missing required header))

AC_CHECK_HEADERS([hdf/hdf.h], , AC_MSG_FAILURE(Missing required header))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile
		puctools.pc
                include/Makefile
                src/Makefile])

AC_OUTPUT
