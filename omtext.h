/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

#ifndef _OMTEXT_H
#define _OMTEXT_H

#include "om.h"

void om_text_print_header(FILE *fp);
void om_text_print_footer(FILE *fp);
void om_text_print_title(FILE *fp, char *title);
void om_text_close_title(FILE *fp);
void om_text_print_subtitle(FILE *fp, char *title);
void om_text_print_numkey_info(FILE *fp, char *key, int val);
void om_text_print_dblkey_info(FILE *fp, char *key, double val);
void om_text_print_strkey_info(FILE *fp, char *key, char *val);
void om_text_print_keykey_entry(FILE *fp, char *key1, char *key2, int num);
void om_text_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num);
void om_text_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta);
void om_text_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta);
void om_text_print_bidimentional_map(FILE *fp, int xlen, int ylen,
                                     char **xlabel, char **ylabel, int *value);
void om_text_print_hline(FILE *fp);
void om_text_print_credits(FILE *fp);
void om_text_print_report_link(FILE *fp, char *report);

struct outputmodule OutputModuleText = {
  om_text_print_header,
  om_text_print_footer,
  om_text_print_title,
  om_text_close_title,
  om_text_print_subtitle,
  om_text_print_numkey_info,
  om_text_print_dblkey_info,
  om_text_print_strkey_info,
  om_text_print_keykey_entry,
  om_text_print_numkey_entry,
  om_text_print_numkeybar_entry,
  om_text_print_numkeycomparativebar_entry,
  om_text_print_bidimentional_map,
  om_text_print_hline,
  om_text_print_credits,
  om_text_print_report_link,
};

#endif
