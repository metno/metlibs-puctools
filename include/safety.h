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


/* safety.h
   Interface for a tiny collection of functions in which the standard
   functions for resource management are extended with error checking.

   Author:  LBS
   History: 17 Sep 1997: Creation
   Part of the puCtools kit
*/

#ifndef _safety_h
#define _safety_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

extern void*  malloc_check(size_t);
extern FILE*  fopen_check(const char*, const char*);
extern size_t fread_check(void*, size_t, size_t, FILE*);
extern char*  strdup_check(const char*);
extern void _memusage();

/* These are `unsafe' equivalents:
   #define fopen_check(A,B) (fopen((A),(B)))
   #define malloc_check(A) (malloc((A)))
   #define fread_check(A,B,C,D) (fread((A),(B),(C),(D)))
   #define strdup_check(A) (strdup((A)))*/

#ifdef __cplusplus
}
#endif

#endif /* _safety_h */
