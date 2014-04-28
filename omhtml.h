#ifndef _OMHTML_H
#define _OMHTML_H

void om_html_entities_abbr(FILE *fp, char *s, int maxlen);
void om_html_entities(FILE *fp, char *s);
void om_html_print_header(FILE *fp);
void om_html_print_footer(FILE *fp);
void om_html_print_title(FILE *fp, char *title);
void om_html_close_title(FILE *fp);
void om_html_print_subtitle(FILE *fp, char *subtitle);
void om_html_print_numkey_info(FILE *fp, char *key, int val);
void om_html_print_dblkey_info(FILE *fp, char *key, double val);
void om_html_print_strkey_info(FILE *fp, char *key, char *val);
void om_html_print_keykey_entry(FILE *fp, char *key1, char *key2, int num);
void om_html_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num);
void om_html_print_bar(FILE *fp, int l, char *leftclass, char *rightclass);
void om_html_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta);
void om_html_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta);
void om_html_print_bidimentional_map(FILE *fp, int xlen, int ylen,
                                     char **xlabel, char **ylabel, int *value);
void om_html_print_hline(FILE *fp);
void om_html_print_credits(FILE *fp);
void om_html_print_report_link(FILE *fp, char *report);

struct outputmodule OutputModuleHtml = {
  om_html_print_header,
  om_html_print_footer,
  om_html_print_title,
  om_html_close_title,
  om_html_print_subtitle,
  om_html_print_numkey_info,
  om_html_print_dblkey_info,
  om_html_print_strkey_info,
  om_html_print_keykey_entry,
  om_html_print_numkey_entry,
  om_html_print_numkeybar_entry,
  om_html_print_numkeycomparativebar_entry,
  om_html_print_bidimentional_map,
  om_html_print_hline,
  om_html_print_credits,
  om_html_print_report_link,
};

#endif
