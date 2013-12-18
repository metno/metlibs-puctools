/*
  libpuCtools - Basic C-Tools
  
  $Id$

  Copyright (C) 2010 met.no

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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/time.h>

#include <time.h>
#include <unistd.h>

#include "sleep.h"

/*
 * Sleep for at least the specified amount of microseconds, unless
 * interrupted.  Returns the remaining amount of time if interrupted, and
 * otherwise 0.
 */
unsigned long
pu_usleep(unsigned long usec)
{
	struct timeval tv1, tv2;
	unsigned long usdiff;

	gettimeofday(&tv1, NULL);
	usleep(usec);
	gettimeofday(&tv2, NULL);
	if (tv2.tv_usec < tv1.tv_usec) {
		tv2.tv_sec -= 1;
		tv2.tv_usec += 1000000;
	}
	usdiff = (tv2.tv_sec - tv1.tv_sec) * 1000000;
	usdiff += tv2.tv_usec - tv1.tv_usec;
	return (usdiff > usec ? 0 : usec - usdiff);
}

/*
 * As above, but in milliseconds.
 */
unsigned long
pu_msleep(unsigned long msec)
{

	return (pu_usleep(msec * 1000UL) / 1000UL);
}

/*
 * As above, but in seconds.
 */
unsigned long
pu_sleep(unsigned long sec)
{

	return (pu_usleep(sec * 1000000UL) / 1000000UL);
}
