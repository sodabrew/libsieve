/* ANSI-C code produced by gperf version 3.0.1 */
/* Command-line: gperf sieve-keywords.gperf  */
/* Computed positions: -k'2,4' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "sieve-keywords.gperf"

/* sieve-keywords.gperf -- RFC 3028 Sieve Keyword Hash
 * Aaron Stone
 * $Id: sieve-lex.l 80 2006-07-24 14:24:53Z sodabrew $
 */
/* * * *
 * Copyright 2007 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* sv_interface */
#include "script.h"
#include "tree.h"

/* sv_parser */
#include "sieve.h"

#line 31 "sieve-keywords.gperf"
struct sieve_keyword { char *name; int value; };

#define TOTAL_KEYWORDS 57
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 18
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 88
/* maximum key range = 87, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 30, 50, 10,
       0,  5,  0, 25,  0,  0, 25, 89, 30, 25,
       5, 50, 15, 40, 18, 40, 30, 10, 15, 89,
       5, 89,  5, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89, 89, 89, 89,
      89, 89, 89, 89, 89, 89, 89
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[3]+1];
      /*FALLTHROUGH*/
      case 3:
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval;
}

static const struct sieve_keyword wordlist[] =
  {
    {""}, {""},
#line 38 "sieve-keywords.gperf"
    {"if",		IF},
#line 82 "sieve-keywords.gperf"
    {":is",		IS},
#line 50 "sieve-keywords.gperf"
    {"size",		SIZE},
#line 73 "sieve-keywords.gperf"
    {":high",	HIGH},
    {""},
#line 57 "sieve-keywords.gperf"
    {"discard",	DISCARD},
#line 52 "sieve-keywords.gperf"
    {"fileinto",	FILEINTO},
    {""},
#line 75 "sieve-keywords.gperf"
    {":days",	DAYS},
#line 51 "sieve-keywords.gperf"
    {"reject",	REJCT},
#line 92 "sieve-keywords.gperf"
    {":domain",	DOMAIN},
#line 47 "sieve-keywords.gperf"
    {"envelope",	ENVELOPE},
    {""},
#line 93 "sieve-keywords.gperf"
    {":user",	USER},
#line 48 "sieve-keywords.gperf"
    {"header",	HEADER},
#line 94 "sieve-keywords.gperf"
    {":detail",	DETAIL},
    {""}, {""},
#line 79 "sieve-keywords.gperf"
    {":from",	FROM},
#line 89 "sieve-keywords.gperf"
    {":under",	UNDER},
#line 45 "sieve-keywords.gperf"
    {"true",		STRUE},
    {""},
#line 87 "sieve-keywords.gperf"
    {":regex",	REGEX},
#line 41 "sieve-keywords.gperf"
    {"anyof",	ANYOF},
#line 81 "sieve-keywords.gperf"
    {":comparator",	COMPARATOR},
#line 55 "sieve-keywords.gperf"
    {"require",	REQUIRE},
    {""}, {""},
#line 60 "sieve-keywords.gperf"
    {"removeflag",	REMOVEFLAG},
#line 83 "sieve-keywords.gperf"
    {":count",	COUNT},
#line 59 "sieve-keywords.gperf"
    {"addflag",	ADDFLAG},
    {""},
#line 40 "sieve-keywords.gperf"
    {"else",		ELSE},
#line 78 "sieve-keywords.gperf"
    {":mime",	MIME},
    {""},
#line 58 "sieve-keywords.gperf"
    {"setflag",	SETFLAG},
#line 53 "sieve-keywords.gperf"
    {"redirect",	REDIRECT},
#line 71 "sieve-keywords.gperf"
    {":low",	 	LOW},
#line 91 "sieve-keywords.gperf"
    {":localpart",	LOCALPART},
#line 43 "sieve-keywords.gperf"
    {"exists",	EXISTS},
#line 69 "sieve-keywords.gperf"
    {":method",	METHOD},
#line 86 "sieve-keywords.gperf"
    {":matches",	MATCHES},
    {""},
#line 76 "sieve-keywords.gperf"
    {":addresses",	ADDRESSES},
#line 84 "sieve-keywords.gperf"
    {":value",	VALUE},
#line 46 "sieve-keywords.gperf"
    {"address",	ADDRESS},
    {""},
#line 54 "sieve-keywords.gperf"
    {"keep",		KEEP},
#line 42 "sieve-keywords.gperf"
    {"allof",	ALLOF},
#line 68 "sieve-keywords.gperf"
    {":importance",	IMPORTANCE},
#line 72 "sieve-keywords.gperf"
    {":normal",	NORMAL},
#line 49 "sieve-keywords.gperf"
    {"not",	 	NOT},
    {""},
#line 88 "sieve-keywords.gperf"
    {":over",	OVER},
#line 67 "sieve-keywords.gperf"
    {":flags",	FLAGS},
#line 80 "sieve-keywords.gperf"
    {":handle",	HANDLE},
#line 77 "sieve-keywords.gperf"
    {":subject",	SUBJECT},
#line 90 "sieve-keywords.gperf"
    {":all",	 	ALL},
#line 39 "sieve-keywords.gperf"
    {"elsif",	ELSIF},
#line 63 "sieve-keywords.gperf"
    {"unmark",	UNMARK},
#line 61 "sieve-keywords.gperf"
    {"hasflag",	HASFLAG},
#line 74 "sieve-keywords.gperf"
    {":message",	MESSAGE},
#line 62 "sieve-keywords.gperf"
    {"mark",		MARK},
#line 44 "sieve-keywords.gperf"
    {"false",	SFALSE},
    {""}, {""},
#line 70 "sieve-keywords.gperf"
    {":options",	OPTIONS},
#line 85 "sieve-keywords.gperf"
    {":contains",	CONTAINS},
    {""}, {""}, {""},
#line 66 "sieve-keywords.gperf"
    {"valid_notif_method",	 VALIDNOTIF},
#line 56 "sieve-keywords.gperf"
    {"stop",		STOP},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 64 "sieve-keywords.gperf"
    {"notify",	NOTIFY},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 65 "sieve-keywords.gperf"
    {"vacation",	VACATION}
  };

#ifdef __GNUC__
__inline
#endif
const struct sieve_keyword *
libsieve_keyword_struct (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
#line 95 "sieve-keywords.gperf"

int libsieve_keyword(const char *str, unsigned int len)
{
	struct sieve_keyword const *s;
	if ((s = libsieve_keyword_struct(str, len)))
		return s->value;
	return 0;
}
