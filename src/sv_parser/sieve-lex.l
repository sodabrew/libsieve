%{
/* sieve.l -- sieve lexer
 * Larry Greenfield
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

#include <string.h>
/* sv_util */
#include "util.h"
/* sv_interface */
#include "tree.h"
#include "sieve.h"

#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_sieveinput(b, ms))

int libsieve_sieveinput(char *buf, int max_size);
extern int libsieve_sieveerror(char *);

#define YY_FATAL_ERROR libsieve_sievefatalerror
void libsieve_sievefatalerror(const char msg[]);

%}

%option yylineno
%option noyywrap
%option nounput
%option prefix="libsieve_sieve"
%option never-interactive

ws		[ \t]+
ident		[a-zA-Z_][a-zA-Z_0-9]*
CRLF		(\r\n|\r|\n)

%state MULTILINE
%state QSTRING

%%
<MULTILINE>^\.{CRLF}	{ BEGIN INITIAL; }
<MULTILINE>^\.\.	{ /* dot stuffing! we want one . */ yyless(1); }
<MULTILINE>([^\.{CRLF}]|\n)+ { libsieve_sievelval.sval = libsieve_strdup(yytext, strlen(yytext));
			  return STRING; }
<MULTILINE><<EOF>>	{ libsieve_sieveerror("unexpected end of file in string"); 
			  yyterminate(); }

<QSTRING>\"		{ BEGIN INITIAL; }
<QSTRING>([^\"]|\\\"|\n)+ { libsieve_sievelval.sval = libsieve_strdup(yytext, strlen(yytext));
			  return STRING; }

<INITIAL>text:{ws}?(#.*)?{CRLF}	{ BEGIN MULTILINE; }
<INITIAL>\"		{ BEGIN QSTRING; }
<INITIAL>[0-9]+[KMG]?	{ libsieve_sievelval.nval = libsieve_strtonum(yytext); return NUMBER; }
<INITIAL>if		return IF;
<INITIAL>elsif		return ELSIF;
<INITIAL>else		return ELSE;
<INITIAL>anyof		return ANYOF;
<INITIAL>allof		return ALLOF;
<INITIAL>exists		return EXISTS;
<INITIAL>false		return SFALSE;
<INITIAL>true		return STRUE;
<INITIAL>address	return ADDRESS;
<INITIAL>envelope	return ENVELOPE;
<INITIAL>header		return HEADER;
<INITIAL>not		return NOT;
<INITIAL>size		return SIZE;
<INITIAL>reject		return REJCT;
<INITIAL>fileinto	return FILEINTO;
<INITIAL>redirect	return REDIRECT;
<INITIAL>keep		return KEEP;
<INITIAL>require	return REQUIRE;
<INITIAL>stop		return STOP;
<INITIAL>discard	return DISCARD;
<INITIAL>setflag	return SETFLAG;
<INITIAL>addflag	return ADDFLAG;
<INITIAL>removeflag	return REMOVEFLAG;
<INITIAL>mark		return MARK;
<INITIAL>unmark		return UNMARK;
<INITIAL>notify		return NOTIFY;
<INITIAL>denotify	return DENOTIFY;
<INITIAL>:id		return ID;
<INITIAL>:method	return METHOD;
<INITIAL>:options	return OPTIONS;
<INITIAL>:low		return LOW;
<INITIAL>:normal	return NORMAL;
<INITIAL>:high		return HIGH;
<INITIAL>:message	return MESSAGE;
<INITIAL>vacation	return VACATION;
<INITIAL>:days		return DAYS;
<INITIAL>:addresses	return ADDRESSES;
<INITIAL>:subject	return SUBJECT;
<INITIAL>:mime		return MIME;
<INITIAL>:comparator	return COMPARATOR;
<INITIAL>:is		return IS;
<INITIAL>:contains	return CONTAINS;
<INITIAL>:matches	return MATCHES;
<INITIAL>:regex		return REGEX;
<INITIAL>:over		return OVER;
<INITIAL>:under		return UNDER;
<INITIAL>:all		return ALL;
<INITIAL>:localpart	return LOCALPART;
<INITIAL>:domain	return DOMAIN;
<INITIAL>:user		return USER;
<INITIAL>:detail	return DETAIL;
<INITIAL>[ \t\n\r] ;	/* ignore whitespace */
<INITIAL>#.* ;		/* ignore comments */
.			return yytext[0];

%%
/* take input from sieve string provided by sieve parser */
int libsieve_sieveinput(char *buf, int max_size)
{
    extern char *libsieve_sieveptr;	/* current position in sieve string */
    size_t n;			/* number of characters to read from string */

    n = strlen(libsieve_sieveptr) < (size_t)max_size ? strlen(libsieve_sieveptr) : max_size;
    if (n > 0) {
	memcpy(buf, libsieve_sieveptr, n);
	libsieve_sieveptr += n;
    }
    return n;
}

/* Clean up after ourselves by free()ing the current buffer */
void libsieve_sievelexfree()
{
    libsieve_sieve_delete_buffer( YY_CURRENT_BUFFER );
}

/* Kind of a hack, but this sets up the file statics */
void libsieve_sievelexalloc()
{
    /* Nothing to do here */
}

/* Replacement for the YY_FATAL_ERROR macro,
 * which would print msg to stderr and exit. */
void libsieve_sievefatalerror(const char msg[])
{
    /* Basically stop and don't do anything */
}

