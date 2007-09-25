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


/* safety.c -- part of libsafe.a
   Functions for allocating and use of resources with
   error checking.  All functions keep their traditional names
   postfixed by _check.

   Author:  LBS
   History: 17 Sep 1997, Creation
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "safety.h"

FILE*  fopen_check(const char*, const char*);
size_t fread_check(void*, size_t, size_t, FILE*);
void*  malloc_check(size_t);
char*  strdup_check(const char*);
void  _memusage();

static void simpleError(const char*);
static int mem=0;

FILE *fopen_check(const char* name, const char* type)
{
  FILE *fp;

  if (!(fp=fopen(name,type))) {
    fflush(NULL);
    fprintf(stderr,"\nError (fatal): Could not open file %s.\n",name);
    exit(1);
  }

  return fp;
}

size_t fread_check(void *ptr, size_t size, size_t nitems, FILE *stream)
{
  size_t ret;

  ret=fread(ptr,size,nitems,stream);
  if (ferror(stream)) {
    fflush(NULL);
    fprintf(stderr,"\nError: File read error.\n");
    exit(1);
  }
  if (feof(stream)) {
    fflush(NULL);
    fprintf(stderr,"\nError: Unexpected end of file.\n");
    exit(1);
  }

  return ret;
}

void* malloc_check(size_t sz)
{
  void *p=malloc(sz);

  if (!p) {
    fflush(NULL);
    fprintf(stderr,"\nError: Out of memory error. Exiting.\n");
    exit(1);
  }

  mem+=sz;
  return p;
}

char* strdup_check(const char* s)
{
  char* t;

  if (!(t=strdup(s))) {
    fflush(NULL);
    fprintf(stderr,"\nError: Out of memory error. Exiting.\n");
    exit(1);
  }

  mem+=strlen(t);
  return t;
}

void _memusage()
{
  printf("Value of mem: %d\n",mem);
}

static void simpleError(const char* error)
{
  fflush(NULL);
  fprintf(stderr,error);
  exit(1);
}
