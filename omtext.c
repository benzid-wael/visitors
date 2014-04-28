/* ---------------------------- text output module -------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

void om_text_print_header(FILE *fp)
{
  (void)fp;
}

void om_text_print_footer(FILE *fp)
{
  (void)fp;
}

void om_text_print_title(FILE *fp, char *title)
{
  fprintf(fp, "=== %s ===\n", title);
}

void om_text_close_title(FILE *fp)
{
  (void)fp;
}

void om_text_print_subtitle(FILE *fp, char *subtitle)
{
  fprintf(fp, "--- %s\n", subtitle);
}

void om_text_print_numkey_info(FILE *fp, char *key, int val)
{
  fprintf(fp, "* %s: %d\n", key, val);
}

void om_text_print_dblkey_info(FILE *fp, char *key, double val)
{
  fprintf(fp, "* %s: %f\n", key, val);
}

void om_text_print_strkey_info(FILE *fp, char *key, char *val)
{
  fprintf(fp, "* %s: %s\n", key, val);
}

void om_text_print_keykey_entry(FILE *fp, char *key1, char *key2, int num)
{
  fprintf(fp, "%d)    %s: %s\n", num, key1, key2);
}

void om_text_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num)
{
  link = link; /* avoid warning. Text output don't use this argument. */
  fprintf(fp, "%d)    %s: %d\n", num, key, val);
}

/* Print a bar, c1 and c2 are the colors of the left and right parts.
 * Max is the maximum value of the bar, the bar length is printed
 * to be porportional to max. tot is the "total" needed to compute
 * the precentage value. */
void om_text_print_bar(FILE *fp, int max, int tot, int this, int cols,
                       char c1, char c2)
{
  int l;
  float p;
  char *bar;
  if (tot == 0) tot++;
  if (max == 0) max++;
  l = ((float)(cols*this))/max;
  p = ((float)(100*this))/tot;
  bar = malloc(cols+1);
  if (!bar) return;
  memset(bar, c2, cols+1);
  memset(bar, c1, l);
  bar[cols] = '\0';
  fprintf(fp, "%s %02.1f%%", bar, p);
  free(bar);
}

void om_text_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta)
{
  (void)time_delta;
  fprintf(fp, "   %-12s: %-9d |", key, this);
  om_text_print_bar(fp, max, tot, this, 44, '#', ' ');
  fprintf(fp, "\n");
}

void om_text_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta)
{
  (void)time_delta;
  fprintf(fp, "   %s: %-10d |", key, this);
  om_text_print_bar(fp, tot, tot, this, 44, '#', '.');
  fprintf(fp, "\n");
}

void om_text_print_bidimentional_map(FILE *fp, int xlen, int ylen,
                                     char **xlabel, char **ylabel, int *value)
{
  char *asciipal = " .-+#";
  int pallen = strlen(asciipal);
  int x, y, l, max = 0;

  /* Get the max value */
  l = xlen*ylen;
  for (x = 0; x < l; x++)
    if (max < value[x])
      max = value[x];
  if (max == 0) max++; /* avoid division by zero */
  /* print the map */
  for (y = 0; y < ylen; y++) {
    fprintf(fp, "%15s: ", ylabel[y]);
    for (x = 0; x < xlen; x++) {
      int coloridx;
      int val = value[(y*xlen)+x];

      coloridx = ((pallen-1)*val)/max;
      fputc(asciipal[coloridx], fp);
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
  /* print the x-labels in vertical */
  {
    char **p = malloc(sizeof(char*)*xlen);
    /* The 'p' pointers array is initialized at the
     * start of all the x-labels. */
    for (x = 0; x < xlen; x++)
      p[x] = xlabel[x];
    while(1) {
      int sentinel = 0;
      fprintf(fp, "%15s  ", "");
      for (x = 0; x < xlen; x++) {
        if (*(p[x]) != '\0') {
          fputc(*(p[x]), fp);
          p[x]++;
          sentinel++;
        } else {
          fputc(' ', fp);
        }
      }
      fputc('\n', fp);
      if (sentinel == 0) break;
    }
    free(p);
  }
}

void om_text_print_hline(FILE *fp)
{
  fprintf(fp, "\n");
}

void om_text_print_credits(FILE *fp)
{
  fprintf(fp, "Statistics generated with VISITORS version %s\n"
          "http://www.hping.org/visitors for more information\n",
          VI_VERSION_STR);
}

void om_text_print_report_link(FILE *fp, char *report)
{
  fprintf(fp, "-> %s\n", report);
  return;
}
