%{
/*
 * header-lex.l -- RFC 2/822 Header Lexer
 * Aaron Stone
 * $Id$
 */
/***********************************************************
 *      FIXME: Needs Copyright                             *
 ***********************************************************/

/* This only works in C99 and higher... */
#ifdef DEBUG
#define libsieve_debugf(...) printf(__VA_ARGS__)
#else
#define libsieve_debugf(...) 
#endif /* ifdef DEBUG */

/* Must be defined before header.h */
#define YYSTYPE char *
#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_headerinput(b, ms))

#include <string.h>
/* sv_util */
#include "util.h"
/* sv_parser */
#include "header.h"
#include "headerinc.h"

static struct mlbuf *ml = NULL;

#define YY_FATAL_ERROR libsieve_headerfatalerror
void libsieve_headerfatalerror(const char msg[]);

/* %option nounput */
%}

%option noyywrap
%option prefix="libsieve_header"

%x S_NAME S_TEXT S_WRAP

%%

^[^\ \t\r\n]            {
                BEGIN S_NAME;
                libsieve_debugf( "Begin NAME\n" );
                yyless(0);
                }
^[\ \t]                 {
                BEGIN S_WRAP;
                libsieve_debugf( "Begin WRAP (line started with whitespace)\n" );
                yyless(0);
                }
\r\n[\ \t]              {
                BEGIN S_WRAP;
                libsieve_debugf( "Begin WRAP (\\r\\n followed either by \\ or \\t\n" );
                /* Push back the whitespace but not the CRLF; since the
		 * unfolding is only supposed to pull off an extra CRLF pair. */
                yyless(2);
                }
:([\ \t])+(\r|\n)+      {
                /* Special case of an empty header: whitespace followed by newlines */
                libsieve_debugf( "Eat some whitespace and return COLON, forget TEXT\n" );
                return COLON;
                }
:([\ \t])+              {
                /* Eat some (optional) whitespace following the colon */
                BEGIN S_TEXT;
                libsieve_debugf( "Begin TEXT, eat some whitespace and return COLON\n" );
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
                libsieve_debugf( "NAME: %s\n", yytext );
		libsieve_headerlval = libsieve_strbuf(ml, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return NAME;
                }

<S_TEXT>([^\r\n])+      {
                libsieve_debugf( "TEXT: %s\n", yytext );
		libsieve_headerlval = libsieve_strbuf(ml, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return TEXT;
                }

<S_WRAP>([^\r\n])+      {
                libsieve_debugf( "WRAP: %s\n", yytext );
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
    libsieve_header_delete_buffer( YY_CURRENT_BUFFER );
}

/* Kind of a hack, but this sets up the file statics */
void libsieve_headerlexalloc()
{
    libsieve_strbufalloc(&ml);
}

/* Replacement for the YY_FATAL_ERROR macro,
 * which would print msg to stderr and exit. */
void libsieve_headerfatalerror(const char msg[])
{
    /* Basically stop and don't do anything */
}

