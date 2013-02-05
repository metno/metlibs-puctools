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


/* timemanip.c -- part of libtimemanip.a

   Functions for manipulation of a simple time type (defined in
   accompanying header file).

   The date functions are based on P. Meyer: `Julian and Gregorian
   Calendars', Dr. Dobbs J., March 1993, but restricted to the
   Gregorian calendar.

   Author:  Lars Brusletto Sveen
   History: 18 Sep 1997: Creation
            Nov. 1998: Prepared for /usr/local/lib */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "timemanip.h"
#include <string.h>

/* Month lengths */
static int ml[13]= {
  0,31,28,31,30,31,30,
  31,31,30,31,30,31
};

/* Accumulated month lenghts for normal and leap years */
static int cum_ml[2][16]={
  {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 400, 0},
  {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 400, 0}};

/* Is a given year a leap year or not? */
static int isLeap(const int y)
{ return ((y%4==0 && y%100!=0) || y%400==0); }

/* Floor function for long integers (assumes b positive) */
static long lfloor(const long a, const long b)
{ return a>=0? a/b: (a%b==0)-1-labs(a)/b; }

static int isValidTime(const struct time* t)
{
  int val=1;

  ml[2]+=isLeap(t->year);
  
  if (t->month<1 || t->month>12 ||
      t->day<0 || t->day>ml[t->month] ||
      t->hour<0 || t->hour>23 ||
      t->minute<0 || t->minute>59 ||
      t->second<0 || t->second>59)
    val=0;
  
  ml[2]-=isLeap(t->year);

  return val;
}

static long timetogdn(const struct time* t)
{
  long dn;
  char *cp=NULL;

  if (!isValidTime(t)) {
    fprintf(stderr,"puCtools (timemanip) error: %s is not a valid time.\n",
	    cp=isoTime(t));
    free(cp);
  }

  dn=((long)t->year-1)*365L + lfloor((long)t->year-1,4L) +
    lfloor((long)t->year-1,400L) - lfloor((long)t->year-1,100L) +
    cum_ml[isLeap(t->year)][t->month] + t->day - 1;

  return dn;
}

/* Add d days to the date specified in t and return the resulting date
   as t. The Gregorian calendar system is assumed. Leap years are of
   course handled correctly. The algorithm computes the date using the
   Julian day number (dn, computed from timetogdn above), i.e. the
   number of days that have passed since 1 Jan 4713 BCE (Julian date).
*/
void timeAddDay(struct time* t, int d)
{
  long y400=146097;
  long y100=36524;
  long y4=1461;
  long dn=timetogdn(t)+d;

  int exception=0;

  t->year=400*lfloor(dn,y400);
  dn-=y400*lfloor(dn,y400);

  if (dn>0) {
    t->year+=100*lfloor(dn,y100);
    dn-=y100*lfloor(dn,y100);
    exception=(dn==0);
    if (dn>0) {
      t->year+=4*lfloor(dn,y4);
      dn-=y4*lfloor(dn,y4);
      if (dn>0) {
	int i=0;
	while (dn>365 && ++i<4) {
	  t->year++;
	  dn-=365;
	}
      }
    }
  }

  if (exception)
    dn=366;
  else {
    t->year++;
    dn++;
  }

  t->month=1;
  while (cum_ml[isLeap(t->year)][t->month]<dn)
    t->month++;
  t->month--;
  dn-=cum_ml[isLeap(t->year)][t->month];
  if (t->month==13) {
    t->month=1;
    t->year++;
  }

  t->day=dn;
}

/* The functions timeAdd{Hour, Minute, Second} quite simply add the
   specified number of time units and call functions higher in the
   hierarchy if nescessary.
*/
void timeAddHour(struct time* t, int h)
{
  int ndays=0;

  t->hour+=h;
  if (t->hour>=0)
    while (t->hour>23) {
      ndays++;
      t->hour-=24;
    }
  else
    while (t->hour<0) {
      ndays--;
      t->hour+=24;
    }

  if (ndays!=0)
    timeAddDay(t,ndays);
}

void timeAddMinute(struct time* t, int m)
{
  int nhours=0;

  t->minute+=m;
  if (t->minute>=0)
    while (t->minute>59) {
      nhours++;
      t->minute-=60;
    }
  else
    while (t->minute<0) {
      nhours--;
      t->minute+=60;
    }

  if (nhours!=0)
    timeAddHour(t,nhours);
}

void timeAddSecond(struct time* t, int s)
{
  int nminutes=0;

  t->second+=s;
  if (t->second>=0)
    while (t->second>59) {
      nminutes++;
      t->second-=60;
    }
  else
    while (t->second<0) {
      nminutes--;
      t->second+=60;
    }

  if (nminutes!=0)
    timeAddMinute(t,nminutes);
}

/* timecmp -- lexicographical comparison of two time structs */

int timecmp(const struct time* s, const struct time* t)
{
  long dns=timetogdn(s);
  long dnt=timetogdn(t);
  long sns=s->hour*3600+s->minute*60+s->second;
  long snt=t->hour*3600+t->minute*60+t->second;

  if (dns!=dnt)
    return dns>dnt? 1: -1;
  return sns>snt? 1: (sns==snt? 0: -1);
}

/* Return the time difference between s and t in hours */

long hourDiff(struct time* s, struct time* t)
{
  return (timetogdn(s)-timetogdn(t))*24L + s->hour-t->hour;
}

/* Give a string representation of t in ISO format. If any of the
   members of t are out of range, this routine will most likely crash
*/

char* isoTime(const struct time* t)
{
  int a;
  char* c;

  /* Compute size of string */
  a=((float)(log10((float)(abs(t->year)))+1)); /* year */
  if (a<4)
    a=4;
  if (t->year<0)
    a++;
  a+=16;

  if ((c=malloc(a)))
    sprintf(c,"%04d-%02d-%02d %02d:%02d:%02d",
	    t->year, t->month, t->day, t->hour, t->minute, t->second);
  else
    fprintf(stderr,"timemanip (isoTime): Memory allocation failed.\n");

  return c;
}

struct time* copyTime(const struct time* t)
{
  struct time* newt=malloc_check(sizeof(struct time));

  if (newt) {
    newt->year=t->year;
    newt->month=t->month;
    newt->day=t->day;
    newt->hour=t->hour;
    newt->minute=t->minute;
    newt->second=t->second;
  }
  else
    fprintf(stderr,"timemanip (copyTime): Memory allocation failed.\n");
    
  return newt;
}

struct time* isostr2time(const char* s)
{
  struct time* t=malloc_check(sizeof(struct time));

  if (t) {
    if (s && strlen(s)==19){
      sscanf(s,"%04d-%02d-%02d %02d:%02d:%02d",
	     &t->year, &t->month, &t->day, &t->hour, &t->minute, &t->second);
    } else {
      fprintf(stderr,"timemanip (isostr2time): Illegal input.\n");
      t->year = t->month = t->day = t->hour = t->minute = t->second = 0;
    }
  }
  else
    fprintf(stderr,"timemanip (isostr2time): Memory allocation failed.\n");
    
  return t;
}

struct time* str2time(const char* s)
{
  struct time* t=malloc_check(sizeof(struct time));

  if (t) {
    if (s && strlen(s)==14){
      sscanf(s,"%04d%02d%02d%02d%02d%02d",
	     &t->year, &t->month, &t->day, &t->hour, &t->minute, &t->second);
    } else {
      fprintf(stderr,"timemanip (str2time): Illegal input.\n");
      t->year = t->month = t->day = t->hour = t->minute = t->second = 0;
    }
  }
  else
    fprintf(stderr,"timemanip (str2time): Memory allocation failed.\n");
    
  return t;
}

struct time* comps2time(const char* s1,const char* s2,const char* s3,
			const char* s4,const char* s5,const char* s6)
{
  struct time* t=malloc_check(sizeof(struct time));

  if (t) {
    t->year=atoi(s1);
    t->month=atoi(s2);
    t->day=atoi(s3);
    t->hour=atoi(s4);
    t->minute=atoi(s5);
    t->second=atoi(s6);
  }
  else
    fprintf(stderr,"timemanip (comps2time): Memory allocation failed.\n");
    
  return t;
}

int dayOfYear(struct time* t)
{ return cum_ml[isLeap(t->year)][t->month]+t->day; }
