%{
/*
 * header.y -- RFC 2/822 Header Parser
 * Aaron Stone
 * $Id$
 */
/**********************************************************
        FIXME: Needs Copyright
 **********************************************************/

#include <stdlib.h>
#include <string.h>

/* This only works in C99 and higher... */
#ifdef DEBUG
#define sv_debugf(...) printf(__VA_ARGS__)
#else
#define sv_debugf(...) 
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
char *headerptr;          /* pointer to sieve string for header lexer */
char *headererr;          /* buffer for sieve parser error messages */
header_list_t *hl = NULL;
static struct mlbuf *ml = NULL;
%}

%token NAME, COLON, TEXT, WRAP
%start headers

%%
headers: header                 {
                /* Allocate a new cache block */
                if (headerappend(&hl) != SIEVE2_OK)
                    /* Problems... */;
                };
        | headers header        {
                /* Allocate a new cache block */
                if (headerappend(&hl) != SIEVE2_OK)
                    /* Problems... */;
                };

header: NAME COLON body         {
                sv_debugf( "header: NAME COLON body: %s:%s\n", $1, $3 );
                headerentry(hl->h, $1, $3);
                };

body: TEXT                      {
                /* Default action is $$ = $1 */
                sv_debugf( "body: TEXT: %s\n", $1 );
                }
        | body WRAP             {
                sv_debugf( "body: body WRAP: %s %s\n", $1, $2 );
                $$ = sv_strbuf(ml, sv_strconcat( $1, $2, NULL ), strlen($1)+strlen($2), FREEME);
                };

%%

/* copy header error message into buffer provided by sieve parser */
void headererror(const char *s)
{
    extern char *headererr;
    headererr = sv_strdup(s, strlen(s));
}

/* Wrapper for headerparse() which sets up the 
 * required environment and allocates variables
 */
header_list_t *header_parse_buffer(header_list_t **data, char **ptr, char **err)
{
    header_list_t *newdata = NULL;
    extern header_list_t *hl;
    extern struct mlbuf *ml;

    hl = NULL;
    if (headerappend(&hl) != SIEVE2_OK)
        /* Problems... */;

    (const char *)headerptr = *ptr;

    if(headerparse()) {
	sv_strbuffree(&ml, FREEME);
	sv_debugf( "Parser ERROR: %s\n", headererr );
	return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while(newdata != NULL) {
        newdata = newdata->next;
    }

    /* Same thing with that extra struct... */
    newdata = hl->next;
    sv_free(hl->h->contents);
    sv_free(hl->h);
    sv_free(hl);

    if(*data == NULL)
        *data = newdata;

    return *data;
}

int headerappend(header_list_t **hl)
{
    header_list_t *newlist = NULL;
    header_t *newhead = NULL;
    char **c = NULL;

    newlist = (header_list_t *)sv_malloc(sizeof(header_list_t));
    if (newlist == NULL)
        return SIEVE2_ERROR_NOMEM;
    newhead = (header_t *)sv_malloc(sizeof(header_t));
    if (newhead == NULL)
        return SIEVE2_ERROR_NOMEM;
    c = (char **)sv_malloc(2 * sizeof(char *));
    if (c == NULL)
        return SIEVE2_ERROR_NOMEM;

    sv_debugf( "Prepending a new headerlist and header struct\n" );
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

void headerentry(header_t *h, char *name, char *body)
{
    sv_debugf( "Entering name and body into header struct\n" );
    if (h == NULL)
        sv_debugf( "Why are you giving me a NULL struct!?\n" );
	/* Hmm, big big trouble here... */;

    h->name = sv_strtolower(sv_strdup(name, strlen(name)), strlen(name));
    /* Looks like we don't need to make a copy here after all
    h->contents[0] = sv_strdup(body, strlen(body));
    */
    h->contents[0] = body;
    h->count = 1;

    /* This function is NOT designed for general purpose
     * entries, but only for making the very first entry!
     */
}

void headeryaccalloc()
{
    sv_strbufalloc(&ml);
}

void headeryaccfree()
{
    /* This must correspond to sieve2_messagecache
     * knowing not to free its contents[] entries.
     */
    sv_strbuffree(&ml, FREEME);
}

