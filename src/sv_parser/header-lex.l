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
#include "src/sv_util/util.h"
/* sv_interface */
#include "src/sv_interface/callbacks2.h"
/* sv_parser */
#include "header.h"
#include "headerinc.h"

#define THIS_MODULE "sv_parser"
%}

%option yylineno 8bit fast
%option noyywrap noinput nounput
%option reentrant never-interactive
%option outfile="header-lex.c" header-file="header-lex.h"
%option bison-bridge
%option prefix="libsieve_header"

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
		*yylval = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return NAME;
                }

<S_TEXT>([^\r\n])+      {
                TRACE_DEBUG( "TEXT: %s", yytext );
		*yylval = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return TEXT;
                }

<S_WRAP>([^\r\n])+      {
                TRACE_DEBUG( "WRAP: %s", yytext );
		*yylval = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
                BEGIN INITIAL;
                return WRAP;
                }

%%
