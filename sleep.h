/* $Id$ */
#ifndef SLEEP_H_INCLUDED
#define SLEEP_H_INCLUDED

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned long pu_usleep(unsigned long);
unsigned long pu_msleep(unsigned long);
unsigned long pu_sleep(unsigned long);

#ifdef __cplusplus
}
#endif

#endif
