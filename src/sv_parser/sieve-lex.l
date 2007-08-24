%{
/* sieve-lex.l -- RFC 3028 Sieve Lexer
 * Aaron Stone
 * $Id$
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

/* C */
#include <ctype.h>
#include <string.h>

/* sv_util */
#include "util.h"

/* sv_interface */
#include "tree.h"
#include "sieve.h"

#include "callbacks2.h"
extern struct sieve2_context *libsieve_parse_context;
#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT libsieve_parse_context

#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_sieveinput(b, ms))

int libsieve_sieveinput(char *buf, int max_size);
extern char *libsieve_encoded_char_hex(char *text, size_t len, size_t *outlen);
extern char *libsieve_encoded_char_uni(char *text, size_t len, size_t *outlen);
extern int libsieve_keyword(const char *str, unsigned int len);
extern int libsieve_sieveerror(char *);

#define YY_FATAL_ERROR libsieve_sievefatalerror
void libsieve_sievefatalerror(const char msg[]);

/* Holds a catbuf for the text: multiline. */
static struct catbuf *text = NULL;

%}

%option yylineno
%option nounput
%option noyywrap
%option prefix="libsieve_sieve"
%option never-interactive

ws		[ \t]+
ident		:?[a-zA-Z_][a-zA-Z_0-9]*
CRLF		(\r\n|\r|\n)

%state MULTILINE
%state QSTRING

%%
<MULTILINE>^\.{CRLF}	{ TRACE_DEBUG("Ending a text: block, found [%s]", text->str);
			  BEGIN INITIAL;
			  libsieve_sievelval.sval = libsieve_catbuf_free(text);
			  text = NULL;
			  return STRING; }
<MULTILINE>^\.\.	{ TRACE_DEBUG("Dot-stuffing - one dot dropped.");
			  libsieve_catbuf(text, yytext, yyleng - 1); }
<MULTILINE>\.		{ TRACE_DEBUG("Just a normal dot. Keep it.");
			  libsieve_catbuf(text, yytext, yyleng); }
<MULTILINE>{CRLF}	{ TRACE_DEBUG("Multiline newline");
			  libsieve_catbuf(text, yytext, yyleng); }
<MULTILINE>[^\.]+	{ TRACE_DEBUG("Multiline line [%s]", yytext);
			  libsieve_catbuf(text, yytext, yyleng); }
<MULTILINE><<EOF>>	{ libsieve_sieveerror("unexpected end of file in string"); 
			  if (text) {
			    libsieve_free(libsieve_catbuf_free(text));
			    text = NULL;
			  }
			  throw(SIEVE2_ERROR_PARSE); }

<QSTRING>\"		{ TRACE_DEBUG("Ending a string, found [%s]", text->str);
			  BEGIN INITIAL;
			  libsieve_sievelval.sval = libsieve_catbuf_free(text);
			  text = NULL;
			  return STRING; }
<QSTRING>\$\{hex:[0-9a-fA-F\ ]+\} {
			  size_t len = 0;
			  char *decoded = libsieve_encoded_char_hex(yytext, yyleng, &len);
			  libsieve_catbuf(text, decoded, len);
			  libsieve_free(decoded); }
<QSTRING>\$\{unicode:[0-9a-fA-F\ ]+\} {
			  size_t len = 0;
			  char *decoded = libsieve_encoded_char_uni(yytext, yyleng, &len);
			  libsieve_catbuf(text, decoded, len);
			  libsieve_free(decoded); }
<QSTRING>([^\"|^\$\{]|\\\"|{CRLF})+ {
			  TRACE_DEBUG("More string found [%s]", yytext);
			  libsieve_catbuf(text, yytext, yyleng); }
<QSTRING>.              { TRACE_DEBUG("Lone string char [%s]", yytext);
			  libsieve_catbuf(text, yytext, yyleng); }

<INITIAL>text:{ws}?(#.*)?{CRLF}	{ TRACE_DEBUG("Beginning a text: block.");
			  BEGIN MULTILINE;
			  if (text) libsieve_free(libsieve_catbuf_free(text));
			  text = libsieve_catbuf_alloc(); }
<INITIAL>\"\"		{ libsieve_sievelval.sval = libsieve_strdup("");
			  return STRING; }
<INITIAL>\"		{ BEGIN QSTRING;
			  if (text) libsieve_free(libsieve_catbuf_free(text));
			  text = libsieve_catbuf_alloc(); }
<INITIAL>[0-9]+[KMG]?	{ libsieve_sievelval.nval = libsieve_strtonum(yytext);
			  return NUMBER; }

<INITIAL>{ident}	{ int k = libsieve_keyword(yytext, yyleng);
			  if (!k) {
			    int len;
			    char error[1024];
			    memset(error, 0, 1024);
			    len = snprintf(error, 1023, "invalid keyword: %s", yytext);
			    if (len < 0 || len > 1023) {
			      snprintf(error, 1023, "invalid keyword.");
			    }
			    libsieve_sieveerror(error); 
			    if (text) {
			      libsieve_free(libsieve_catbuf_free(text));
			      text = NULL;
			    }
			    throw(SIEVE2_ERROR_PARSE);
			} return k; }
	
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
    libsieve_sievelex_destroy();
}

/* Kind of a hack, but this sets up the file statics */
void libsieve_sievelexalloc()
{
    libsieve_sieverestart( (FILE *)YY_CURRENT_BUFFER );
}

/* Restart the lexer before each invocation of the parser */
void libsieve_sievelexrestart()
{
    libsieve_sieverestart( (FILE *)YY_CURRENT_BUFFER );
}

/* Replacement for the YY_FATAL_ERROR macro,
 * which would print msg to stderr and exit. */
void libsieve_sievefatalerror(const char msg[])
{
    /* Basically stop and don't do anything
     * Supress the unused yy_fatal_error warning. */
    if (0) yy_fatal_error(msg);
}

