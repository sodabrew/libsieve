%{
/* header-lex.l -- RFC 2/822 Header Lexer
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */


/* Must be defined before header.h */
#define YYSTYPE char *
#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_headerinput(b, ms))

#include <string.h>

/* sv_util */
#include "src/sv_util/util.h"

/* sv_parser */
#include "header.h"
#include "headerinc.h"

/* sv_interface */
#include "src/sv_interface/callbacks2.h"

#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT libsieve_parse_context
extern struct sieve2_context *libsieve_parse_context;

static struct mlbuf *ml = NULL;

#define YY_NO_UNISTD_H 1
#define YY_FATAL_ERROR libsieve_headerfatalerror
void libsieve_headerfatalerror(const char msg[]);

%}

%option yylineno
%option noinput
%option noyywrap
%option nounput
%option prefix="libsieve_header"
%option never-interactive

%x S_NAME S_TEXT S_WRAP

%%

^[^\ \t\r\n]            {
                BEGIN S_NAME;
                TRACE_DEBUG( "Begin NAME" );
                yyless(0);
                }
^[\ \t]                 {
                BEGIN S_WRAP;
                TRACE_DEBUG( "Begin WRAP (line started with whitespace)" );
                yyless(0);
                }
\r\n[\ \t]              {
                BEGIN S_WRAP;
                TRACE_DEBUG( "Begin WRAP (\\r\\n followed either by \\ or \\t" );
                /* Push back the whitespace but not the CRLF; since the
		 * unfolding is only supposed to pull off an extra CRLF pair. */
                yyless(2);
                }
:([\ \t])+(\r|\n)+      {
                /* Special case of an empty header: whitespace followed by newlines */
                TRACE_DEBUG( "Eat some whitespace and return COLON, forget TEXT" );
                return COLON;
                }
:([\ \t])+              {
                /* Eat some (optional) whitespace following the colon */
                BEGIN S_TEXT;
                TRACE_DEBUG( "Begin TEXT, eat some whitespace and return COLON" );
                return COLON;
                }
(\r|\n)+                {
                /* Eat stray newlines, such as those at the end of every line... */
                }

<S_NAME>([^:])+         {
                /* FIXME: Should be something like [!-9;-~]... */
                /* Field names must be in these ASCII ranges:
                 * 33  !  to  57  9
                 * 59  ;  to  126 ~
                 * Note that  58  :  is reserved as the field separator */
                TRACE_DEBUG( "NAME: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(ml, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return NAME;
                }

<S_TEXT>([^\r\n])+      {
                TRACE_DEBUG( "TEXT: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(ml, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return TEXT;
                }

<S_WRAP>([^\r\n])+      {
                TRACE_DEBUG( "WRAP: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(ml, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return WRAP;
                }

%%

/* take input from header string provided by sieve parser */
int libsieve_headerinput(char *buf, int max)
{
    extern char *libsieve_headerptr;	/* current position in header string */
    size_t n;			/* number of characters to read from string */
    size_t max_size = (size_t)max;

    if(libsieve_headerptr == NULL)
        n = 0;
    else
        n = strlen(libsieve_headerptr) < max_size ? strlen(libsieve_headerptr) : max_size;
    if (n > 0) {
	memcpy(buf, libsieve_headerptr, n);
	libsieve_headerptr += n;
    }
    return n;
}

/* Clean up after ourselves by free()ing the current buffer */
void libsieve_headerlexfree()
{
    libsieve_strbuffree(&ml, FREEME);
    libsieve_headerlex_destroy();
}

/* Kind of a hack, but this sets up the file statics */
void libsieve_headerlexalloc()
{
    libsieve_strbufalloc(&ml);
    libsieve_headerrestart( (FILE *)YY_CURRENT_BUFFER );
}

/* Restart the lexer before each invocation of the parser */
void libsieve_headerlexrestart()
{
    libsieve_headerrestart( (FILE *)YY_CURRENT_BUFFER );
}

/* Replacement for the YY_FATAL_ERROR macro,
 * which would print msg to stderr and exit. */
void libsieve_headerfatalerror(const char msg[])
{
    /* Basically stop and don't do anything
     * Supress the unused yy_fatal_error warning. */
    if (0) yy_fatal_error(msg);
}

