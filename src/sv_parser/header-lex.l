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

#include <string.h>

/* sv_util */
#include "util.h"

/* sv_parser */
#include "header.h"
#include "headerinc.h"

/* sv_interface */
#include "callbacks2.h"

#define context yyextra
#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT context

#define YY_NO_UNISTD_H 1

#undef YY_INPUT
#define YY_INPUT(b, r, ms) (r = libsieve_lexinput(&context->header_ptr, &context->header_len, b, ms))
#define YY_FATAL_ERROR(msg) libsieve_do_error_exec(libsieve_headerget_extra(yyscanner), msg)

%}

%option noyywrap nounput
%option never-interactive
%option prefix="libsieve_header"
%option header-file="header-lex.h"
%option reentrant extra-type="struct sieve2_context *"

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
:([\ \t])+(\r|\n)+([\ \t])+      {
                /* Special case of a malformed header: whitespace followed by newlines followed by whitespace */
                BEGIN S_TEXT;
                TRACE_DEBUG( "Begin TEXT, eat some whitespace and return COLON" );
                return COLON;
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

<S_NAME>TODO      {
                /* Special case of a malformed header: wrapped line not starting with whitespace */
                BEGIN S_WRAP;
                TRACE_DEBUG( "Begin TEXT, eat some whitespace and return COLON" );
                return WRAP;
                }

<S_NAME>([^:])+         {
                /* FIXME: Should be something like [!-9;-~]... */
                /* Field names must be in these ASCII ranges:
                 * 33  !  to  57  9
                 * 59  ;  to  126 ~
                 * Note that  58  :  is reserved as the field separator */
                TRACE_DEBUG( "NAME: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(context->ml, yytext, yyleng, NOFREE);
                BEGIN INITIAL;
                return NAME;
                }

<S_TEXT>([^\r\n])+      {
                TRACE_DEBUG( "TEXT: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(context->ml, yytext, yyleng, NOFREE);
                BEGIN INITIAL;
                return TEXT;
                }

<S_WRAP>([^\r\n])+      {
                TRACE_DEBUG( "WRAP: %s", yytext );
		libsieve_headerlval = libsieve_strbuf(context->ml, yytext, yyleng, NOFREE);
                BEGIN INITIAL;
                return WRAP;
                }

%%

