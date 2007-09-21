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

/* sv_parser */
#include "sieve-encodedchar.h"
#include "sieve-keywords.h"
#include "parser.h"

/* sv_interface */
#include "tree.h"
#include "sieve.h"

#include "callbacks2.h"

#define context yyextra
#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT context

#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_lexinput(&context->sieve_ptr, &context->sieve_len, b, ms))
#define YY_FATAL_ERROR(msg) libsieve_do_error_exec(libsieve_sieveget_extra(yyscanner), msg)

/* Holds a catbuf for the text: multiline. */
static struct catbuf *text = NULL;

%}

%option noyywrap nounput
%option yylineno never-interactive
%option prefix="libsieve_sieve"
%option header-file="sieve-lex.h"
%option reentrant extra-type="struct sieve2_context *"

ws		[ \t]+
ident		:?[a-zA-Z_][a-zA-Z_0-9]*
CRLF		(\r\n|\r|\n)

%state MULTILINE
%state QSTRING
%state COMMENT

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
<MULTILINE><<EOF>>	{ libsieve_sieveerror(context, "unexpected end of file in string"); 
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
			  char *decoded = libsieve_encoded_char_hex(context, yytext, yyleng, &len);
			  libsieve_catbuf(text, decoded, len);
			  libsieve_free(decoded); }
<QSTRING>\$\{unicode:[0-9a-fA-F\ ]+\} {
			  size_t len = 0;
			  char *decoded = libsieve_encoded_char_uni(context, yytext, yyleng, &len);
			  libsieve_catbuf(text, decoded, len);
			  libsieve_free(decoded); }
<QSTRING>([^\"|^\$\{]|\\\"|{CRLF})+ {
			  TRACE_DEBUG("More string found [%s]", yytext);
			  libsieve_catbuf(text, yytext, yyleng); }
<QSTRING>.              { TRACE_DEBUG("Lone string char [%s]", yytext);
			  libsieve_catbuf(text, yytext, yyleng); }

<COMMENT>\*\/           { BEGIN INITIAL; }
<COMMENT>. ;            /* ignore comments */

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
			    libsieve_sieveerror(context, error); 
			    if (text) {
			      libsieve_free(libsieve_catbuf_free(text));
			      text = NULL;
			    }
			    throw(SIEVE2_ERROR_PARSE);
			} return k; }
	
<INITIAL>[ \t\n\r] ;	/* ignore whitespace */
<INITIAL>#.* ;		/* ignore comments */
<INITIAL>\/\*           { BEGIN COMMENT; }
.			return yytext[0];

%%

