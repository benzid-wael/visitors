/* xvisitors -- very fast web logs analyzer.
 *
 * Copyright (C) 2014 Wael BEN ZID <benzid.wael@hotmail.fr>
 * All Rights Reserved.
 *
 * This software is released under the terms of the GPL license version 2.
 * Read the COPYING file in this distribution for more details. */

/* -------------------------- html output module ------------------------ */

#include <stdio.h>
#include "om.h"
#include "config.h"
#include "date_utils.h"

/* Use html entities for special chars. Abbreviates at 'maxlen' if needed. */
void om_html_entities_abbr(FILE *fp, char *s, int maxlen)
{
  while(*s) {
    if (maxlen-- == 0) {
      fprintf(fp, "...");
      break;
    }
    switch(*s) {
    case '\'': fprintf(fp, "&#39;"); break;
    case '"': fprintf(fp, "&#34;"); break;
    case '&': fprintf(fp, "&amp;"); break;
    case '<': fprintf(fp, "&lt;"); break;
    case '>': fprintf(fp, "&gt;"); break;
    default: fputc(*s, fp); break;
    }
    s++;
  }
}

/* A wrapper to om_html_entities_abbr() with a fixed abbreviation length */
void om_html_entities(FILE *fp, char *s)
{
  om_html_entities_abbr(fp, s, VI_HTML_ABBR_LEN);
}

void om_html_print_header(FILE *fp)
{
  fprintf(fp,
          "<html>\n"
          "<head>\n"
          "<style>\n"
          "BODY, TD, B, LI, U, DIV, SPAN {\n"
          "	background-color: #ffffff;\n"
          "	color: #000000;\n"
          "	font-family: Verdana, Arial, Helvetica, Sans-Serif;\n"
          "	font-size: 10px;\n"
          "}\n"
          "A {\n"
          "	color: #0066ff;\n"
          "	text-decoration: none;\n"
          "}\n"
          "A:visited {\n"
          "	color: #000099;\n"
          "	text-decoration: none;\n"
          "}\n"
          "A:active {\n"
          "	color: #26a0be;\n"
          "	text-decoration: none;\n"
          "}\n"
          "A:hover {\n"
          "	color: #ffffff;\n"
          "	text-decoration: none;\n"
          "	background-color: #26a0be;\n"
          "}\n"
          ".barfill {\n"
          "	background-color: #96ef94;\n"
          "	border-left: 1px;\n"
          "	border-right: 1px;\n"
          "	border-top: 1px;\n"
          "	border-bottom: 1px;\n"
          "	border-color: #4c934a;\n"
          "	border-style: solid;\n"
          "	font-size: 10px;\n"
          "	height: 3px;\n"
          "	line-height: 4px;\n"
          "}\n"
          ".barempty {\n"
          "	font-size: 10px;\n"
          "	line-height: 4px;\n"
          "}\n"
          ".barleft {\n"
          "	background-color: #ff9696;\n"
          "	border-left: 1px;\n"
          "	border-right: 1px;\n"
          "	border-top: 1px;\n"
          "	border-bottom: 1px;\n"
          "	border-color: #4c934a;\n"
          "	border-style: solid;\n"
          "	font-size: 10px;\n"
          "	height: 3px;\n"
          "	line-height: 4px;\n"
          "}\n"
          ".barright {\n"
          "	background-color: #f8f8f8;\n"
          "	border-left: 0px;\n"
          "	border-right: 1px;\n"
          "	border-top: 1px;\n"
          "	border-bottom: 1px;\n"
          "	border-color: #4c934a;\n"
          "	border-style: solid;\n"
          "	font-size: 10px;\n"
          "	height: 3px;\n"
          "	line-height: 4px;\n"
          "}\n"
          ".title {\n"
          "	background-color: #007f9e;\n"
          "	font-size: 12px;\n"
          "	font-weight: bold;\n"
          "	padding: 3px;\n"
          "	color: #ffffff;\n"
          "}\n"
          ".reportlink {\n"
          "	background-color: #ffffff;\n"
          "	font-size: 12px;\n"
          "	font-weight: bold;\n"
          "	color: #000000;\n"
          "	padding-left: 3px;\n"
          "}\n"
          ".subtitle {\n"
          "	background-color: #007f9e;\n"
          "	font-size: 12px;\n"
          "	font-weight: normal;\n"
          "	padding: 3px;\n"
          "	color: #ffffff;\n"
          "}\n"
          ".info {\n"
          "	background-color: #badfee;\n"
          "	font-size: 12px;\n"
          "	padding-left: 3px;\n"
          "	padding-right: 3px;\n"
          "}\n"
          ".keyentry {\n"
          "	font-size: 10px;\n"
          "	padding-left: 2px;\n"
          "	border-bottom: 1px dashed #bcbcbc;\n"
          "}\n"
          ".keyentrywe {\n"
          "	background-color: #f0f090;\n"
          "	font-size: 10px;\n"
          "	padding-left: 2px;\n"
          "	border-bottom: 1px dashed #bcbcbc;\n"
          "}\n"
          ".valueentry {\n"
          "	font-size: 10px;\n"
          "	padding-left: 2px;\n"
          "	color: #905d14;\n"
          "	border-bottom: 1px dashed #f6c074;\n"
          "}\n"
          ".credits {\n"
          "	font-size: 12px;\n"
          "	font-weight: bold;\n"
          "}\n"
          ".maintable {\n"
          "	border-style: solid;\n"
          "	border-color: #0b4b5b;\n"
          "	border-width: 1px;\n"
          "}\n"
          "</style>\n"
          "</head>\n"
          "<body><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"maintable\">\n"
          );
}

void om_html_print_footer(FILE *fp)
{
  fprintf(fp, "</table></body></html>\n");
}

void om_html_print_title(FILE *fp, char *title)
{
  fprintf(fp, "<tr><td align=\"center\" class=\"title\" colspan=\"3\"><a name=\"%s\"></a>", title);
  om_html_entities(fp, title);
  fprintf(fp, "</td></tr>\n");
}

void om_html_close_title(FILE *fp)
{
  (void)fp;
}

void om_html_print_subtitle(FILE *fp, char *subtitle)
{
  fprintf(fp, "<tr><td align=\"center\" class=\"subtitle\" colspan=\"3\">");
  om_html_entities(fp, subtitle);
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_numkey_info(FILE *fp, char *key, int val)
{
  fprintf(fp, "<tr><td align=\"left\" colspan=\"3\" class=\"info\">");
  om_html_entities(fp, key);
  fprintf(fp, " %d", val);
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_dblkey_info(FILE *fp, char *key, double val)
{
  fprintf(fp, "<tr><td align=\"left\" colspan=\"3\" class=\"info\">");
  om_html_entities(fp, key);
  fprintf(fp, " %.3f", val);
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_strkey_info(FILE *fp, char *key, char *val)
{
  fprintf(fp, "<tr><td align=\"left\" colspan=\"3\" class=\"info\">");
  om_html_entities(fp, key);
  fprintf(fp, " %s", val);
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_keykey_entry(FILE *fp, char *key1, char *key2, int num)
{
  fprintf(fp, "<tr><td align=\"left\" class=\"keyentry\">");
  fprintf(fp, "%d)", num);
  fprintf(fp, "<td align=\"left\" class=\"valueentry\">");
  om_html_entities(fp, key1);
  fprintf(fp, "</td><td align=\"left\" class=\"keyentry\">");
  if (!strncmp(key2, "http://", 7)) {
    fprintf(fp, "<a class=\"url\" href=\"%s\">", key2);
    om_html_entities(fp, key2);
    fprintf(fp, "</a>");
  } else {
    om_html_entities(fp, key2);
  }
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_numkey_entry(FILE *fp, char *key, int val, char *link,
                                int num)
{
  fprintf(fp, "<tr><td align=\"left\" class=\"keyentry\">");
  fprintf(fp, "%d)", num);
  fprintf(fp, "<td align=\"left\" class=\"valueentry\">");
  fprintf(fp, "%d", val);
  fprintf(fp, "</td><td align=\"left\" class=\"keyentry\">");
  if (link != NULL) {
    fprintf(fp, "<a class=\"url\" href=\"%s\">", link);
    om_html_entities(fp, key);
    fprintf(fp, "</a>");
  } else if (!strncmp(key, "http://", 7)) {
    fprintf(fp, "<a class=\"url\" href=\"%s\">", key);
    om_html_entities(fp, key);
    fprintf(fp, "</a>");
  } else {
    om_html_entities(fp, key);
  }
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_bar(FILE *fp, int l, char *leftclass, char *rightclass)
{
  fprintf(fp, "<table cellpadding=\"0\" cellspacing=\"0\" width=\"400\" border=\"0\">\n");
  fprintf(fp, "<tr><td align=\"center\" class=\"%s\" width=\"%d%%\">%s</td>\n", leftclass, l, l ? "&nbsp;" : "");
  fprintf(fp, "<td align=\"center\" class=\"%s\" width=\"%d%%\">%s</td></tr>\n", rightclass, 100-l, (l!=100) ? "&nbsp;" : "");
  fprintf(fp, "</table>\n");
}

void om_html_print_numkeybar_entry(FILE *fp, char *key, int max, int tot,
                                   int this, int time_delta)
{
  int l, weekend;
  float p;

  if (tot == 0) tot++;
  if (max == 0) max++;
  l = ((float)(100*this))/max;
  p = ((float)(100*this))/tot;
  weekend = vi_is_weekend(key, time_delta);

  if (weekend)
    fprintf(fp, "<tr><td align=\"left\" class=\"keyentrywe\">");
  else
    fprintf(fp, "<tr><td align=\"left\" class=\"keyentry\">");
  om_html_entities(fp, key);
  fprintf(fp, "&nbsp;&nbsp;&nbsp;</td><td align=\"left\" class=\"valueentry\">");
  fprintf(fp, "%d (%02.1f%%)", this, p);
  fprintf(fp, "</td><td align=\"left\" class=\"bar\">");
  om_html_print_bar(fp, l, "barfill", "barempty");
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_numkeycomparativebar_entry(FILE *fp, char *key, int tot,
                                              int this, int time_delta)
{
  int l, weekend;
  float p;

  if (tot == 0) tot++;
  p = ((float)(100*this))/tot;
  l = (int) p;
  weekend = vi_is_weekend(key, time_delta);

  if (weekend)
    fprintf(fp, "<tr><td align=\"left\" class=\"keyentrywe\">");
  else
    fprintf(fp, "<tr><td align=\"left\" class=\"keyentry\">");
  om_html_entities(fp, key);
  fprintf(fp, "&nbsp;&nbsp;&nbsp;</td><td align=\"left\" class=\"valueentry\">");
  fprintf(fp, "%d (%02.1f%%)", this, p);
  fprintf(fp, "</td><td align=\"left\" class=\"bar\">");
  om_html_print_bar(fp, l, "barleft", "barright");
  fprintf(fp, "</td></tr>\n");
}

void om_html_print_bidimentional_map(FILE *fp, int xlen, int ylen,
                                     char **xlabel, char **ylabel, int *value)
{
  int x, y, l, max = 0;

  /* Get the max value */
  l = xlen*ylen;
  for (x = 0; x < l; x++)
    if (max < value[x])
      max = value[x];
  if (max == 0) max++; /* avoid division by zero */
  /* print the map */
  fprintf(fp, "<tr><td colspan=\"3\" align=\"center\">");
  fprintf(fp, "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
  for (y = 0; y < ylen; y++) {
    fprintf(fp, "<tr>");
    fprintf(fp, "<td class=\"valueentry\">%s</td>", ylabel[y]);
    for (x = 0; x < xlen; x++) {
      int r, g, b;
      int val = value[(y*xlen)+x];

      r = (0xAA*val)/max;
      g = (0xBB*val)/max;
      b = (0xFF*val)/max;
      fprintf(fp, "<td style=\"background-color: #%02X%02X%02X;\">&nbsp;</td>\n", r, g, b);
    }
    fprintf(fp, "</tr>\n");
  }
  fprintf(fp, "<tr><td>&nbsp;</td>");
  for (x = 0; x < xlen; x++) {
    fprintf(fp, "<td class=\"keyentry\">%s</td>", xlabel[x]);
  }
  fprintf(fp, "</tr></table></td></tr>");
}

void om_html_print_hline(FILE *fp)
{
  fprintf(fp, "<tr><td colspan=\"3\">&nbsp;</td></tr>");
}

void om_html_print_credits(FILE *fp)
{
  fprintf(fp, "<tr><td colspan=\"3\" align=\"center\" class=\"credits\">Statistics generated with <a href=\"http://www.hping.org/visitors\">VISITORS Web Log Analyzer</a> version %s\n</td></tr>", VI_VERSION_STR);
}

void om_html_print_report_link(FILE *fp, char *report)
{
  fprintf(fp, "<tr><td align=\"left\" class=\"reportlink\" colspan=\"3\"><a href=\"#%s\">", report);
  om_html_entities(fp, report);
  fprintf(fp, "</a></td></tr>\n");
  return;
}
