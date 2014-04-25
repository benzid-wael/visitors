#ifndef _CONFIG_H
#define _CONFIG_H

/* Max length of an error stored in the visitors handle */
#define VI_ERROR_MAX 1024
/* Max length of a log line */
#define VI_LINE_MAX 4096
/* Max number of filenames in the command line */
#define VI_FILENAMES_MAX 1024
/* Max number of prefixes in the command line */
#define VI_PREFIXES_MAX 1024
/* Max number of --grep --exclude patterns in the command line */
#define VI_GREP_PATTERNS_MAX 1024
/* Abbreviation length for HTML outputs */
#define VI_HTML_ABBR_LEN 100
/* Version as a string */
#define VI_DATE_MAX 64
/* Max length of a log entry date */
#define VI_VERSION_STR "0.7"

#endif
