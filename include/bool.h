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


/* File bool.h -- define a boolean type
   Languages: C and C++
   Author: LBS, 24 Feb 1998

   This is a substitutution for the bool.h shipped with the old version of
   SGI's STL implementation.  The difference is that the present file,
   because of the typedef, can be used with both old and new STL versions,
   wheras SGI's own file cannot.  If possible, use this file instead to insure
   compatability.
*/
#ifndef __cplusplus

#ifndef _bool_h
#define _bool_h

#ifndef _BOOL /* Check whether the compiler supports bool already */
typedef int bool;
#define true 1
#define false 0
#endif

#endif
#endif
