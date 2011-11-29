%{
/* header.y -- RFC 2/822 Header Parser
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Better yacc error messages please */
#define YYERROR_VERBOSE
/* Must be defined before header.h */
#define YYSTYPE char *

/* sv_util */
#include "src/sv_util/util.h"
#include "src/sv_interface/callbacks2.h"
/* sv_parser */
#include "header.h"
#include "headerinc.h"
#include "header-lex.h"
extern YY_DECL;
/* sv_include */
#include "src/sv_include/sieve2_error.h"

#define THIS_MODULE "sv_parser"
static void libsieve_headerentry(struct sieve2_context *context, char *name, char *body);
static int libsieve_headerappend(struct sieve2_context *context);
static void libsieve_headererror(struct sieve2_context *context, void *yyscanner, const char *str);

%}

%name-prefix="libsieve_header"
%define api.pure
%lex-param {struct sieve2_context *context}
%lex-param {void *header_scan}
%parse-param {struct sieve2_context *context}
%parse-param {void *header_scan}
%token NAME COLON TEXT WRAP
%start headers

%%
headers: header                 {
                /* Allocate a new cache block */
                if (libsieve_headerappend(context) != SIEVE2_OK)
                    /* Problems... */;
                }
        | headers header        {
                /* Allocate a new cache block */
                if (libsieve_headerappend(context) != SIEVE2_OK)
                    /* Problems... */;
                };

header: NAME COLON              {
                TRACE_DEBUG( "header: NAME COLON: %s:", $1 );
                libsieve_headerentry(context, $1, NULL);
                }
        | NAME COLON body       {
                TRACE_DEBUG( "header: NAME COLON body: %s:%s", $1, $3 );
                libsieve_headerentry(context, $1, $3);
                };

body: TEXT                      {
                /* Default action is $$ = $1 */
                TRACE_DEBUG( "body: TEXT: %s", $1 );
                }
        | body WRAP             {
                TRACE_DEBUG( "body: body WRAP: %s %s", $1, $2 );
                $$ = libsieve_strbuf(context->strbuf, libsieve_strconcat( $1, $2, NULL ), strlen($1)+strlen($2), FREEME);
                };

%%

/* copy header error message into buffer provided by sieve parser */
void libsieve_headererror(struct sieve2_context *context, yyscan_t yyscanner, const char *s)
{
    TRACE_DEBUG( "Header parse error on line %d: %s",
		 libsieve_headerget_lineno(yyscanner), s);
    libsieve_do_error_header(context, libsieve_headerget_lineno(yyscanner), s);
}

/* Wrapper for headerparse() which sets up the 
 * required environment and allocates variables
 * */
header_list_t *libsieve_header_parse_buffer(struct sieve2_context *context, header_list_t **data, char **ptr)
{
    header_list_t *newdata = NULL;
    yyscan_t header_scan = context->header_scan;

    context->header_hl = NULL;
    if (libsieve_headerappend(context) != SIEVE2_OK)
        /* Problems... */;
    YY_BUFFER_STATE buf = libsieve_header_scan_string(*ptr, header_scan);

    if(libsieve_headerparse(context, header_scan)) {
        TRACE_DEBUG( "Header parse error, returning null" );
	while (context->header_hl) {
	    header_list_t *next = context->header_hl->next;
            libsieve_free(context->header_hl->h->contents);
            libsieve_free(context->header_hl->h);
            libsieve_free(context->header_hl);
	    context->header_hl = next;
	}
	libsieve_header_delete_buffer(buf, header_scan);
	context->header_hl = NULL;
	return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while(newdata != NULL) {
        newdata = newdata->next;
    }

    /* Same thing with that extra struct... */
    newdata = context->header_hl->next;
    libsieve_header_delete_buffer(buf, header_scan);
    libsieve_free(context->header_hl->h->contents);
    libsieve_free(context->header_hl->h);
    libsieve_free(context->header_hl);

    if(*data == NULL)
        *data = newdata;

    context->header_hl = newdata;
    return *data;
}

int libsieve_headerappend(struct sieve2_context *context)
{
    header_list_t *newlist = NULL;
    header_t *newhead = NULL;
    char **c = NULL;

    newlist = (header_list_t *)libsieve_malloc(sizeof(header_list_t));
    if (newlist == NULL)
        return SIEVE2_ERROR_NOMEM;

    newhead = (header_t *)libsieve_malloc(sizeof(header_t));
    if (newhead == NULL) {
        libsieve_free(newlist);
        return SIEVE2_ERROR_NOMEM;
    }

    c = (char **)libsieve_malloc(2 * sizeof(char *));
    if (c == NULL) {
        libsieve_free(newlist);
        libsieve_free(newhead);
        return SIEVE2_ERROR_NOMEM;
    }

    TRACE_DEBUG( "Prepending a new headerlist and header struct" );
    newhead->count = 0;
    newhead->space = 1;
    newhead->contents = c;
    newhead->contents[0] = NULL;
    newhead->contents[1] = NULL;
    newlist->h = newhead;
    newlist->next = context->header_hl;
    context->header_hl = newlist;

    return SIEVE2_OK;
}

void libsieve_headerentry(struct sieve2_context *context, char *name, char *body)
{
    header_t *h = context->header_hl->h;
    TRACE_DEBUG( "Entering name and body into header struct" );
    if (h == NULL)
        TRACE_DEBUG( "Why are you giving me a NULL struct!?" );
	/* Hmm, big big trouble here... */;

    size_t namelen = strlen(name);
    // h->name = libsieve_strtolower(libsieve_strndup(name, namelen), namelen);
    h->name = libsieve_strtolower(name, namelen);
    h->contents[0] = body;
    h->count = 1;

    /* This function is NOT designed for general purpose
     * entries, but only for making the very first entry!
     * */
}
