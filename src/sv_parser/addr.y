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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This only works in C99 and higher... */
#ifdef DEBUG
#define libsieve_debugf(...) printf(__VA_ARGS__)
#else
#define libsieve_debugf(...) 
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
char *libsieve_addrptr;          /* pointer to sieve string for address lexer */
char *libsieve_addrerr;          /* buffer for sieve parser error messages */
static struct address *addr = NULL;
static struct mlbuf *ml = NULL;
%}

%token ATOM QTEXT DTEXT QUOTE
%start address

%%
address: mailboxes			{ libsieve_debugf( "address: mailbox: %s\n", $1 ); }
	| group				{ libsieve_debugf( "address: group: %s\n", $1 ); };

group: phrase ':' ';'			{ libsieve_debugf( "group: phrase: %s\n", $1 ); }
	| phrase ':' mailboxes ';'	{ libsieve_debugf( "group: phrase mailboxes: %s %s\n", $1, $3 ); };

mailboxes: mailbox			{
	 	/* Each new address is allocated here and back-linked */
		libsieve_debugf( "mailboxes: mailbox: %s\n", $1 );
		libsieve_debugf( "allocating newaddr\n" );
		addrappend(&addr);
		}
	| mailboxes ',' mailbox		{
	 	/* Each new address is allocated here and back-linked */
		libsieve_debugf( "mailboxes: mailboxes mailbox: %s %s\n", $1, $3 );
		libsieve_debugf( "allocating newaddr\n" );
		addrappend(&addr);
		};

mailbox: 
	routeaddr			{ libsieve_debugf( "mailbox: routeaddr: %s\n", $1 ); }
	| addrspec			{ libsieve_debugf( "mailbox: addrspec: %s\n", $1 ); }
	| phrase routeaddr		{
		libsieve_debugf( "mailbox: phrase routeaddr: %s %s\n", $1, $2 );
		// This is a "top terminal" state...
		libsieve_debugf( "addr->name: %s\n", $1 );
		addr->name = libsieve_strdup( $1, strlen($1) );
		};

routeaddr: '<' addrspec '>'		{ libsieve_debugf( "routeaddr: addrspec: %s\n", $2 ); }
	| '<' route ':' addrspec '>'	{
		libsieve_debugf( "routeaddr: route addrspec: %s:%s\n", $2, $4 );
		// This is a "top terminal" state...
		libsieve_debugf( "addr->route: %s\n", $2 );
		addr->route = libsieve_strdup( $2, strlen($2) );
		};
	
addrspec: localpart '@' domain		{
		libsieve_debugf( "addrspec: localpart domain: %s %s\n", $1, $3 );
		// This is a "top terminal" state...
		libsieve_debugf( "addr->mailbox: %s\n", $1 );
		addr->mailbox = libsieve_strdup( $1, strlen($1) );
		libsieve_debugf( "addr->domain: %s\n", $3 );
		addr->domain = libsieve_strdup( $3, strlen($3) );
		};

route: '@' domain			{
		libsieve_debugf( "route: domain: %s\n", $2 );
                $$ = libsieve_strbuf(ml, libsieve_strconcat( "@", $2, NULL ), strlen($2)+1, FREEME);
		}
	| '@' domain ',' route		{
		libsieve_debugf( "route: domain route: %s %s\n", $2, $4 );
		$$ = libsieve_strbuf(ml, libsieve_strconcat( "@", $2, ",", $4, NULL ), strlen($2)+strlen($4)+2, FREEME);
		};

localpart: word				{ libsieve_debugf( "localpart: word: %s\n", $1 ); }
	| localpart '.' word		{
		libsieve_debugf( "localpart: localpart word: %s %s\n", $1, $3 );
		$$ = libsieve_strbuf(ml, libsieve_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

domain: subdomain			{ libsieve_debugf( "domain: subdomain: %s\n", $1 ); }
	| domain '.' subdomain		{
		libsieve_debugf( "domain: domain subdomain: %s %s\n", $1, $3 );
		$$ = libsieve_strbuf(ml, libsieve_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

subdomain: domainref		{ libsieve_debugf( "subdomain: domainref: %s\n", $1 ); }
	| domainlit		{ libsieve_debugf( "subdomain: domainlit: %s\n", $1 ); };

domainref: ATOM			{ libsieve_debugf( "domainref: ATOM: %s\n", $1 ); };

domainlit: '[' DTEXT ']'	{
	 	libsieve_debugf( "domainlit: DTEXT: %s\n", $2 );
		$$ = $2;
		};

phrase: word			{ libsieve_debugf( "phrase: word: %s\n", $1 ); }
	| phrase word		{
		libsieve_debugf( "phrase: phrase word: %s %s\n", $1, $2 );
		$$ = libsieve_strbuf(ml, libsieve_strconcat( $1, " ", $2, NULL ), strlen($1)+strlen($2)+1, FREEME);
		};

word: ATOM			{ libsieve_debugf( "word: ATOM: %s\n", $1 ); }
	| qstring		{ libsieve_debugf( "word: qstring: %s\n", $1 ); };

qstring: QUOTE QTEXT QUOTE	{
		libsieve_debugf( "qstring: QTEXT: %s\n", $2 );
		$$ = $2;
		};

%%

/* copy address error message into buffer provided by sieve parser */
void libsieve_addrerror(const char *s)
{
    extern char *addrerr;
    addrerr = libsieve_strdup(s, strlen(s));
}

/* Wrapper for addrparse() which sets up the 
 * required environment and allocates variables
 */
struct address *libsieve_addr_parse_buffer(struct address **data, const char **ptr, char **err)
{
    struct address *newdata = NULL;
    extern struct mlbuf *ml;
    extern struct address *addr;

    addr = NULL;
    libsieve_addrappend(&addr);

    libsieve_strbufalloc(&ml);

    (const char *)libsieve_addrptr = *ptr;

    /* This is now done higher up the call chain...
     * addrlexalloc();
     */
    if(libsieve_addrparse()) {
        /*
        *err = libsieve_strdup(addrerr);
        libsieve_debugf( "%s\n", err );
        libsieve_free(err);
        */
        // FIXME: Make sure that this is sufficient cleanup
        libsieve_addrstructfree(addr, CHARSALSO);
        libsieve_strbuffree(&ml, FREEME);
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
    libsieve_addrstructfree(addr, STRUCTONLY);
    libsieve_strbuffree(&ml, FREEME);
    /* This causes a segfault here...
     * but now it's been put much higher up and works
     * addrlexfree();
     */

    if(*data == NULL)
        *data = newdata;

    return *data;
}

void libsieve_addrstructfree(struct address *addr, int freeall)
{
    struct address *bddr;

    while(addr != NULL) {
        bddr = addr;
        if(freeall) {
            libsieve_debugf("I'd like to free this: %s\n", bddr->mailbox);
            libsieve_free(bddr->mailbox);
            libsieve_debugf("I'd like to free this: %s\n", bddr->domain);
            libsieve_free(bddr->domain);
            libsieve_debugf("I'd like to free this: %s\n", bddr->route);
            libsieve_free(bddr->route);
            libsieve_debugf("I'd like to free this: %s\n", bddr->name);
            libsieve_free(bddr->name);
        }
        addr = bddr->next;
        libsieve_free(bddr);
    }
}

struct address *libsieve_addrstructcopy(struct address *addr, int copyall)
{
    struct address *new;
    struct address *tmp = addr;
    struct address *top = libsieve_malloc(sizeof(struct address));

    libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
    top->mailbox = tmp->mailbox;
    libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
    top->domain = tmp->domain;
    libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
    top->route = tmp->route;
    libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
    top->name = tmp->name;
    tmp = tmp->next;
    new = top;
    while(tmp != NULL) {
        new->next = (struct address *)libsieve_malloc(sizeof(struct address));
        if (new->next == NULL)
            return NULL;   
        else
            new = new->next;
        libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
        new->mailbox = tmp->mailbox;
        libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
        new->domain = tmp->domain;
        libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
        new->route = tmp->route;
        libsieve_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
        new->name = tmp->name;
        tmp = tmp->next;
    }
    new->next = NULL; /* Clear the last entry */

    return top;
}

void libsieve_addrappend(struct address **a)
{
    libsieve_debugf( "Prepending a new addr struct\n" );
    struct address *new = (struct address *)libsieve_malloc(sizeof(struct address));
    new->mailbox = NULL;
    new->domain = NULL;
    new->route = NULL;
    new->name = NULL;
    new->next = *a;
    *a = new;
}

