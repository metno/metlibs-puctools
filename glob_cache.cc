/*	$OpenBSD: glob.c,v 1.26 2005/11/28 17:50:12 deraadt Exp $ */
/*	$Id: glob.c 3237 2010-04-29 10:17:13Z stefan.fagerstrom@smhi.se $	*/
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* Imported into metlibs from OpenSSH 5.3p1 */
/* OPENBSD ORIGINAL: lib/libc/gen/glob.c */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>

#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#if HAVE_PWD_H
#include <pwd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "glob_cache.h"
#include "stat.h"
#include "strlcpy.h"

#include <time.h>
#include <sys/time.h>

#include <string>
#include <map>


#define M_TIME 1

using namespace std;

// Default constructor

static std::map<std::string, glob_cache_t > glob_map;
//std::map<std::string, glob_cache_t > glob_map = init_glob_map();
/*
std::map<std::string, glob_cache_t > init_glob_map()
{
	std::map<std::string, glob_cache_t > tmpmap;
	tmpmap.clear();
	return tmpmap;
}
*/
#ifndef WIN32
/** small helper function, copies only a part of a string into another
 * (we append a 0 in contrary to strncpy)
 */
static inline void strcpypart(char* dest, const char* src, size_t size)
{
    memcpy(dest, src, size);
    dest[size] = 0;
}

/** Unix version of the _splitpath functions which breaks a path into it's
 * components. (Warning: Don't use in your own code, you're asking for security
 * problems (buffer overflow)
 */
void _splitpath(const char* path, char* drive, char* dir,
                char* fname, char* ext)
{
    // Step1: Fill in driver ("" on unix systems since we don't have drives)
    if(drive)
        strcpy(drive, "");

    // Step1: find the last slash in the path
    const char* lastslash = 0;
    for(const char* p = path; *p != '\0'; p++) {
        if(*p == '/')
            lastslash = p;
    }
    // now fill in directory
    if(dir) {
        if(lastslash == 0)
            strcpy(dir, "");
        else
            strcpypart(dir, path, lastslash - path + 1);
    }

    // Step2: Get the (last) dot in the filename
    const char* lastdot = 0;
    const char* begin = (lastslash != 0) ? lastslash+1 : path;
    for(const char* p = begin; *p != '\0'; p++) {
        if(*p == '.')
            lastdot = p;
    }
    // now we can fill in filename and extension
    if(lastdot==0) {
        if(fname)
            strcpy(fname, begin);
        if(ext)
            strcpy(ext, "");
    } else {
        if(fname)
            strcpypart(fname, begin, lastdot - begin);
        if(ext)
            strcpy(ext, lastdot);
    }

}

#endif

/* Free allocated data belonging to a glob_t structure. */
void
_glob_cache_free(glob_cache_t *pglob)
{

	int i;
	char **pp;

	if (pglob->gl_pathv != NULL) {
		pp = pglob->gl_pathv + pglob->gl_offs;
		for (i = pglob->gl_pathc; i--; ++pp)
			if (*pp)
				free(*pp);
		free(pglob->gl_pathv);
		pglob->gl_pathv = NULL;
	}
}

// dummy implementation just in case
void
globfree_cache(glob_t *)
{
	// just a dummy
}

int
glob_cache(const char *pattern, int flags, int (*errfunc)(const char *, int),
    glob_t *pglob)
{

  // all is well
  int use_loghandler = 1;
  milogger::LogHandler * plog = milogger::LogHandler::getInstance();
  if (plog)
	  plog->setObjectName("metlibs.puCtools.glob_cache");
  else
	  use_loghandler = 0;
  int result = 0;
#ifdef DEBUGPRINT
  if (use_loghandler)
	  COMMON_LOG::getInstance("common").debugStream() << "pattern: " << pattern;
  else
	  printf ("glob_cache pattern: %s\n",pattern);
#endif

  // Lets get the directory part of pattern
  char drive[2];
  char dir[PATH_MAX+1];
  char fname[PATH_MAX+1];
  char ext[PATH_MAX+1];

  _splitpath(pattern, drive, dir, fname, ext);

#ifdef DEBUGPRINT
  if (use_loghandler)
	  COMMON_LOG::getInstance("common").debugStream() << "Splitted Path : " << pattern << " - " << drive << " - " << dir << " - " << fname << " - " << ext;
  else
	  printf ("Splitted Path : %s => %s - %s - %s - %s.\n", pattern,
    		drive, dir, fname, ext);
#endif

  glob_cache_t glob_res;

  // search for pattern in cache
  map< string, glob_cache_t >::iterator its = glob_map.find(pattern);
  if (its != glob_map.end())
  {
  	// Pattern was globbed before
	glob_res = its->second;
	// check if directory has changed
	pu_struct_stat stat_buf;
	int sres = pu_stat(dir, &stat_buf);
	if (!sres)
	{
		// directory has changed ?
		if (stat_buf.st_mtim.tv_sec > glob_res.mod_time.tv_sec)
		{
			// free the old gl_pathv, use an internal function
			_glob_cache_free(&glob_res);
			// do the usual glob and save the result in cahce
			#ifdef M_TIME
			  struct timeval pre;
			  struct timeval post;
			  gettimeofday(&pre, NULL);
			#endif
			    result = glob(pattern, flags, errfunc, pglob);
			#ifdef M_TIME
			  gettimeofday(&post, NULL);
			  double s = (((double)post.tv_sec*1000000.0 + (double)post.tv_usec)-((double)pre.tv_sec*1000000.0 + (double)pre.tv_usec))/1000000.0;
			  if (use_loghandler)
				  if (use_loghandler)
				  {
//				  	COMMON_LOG::getInstance("common").debugStream() << "glob_cache done in: " << s << " s";
//				    COMMON_LOG::getInstance("common").debugStream().flush();
				  }
			  else
				  printf ("glob_cache done in: %f s\n",s);
			#endif
			glob_res.gl_offs = pglob->gl_offs;
			glob_res.gl_pathc = pglob->gl_pathc;
			glob_res.gl_pathv = pglob->gl_pathv;
			glob_res.mod_time = stat_buf.st_mtim;
			// update cache
			glob_map[pattern] = glob_res;
			return result;
		}
		else
		{
			//No change, resturn the cached information in pglob
			pglob->gl_pathc = glob_res.gl_pathc;
			pglob->gl_offs = glob_res.gl_offs;
			pglob->gl_pathv = glob_res.gl_pathv;
			return result;
		}
	}
	else
	{
		return GLOB_ABORTED;
	}

  }
  else
  {
	  // do the usual glob and save the result in cahce
#ifdef M_TIME
  struct timeval pre;
  struct timeval post;
  gettimeofday(&pre, NULL);
#endif
    result = glob(pattern, flags, errfunc, pglob);
#ifdef M_TIME
  gettimeofday(&post, NULL);
  double s = (((double)post.tv_sec*1000000.0 + (double)post.tv_usec)-((double)pre.tv_sec*1000000.0 + (double)pre.tv_usec))/1000000.0;
  if (use_loghandler)
  {
//	  COMMON_LOG::getInstance("common").debugStream() << "glob_cache done in: " << s << " s";
//  	  COMMON_LOG::getInstance("common").debugStream().flush();
  }
  else
	  printf ("glob_cache done in: %f s\n",s);
#endif
    // some globbing error
    if (result)
    	return result;

  	pu_struct_stat stat_buf;
  	int sres = pu_stat(dir, &stat_buf);
  	if (!sres)
  	{
  		glob_res.gl_offs = pglob->gl_offs;
  		glob_res.gl_pathc = pglob->gl_pathc;
  		glob_res.gl_pathv = pglob->gl_pathv;
  		glob_res.mod_time = stat_buf.st_mtim;
  		// add to cache
  		glob_map[pattern] = glob_res;
  		return result;
  	}
  	else
  	{
  		return GLOB_ABORTED;
  	}

  } // End previous glob

	return result;
}

