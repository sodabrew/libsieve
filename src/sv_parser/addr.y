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

/* Better yacc error messages make me happy */
#define YYERROR_VERBOSE
/* Must be defined before addr.h */
#define YYSTYPE char *

/* sv_util */
#include "src/sv_util/util.h"

/* sv_parser */
#include "addr.h"
#include "addrinc.h"
#include "addr-lex.h"
extern YY_DECL;
static void libsieve_addrappend(struct sieve2_context *context);
static struct address *libsieve_addrstructcopy(struct sieve2_context *context);

/* sv_interface */
#include "src/sv_interface/callbacks2.h"

#define THIS_MODULE "sv_parser"

%}

%name-prefix="libsieve_addr"

%define api.pure
%lex-param {struct sieve2_context *context}
%lex-param {void *addr_scan}
%parse-param {struct sieve2_context *context}
%parse-param {void *addr_scan}
%token ATOM QTEXT DTEXT QUOTE

%%

start:  /* Empty */			{ libsieve_addrappend(context); }
	| address			{ $$ = $1; }
	| word				{
		/* Lousy case to catch malformed addresses. */
	        libsieve_addrappend(context);
		context->addr_addr->name = $1;
		};

address: mailboxes			{ TRACE_DEBUG( "address: mailbox: %s", $1 ); }
	| group				{ TRACE_DEBUG( "address: group: %s", $1 ); };

group: phrase ':' ';'			{ TRACE_DEBUG( "group: phrase: %s", $1 ); }
	| phrase ':' mailboxes ';'	{ TRACE_DEBUG( "group: phrase mailboxes: %s %s", $1, $3 ); };

mailboxes: mailbox			{
	 	/* Each new address is allocated here and back-linked */
		TRACE_DEBUG( "mailboxes: mailbox: %s", $1 );
		TRACE_DEBUG( "allocating newaddr" );
		libsieve_addrappend(context);
		}
	| mailboxes ',' mailbox		{
	 	/* Each new address is allocated here and back-linked */
		TRACE_DEBUG( "mailboxes: mailboxes mailbox: %s %s", $1, $3 );
		TRACE_DEBUG( "allocating newaddr" );
		libsieve_addrappend(context);
		};

mailbox: 
	routeaddr			{ TRACE_DEBUG( "mailbox: routeaddr: %s", $1 ); }
	| addrspec			{ TRACE_DEBUG( "mailbox: addrspec: %s", $1 ); }
	| phrase routeaddr		{
		TRACE_DEBUG( "mailbox: phrase routeaddr: %s %s", $1, $2 );
		// This is a "top terminal" state...
		TRACE_DEBUG( "context->addr_addr->name: %s", $1 );
		context->addr_addr->name = libsieve_strdup( $1 );
		};

routeaddr: '<' addrspec '>'		{ TRACE_DEBUG( "routeaddr: addrspec: %s", $2 ); }
	| '<' route ':' addrspec '>'	{
		TRACE_DEBUG( "routeaddr: route addrspec: %s:%s", $2, $4 );
		// This is a "top terminal" state...
		TRACE_DEBUG( "context->addr_addr->route: %s", $2 );
		context->addr_addr->route = libsieve_strdup( $2 );
		}
	| '<' '>'			{
		TRACE_DEBUG("routeaddr: <>");
		context->addr_addr->mailbox = libsieve_strdup( "" );
		};

addrspec: localpart '@' domain		{
		TRACE_DEBUG( "addrspec: localpart domain: %s %s", $1, $3 );
		// This is a "top terminal" state...
		TRACE_DEBUG( "context->addr_addr->mailbox: %s", $1 );
		context->addr_addr->mailbox = libsieve_strdup( $1 );
		TRACE_DEBUG( "context->addr_addr->domain: %s", $3 );
		context->addr_addr->domain = libsieve_strdup( $3 );
		};

route: '@' domain			{
		TRACE_DEBUG( "route: domain: %s", $2 );
                $$ = libsieve_strbuf(context->strbuf, libsieve_strconcat( "@", $2, NULL ), strlen($2)+1, FREEME);
		}
	| '@' domain ',' route		{
		TRACE_DEBUG( "route: domain route: %s %s", $2, $4 );
		$$ = libsieve_strbuf(context->strbuf, libsieve_strconcat( "@", $2, ",", $4, NULL ), strlen($2)+strlen($4)+2, FREEME);
		};

localpart: word				{ TRACE_DEBUG( "localpart: word: %s", $1 ); }
	| localpart '.' word		{
		TRACE_DEBUG( "localpart: localpart word: %s %s", $1, $3 );
		$$ = libsieve_strbuf(context->addr_ml, libsieve_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

domain: subdomain			{ TRACE_DEBUG( "domain: subdomain: %s", $1 ); }
	| domain '.' subdomain		{
		TRACE_DEBUG( "domain: domain subdomain: %s %s", $1, $3 );
		$$ = libsieve_strbuf(context->addr_ml, libsieve_strconcat( $1, ".", $3, NULL ), strlen($1)+strlen($3)+1, FREEME);
		};

subdomain: domainref		{ TRACE_DEBUG( "subdomain: domainref: %s", $1 ); }
	| domainlit		{ TRACE_DEBUG( "subdomain: domainlit: %s", $1 ); };

domainref: ATOM			{ TRACE_DEBUG( "domainref: ATOM: %s", $1 ); };

domainlit: '[' DTEXT ']'	{
	 	TRACE_DEBUG( "domainlit: DTEXT: %s", $2 );
		$$ = $2;
		};

phrase: word			{ TRACE_DEBUG( "phrase: word: %s", $1 ); }
	| phrase word		{
		TRACE_DEBUG( "phrase: phrase word: %s %s", $1, $2 );
		$$ = libsieve_strbuf(context->strbuf, libsieve_strconcat( $1, " ", $2, NULL ), strlen($1)+strlen($2)+1, FREEME);
		};

word: ATOM			{ TRACE_DEBUG( "word: ATOM: %s", $1 ); }
	| qstring		{ TRACE_DEBUG( "word: qstring: %s", $1 ); };

qstring: QUOTE QTEXT QUOTE	{
		TRACE_DEBUG( "qstring: QTEXT: %s", $2 );
		$$ = $2;
		};

%%

/* Run an execution error callback. */
void libsieve_addrerror(struct sieve2_context *context, void *yyscanner, const char *msg)
{
    context->exec_errors++;

    libsieve_do_error_address(context, msg);
}

/* Wrapper for addrparse() which sets up the 
 * required environment and allocates variables
 */
struct address *libsieve_addr_parse_buffer(struct sieve2_context *context, struct address **data, const char **ptr)
{
    struct address *newdata = NULL;
    void *addr_scan = context->addr_scan;

    context->addr_addr = NULL;
    libsieve_addrappend(context);
    YY_BUFFER_STATE buf = libsieve_addr_scan_string((char*)*ptr, addr_scan);
/*
        serr = libsieve_strconcat("address '", s, "': ", aerr, NULL);
        libsieve_sieveerror(serr);
        libsieve_free(serr);
        libsieve_free(aerr);
	*/

    if(libsieve_addrparse(context, addr_scan)) {
        // FIXME: Make sure that this is sufficient cleanup
        libsieve_addrstructfree(context, context->addr_addr, CHARSALSO);
        libsieve_addr_delete_buffer(buf, addr_scan);
        return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while (newdata != NULL) {
        newdata = newdata->next;
    }

    /* While adding the new results onto the current set,
     * we notice that addrparse() leaves an extra struct
     * at the top, but at least we can hide that here!
     */
    newdata = libsieve_addrstructcopy(context);
    libsieve_addr_delete_buffer(buf, addr_scan);
    libsieve_addrstructfree(context, context->addr_addr, STRUCTONLY);

    if (*data == NULL)
        *data = newdata;

    return *data;
}

void libsieve_addrstructfree(struct sieve2_context *context, struct address *addr, int freeall)
{
    struct address *bddr;

    while (addr != NULL) {
        bddr = addr;
        if(freeall) {
            TRACE_DEBUG("I'd like to free this: %s", bddr->mailbox);
            libsieve_free(bddr->mailbox);
            TRACE_DEBUG("I'd like to free this: %s", bddr->domain);
            libsieve_free(bddr->domain);
            TRACE_DEBUG("I'd like to free this: %s", bddr->route);
            libsieve_free(bddr->route);
            TRACE_DEBUG("I'd like to free this: %s", bddr->name);
            libsieve_free(bddr->name);
        }
        addr = bddr->next;
        libsieve_free(bddr);
    }
}

struct address *libsieve_addrstructcopy(struct sieve2_context *context)
{
    struct address *new;
    struct address *tmp = context->addr_addr->next;
    struct address *top;

    if (!tmp) {
        TRACE_DEBUG("No addresses found at all, returning NULL.");
	return NULL;
    }

    top = libsieve_malloc(sizeof(struct address));

    TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->mailbox, tmp->mailbox);
    top->mailbox = tmp->mailbox;
    TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->domain, tmp->domain);
    top->domain = tmp->domain;
    TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->route, tmp->route);
    top->route = tmp->route;
    TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->name, tmp->name);
    top->name = tmp->name;
    tmp = tmp->next;
    new = top;
    while (tmp != NULL) {
        new->next = (struct address *)libsieve_malloc(sizeof(struct address));
        if (new->next == NULL) {
            TRACE_DEBUG("malloc failed, returning what we have so far.");
	    return top;
        } else {
            new = new->next;
	}
        TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->mailbox, tmp->mailbox);
        new->mailbox = tmp->mailbox;
        TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->domain, tmp->domain);
        new->domain = tmp->domain;
        TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->route, tmp->route);
        new->route = tmp->route;
        TRACE_DEBUG("I'd like to copy this pointer: %p: %s", tmp->name, tmp->name);
        new->name = tmp->name;
        tmp = tmp->next;
    }
    new->next = NULL; /* Clear the last entry */

    return top;
}

void libsieve_addrappend(struct sieve2_context *context)
{
    struct address *new = (struct address *)libsieve_malloc(sizeof(struct address));
    TRACE_DEBUG( "Prepending a new addr struct" );
    new->mailbox = NULL;
    new->domain = NULL;
    new->route = NULL;
    new->name = NULL;
    new->next = context->addr_addr;
    context->addr_addr = new;
}
