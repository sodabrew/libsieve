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
/* sv_interface */
#include "sieve_interface.h"
#include "sieve2_interface.h"
#include "tree.h"
#include "interp.h"
#include "script.h"
#include "message.h"
/* sv_parser */
#include "parser.h"
/* sv_util */
#include "util.h"

/* reject message m with message msg
 *
 * incompatible with: fileinto, redirect
 */
int libsieve_do_reject(action_list_t *a, char *msg)
{
    action_list_t *b = NULL;
    sieve_reject_context_t *u;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_FILEINTO ||
	    a->a == ACTION_KEEP ||
	    a->a == ACTION_REDIRECT ||
	    a->a == ACTION_REJECT ||
	    a->a == ACTION_VACATION ||
	    a->a == ACTION_SETFLAG ||
	    a->a == ACTION_ADDFLAG ||
	    a->a == ACTION_REMOVEFLAG ||
	    a->a == ACTION_MARK ||
	    a->a == ACTION_UNMARK
	    )
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_REJECT;
    a->u = (sieve_reject_context_t *) libsieve_malloc(sizeof(sieve_reject_context_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_reject_context_t *)(a->u);
    u->msg = msg;
    b->next = a;
    a->next =  NULL;
    return SIEVE_OK;
}

/* fileinto message m into mailbox 
 *
 * incompatible with: reject
 */
int libsieve_do_fileinto(action_list_t *a, char *mbox, sieve_imapflags_t *imapflags)
{
    action_list_t *b = NULL;
    sieve_fileinto_context_t *u;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_FILEINTO;
    a->u = (sieve_fileinto_context_t *) libsieve_malloc(sizeof(sieve_fileinto_context_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_fileinto_context_t *)(a->u);
    u->mailbox = mbox;
    u->imapflags = imapflags;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}

/* redirect message m to to addr
 *
 * incompatible with: reject
 */
int libsieve_do_redirect(action_list_t *a, char *addr)
{
    action_list_t *b = NULL;
    sieve_redirect_context_t *u;

    /* FIXME: we should validate addr */

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_REDIRECT;
    a->u = (sieve_redirect_context_t *) libsieve_malloc(sizeof(sieve_redirect_context_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_redirect_context_t *)(a->u);
//    u->addr = libsieve_strdup(addr, strlen(addr));
    u->addr = addr;
    a->next = NULL;
    b->next = a;
    return SIEVE_OK;
}

/* keep message
 *
 * incompatible with: reject
 */
int libsieve_do_keep(action_list_t *a, sieve_imapflags_t *imapflags)
{
    action_list_t *b = NULL;
    sieve_keep_context_t *u;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	if (a->a == ACTION_KEEP) /* don't bother doing it twice */
	    return SIEVE_OK;
	a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_KEEP;
    a->u = (sieve_keep_context_t *) libsieve_malloc(sizeof(sieve_keep_context_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_keep_context_t *)(a->u);
    u->imapflags = imapflags;
    a->next = NULL;
    b->next = a;
    return SIEVE_OK;
}

/* discard message m
 *
 * incompatible with: nothing---it doesn't cancel any actions
 */
int libsieve_do_discard(action_list_t *a)
{
    action_list_t *b = NULL;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_DISCARD) /* don't bother doing twice */
	    return SIEVE_OK;
	a = a->next;
    }

    /* add to the action list */
    // a = (action_list_t *) libsieve_malloc(sizeof(action_list_t));
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_DISCARD;
    a->next = NULL;
    b->next = a;
    return SIEVE_OK;
}

int libsieve_do_vacation(action_list_t *a, char *addr, char *fromaddr,
		char *subj, char *msg, int days,
		int mime)
{
    action_list_t *b = NULL;
    sieve2_vacation_context_t *u;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
        b = a;
        if (a->a == ACTION_REJECT ||
            a->a == ACTION_VACATION) /* vacation can't be used twice */
            return SIEVE_RUN_ERROR;
        a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_VACATION;
    a->u = (sieve2_vacation_context_t *) libsieve_malloc(sizeof(sieve2_vacation_context_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve2_vacation_context_t *)(a->u);
    u->send.addr = addr;
    u->send.fromaddr = fromaddr;
    u->send.subj = subj;	/* user specified subject */
    u->send.msg = msg;
    u->send.mime = mime;
    u->check.days = days;
    a->next = NULL;
    b->next = a;
    return SIEVE_OK;
}

/* setflag f on message m
 *
 * incompatible with: reject
 */
int libsieve_do_setflag(action_list_t *a, char *flag)
{
    action_list_t *b = NULL;
    sieve_imaponeflag_t *u;
 
    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }
 
    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_SETFLAG;
    a->u = (sieve_imaponeflag_t *) libsieve_malloc(sizeof(sieve_imaponeflag_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_imaponeflag_t *)(a->u);
    u->flag = flag;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}

/* addflag f on message m
 *
 * incompatible with: reject
 */
int libsieve_do_addflag(action_list_t *a, char *flag)
{
    action_list_t *b = NULL;
    sieve_imaponeflag_t *u;
 
    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }
 
    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_ADDFLAG;
    a->u = (sieve_imaponeflag_t *) libsieve_malloc(sizeof(sieve_imaponeflag_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_imaponeflag_t *)(a->u);
    u->flag = flag;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}

/* removeflag f on message m
 *
 * incompatible with: reject
 */
int libsieve_do_removeflag(action_list_t *a, char *flag)
{
    action_list_t *b = NULL;
    sieve_imaponeflag_t *u;
 
    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }
 
    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_REMOVEFLAG;
    a->u = (sieve_imaponeflag_t *) libsieve_malloc(sizeof(sieve_imaponeflag_t));
    if (a->u == NULL)
	return SIEVE_NOMEM;
    u = (sieve_imaponeflag_t *)(a->u);
    u->flag = flag;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}


/* mark message m
 *
 * incompatible with: reject
 */
int libsieve_do_mark(action_list_t *a)
{
    action_list_t *b = NULL;
 
    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }
 
    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_MARK;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}


/* unmark message m
 *
 * incompatible with: reject
 */
int libsieve_do_unmark(action_list_t *a)
{
    action_list_t *b = NULL;
 
    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_REJECT)
	    return SIEVE_RUN_ERROR;
	a = a->next;
    }
 
    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_UNMARK;
    b->next = a;
    a->next = NULL;
    return SIEVE_OK;
}

/* notify
 *
 * incompatible with: none
 */
int libsieve_do_notify(action_list_t *a, char *id,
	      char *method, stringlist_t *options,
	      const char *priority, char *message)
{
    action_list_t *b = NULL;
    notify_list_t *n = NULL;
    notify_list_t *m = NULL;

    /* Find the notify list inside the action list */
    while (a != NULL) {
        if(a->a == ACTION_NOTIFY)
            break;
        b = a;
        a = a->next;
    }

    /* Add to the action list */
    if(a == NULL) {
        a = libsieve_new_action_list();
        if (a == NULL)
            return SIEVE_NOMEM;
        a->a = ACTION_NOTIFY;
	a->u = NULL;
        b->next = a;
        a->next = NULL;

        /* Create the notify list */
        n = a->u = libsieve_new_notify_list();
        if (a->u == NULL)
            return SIEVE_NOMEM;

        /* Grab the top notify list */
        //n = (notify_list_t *)(a->u);
    } else {
        /* Grab the top notify list */
        n = (notify_list_t *)(a->u);
 
        /* Find the end of the notify list */
        while (n != NULL) {
            m = n;
            n = n->next;
        }
 
        /* Add to the notify list */
        m->next = n = libsieve_new_notify_list();
        if (n == NULL)
            return SIEVE_NOMEM;

        /* Attach to the existing notify list */
        //m->next = n;
    }

/*
    / * Grab the top notify list * /
    n = (notify_list_t *)(a->u);
 
    / * If there's already a list, find the end of it * /
    if( a->u != NULL) {
        while (n != NULL) {
            m = n;
            n = n->next;
        }
    }

    / * Create / Add to the notify list * /
    n = (notify_list_t *) libsieve_malloc(sizeof(notify_list_t));
    if (n == NULL)
	return SIEVE_NOMEM;
*/

    /* Finally set up the newest entry in the notify list */
    n->isactive = 1;
    n->id = id;
    n->method = method;
    n->options = libsieve_stringlist_to_chararray(options);
    n->priority = priority;
    n->message = message;
    n->next = NULL;
    return SIEVE_OK;
}

/* denotify
 *
 * incomaptible with: none
 */
int libsieve_do_denotify(action_list_t *a, comparator_t *comp, void *pat,
		const char *priority)
{
    action_list_t *b = NULL;
    notify_list_t *n = NULL;

    /* Find the notify list inside the action list */
    while (a != NULL) {
        if(a->a == ACTION_NOTIFY)
            break;
        b = a;
        a = a->next;
    }

    /* If there isn't any notify in the action list, give up */
    if(a == NULL)
        return SIEVE_OK;

    n = (notify_list_t *)(a->u);

    while (n != NULL) {
	if (n->isactive && 
	    (!priority || !strcasecmp(n->priority, priority)) &&
	    (!comp || (n->id && comp(pat, n->id)))) {
	    n->isactive = 0;
	}
	n = n->next;
    }

    return SIEVE_OK;
}


/* Append error to action list
 *
 * Incompatible with: nothing
 */
int libsieve_do_error(action_list_t *a)
{
    action_list_t *b = NULL;

    /* see if this conflicts with any previous actions taken on this message */
    while (a != NULL) {
	b = a;
	if (a->a == ACTION_DISCARD) /* don't bother doing twice */
	    return SIEVE_OK;
	a = a->next;
    }

    /* add to the action list */
    a = libsieve_new_action_list();
    if (a == NULL)
	return SIEVE_NOMEM;
    a->a = ACTION_DISCARD;
    a->next = NULL;
    b->next = a;
    return SIEVE_OK;
}

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
        return SIEVE_RUN_ERROR;

    am = (struct addr_marker *)libsieve_malloc(sizeof(struct addr_marker));
    am->where = newdata;
    am->freeme = NULL;
    *marker = am;
    return SIEVE_OK;
}

char *libsieve_get_address(address_part_t addrpart,
		  struct address **data __attribute__((unused)),
		  struct addr_marker **marker,
		  int canon_domain)
{
    char *ret = NULL;
    struct address *a;
    struct addr_marker *am = *marker;

    a = am->where;
    if (am->freeme) {
	libsieve_free(am->freeme);
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
    return SIEVE_OK;
}

notify_list_t *libsieve_new_notify_list(void)    
{
    notify_list_t *ret = libsieve_malloc(sizeof(notify_list_t));

    if (ret != NULL) {
	ret->isactive = 0;
	ret->id       = NULL;
	ret->method   = NULL;
	ret->options  = NULL;
	ret->priority = NULL;
	ret->message  = NULL;
	ret->next     = NULL;
    }
    return ret;
}

void libsieve_free_notify_list(notify_list_t *n)
{
    /* Don't free the very top of the list */
    libsieve_free(n->options); // FIXME: Why aren't we freeing the top?
    n = n->next;
    while (n != NULL) {
        notify_list_t *b = n->next;
        libsieve_free(n->options);
        libsieve_free(n);
        n = b;
    }
}

action_list_t *libsieve_new_action_list(void)
{
    action_list_t *ret = libsieve_malloc(sizeof(action_list_t));

    if (ret != NULL) {
        ret->a = ACTION_NONE;
//      FIXME: deprecated, can it be removed?
//      ret->param = NULL;
        ret->next = NULL;
    }
    return ret;
}

void libsieve_free_action_list(action_list_t *a)
{
    while (a) {
	action_list_t *b = a->next;
	switch (a->a) {
	case ACTION_VACATION:
	    libsieve_free(((sieve2_vacation_context_t *)(a->u))->send.addr);
	    libsieve_free(((sieve2_vacation_context_t *)(a->u))->send.fromaddr);
	    libsieve_free(((sieve2_vacation_context_t *)(a->u))->send.subj);
	    break;

	default:
	    break;
	}
	libsieve_free(a);
	a = b;
    }
}

