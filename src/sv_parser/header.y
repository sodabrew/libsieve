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
#include "util.h"
#include "callbacks2.h"
/* sv_parser */
#include "header.h"
#include "headerinc.h"
/* sv_include */
#include "sieve2_error.h"

#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT libsieve_parse_context

/* There are global to this file */
char *libsieve_headerptr;          /* pointer to sieve string for header lexer */
char *libsieve_headererr;          /* buffer for sieve parser error messages */
extern struct sieve2_context *libsieve_parse_context;
static header_list_t *hl = NULL;
static struct mlbuf *ml = NULL;
%}

%name-prefix="libsieve_header"

%token NAME COLON TEXT WRAP
%start headers

%%
headers: header                 {
                /* Allocate a new cache block */
                if (libsieve_headerappend(&hl) != SIEVE2_OK)
                    /* Problems... */;
                }
        | headers header        {
                /* Allocate a new cache block */
                if (libsieve_headerappend(&hl) != SIEVE2_OK)
                    /* Problems... */;
                };

header: NAME COLON              {
                TRACE_DEBUG( "header: NAME COLON: %s:", $1 );
                libsieve_headerentry(hl->h, $1, NULL);
                }
        | NAME COLON body       {
                TRACE_DEBUG( "header: NAME COLON body: %s:%s", $1, $3 );
                libsieve_headerentry(hl->h, $1, $3);
                };

body: TEXT                      {
                /* Default action is $$ = $1 */
                TRACE_DEBUG( "body: TEXT: %s", $1 );
                }
        | body WRAP             {
                TRACE_DEBUG( "body: body WRAP: %s %s", $1, $2 );
                $$ = libsieve_strbuf(ml, libsieve_strconcat( $1, $2, NULL ), strlen($1)+strlen($2), FREEME);
                };

%%

/* copy header error message into buffer provided by sieve parser */
void libsieve_headererror(const char *s)
{
    extern char *libsieve_headererr;
    libsieve_headererr = libsieve_strdup(s);
}

/* Wrapper for headerparse() which sets up the 
 * required environment and allocates variables
 * */
header_list_t *libsieve_header_parse_buffer(header_list_t **data, char **ptr, char **err)
{
    header_list_t *newdata = NULL;
    extern header_list_t *hl;

    hl = NULL;
    if (libsieve_headerappend(&hl) != SIEVE2_OK)
        /* Problems... */;

    libsieve_headerptr = *ptr;

    libsieve_headerlexrestart();

    if(libsieve_headerparse()) {
        TRACE_DEBUG( "Header parse error: %s", libsieve_headererr );
        *err = libsieve_headererr;
        libsieve_free(hl->h->contents);
        libsieve_free(hl->h);
        libsieve_free(hl);
	return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while(newdata != NULL) {
        newdata = newdata->next;
    }

    /* Same thing with that extra struct... */
    newdata = hl->next;
    libsieve_free(hl->h->contents);
    libsieve_free(hl->h);
    libsieve_free(hl);

    if(*data == NULL)
        *data = newdata;

    return *data;
}

int libsieve_headerappend(header_list_t **hl)
{
    header_list_t *newlist = NULL;
    header_t *newhead = NULL;
    char **c = NULL;

    newlist = (header_list_t *)libsieve_malloc(sizeof(header_list_t));
    if (newlist == NULL)
        return SIEVE2_ERROR_NOMEM;
    newhead = (header_t *)libsieve_malloc(sizeof(header_t));
    if (newhead == NULL)
        return SIEVE2_ERROR_NOMEM;
    c = (char **)libsieve_malloc(2 * sizeof(char *));
    if (c == NULL)
        return SIEVE2_ERROR_NOMEM;

    TRACE_DEBUG( "Prepending a new headerlist and header struct" );
    newhead->count = 0;
    newhead->space = 1;
    newhead->contents = c;
    newhead->contents[0] = NULL;
    newhead->contents[1] = NULL;
    newlist->h = newhead;
    newlist->next = *hl;
    *hl = newlist;

    return SIEVE2_OK;
}

void libsieve_headerentry(header_t *h, char *name, char *body)
{
    TRACE_DEBUG( "Entering name and body into header struct" );
    if (h == NULL)
        TRACE_DEBUG( "Why are you giving me a NULL struct!?" );
	/* Hmm, big big trouble here... */;

    size_t namelen = strlen(name);
    h->name = libsieve_strtolower(libsieve_strndup(name, namelen), namelen);
    h->contents[0] = body;
    h->count = 1;

    /* This function is NOT designed for general purpose
     * entries, but only for making the very first entry!
     * */
}

void libsieve_headeryaccalloc()
{
    libsieve_strbufalloc(&ml);
}

void libsieve_headeryaccfree()
{
    /* This must correspond to sieve2_messagecache
     * knowing not to free its contents[] entries.
     * */
    libsieve_strbuffree(&ml, FREEME);
}

