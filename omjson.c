/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

/* -------------------------- json output module ------------------------ */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <err.h>
#include "config.h"

#include <glib.h>

/*
*
* Note: the strings returned by escape and id are not freed. As long as we
*  create only a few objects at the end of the statistics, this leak should
*  not have practical consequences
*
*/

void init_omjson()
{
  char *loc = setlocale(LC_CTYPE, "");
  if (loc == NULL)
    err(1, "Could not set LC_CTYPE to local value");
  if (strcasestr(loc, "utf8") == NULL && strcasestr(loc, "utf-8") == NULL)
    errx(1, "LC_CTYPE %s does not seem to use UTF-8", loc);
}

// Taken from glib-json-1.0

/* non-ASCII characters can't be escaped, otherwise UTF-8
 * chars will break, so we just pregenerate this table of
 * high characters and then we feed it to g_strescape()
 */
static const char json_exceptions[] = {
  0x7f,  0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,
  0x87,  0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,
  0x8f,  0x90,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
  0x97,  0x98,  0x99,  0x9a,  0x9b,  0x9c,  0x9d,  0x9e,
  0x9f,  0xa0,  0xa1,  0xa2,  0xa3,  0xa4,  0xa5,  0xa6,
  0xa7,  0xa8,  0xa9,  0xaa,  0xab,  0xac,  0xad,  0xae,
  0xaf,  0xb0,  0xb1,  0xb2,  0xb3,  0xb4,  0xb5,  0xb6,
  0xb7,  0xb8,  0xb9,  0xba,  0xbb,  0xbc,  0xbd,  0xbe,
  0xbf,  0xc0,  0xc1,  0xc2,  0xc3,  0xc4,  0xc5,  0xc6,
  0xc7,  0xc8,  0xc9,  0xca,  0xcb,  0xcc,  0xcd,  0xce,
  0xcf,  0xd0,  0xd1,  0xd2,  0xd3,  0xd4,  0xd5,  0xd6,
  0xd7,  0xd8,  0xd9,  0xda,  0xdb,  0xdc,  0xdd,  0xde,
  0xdf,  0xe0,  0xe1,  0xe2,  0xe3,  0xe4,  0xe5,  0xe6,
  0xe7,  0xe8,  0xe9,  0xea,  0xeb,  0xec,  0xed,  0xee,
  0xef,  0xf0,  0xf1,  0xf2,  0xf3,  0xf4,  0xf5,  0xf6,
  0xf7,  0xf8,  0xf9,  0xfa,  0xfb,  0xfc,  0xfd,  0xfe,
  0xff,
  '\0'   /* g_strescape() expects a NUL-terminated string */
};

static gchar *
json_strescape(const gchar *str)
{
  return g_strescape(str, json_exceptions);
}

// end glib-json-1.0

// Truncates s at the first character that could not be decoded as UTF-8. The
// locale must have been set up to use UTF-8 for this function to work.
void utf8_truncate(char *s)
{
  int ch_len;
  mbstate_t ps;
  memset(&ps, 0, sizeof(ps));
  while ((ch_len = mbrlen(s, MB_CUR_MAX, &ps)) > 0)
    s += ch_len;
  *s = '\0';
}

// Turn s into a JSON string. Allocates a new string.
// Replaces '\b', '\f', '\n', '\r', '\t', '\' and '"' with a '\'
// sequence. Other control characters are converted to their octal
// representation "\0xy". To ensure valid UTF-8 is produced, the result is then
// truncated at the first character that could not be decoded as UTF-8.
// Note: we assume the input is UTF-8 because we cannot guess easily the
// original encoding of the string (it can be a URL found in a log, a search
// query, etc.).
char *escape(const char *s)
{
  char *t = strdup(s);
  utf8_truncate(t);
  return json_strescape(t);
}

// Turn s into a suitable JSON field identifier, that is, a JSON string.
char *id(const char *s)
{
  return escape(s);
}

// hack to put a comma only after a previous member
int first_object_member;

void maybe_print_comma_nl(FILE *fp, int first_item)
{
  if (first_item)
    fprintf(fp, "\n");
  else
    fprintf(fp, ",\n");
}

void om_json_print_header(FILE *fp)
{
  fprintf(fp, "{\n\"version\": \"%s\"", VI_VERSION_STR);
}

void om_json_print_footer(FILE *fp)
{
  fprintf(fp, "\n}\n");
}

void om_json_print_title(FILE *fp, char *title)
{
  fprintf(fp, ",\n\"%s\": {", id(title));
  first_object_member = 1;
}

void om_json_close_title(FILE *fp)
{
  fprintf(fp, "\n}");
}

void om_json_print_subtitle(FILE *fp, char *subtitle)
{
  (void)fp;
  (void)subtitle;
}

void om_json_print_numkey_info(FILE *fp, char *key, int val)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %d", id(key), val);
  first_object_member = 0;
}

void om_json_print_dblkey_info(FILE *fp, char *key, double val)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %f", id(key), val);
  first_object_member = 0;
}

void om_json_print_strkey_info(FILE *fp, char *key, char *val)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": \"%s\"", id(key), escape(val));
  first_object_member = 0;
}

// TODO get rid of num? seems to be only used to count from 1
void om_json_print_keykey_entry(FILE *fp, char *key1, char *key2, int num)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%d\": [\"%s\", \"%s\"]", num, escape(key1), escape(key2));
  first_object_member = 0;
}

void om_json_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num)
{
  (void)link;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%d\": [\"%s\", %d]", num, escape(key), val);
  first_object_member = 0;
}

void om_json_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta)
{
  (void)max, (void)tot, (void)time_delta;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %d", id(key), this);
  first_object_member = 0;
}

void om_json_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta)
{
  (void)tot, (void)time_delta;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %d", id(key), this);
  first_object_member = 0;
}

void om_json_print_bidimentional_map(FILE *fp, int xlen, int ylen,
                                     char **xlabel, char **ylabel, int *value)
{
  (void)xlabel;
  int x, y;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"map\": [\n");
  for (y = 0; y < ylen; y++) {
    if (y > 0)
      fprintf(fp, ",\n");
    fprintf(fp, "[\"%s\", [", escape(ylabel[y]));
    for (x = 0; x < xlen; x++) {
      if (x > 0)
        fprintf(fp, ", ");
      fprintf(fp, "%d", value[y * xlen + x]);
    }
    fprintf(fp, "]]");
  }
  fprintf(fp, "]");
  first_object_member = 0;
}

void om_json_print_hline(FILE *fp)
{
  (void)fp;
}

void om_json_print_credits(FILE *fp)
{
  (void)fp;
}

void om_json_print_report_link(FILE *fp, char *report)
{
  (void)fp;
  (void)report;
}
