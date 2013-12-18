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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stringmanip.h"

/* Function rtrim:
   Remove trailing blanks from a string and pad with \0s. */

void rtrim(char *s)
{
  int i;

  for (i=strlen(s)-1; isspace(*(s+i)) && i>=0; *(s+i--)='\0')
    ;
}

/* Function trim:
   Remove trailing and initial blanks from s */
void trim(char* s)
{
  char* nonspace;

  if (!s)
    return;

  rtrim(s);

  if (isspace(*s)) {
    for (nonspace=s; isspace(*nonspace); nonspace++)
      ;
    while ((*s++=*nonspace++))
      ;
  }
}
      
/* Function vsrtrcat.
   Returns a pointer to a concatenation of an arbitrary number of
   strings. Memory should be freed by the calling function. The code
   is a theft from the comp.lang.c faq. */

char *vstrcat(char *first, ...)
{
  size_t  len=0;
  char    *p, *ret;
  va_list argp;
  
  if (!first)
    return NULL;
  len=strlen(first);

  va_start(argp,first);
  while((p=va_arg(argp, char *)))
    len+=strlen(p);
  va_end(argp);

  ret=malloc_check((len+1)*sizeof(char));

  strcpy(ret,first);

  va_start(argp, first);
  while((p=va_arg(argp, char *)))
    strcat(ret,p);
  va_end(argp);

  return ret;
}
