/* message.c -- message parsing functions
 * Larry Greenfield
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

/* sv_include */
#include "sieve2.h"
#include "sieve2_error.h"

/* sv_interface */
#include "tree.h"
#include "script.h"
#include "message.h"
#include "callbacks2.h"

/* sv_parser */
#include "src/sv_parser/parser.h"

/* sv_util */
#include "src/sv_util/util.h"

/* given a header, extract an address out of it.  if marker points to NULL,
   extract the first address.  otherwise, it's an index into the header to
   say where to start extracting */
int libsieve_parse_address(struct sieve2_context *context, const char *header, struct address **data, struct addr_marker **marker)
{
    struct addr_marker *am;
    struct address *newdata = NULL;

    newdata = libsieve_addr_parse_buffer(context, data, &header);
    if( newdata == NULL )
        return SIEVE2_ERROR_EXEC;

    am = (struct addr_marker *)libsieve_malloc(sizeof(struct addr_marker));
    am->where = newdata;
    am->freeme = NULL;
    *marker = am;
    return SIEVE2_OK;
}

/* Returns the specified part of the current address in the marker array,
 * frees the address and advances the caller's array pointer. */
char *libsieve_get_address(struct sieve2_context *context,
		address_part_t addrpart,
		struct addr_marker **marker,
		int canon_domain)
{
    char *ret = NULL;
    struct address *a;
    struct addr_marker *am = *marker;
    char *address;

    if (!am) {
        return NULL;
    }

    a = am->where;
    if (am->freeme) {
	libsieve_free(am->freeme);
	am->freeme = NULL;
    }

    if (a == NULL) {
        return NULL;
    }

    if (canon_domain && a->domain)
        libsieve_strtolower(a->domain,strlen(a->domain));

#define U_DOMAIN "unspecified-domain"
#define U_USER "unknown-user"
    if (a->mailbox || a->domain) {
        if (strlen(a->mailbox) == 0 && a->domain == NULL) {
            address = "";
        } else {
    	    char *m = a->mailbox ? a->mailbox : U_USER;
    	    char *d = a->domain ? a->domain : U_DOMAIN;
    	    address = am->freeme = libsieve_strconcat(m, "@", d, NULL);
	}
    } else {
    	ret = NULL;
	goto got_address;
    }

    if (addrpart == ADDRESS_ALL) {
	ret = address;
	goto got_address;
    }

    char *user, *detail, *localpart, *domain;

    if (libsieve_do_getsubaddress(context, address,
    	&user, &detail, &localpart, &domain) != SIEVE2_OK) {
    	// Error of some kind.
	ret = NULL;
	goto got_address;
    }

    switch (addrpart) { 
    case ADDRESS_LOCALPART:
        ret = localpart;
        break;
        
    case ADDRESS_DOMAIN:
        ret = domain;
        break;

    case ADDRESS_USER:
        ret = user;
        break;

    case ADDRESS_DETAIL:
        ret = detail;
        break;

    case ADDRESS_ALL:
	// Shut up, compiler.
	break;
    }

got_address:
    a = a->next;
    am->where = a;
    *marker = am;

    return ret;
}

int libsieve_free_address(struct address **data, struct addr_marker **marker)
{
    struct addr_marker *am = *marker;
    struct address *freedata;

    while( *data ) {
        freedata = (*data)->next;
        libsieve_free((*data)->mailbox);
        libsieve_free((*data)->domain);
        libsieve_free((*data)->route);
        libsieve_free((*data)->name);
        libsieve_free(*data);
        *data = freedata;
    }
    *data = NULL;

    if (am) {
        libsieve_free(am->freeme);
        libsieve_free(am);
    }
    *marker = NULL;

    return SIEVE2_OK;
}

