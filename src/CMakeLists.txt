
ADD_DEFINITIONS(-W -Wall)

SET(puctools_SOURCES
  getopt.c
  puMath.c
  safety.c
  sleep.c
  stringmanip.c
  strlcpy.c
  timemanip.c
)

METNO_HEADERS (puctools_HEADERS puctools_SOURCES ".c" ".h")
LIST(APPEND puctools_HEADERS
  "bool.h"
  deprecated.h
  puCglob.h
  porttypes.h
  mkdir.h
  puCtools.h
  stat.h
  puCtoolsVersion.h
)
LIST(APPEND puctools_SOURCES
  glob.c
  glob_cache.cc
)
LIST(APPEND puctools_HEADERS
  glob_cache.h
)

########################################################################

ADD_LIBRARY(puctools SHARED
  ${puctools_SOURCES}
)

SET_TARGET_PROPERTIES(puctools PROPERTIES
  VERSION ${PUCTOOLS_PVERSION_FULL}
  SOVERSION "${PUCTOOLS_VERSION_MAJOR}"
  OUTPUT_NAME "${lib_name}"
)

TARGET_LINK_LIBRARIES(puctools
  ${Boost_LIBRARIES}
)

INSTALL(TARGETS puctools
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

INSTALL(FILES ${puctools_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/metlibs/puCtools
)
