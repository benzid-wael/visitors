#ifndef _DATE_UTILS_H
#define _DATE_UTILS_H

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

time_t parse_date(char *s, struct tm *tmptr, int time_delta);
int vi_is_weekend(char *s, int time_delta);

#endif
