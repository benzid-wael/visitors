/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

/* -------------------------- json output module ------------------------ */

#include <stdio.h>
#include "om.h"
#include "config.h"


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
  fprintf(fp, ",\n\"%s\": {", title);
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
  fprintf(fp, "\"%s\": %d", key, val);
  first_object_member = 0;
}

void om_json_print_dblkey_info(FILE *fp, char *key, double val)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %f", key, val);
  first_object_member = 0;
}

void om_json_print_strkey_info(FILE *fp, char *key, char *val)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": \"%s\"", key, val);
  first_object_member = 0;
}

// TODO get rid of num? seems to be only used to count from 1
void om_json_print_keykey_entry(FILE *fp, char *key1, char *key2, int num)
{
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%d\": [\"%s\", \"%s\"]", num, key1, key2);
  first_object_member = 0;
}

void om_json_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num)
{
  (void)link;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%d\": [\"%s\", %d]", num, key, val);
  first_object_member = 0;
}

void om_json_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta)
{
  (void)max, (void)tot, (void)time_delta;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %d", key, this);
  first_object_member = 0;
}

void om_json_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta)
{
  (void)tot, (void)time_delta;
  maybe_print_comma_nl(fp, first_object_member);
  fprintf(fp, "\"%s\": %d", key, this);
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
    fprintf(fp, "[\"%s\", [", ylabel[y]);
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
