/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

#ifndef _DATE_UTILS_H
#define _DATE_UTILS_H

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

time_t parse_date(char *s, struct tm *tmptr, int time_delta);
int vi_is_weekend(char *s, int time_delta);

#endif
