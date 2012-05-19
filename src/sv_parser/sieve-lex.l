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
#include "src/sv_util/util.h"
/* sv_interface */
#include "src/sv_interface/tree.h"
#include "src/sv_interface/callbacks2.h"
/* sv_parser */
#include "sieve.h"
#include "sieveinc.h"

#define THIS_MODULE "sv_parser"
extern YY_DECL;

%}

%option yylineno 8bit fast
%option noyywrap noinput nounput
%option noyyget_extra noyyget_leng noyyget_text noyyget_in noyyset_in
%option noyyset_out noyyget_out noyyget_lval noyyset_lval
%option noyyset_debug noyyget_debug
%option reentrant never-interactive
%option outfile="sieve-lex.c" header-file="sieve-lex.h"
%option bison-bridge extra-type="struct catbuf*"
%option prefix="libsieve_sieve"

ws		[ \t]+
ident		[a-zA-Z_][a-zA-Z_0-9]*
CRLF		(\r\n|\r|\n)

%state MULTILINE
%state QSTRING
%state COMMENT

%%
<MULTILINE>^\.{CRLF}	{ TRACE_DEBUG("Ending a text: block, found [%s]", yyextra->str);
			  BEGIN INITIAL;
			  (*yylval).sval = libsieve_catbuf_free(yyextra);
			  return STRING; }
<MULTILINE>^\.\.	{ TRACE_DEBUG("Dot-stuffing - one dot dropped.");
			  libsieve_catbuf(yyextra, yytext, yyleng - 1); }
<MULTILINE>\.		{ TRACE_DEBUG("Just a normal dot. Keep it.");
			  libsieve_catbuf(yyextra, yytext, yyleng); }
<MULTILINE>{CRLF}	{ TRACE_DEBUG("Multiline newline");
			  libsieve_catbuf(yyextra, yytext, yyleng); }
<MULTILINE>[^\.]+	{ TRACE_DEBUG("Multiline line [%s]", yytext);
			  libsieve_catbuf(yyextra, yytext, yyleng); }
<MULTILINE><<EOF>>	{ libsieve_sieveerror(context, yyscanner, "unexpected end of file in string"); 
			  yyterminate(); }

<QSTRING>\"		{ BEGIN INITIAL; }
<QSTRING>([^\"]|\\\"|{CRLF})+ { (*yylval).sval = libsieve_strndup(yytext, yyleng);
			  return STRING; }

<COMMENT>\*\/           { BEGIN INITIAL; }
<COMMENT>. ;            /* ignore comments */

<INITIAL>text:{ws}?(#.*)?{CRLF}	{ TRACE_DEBUG("Beginning a text: block.");
			  BEGIN MULTILINE;
			  yyextra = libsieve_catbuf_alloc(); }
<INITIAL>\"\"		{ (*yylval).sval = libsieve_strdup("");
			  return STRING; }
<INITIAL>\"		{ BEGIN QSTRING; }
<INITIAL>[0-9]+[KMG]?	{ (*yylval).nval = libsieve_strtonum(yytext);
			  return NUMBER; }
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
<INITIAL>hasflag	return HASFLAG;
<INITIAL>mark		return MARK;
<INITIAL>unmark		return UNMARK;
<INITIAL>:flags		return FLAGS;
<INITIAL>notify		return NOTIFY;
<INITIAL>valid_notif_method return VALIDNOTIF;
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
<INITIAL>:from		return FROM;
<INITIAL>:handle	return HANDLE;
<INITIAL>:comparator	return COMPARATOR;
<INITIAL>:is		return IS;
<INITIAL>:count		return COUNT;
<INITIAL>:value		return VALUE;
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
<INITIAL>\/\*           { BEGIN COMMENT; }
.			return yytext[0];

%%
