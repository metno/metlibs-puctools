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


/* timemanip.h

   Interface for a set of basic time handling functions.  A simple
   struct time is defined together with functions for
   addition/subtraction of days, hours, minutes and seconds.
   And yes, it's `Year 2000 compliant'.

   Author:  Lars Brusletto Sveen, met.no/FoU
   History: 18 Sep 1997: Creation
*/

#ifndef _timemanip_h
#define _timemanip_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "safety.h"

#ifdef __cplusplus
extern "C" {
#endif

struct time {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
};

/* Add a time unit to a time struct: */
extern void timeAddDay(struct time*,int);
extern void timeAddHour(struct time*,int);
extern void timeAddMinute(struct time*,int);
extern void timeAddSecond(struct time*,int);

/* Return difference between two times in hours */
extern long hourDiff(struct time*, struct time*);

/* Lexical comparison of time structs */
extern int timecmp(const struct time*,const struct time*);

/* String format (ISO standard) */
extern char* isoTime(const struct time*);

/* time from String format (ISO standard) */
extern struct time* isostr2time(const char*);

/* time from String format (YYYYMMDDhhmmss) */
extern struct time* str2time(const char*);

/* time from String components */
  extern struct time* comps2time(const char*,const char*,const char*,
				 const char*,const char*,const char*);

/* Return a copy of the input */
extern struct time* copyTime(const struct time*);

/* Day number */
extern int dayOfYear(struct time*);
#ifdef __cplusplus
}
#endif

#endif
