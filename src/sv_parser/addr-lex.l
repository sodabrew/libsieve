%{
/*
 * addr-lex.l -- RFC 822 address lexer
 * Ken Murchison
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

/* This only works in C99 and higher... */
#ifdef DEBUG
#define sv_debugf(...) printf(__VA_ARGS__)
#else
#define sv_debugf(...) 
#endif /* ifdef DEBUG */

/* Must be defined before addr.h */
#define YYSTYPE char *
#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = addrinput(b, ms))

#include <string.h>
/* sv_util */
#include "util.h"
/* sv_parser */
#include "addr.h"
#include "addrinc.h"

static int ncom = 0;	/* number of open comments */
static struct mlbuf *ml = NULL;

#define YY_FATAL_ERROR addrfatalerror
void addrfatalerror(const char msg[]);

%}

%option noyywrap
%option nounput
%option prefix="addr"

%x QSTRING DOMAINLIT COMMENT

%%

\"				{ BEGIN QSTRING; sv_debugf( "Begin QSTRING\n" ); return QUOTE; }
\[				{ BEGIN DOMAINLIT; sv_debugf( "Begin DOMAINLIT\n" ); return yytext[0]; }
\(				{ ncom = 1; sv_debugf( "Begin COMMENT\n" ); BEGIN COMMENT; }
\)				{ addrerror("address parse error, "
					  "unexpected `')'' "
					  "(unbalanced comment)");
				  yyterminate(); }

[<>\(\)@,;:\"\.\[\]\\]	{
		/* Return the special character */
		return yytext[0];
				}
([ \t\n\r])+			{
		sv_debugf( "Whitespace silently murdered.\n" );
		/* Ignore whitespace by not returning */
				}
([^<>\(\)@,;:\"\.\[\]\\ \t\n\r])+	{
		/* Match any set of non-special-characters */
		addrlval = sv_strbuf(ml, yytext, strlen(yytext), NOFREE);
		return ATOM;
				}

<QSTRING>([^\"]|\\\")+		{
		/* Match anything that's not a quote or is an escaped quote */
		/* We ended up making this a symbol rather than real character */
		addrlval = sv_strbuf(ml, yytext, strlen(yytext), NOFREE);
		return QTEXT;
				}
<QSTRING>\"			{
		BEGIN INITIAL;
		sv_debugf( "End QSTRING\n" );
		return QUOTE;
				}

<DOMAINLIT>([^\[\]\n\r\\]|\\.)*	return DTEXT;
<DOMAINLIT>\]			{
		BEGIN INITIAL;
		sv_debugf( "End DOMAINLIT\n" );
		return yytext[0];
		};

<COMMENT>([^\(\)\n\0\\]|\\.)*	/* ignore comments */
<COMMENT>\(			ncom++;
<COMMENT>\)			{ ncom--; if (ncom == 0) BEGIN INITIAL; }
<COMMENT><<EOF>>		{ addrerror("address parse error, "
					  "expecting `')'' "
					  "(unterminated comment)");
				  yyterminate(); }

%%

/* take input from address string provided by sieve parser */
int addrinput(char *buf, int max)
{
    extern char *addrptr;	/* current position in address string */
    size_t n;			/* number of characters to read from string */
    size_t max_size = (size_t)max;

    if(addrptr == NULL)
        n = 0;
    else
        n = strlen(addrptr) < max_size ? strlen(addrptr) : max_size;
    if (n > 0) {
	memcpy(buf, addrptr, n);
	addrptr += n;
    }
    return n;
}

/* Clean up after ourselves by free()ing the current buffer */
void addrlexfree()
{
    sv_strbuffree(&ml, FREEME);
    addr_delete_buffer( YY_CURRENT_BUFFER );
}

/* Kind of a hack, but this sets up the file statics */
void addrlexalloc()
{
    sv_strbufalloc(&ml);
}

/* Replacement for the YY_FATAL_ERROR macro,
 * which would print msg to stderr and exit. */
void addrfatalerror(const char msg[])
{
    /* Basically stop and don't do anything */
}

