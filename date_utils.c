/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

#include "date_utils.h"

/* returns the time converted into a time_t value.
 * On error (time_t) -1 is returned.
 * Note that this function is specific for the following format:
 * "10/May/2004:04:15:33". Works if the month is not an abbreviation, or if the
 * year is abbreviated to only the last two digits.
 * The time can be omitted like in "10/May/2004". */
time_t parse_date(char *s, struct tm *tmptr, int time_delta)
{
  struct tm tm;
  time_t t;
  char *months[] = {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec",
  };
  char *day, *month, *year, *time = NULL;
  char monthaux[32];
  int i, len;

  /* make a copy to mess with it */
  len = strlen(s);
  if (len >= 32) goto fmterr;
  memcpy(monthaux, s, len);
  monthaux[len] = '\0';

  /* Inizialize the tm structure. We just fill three fields */
  tm.tm_sec = 0;
  tm.tm_min = 0;
  tm.tm_hour = 0;
  tm.tm_mday = 0;
  tm.tm_mon = 0;
  tm.tm_year = 0;
  tm.tm_wday = 0;
  tm.tm_yday = 0;
  tm.tm_isdst = -1;

  /* search delimiters */
  day = monthaux;
  if ((month = strchr(day, '/')) == NULL) goto fmterr;
  *month++ = '\0';
  if ((year = strchr(month, '/')) == NULL) goto fmterr;
  *year++ = '\0';
  /* time, optional for this parser. */
  if ((time = strchr(year, ':')) != NULL) {
    *time++ = '\0';
  }
  /* convert day */
  tm.tm_mday = atoi(day);
  if (tm.tm_mday < 1 || tm.tm_mday > 31) goto fmterr;
  /* convert month */
  if (strlen(month) < 3) goto fmterr;
  month[0] = tolower(month[0]);
  month[1] = tolower(month[1]);
  month[2] = tolower(month[2]);
  for (i = 0; i < 12; i++) {
    if (memcmp(month, months[i], 3) == 0) break;
  }
  if (i == 12) goto fmterr;
  tm.tm_mon = i;
  /* convert year */
  tm.tm_year = atoi(year);
  if (tm.tm_year > 100) {
    if (tm.tm_year < 1900 || tm.tm_year > 2500) goto fmterr;
    tm.tm_year -= 1900;
  } else {
    /* if the year is in two-digits form, the 0 - 68 range
     * is converted to 2000 - 2068 */
    if (tm.tm_year < 69)
      tm.tm_year += 100;
  }
  /* convert time */
  if (time) { /* format is HH:MM:SS */
    if (strlen(time) < 8) goto fmterr;
    tm.tm_hour = ((time[0]-'0')*10)+(time[1]-'0');
    if (tm.tm_hour < 0 || tm.tm_hour > 23) goto fmterr;
    tm.tm_min = ((time[3]-'0')*10)+(time[4]-'0');
    if (tm.tm_min < 0 || tm.tm_min > 59) goto fmterr;
    tm.tm_sec = ((time[6]-'0')*10)+(time[7]-'0');
    if (tm.tm_sec < 0 || tm.tm_sec > 60) goto fmterr;
  }
  t = mktime(&tm);
  if (t == (time_t)-1) goto fmterr;
  t += time_delta * 3600;
  if (tmptr) {
    struct tm *auxtm;

    if ((auxtm = localtime(&t)) != NULL)
      *tmptr = *auxtm;
  }
  return t;

 fmterr: /* format error */
  return (time_t) -1;
}

/* returns 1 if the given date is Saturday or Sunday.
 * Zero is otherwise returned. */
int vi_is_weekend(char *s, int time_delta)
{
  struct tm tm;

  if (parse_date(s, &tm, time_delta) != (time_t)-1) {
    if (tm.tm_wday == 0 || tm.tm_wday == 6)
      return 1;
  }
  return 0;
}

#if 0
/* Returns true if 'year' is a leap year. */
int isleap(int year)
{
  int conda, condb, condc;

  conda = (year % 4) == 0;
  condb = (year % 100) == 0;
  condc = (year % 400) == 0;
  return conda && !(condb && !condc);
}
#endif
