%{
/*
 * addr.y -- RFC 822 address parser
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

#include <stdlib.h>
#include <string.h>

/* This only works in C99 and higher... */
#ifdef DEBUG
#define sv_debugf(...) printf(__VA_ARGS__)
#else
#define sv_debugf(...) 
#endif /* ifdef DEBUG */

/* Better yacc error messages make me happy */
#define YYERROR_VERBOSE
/* Must be defined before addr.h */
#define YYSTYPE char *

/* sv_util */
#include "util.h"
/* sv_parser */
#include "addr.h"
#include "addrinc.h"

/* There are global to this file */
char *addrptr;          /* pointer to sieve string for address lexer */
char *addrerr;          /* buffer for sieve parser error messages */
struct address *addr = NULL;
static struct mlbuf *ml = NULL;
%}

%token ATOM, QTEXT, DTEXT, QUOTE
%start address

%%
address: mailboxes			{ sv_debugf( "address: mailbox: %s\n", $1 ); }
	| group				{ sv_debugf( "address: group: %s\n", $1 ); };

group: phrase ':' ';'			{ sv_debugf( "group: phrase: %s\n", $1 ); }
	| phrase ':' mailboxes ';'	{ sv_debugf( "group: phrase mailboxes: %s %s\n", $1, $3 ); };

mailboxes: mailbox			{
	 	/* Each new address is allocated here and back-linked */
		sv_debugf( "mailboxes: mailbox: %s\n", $1 );
		sv_debugf( "allocating newaddr %s\n" );
		addrappend(&addr);
		}
	| mailboxes ',' mailbox		{
	 	/* Each new address is allocated here and back-linked */
		sv_debugf( "mailboxes: mailboxes mailbox: %s %s\n", $1, $3 );
		sv_debugf( "allocating newaddr %s\n" );
		addrappend(&addr);
		};

mailbox: 
	routeaddr			{ sv_debugf( "mailbox: routeaddr: %s\n", $1 ); };
	| addrspec			{ sv_debugf( "mailbox: addrspec: %s\n", $1 ); };
	| phrase routeaddr		{
		sv_debugf( "mailbox: phrase routeaddr: %s %s\n", $1, $2 );
		// This is a "top terminal" state...
		sv_debugf( "addr->name: %s\n", $1 );
		addr->name = sv_strdup( $1, strlen($1) );
		};

routeaddr: '<' addrspec '>'		{ sv_debugf( "routeaddr: addrspec: %s\n", $2 ); }
	| '<' route ':' addrspec '>'	{
		sv_debugf( "routeaddr: route addrspec: %s\n", $2, $4 );
		// This is a "top terminal" state...
		sv_debugf( "addr->route: %s\n", $2 );
		addr->route = sv_strdup( $2, strlen($2) );
		};
	
addrspec: localpart '@' domain		{
		sv_debugf( "addrspec: localpart domain: %s %s\n", $1, $3 );
		// This is a "top terminal" state...
		sv_debugf( "addr->mailbox: %s\n", $1 );
		addr->mailbox = sv_strdup( $1, strlen($1) );
		sv_debugf( "addr->domain: %s\n", $3 );
		addr->domain = sv_strdup( $3, strlen($3) );
		};

route: '@' domain			{
		sv_debugf( "route: domain: %s\n", $2 );
                $$ = sv_strbuf(ml, sv_strconcat( "@", $2, NULL ), strlen($2)+1, FREEME);
		};
	| '@' domain ',' route		{
		sv_debugf( "route: domain route: %s %s\n", $2, $4 );
		$$ = sv_strbuf(ml, sv_strconcat( "@", $2, ",", $4, NULL ), strlen($2)+strlen($4)+2, FREEME);
		};

localpart: word				{ sv_debugf( "localpart: word: %s\n", $1 ); };
	| localpart '.' word		{
		sv_debugf( "localpart: localpart word: %s %s\n", $1, $3 );
		$$ = sv_strbuf(ml, sv_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

domain: subdomain			{ sv_debugf( "domain: subdomain: %s\n", $1 ); };
	| domain '.' subdomain		{
		sv_debugf( "domain: domain subdomain: %s %s\n", $1, $3 );
		$$ = sv_strbuf(ml, sv_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

subdomain: domainref		{ sv_debugf( "subdomain: domainref: %s\n", $1 ); }
	| domainlit		{ sv_debugf( "subdomain: domainlit: %s\n", $1 ); };

domainref: ATOM			{ sv_debugf( "domainref: ATOM: %s\n", $1 ); };

domainlit: '[' DTEXT ']'	{
	 	sv_debugf( "domainlit: DTEXT: %s\n", $2 );
		$$ = $2;
		};

phrase: word			{ sv_debugf( "phrase: word: %s\n", $1 ); }
	| phrase word		{
		sv_debugf( "phrase: phrase word: %s %s\n", $1, $2 );
		$$ = sv_strbuf(ml, sv_strconcat( $1, " ", $2, NULL ), strlen($1)+strlen($2)+1, FREEME);
		};

word: ATOM			{ sv_debugf( "word: ATOM: %s\n", $1 ); }
	| qstring		{ sv_debugf( "word: qstring: %s\n", $1 ); };

qstring: QUOTE QTEXT QUOTE	{
		sv_debugf( "qstring: QTEXT: %s\n", $2 );
		$$ = $2;
		};

%%

/* copy address error message into buffer provided by sieve parser */
void addrerror(const char *s)
{
    extern char *addrerr;
    addrerr = sv_strdup(s, strlen(s));
}

/* Wrapper for addrparse() which sets up the 
 * required environment and allocates variables
 */
struct address *addr_parse_buffer(struct address **data, const char **ptr, char **err)
{
    struct address *newdata = NULL;
    extern struct mlbuf *ml;
    extern struct address *addr;

    addr = NULL;
    addrappend(&addr);

    sv_strbufalloc(&ml);

    (const char *)addrptr = *ptr;

    /* This is now done higher up the call chain...
     * addrlexalloc();
     */
    if(addrparse()) {
        /*
        *err = sv_strdup(addrerr);
        sv_debugf( "%s\n", err );
        sv_free(err);
        */
        // FIXME: Make sure that this is sufficient cleanup
        addrstructfree(addr, CHARSALSO);
        sv_strbuffree(&ml);
        return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while(newdata != NULL) {
        newdata = newdata->next;
    }

    /* While adding the new results onto the current set,
     * we notice that addrparse() leaves an extra struct
     * at the top, but at least we can hide that here!
     */
    newdata = addrstructcopy(addr->next, STRUCTONLY);
    addrstructfree(addr, STRUCTONLY);
    sv_strbuffree(&ml);
    /* This causes a segfault here...
     * but now it's been put much higher up and works
     * addrlexfree();
     */

    if(*data == NULL)
        *data = newdata;

    return *data;
}

void addrstructfree(struct address *addr, int freeall)
{
    struct address *bddr;

    while(addr != NULL) {
        bddr = addr;
        if(freeall) {
            sv_debugf("I'd like to free this: %s\n", bddr->mailbox);
            sv_free(bddr->mailbox);
            sv_debugf("I'd like to free this: %s\n", bddr->domain);
            sv_free(bddr->domain);
            sv_debugf("I'd like to free this: %s\n", bddr->route);
            sv_free(bddr->route);
            sv_debugf("I'd like to free this: %s\n", bddr->name);
            sv_free(bddr->name);
        }
        addr = bddr->next;
        sv_free(bddr);
    }
}

struct address *addrstructcopy(struct address *addr, int copyall)
{
    struct address *new;
    struct address *tmp = addr;
    struct address *top = sv_malloc(sizeof(struct address));

    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
    top->mailbox = tmp->mailbox;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
    top->domain = tmp->domain;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
    top->route = tmp->route;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
    top->name = tmp->name;
    tmp = tmp->next;
    new = top;
    while(tmp != NULL) {
        new->next = (struct address *)sv_malloc(sizeof(struct address));
        if (new->next == NULL)
            return NULL;   
        else
            new = new->next;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
        new->mailbox = tmp->mailbox;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
        new->domain = tmp->domain;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
        new->route = tmp->route;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
        new->name = tmp->name;
        tmp = tmp->next;
    }
    new->next = NULL; /* Clear the last entry */

    return top;
}

void addrappend(struct address **a)
{
    sv_debugf( "Prepending a new addr struct\n" );
    struct address *new = (struct address *)sv_malloc(sizeof(struct address));
    new->mailbox = NULL;
    new->domain = NULL;
    new->route = NULL;
    new->name = NULL;
    new->next = *a;
    *a = new;
}

