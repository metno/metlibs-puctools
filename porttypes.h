/*
  libpuCtools - Basic C-Tools
  
  $Id$

  Copyright (C) 2006 met.no

  Contact information:
  Norwegian Meteorological Institute
  Box 43 Blindern
  0313 OSLO
  NORWAY
  email: diana@met.no
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


/* -*- C -*- */
/*
  porttypes.h -- defines names for hardware-independent types

  Author: LBS (who nicked it from NSCA's HDF distribution)
  Date:   1997-03-10 (creation)

  WARNING: Since these definitions are taken from the HDF files, it
  will NOT go well with header files like hdfi.h.  Therefore, if both
  HDF headers and porttypes.h are needed, include the HDF files first,
  like this:

    #include <hdf/hdf.h> // say...
    #include <porttypes.h>

    or, better still, drop this file altogether, because you won't need it.
*/





#ifndef _porttypes_h
#define _porttypes_h

#include <sys/types.h>

#ifndef HDFI_H

typedef int8_t     int8;
typedef int8_t     char8;
typedef u_int8_t   uint8;
typedef u_int8_t   uchar8;
typedef int16_t    int16;
typedef u_int16_t  uint16;
typedef int32_t    int32;
typedef u_int32_t  uint32;

typedef float      float32;
typedef double     float64;

#endif

typedef unsigned char uchar_t;

#endif /* _porttypes_h */



