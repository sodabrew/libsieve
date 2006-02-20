/* script.c -- sieve script functions
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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* sv_include */
#include "sieve2.h"

/* sv_interface */
#include "message.h"
#include "message2.h"
#include "callbacks2.h"
#include "context2.h"
#include "script.h"
#include "sieve.h"
#include "tree.h"

/* sv_util */
#include "util.h"

/* sv_parser */
#include "parser.h"

static int sysaddr(char *addr)
{
    if (!strncasecmp(addr, "MAILER-DAEMON", 13))
	return 1;

    if (!strncasecmp(addr, "LISTSERV", 8))
	return 1;

    if (!strncasecmp(addr, "majordomo", 9))
	return 1;

    if (strstr(addr, "-request"))
	return 1;

    if (!strncmp(addr, "owner-", 6))
	return 1;

    return 0;
}

/* look for myaddr and myaddrs in the body of a header - return the match */
static char *look_for_me(char *myaddr, stringlist_t *myaddrs, const char **body)
{
    char *found = NULL;
    int l;
    stringlist_t *sl;

    /* loop through each TO header */
    for (l = 0; body[l] != NULL && !found; l++) {
	struct address *data = NULL;
	struct addr_marker *marker = NULL;
	char *addr;
	
	libsieve_parse_address(body[l], &data, &marker);
	/* loop through each address in the header */
	while (!found && ((addr = libsieve_get_address(ADDRESS_ALL, &marker, 1)) != NULL)) {
	    if (!strcasecmp(addr, myaddr)) {
		found = myaddr;
		break;
	    }

	    for (sl = myaddrs; sl != NULL && !found; sl = sl->next) {
		struct address *altdata = NULL;
		struct addr_marker *altmarker = NULL;
		char *altaddr;

		/* is this address one of my addresses? */
		libsieve_parse_address(sl->s, &altdata, &altmarker);
		altaddr = libsieve_get_address(ADDRESS_ALL, &altmarker, 1);
		if (!strcasecmp(addr, altaddr))
		    found = sl->s;

		libsieve_free_address(&altdata, &altmarker);
	    }
	}
	libsieve_free_address(&data, &marker);
    }

    return found;
}

/* evaluates the test t. returns 1 if true, 0 if false.
 */
static int static_evaltest(struct sieve2_context *context, test_t *t)
{
    testlist_t *tl;
    stringlist_t *sl;
    patternlist_t *pl;
    int res = 0;
    int addrpart = 0;

    switch (t->type) {
    case ADDRESS:
    case ENVELOPE:
	res = 0;
	switch (t->u.ae.addrpart) {
	case ALL: addrpart = ADDRESS_ALL; break;
	case LOCALPART: addrpart = ADDRESS_LOCALPART; break;
	case DOMAIN: addrpart = ADDRESS_DOMAIN; break;
	case USER: addrpart = ADDRESS_USER; break;
	case DETAIL: addrpart = ADDRESS_DETAIL; break;
	}
	for (sl = t->u.ae.sl; sl != NULL && !res; sl = sl->next) {
	    int l;
	    const char **body;

	    /* use getheader for address, getenvelope for envelope */
	    if (((t->type == ADDRESS) ? 
		   libsieve_do_getheader(context, sl->s, &body) :
		   libsieve_do_getenvelope(context, sl->s, &body)) != SIEVE2_OK) {
		continue; /* try next header */
	    }
	    for (pl = t->u.ae.pl; pl != NULL && !res; pl = pl->next) {
		for (l = 0; body[l] != NULL && !res; l++) {
		    /* loop through each header */
		    struct address *data = NULL;
		    struct addr_marker *marker = NULL;
		    char *val;

		    libsieve_parse_address(body[l], &data, &marker);
                    val = libsieve_get_address(addrpart, &marker, 0);
		    while (val != NULL && !res) { 
			/* loop through each address */
			res |= t->u.ae.comp(pl->p, val);
			val = libsieve_get_address(addrpart, &marker, 0);
       		    }
		    libsieve_free_address(&data, &marker);
		}
	    }
	}
	break;
    case ANYOF:
	res = 0;
	for (tl = t->u.tl; tl != NULL && !res; tl = tl->next) {
	    res |= static_evaltest(context, tl->t);
	}
	break;
    case ALLOF:
	res = 1;
	for (tl = t->u.tl; tl != NULL && res; tl = tl->next) {
	    res &= static_evaltest(context, tl->t);
	}
	break;
    case EXISTS:
	res = 1;
	for (sl = t->u.sl; sl != NULL && res; sl = sl->next) {
	    const char **headbody = NULL;
	    res &= (libsieve_do_getheader(context, sl->s, &headbody) == SIEVE2_OK);
	}
	break;
    case SFALSE:
	res = 0;
	break;
    case STRUE:
	res = 1;
	break;
    case HEADER:
	res = 0;
	for (sl = t->u.h.sl; sl != NULL && !res; sl = sl->next) {
	    const char **val;
	    size_t l;
	    if (libsieve_do_getheader(context, sl->s, &val) != SIEVE2_OK)
		continue;
	    for (pl = t->u.h.pl; pl != NULL && !res; pl = pl->next) {
		for (l = 0; val[l] != NULL && !res; l++) {
		    res |= t->u.h.comp(pl->p, val[l]);
		}
	    }
	}
	break;
    case NOT:
	res = !static_evaltest(context, t->u.t);
	break;
    case SIZE:
    {
	int sz;

	if (libsieve_do_getsize(context, &sz) != SIEVE2_OK)
	    break;

	if (t->u.sz.t == OVER) {
	    res = (sz > t->u.sz.n);
	} else { /* UNDER */
	    res = (sz < t->u.sz.n);
	}
	break;
    }
    }

    return res;
}

/* evaluate the script c.  returns negative if error was encountered,
   0 if it exited off the end, or positive if a stop action was encountered.
   note that this is very stack hungry; we just evaluate the AST in
   the naivest way.  if we implement some sort of depth limit, we'll
   be ok here; otherwise we'd want to transform it a little smarter */
int libsieve_eval(struct sieve2_context *context,
                  commandlist_t *c, const char **errmsg)
{
    int res = 0;
    stringlist_t *sl;

    while (c != NULL) {
	switch (c->type) {
	case IF:
	    if (static_evaltest(context, c->u.i.t))
		res = libsieve_eval(context, c->u.i.do_then, errmsg);
	    else
		res = libsieve_eval(context, c->u.i.do_else, errmsg);
	    break;
	case REJCT:
	    res = libsieve_do_reject(context, c->u.str);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Reject can not be used with any other action";
	    break;
	case FILEINTO:
	    res = libsieve_do_fileinto(context, c->u.str, &context->imapflags);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Fileinto can not be used with Reject";
	    break;
	case REDIRECT:
	    res = libsieve_do_redirect(context, c->u.str);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Redirect can not be used with Reject";
	    break;
	case KEEP:
	    res = libsieve_do_keep(context, &context->imapflags);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Keep can not be used with Reject";
	    break;
	case VACATION:
	    {
		const char **body;
		char buf[128], *fromaddr;
		char *found = NULL;
		char *myaddr = NULL;
		char *reply_to = NULL;
		int l = SIEVE2_OK;
		struct address *data = NULL;
		struct addr_marker *marker = NULL;
		char *tmp;

		libsieve_debugf(("Starting into a VACATION action.\n"));

		/* is there an Auto-Submitted keyword other than "no"? */
		strcpy(buf, "auto-submitted");
		if (libsieve_do_getheader(context, buf, &body) == SIEVE2_OK) {
		    /* we don't deal with comments, etc. here */
		    /* skip leading white-space */
		    while (body[0] && *body[0] && isspace((int) *body[0])) body[0]++;
		    if (strcasecmp(body[0], "no")) l = SIEVE2_DONE;
		}

		if (l == SIEVE2_DONE)
			libsieve_debugf(("VACATION aborted by Auto-Submitted header.\n"));

		/* is there a Precedence keyword of "junk | bulk | list"? */
		strcpy(buf, "precedence");
		if (libsieve_do_getheader(context, buf, &body) == SIEVE2_OK) {
		    /* we don't deal with comments, etc. here */
		    /* skip leading white-space */
		    while (body[0] && *body[0] && isspace((int) *body[0])) body[0]++;
		    if (!strcasecmp(body[0], "junk") ||
			!strcasecmp(body[0], "bulk") ||
			!strcasecmp(body[0], "list"))
			l = SIEVE2_DONE;
		}

		if (l == SIEVE2_DONE)
			libsieve_debugf(("VACATION aborted by Precedence header.\n"));

		/* Note: the domain-part of all addresses are canonicalized */

		/* grab my address from the envelope */
		if (l == SIEVE2_OK) {
		    strcpy(buf, "to");
		    l = libsieve_do_getenvelope(context, buf, &body);
		    if (body[0]) {
			libsieve_parse_address(body[0], &data, &marker);
			tmp = libsieve_get_address(ADDRESS_ALL, &marker, 1);
			myaddr = (tmp != NULL) ? libsieve_strdup(tmp, strlen(tmp)) : NULL;
			libsieve_free_address(&data, &marker);
		    }
		}
		if (l == SIEVE2_OK) {
		    strcpy(buf, "from");
		    l = libsieve_do_getenvelope(context, buf, &body);
		}
		if (l == SIEVE2_OK && body[0]) {
		    /* we have to parse this address & decide whether we
		       want to respond to it */
		    libsieve_parse_address(body[0], &data, &marker);
		    tmp = libsieve_get_address(ADDRESS_ALL, &marker, 1);
		    reply_to = (tmp != NULL) ? libsieve_strdup(tmp, strlen(tmp)) : NULL;
		    libsieve_free_address(&data, &marker);

		    /* first, is there a reply-to address? */
		    if (reply_to == NULL) {
			l = SIEVE2_DONE;
		    }

		    /* first, is it from me? */
		    if (l == SIEVE2_OK && !strcmp(myaddr, reply_to)) {
			l = SIEVE2_DONE;
		    }

		    /* ok, is it any of the other addresses i've
		       specified? */
		    if (l == SIEVE2_OK)
			for (sl = c->u.v.addresses; sl != NULL; sl = sl->next)
			    if (!strcmp(sl->s, reply_to))
				l = SIEVE2_DONE;
		
		    /* ok, is it a system address? */
		    if (l == SIEVE2_OK && sysaddr(reply_to)) {
			l = SIEVE2_DONE;
		    }
		}

		if (l == SIEVE2_OK) {
		    /* ok, we're willing to respond to the sender.
		       but is this message to me?  that is, is my address
		       in the TO, CC or BCC fields? */
		    if (strcpy(buf, "to"), 
			libsieve_do_getheader(context, buf, &body) == SIEVE2_OK)
			found = look_for_me(myaddr, c->u.v.addresses, body);

		    if (!found && (strcpy(buf, "cc"),
				   (libsieve_do_getheader(context, buf, &body) == SIEVE2_OK)))
			found = look_for_me(myaddr, c->u.v.addresses, body);

		    if (!found && (strcpy(buf, "bcc"),
				   (libsieve_do_getheader(context, buf, &body) == SIEVE2_OK)))
			found = look_for_me(myaddr, c->u.v.addresses, body);

		    if (!found) {
			libsieve_debugf(("Vacation didn't find my address in to, cc or bcc.\n"));
			l = SIEVE2_DONE;
		    }
		}

		if (l == SIEVE2_OK) {
		    /* ok, ok, if we got here maybe we should reply */
		
		    if (c->u.v.subject == NULL) {
			/* we have to generate a subject */
			const char **s;
		    
			strcpy(buf, "subject");
			if (libsieve_do_getheader(context, buf, &s) != SIEVE2_OK ||
			    s[0] == NULL) {
			    strcpy(buf, "Automated reply");
			} else {
			    /* s[0] contains the original subject */
			    const char *origsubj = s[0];
			    
			    while (!strncasecmp(origsubj, "Re: ", 4)) {
				origsubj += 4;
			    }
			    snprintf(buf, sizeof(buf), "Re: %s", origsubj);
			}
		    } else {
			/* user specified subject */
			strncpy(buf, c->u.v.subject, sizeof(buf)-1);
			buf[sizeof(buf)-1] = '\0';
		    }

		    /* who do we want the message coming from? */
		    fromaddr = found;
		
		    res = libsieve_do_vacation(context, reply_to,
				      libsieve_strdup(fromaddr, strlen(fromaddr)),
				      libsieve_strdup(buf, strlen(buf)),
				      c->u.v.message, c->u.v.days, c->u.v.mime);
		
		     if (res == SIEVE2_ERROR_EXEC)
			 *errmsg = "Vacation can not be used with Reject or Vacation";

		} else {
                    libsieve_free(reply_to);
		    if (l != SIEVE2_DONE) res = -1; /* something went wrong */
		}
		libsieve_free(myaddr);
		break;
	    }
	case STOP:
	    res = 1;
	    break;
	case DISCARD:
	    res = libsieve_do_discard(context);
	    break;
	case SETFLAG:
	    sl = c->u.sl;
	    res = libsieve_do_setflag(context, sl->s);
	    for (sl = sl->next; res == 0 && sl != NULL; sl = sl->next) {
		res = libsieve_do_addflag(context, sl->s);
	    }
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Setflag can not be used with Reject";
	    break;
	case ADDFLAG:
	    for (sl = c->u.sl; res == 0 && sl != NULL; sl = sl->next) {
		res = libsieve_do_addflag(context, sl->s);
	    }
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Addflag can not be used with Reject";
	    break;
	case REMOVEFLAG:
	    for (sl = c->u.sl; res == 0 && sl != NULL; sl = sl->next) {
		res = libsieve_do_removeflag(context, sl->s);
	    }
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Removeflag can not be used with Reject";
	    break;
	case MARK:
	    res = libsieve_do_mark(context);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Mark can not be used with Reject";
	    break;
	case UNMARK:
	    res = libsieve_do_unmark(context);
	    if (res == SIEVE2_ERROR_EXEC)
		*errmsg = "Unmark can not be used with Reject";
	    break;
	case NOTIFY:
	    res = libsieve_do_notify(context, c->u.n.id, c->u.n.method,
			    c->u.n.options, c->u.n.priority, c->u.n.message);
			    
	    break;
	case DENOTIFY:
	    res = libsieve_do_denotify(context, c->u.d.comp, c->u.d.pattern,
			      c->u.d.priority);
	    break;

	}

	if (res) /* we've either encountered an error or a stop */
	    break;

	/* execute next command */
	c = c->next;
    }

    return res;
}

#if 0
#define GROW_AMOUNT 100

static void add_header(struct sieve2_context *c, int isenv, char *header, 
		       char **out, size_t *outlen, size_t *outalloc)
{
    const char **h;
    int addlen;
    /* get header value */
    if (isenv)
	libsieve_do_getenvelope(c, header, &h);	
    else
	libsieve_do_getheader(c, header, &h);	

    if (!h || !h[0])
	return;

    addlen = strlen(h[0]) + 1;

    /* realloc if necessary */
    if ( (*outlen) + addlen >= *outalloc)
    {
	*outalloc = (*outlen) + addlen + GROW_AMOUNT;
	*out = libsieve_realloc(*out, *outalloc);
    }

    /* add header value */
    strcat(*out,h[0]);

    *outlen += addlen;
}

    /* This seems to be the only relevant thing to keep 
     * from this whole mess of notify functions...
     * But it looks like its tied closely to the message_context,
     * which is something that was in Cyrus but is gone in libSieve.
    fillin_headers(context, notify->message, message_context, 
		   &out_msg, &out_msglen);
   */
static int fillin_headers(struct sieve2_context *i, char *msg, 
			  void *message_context, char **out, size_t *outlen)
{
    size_t allocsize = GROW_AMOUNT;
    char *c;
    size_t n;

    *out = libsieve_malloc(GROW_AMOUNT);
    *outlen = 0;
    (*out)[0]='\0';

    if (msg == NULL) return SIEVE2_OK;

    /* construct the message */
    c = msg;
    while (*c) {
	/* expand variables */
	if (!strncasecmp(c, "$from$", 6)) {
	    add_header(i, 0 ,"From", out, outlen, &allocsize);
	    c += 6;
	}
	else if (!strncasecmp(c, "$env-from$", 10)) {
	    add_header(i, 1, "From", out, outlen, &allocsize);
	    c += 10;
	}
	else if (!strncasecmp(c, "$subject$", 9)) {
	    add_header(i, 0, "Subject", out, outlen, &allocsize);
	    c += 9;
	}
	/* XXX need to do $text$ variables */
	else {
	    /* find length of plaintext up to next potential variable */
	    n = strcspn(c+1, "$") + 1; /* skip opening '$' */
	    /* realloc if necessary */
	    if ( (*outlen) + n+1 >= allocsize) {
		allocsize = (*outlen) + n+1 + GROW_AMOUNT;
		*out = libsieve_realloc(*out, allocsize);
	    }
	    /* copy the plaintext */
	    strncat(*out, c, n);
	    (*out)[*outlen+n]='\0';
	    (*outlen) += n;
	    c += n;
	}
    }

    return SIEVE2_OK;
}

static int sieve_addflag(sieve_imapflags_t *imapflags, char *flag)
{
    int n;
 
    /* search for flag already in list */
    for (n = 0; n < imapflags->nflags; n++) {
	if (strcmp(imapflags->flag[n], flag) == 0)
	    break;
    }
 
    /* add flag to list, iff not in list */
    if (n == imapflags->nflags) {
	imapflags->nflags++;
	imapflags->flag =
	    (char **) libsieve_realloc((char *)imapflags->flag,
			       imapflags->nflags*sizeof(char *));
	imapflags->flag[imapflags->nflags-1] = libsieve_strdup(flag, strlen(flag));
    }
 
    return SIEVE2_OK;
}

static int sieve_removeflag(sieve_imapflags_t *imapflags, char *flag)
{
    int n;
 
    /* search for flag already in list */
    for (n = 0; n < imapflags->nflags; n++) {
	if (!strcmp(imapflags->flag[n], flag))
	    break;
    }
 
    /* remove flag from list, iff in list */
    if (n < imapflags->nflags) {
	libsieve_free(imapflags->flag[n]);
	imapflags->nflags--;
 
	for (; n < imapflags->nflags; n++)
	    imapflags->flag[n] = imapflags->flag[n+1];
    }
 
    return SIEVE2_OK;
}

static char *action_to_string(action_t action)
{
    switch(action)
	{
	case ACTION_REJECT: return "Reject";
	case ACTION_FILEINTO: return "Fileinto";
	case ACTION_KEEP: return "Keep";
	case ACTION_REDIRECT: return "Redirect";
	case ACTION_DISCARD: return "Discard";
	case ACTION_VACATION: return "Vacation";
	case ACTION_SETFLAG: return "Setflag";
	case ACTION_ADDFLAG: return "Addflag";
	case ACTION_REMOVEFLAG: return "Removeflag";
	case ACTION_MARK: return "Mark";
	case ACTION_UNMARK: return "Unmark";
	case ACTION_NOTIFY: return "Notify";
	case ACTION_DENOTIFY: return "Denotify";
	default: return "Unknown";
	}

    return "Error!";
}

#endif
