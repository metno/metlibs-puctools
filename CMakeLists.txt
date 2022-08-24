PROJECT(metlibs-puctools)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(MetnoUtils)

METNO_PVERSION_DEFINES(PUCTOOLS "src/puCtoolsVersion.h")

# metlibs-milogger would be necessary if glob_cache.cc had DEBUGPRINT enabled ...
#SET(PKGS
#  metlibs-milogger>=6.0.0
#)
#PKG_CHECK_MODULES(PC_METLIBS REQUIRED
#  ${PKGS}
#)

SET(lib_name "metlibs-puctools")

METNO_GEN_PKGCONFIG("${lib_name}.pc.in" "${lib_name}.pc"
  "${PKGS}" "" "" "")

CONFIGURE_FILE(puCtools.pc.in puCtools.pc @ONLY)
INSTALL(FILES ${CMAKE_BINARY_DIR}/puCtools.pc DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig")

ADD_SUBDIRECTORY(src)
