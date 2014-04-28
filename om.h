#ifndef _OUTPUT_H
#define _OUTPUT_H

/* output module structure. See below for the definition of
 * the text and html output modules. */
struct outputmodule {
  void (*print_header)(FILE *fp);
  void (*print_footer)(FILE *fp);
  void (*print_title)(FILE *fp, char *title);
  void (*close_title)(FILE *fp);
  void (*print_subtitle)(FILE *fp, char *title);
  void (*print_numkey_info)(FILE *fp, char *key, int val);
  void (*print_dblkey_info)(FILE *fp, char *key, double val);
  void (*print_strkey_info)(FILE *fp, char *key, char *val);
  void (*print_keykey_entry)(FILE *fp, char *key1, char *key2, int num);
  void (*print_numkey_entry)(FILE *fp, char *key, int val, char *link,
                             int num);
  void (*print_numkeybar_entry)(FILE *fp, char *key, int max, int tot,
                                int this, int time_delta);
  void (*print_numkeycomparativebar_entry)(FILE *fp, char *key, int tot,
                                           int this, int time_delta);
  void (*print_bidimentional_map)(FILE *fp, int xlen, int ylen,
                                  char **xlabel, char **ylabel, int *value);
  void (*print_hline)(FILE *fp);
  void (*print_credits)(FILE *fp);
  void (*print_report_link)(FILE *fp, char *report);
};

#endif
