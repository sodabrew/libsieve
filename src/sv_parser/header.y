%{
/*
 * header.y -- RFC 2/822 Header Parser
 * Aaron Stone
 * $Id$
 */
/**********************************************************
        FIXME: Needs Copyright
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This only works in C99 and higher... */
#ifdef DEBUG
#define libsieve_debugf(...) printf(__VA_ARGS__)
#else
#define libsieve_debugf(...) 
#endif /* ifdef DEBUG */

/* Better yacc error messages please */
#define YYERROR_VERBOSE
/* Must be defined before header.h */
#define YYSTYPE char *

/* sv_util */
#include "util.h"
/* sv_parser */
#include "header.h"
#include "headerinc.h"
/* sv_include */
#include "sieve2_error.h"

/* There are global to this file */
char *libsieve_headerptr;          /* pointer to sieve string for header lexer */
char *libsieve_headererr;          /* buffer for sieve parser error messages */
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
                libsieve_debugf( "header: NAME COLON: %s:\n", $1 );
                libsieve_headerentry(hl->h, $1, NULL);
                }
        | NAME COLON body       {
                libsieve_debugf( "header: NAME COLON body: %s:%s\n", $1, $3 );
                libsieve_headerentry(hl->h, $1, $3);
                };

body: TEXT                      {
                /* Default action is $$ = $1 */
                libsieve_debugf( "body: TEXT: %s\n", $1 );
                }
        | body WRAP             {
                libsieve_debugf( "body: body WRAP: %s %s\n", $1, $2 );
                $$ = libsieve_strbuf(ml, libsieve_strconcat( $1, $2, NULL ), strlen($1)+strlen($2), FREEME);
                };

%%

/* copy header error message into buffer provided by sieve parser */
void libsieve_headererror(const char *s)
{
    extern char *libsieve_headererr;
    libsieve_headererr = libsieve_strdup(s, strlen(s));
}

/* Wrapper for headerparse() which sets up the 
 * required environment and allocates variables
 */
header_list_t *libsieve_header_parse_buffer(header_list_t **data, char **ptr, char **err)
{
    header_list_t *newdata = NULL;
    extern header_list_t *hl;
    extern struct mlbuf *ml;

    hl = NULL;
    if (libsieve_headerappend(&hl) != SIEVE2_OK)
        /* Problems... */;

    (const char *)libsieve_headerptr = *ptr;

    if(libsieve_headerparse()) {
	libsieve_strbuffree(&ml, FREEME);
	libsieve_debugf( "Parser ERROR: %s\n", libsieve_headererr );
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

    libsieve_debugf( "Prepending a new headerlist and header struct\n" );
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
    libsieve_debugf( "Entering name and body into header struct\n" );
    if (h == NULL)
        libsieve_debugf( "Why are you giving me a NULL struct!?\n" );
	/* Hmm, big big trouble here... */;

    h->name = libsieve_strtolower(libsieve_strdup(name, strlen(name)), strlen(name));
    /* Looks like we don't need to make a copy here after all
    h->contents[0] = libsieve_strdup(body, strlen(body));
    */
    h->contents[0] = body;
    h->count = 1;

    /* This function is NOT designed for general purpose
     * entries, but only for making the very first entry!
     */
}

void libsieve_headeryaccalloc()
{
    libsieve_strbufalloc(&ml);
}

void libsieve_headeryaccfree()
{
    /* This must correspond to sieve2_messagecache
     * knowing not to free its contents[] entries.
     */
    libsieve_strbuffree(&ml, FREEME);
}

