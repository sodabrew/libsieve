/* comparator.c -- comparator functions
 * Larry Greenfield
 * $Id$
 */
/***********************************************************
        Copyright 1999 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Carnegie Mellon
University not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR
ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "comparator.h"
#include "src/sv_interface/tree.h"
#include "sieve.h"
#include "src/sv_util/util.h"
#include "src/sv_interface/callbacks2.h"

#define THIS_MODULE "sv_comparator"

/* --- i;octet comparators --- */

/* just compare the two; these should be NULL terminated */
static int octet_is(struct sieve2_context *context, const char *pat, const char *text)
{
    size_t sl;
    sl = strlen(pat);

    return (sl == strlen(text)) && !memcmp(pat, text, sl);
}

/* we do a brute force attack */
static int octet_contains(struct sieve2_context *context, const char *pat, const char *text)
{
    return (strstr(text, pat) != NULL);
}

static int octet_matches_(struct sieve2_context *context, const char *pat, const char *text, int casemap)
{
    const char *p;
    const char *t;
    char c;

    t = text;
    p = pat;
    for (;;) {
	if (*p == '\0') {
	    /* ran out of pattern */
	    return (*t == '\0');
	}
	c = *p++;
	switch (c) {
	case '?':
	    if (*t == '\0') {
		return 0;
	    }
	    t++;
	    break;
	case '*':
	    while (*p == '*' || *p == '?') {
		if (*p == '?') {
		    /* eat the character now */
		    if (*t == '\0') {
			return 0;
		    }
		    t++;
		}
		/* coalesce into a single wildcard */
		p++;
	    }
	    if (*p == '\0') {
		/* wildcard at end of string, any remaining text is ok */
		return 1;
	    }

	    while (*t != '\0') {
		/* recurse */
	        if (octet_matches_(context, p, t, casemap)) return 1;
		t++;
	    }
	case '\\':
	    p++;
	    /* falls through */
	default:
	    if (casemap && (toupper((int)(unsigned char)c) ==
			    toupper((int)(unsigned char)*t))) {
		t++;
	    } else if (!casemap && (c == *t)) {
		t++;
	    } else {
		/* literal char doesn't match */
		return 0;
	    }
	}
    }
    /* never reaches */
    abort();
}

static int octet_matches(struct sieve2_context *context, const char *pat, const char *text)
{
    return octet_matches_(context, pat, text, 0);
}

static int octet_regex(struct sieve2_context *context, const char *pat, const char *text)
{
    return (!libsieve_regexec((const regex_t *)pat, text, 0, NULL, 0));
}


/* --- i;ascii-casemap comparators --- */

/* sheer brute force */
static int ascii_casemap_contains(struct sieve2_context *context, const char *pat, const char *text)
{
    int N, M, i, j;

    N = strlen(text);
    M = strlen(pat);
    i = 0;
    j = 0;
    while ((j < M) && (i < N)) {
	if (toupper((int)(unsigned char)text[i]) ==
	    toupper((int)(unsigned char)pat[j])) {
	    i++; j++;
	} else {
	    i = i - j + 1;
	    j = 0;
	}
    }
    return (j == M); /* we found a match! */
}

static int ascii_casemap_matches(struct sieve2_context *context, const char *pat, const char *text)
{
    return octet_matches_(context, pat, text, 1);
}

static int ascii_numeric_unknown(struct sieve2_context *context, const char *pat, const char *text)
{
    TRACE_DEBUG("Unknown numeric comparison requested");
    return 0;
}

/* i;ascii-numeric
 * Note that the inequalities are backwards.
 * This is because pat is the RHS and text is the LHS.
 */
static int ascii_numeric(struct sieve2_context *context, enum num num, const char *pat, const char *text)
{
    TRACE_DEBUG("Testing [%s] [%d] [%s]", pat, num, text);
    if (isdigit((int)(unsigned char)*pat)) {
	if (isdigit((int)(unsigned char)*text)) {
            TRACE_DEBUG("Testing [%d] [%d] [%d]", atoi(pat), num, atoi(text));
	    switch (num) {
	    case gt:
	        return atoi(pat) <  atoi(text);
	    case ge:
	        return atoi(pat) <= atoi(text);
	    case lt:
	        return atoi(pat) >  atoi(text);
	    case le:
	        return atoi(pat) >= atoi(text);
	    case eq:
	        return atoi(pat) == atoi(text);
	    case ne:
	        return atoi(pat) != atoi(text);
            default:
	        return 0;
            }
	} else {
	    return 0;
	}
    } else if (isdigit((int)(unsigned char)*text)) return 0;
    else return 1; /* both not digits */
}

static int ascii_numeric_gt(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, gt, pat, text); }
static int ascii_numeric_ge(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, ge, pat, text); }
static int ascii_numeric_lt(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, lt, pat, text); }
static int ascii_numeric_le(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, le, pat, text); }
static int ascii_numeric_eq(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, eq, pat, text); }
static int ascii_numeric_ne(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_numeric(context, ne, pat, text); }

static int ascii_casemap_unknown(struct sieve2_context *context, const char *pat, const char *text)
{
    TRACE_DEBUG("Unknown casemap comparison requested");
    return 0;
}

/* i;ascii-casemap
 * Note that the inequalities are backwards.
 * This is because pat is the RHS and text is the LHS.
 */
static int ascii_casemap(struct sieve2_context* context, enum num num, const char *pat, const char *text)
{
    TRACE_DEBUG("Testing [%s] [%d] [%s]", pat, num, text);
    switch (num) {
    case gt:
        return strcasecmp(pat, text) <  0;
    case ge:
        return strcasecmp(pat, text) <= 0;
    case lt:
        return strcasecmp(pat, text) >  0;
    case le:
        return strcasecmp(pat, text) >= 0;
    case eq:
        return strcasecmp(pat, text) == 0;
    case ne:
        return strcasecmp(pat, text) != 0;
    default:
        return 0;
    }
}

static int ascii_casemap_gt(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, gt, pat, text); }
static int ascii_casemap_ge(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, ge, pat, text); }
static int ascii_casemap_lt(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, lt, pat, text); }
static int ascii_casemap_le(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, le, pat, text); }
static int ascii_casemap_eq(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, eq, pat, text); }
static int ascii_casemap_ne(struct sieve2_context *context, const char *pat, const char *text)
    { return ascii_casemap(context, ne, pat, text); }

int libsieve_relational_lookup(const char *rel)
{
    enum num num;

    if (!rel) {
        return 0;
    } else if (!strcmp(rel, "gt")) {
        return (num = gt) << 10;
    } else if (!strcmp(rel, "ge")) {
        return (num = ge) << 10;
    } else if (!strcmp(rel, "lt")) {
        return (num = lt) << 10;
    } else if (!strcmp(rel, "le")) {
        return (num = le) << 10;
    } else if (!strcmp(rel, "eq")) {
        return (num = eq) << 10;
    } else if (!strcmp(rel, "ne")) {
        return (num = ne) << 10;
    } else {
        return 0;
    }
}

VISIBLE comparator_t *libsieve_comparator_lookup(struct sieve2_context *context, const char *comp, int mode)
{
    comparator_t *ret;

    ret = NULL;
    if (!strcmp(comp, "i;octet")) {
	switch (mode) {
	case IS:
	    ret = &octet_is;
	    break;
	case CONTAINS:
	    ret = &octet_contains;
	    break;
	case MATCHES:
	    ret = &octet_matches;
	    break;
	case REGEX:
	    ret = &octet_regex;
	    break;
	}
    } else if (!strcmp(comp, "i;ascii-casemap")) {
	switch (mode) {
	case IS:
	    ret = &ascii_casemap_eq;
	    break;
	case CONTAINS:
	    ret = &ascii_casemap_contains;
	    break;
	case MATCHES:
	    ret = &ascii_casemap_matches;
	    break;
	case REGEX:
	    /* the ascii-casemap destinction is made during
	       the compilation of the regex in verify_regex() */
	    ret = &octet_regex;
	    break;
	case VALUE:
	    TRACE_DEBUG("Value comparison requested with default relation");
	    goto casemap_switch;
	case COUNT:
	    TRACE_DEBUG("Count comparison requested with default relation");
	default:
        casemap_switch:
	    switch ((enum num)(mode >> 10)) {
            case gt:
	        ret = &ascii_casemap_gt;
		break;
            case ge:
	        ret = &ascii_casemap_ge;
		break;
            case lt:
	        ret = &ascii_casemap_lt;
		break;
            case le:
	        ret = &ascii_casemap_le;
		break;
            case eq:
	        ret = &ascii_casemap_eq;
		break;
            case ne:
	        ret = &ascii_casemap_ne;
		break;
	    default:
	    	ret = &ascii_casemap_unknown;
	    }
	}
    } else if (!strcmp(comp, "i;ascii-numeric")) {
	switch (mode) {
	case IS:
	    ret = &ascii_numeric_eq;
	    break;
	case VALUE:
	    TRACE_DEBUG("Value comparison requested with default relation");
	    goto numeric_switch;
	case COUNT:
	    TRACE_DEBUG("Count comparison requested with default relation");
        default:
        numeric_switch:
	    switch ((enum num)(mode >> 10)) {
            case gt:
	        ret = &ascii_numeric_gt;
		break;
            case ge:
	        ret = &ascii_numeric_ge;
		break;
            case lt:
	        ret = &ascii_numeric_lt;
		break;
            case le:
	        ret = &ascii_numeric_le;
		break;
            case eq:
	        ret = &ascii_numeric_eq;
		break;
            case ne:
	        ret = &ascii_numeric_ne;
		break;
	    default:
	    	ret = &ascii_numeric_unknown;
            }
	}
    }
    return ret;
}

int libsieve_relational_count(struct sieve2_context *context, int mode)
{
    if ((mode & COUNT) == COUNT) {
        TRACE_DEBUG("Count relation [%d]", mode >> 10);
        return 1;
    }
    if ((mode & VALUE) == VALUE) {
        TRACE_DEBUG("Value relation [%d]", mode >> 10);
        return 0;
    }
    return 0;
}
