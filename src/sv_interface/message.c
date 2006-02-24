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

/* sv_parser */
#include "parser.h"

/* sv_util */
#include "util.h"

/* given a header, extract an address out of it.  if marker points to NULL,
   extract the first address.  otherwise, it's an index into the header to
   say where to start extracting */
int libsieve_parse_address(const char *header, struct address **data, struct addr_marker **marker)
{
    char *err;
    struct addr_marker *am;
    struct address *newdata = NULL;

    newdata = libsieve_addr_parse_buffer(data, &header, &err);
    if( newdata == NULL )
        return SIEVE2_ERROR_EXEC;

    am = (struct addr_marker *)libsieve_malloc(sizeof(struct addr_marker));
    am->where = newdata;
    am->freeme = NULL;
    *marker = am;
    return SIEVE2_OK;
}

char *libsieve_get_address(address_part_t addrpart,
		  struct addr_marker **marker,
		  int canon_domain)
{
    char *ret = NULL;
    struct address *a;
    struct addr_marker *am = *marker;

    if (!am) {
	    libsieve_debugf(("libsieve_get_address: am is null, returning null.\n"));
	    return NULL;
    }

    a = am->where;
    if (am->freeme) {
	libsieve_free(am->freeme);
	libsieve_debugf(("libsieve_get_address: am->freeme is set, returning null.\n"));
	am->freeme = NULL;
    }

    if (a == NULL) {
	ret = NULL;
    } else {
	if (canon_domain && a->domain)
	    libsieve_strtolower(a->domain,strlen(a->domain));

	switch (addrpart) { 
	case ADDRESS_ALL:
#define U_DOMAIN "unspecified-domain"
#define U_USER "unknown-user"
	    if (a->mailbox || a->domain) {
		char *m = a->mailbox ? a->mailbox : U_USER;
		char *d = a->domain ? a->domain : U_DOMAIN;
		am->freeme = libsieve_strconcat(m, "@", d, NULL);
		ret = am->freeme;
	    } else {
		ret = NULL;
	    }
	    break;

	case ADDRESS_LOCALPART:
	    ret = a->mailbox;
	    break;
	    
	case ADDRESS_DOMAIN:
	    ret = a->domain;
	    break;

	case ADDRESS_USER:
	    if (a->mailbox) {
		char *p = strchr(a->mailbox, '+');
		int len = p ? p - a->mailbox : strlen(a->mailbox);

		am->freeme = libsieve_strdup(a->mailbox, len);
		/* FIXME: Confirm this works then delete.
		am->freeme = (char *) libsieve_malloc(len + 1);
		strncpy(am->freeme, a->mailbox, len);
		am->freeme[len] = '\0';
		*/
		ret = am->freeme;
	    } else {
		ret = NULL;
	    }
	    break;

	case ADDRESS_DETAIL:
	    if (a->mailbox) {
		char *p = strchr(a->mailbox, '+');
		ret = (p ? p + 1 : NULL);
	    } else {
		ret = NULL;
	    }
	    break;
	}
	a = a->next;
	am->where = a;
    }
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
    libsieve_free(am->freeme);
    libsieve_free(am);
    *marker = NULL;
    return SIEVE2_OK;
}

