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


/* Must be defined before addr.h */
#define YYSTYPE char *

#include <string.h>
/* sv_util */
#include "src/sv_util/util.h"
/* sv_interface */
#include "src/sv_interface/callbacks2.h"
/* sv_parser */
#include "addr.h"
#include "addrinc.h"

#define THIS_MODULE "sv_parser"
%}

%option 8bit fast
%option noyywrap noinput nounput
%option reentrant never-interactive
%option outfile="addr-lex.c" header-file="addr-lex.h"
%option bison-bridge extra-type="int"
%option prefix="libsieve_addr"

%x QSTRING DOMAINLIT COMMENT

%%

\"				{ BEGIN QSTRING; TRACE_DEBUG( "Begin QSTRING" ); return QUOTE; }
\[				{ BEGIN DOMAINLIT; TRACE_DEBUG( "Begin DOMAINLIT" ); return yytext[0]; }
\(				{ yyextra = 1; TRACE_DEBUG( "Begin COMMENT" ); BEGIN COMMENT; }
\)				{ libsieve_addrerror(context, yyscanner, "address parse error, "
					  "unexpected `')'' "
					  "(unbalanced comment)");
				  yyterminate(); }

[<>\(\)@,;:\"\.\[\]\\]	{
		/* Return the special character */
		return yytext[0];
				}
([ \t\n\r])+			{
		TRACE_DEBUG( "Whitespace silently murdered." );
		/* Ignore whitespace by not returning */
				}
([^<>\(\)@,;:\"\.\[\]\\ \t\n\r])+	{
		/* Match any set of non-special-characters */
		(*yylval) = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
		return ATOM;
				}
([^<>\(\)@,;:\"\.\[\]\\ \t\n\r])([^<>\(\)@,;:\"\[\]\\ \t\n\r])*        {
                /* Match any set of non-special-characters, the first char may not be dot */
                (*yylval) = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
               return DOTATOM;
                                }
<QSTRING>([^\"]|\\\")+		{
		/* Match anything that's not a quote or is an escaped quote */
		/* We ended up making this a symbol rather than real character */
		(*yylval) = libsieve_strbuf(context->strbuf, yytext, strlen(yytext), NOFREE);
		return QTEXT;
				}
<QSTRING>\"			{
		BEGIN INITIAL;
		TRACE_DEBUG( "End QSTRING" );
		return QUOTE;
				}

<DOMAINLIT>([^\[\]\n\r\\]|\\.)*	return DTEXT;
<DOMAINLIT>\]			{
		BEGIN INITIAL;
		TRACE_DEBUG( "End DOMAINLIT" );
		return yytext[0];
		};

<COMMENT>([^\(\)\n\0\\]|\\.)*	/* ignore comments */
<COMMENT>\(			yyextra++;
<COMMENT>\)			{ yyextra--; if (yyextra == 0) BEGIN INITIAL; }
<COMMENT><<EOF>>		{ libsieve_addrerror(context, yyscanner, "address parse error, "
					  "expecting `')'' "
					  "(unterminated comment)");
				  yyterminate(); }

%%
