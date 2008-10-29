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

#define THIS_MODULE "sv_interface"
#define THIS_CONTEXT context

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
static char *look_for_me(char *myaddr, stringlist_t *myaddrs, char **body)
{
    char *found = NULL;
    int l;
    stringlist_t *sl;

    /* Short circuit if myaddr is NULL */
    if (myaddr == NULL)
            return NULL;

    /* loop through each TO header */
    for (l = 0; body[l] != NULL && !found; l++) {
        struct address *data = NULL;
        struct addr_marker *marker = NULL;
        char *addr;
        
        libsieve_parse_address(body[l], &data, &marker);
        /* loop through each address in the header */
        while (!found && ((addr = libsieve_get_address(NULL, ADDRESS_ALL, &marker, 1)) != NULL)) {
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
                altaddr = libsieve_get_address(NULL, ADDRESS_ALL, &altmarker, 1);
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

    if (t == NULL) {
            TRACE_DEBUG("t is null");
            return 0;
    }

    switch (t->type) {
    case ADDRESS:
    case ENVELOPE:
        switch (t->u.ae.addrpart) {
        case ALL: addrpart = ADDRESS_ALL; break;
        case LOCALPART: addrpart = ADDRESS_LOCALPART; break;
        case DOMAIN: addrpart = ADDRESS_DOMAIN; break;
        case USER: addrpart = ADDRESS_USER; break;
        case DETAIL: addrpart = ADDRESS_DETAIL; break;
        }
        for (sl = t->u.ae.sl; sl != NULL && !res; sl = sl->next) {
            int l;
            char **body;
            char **header;
            char *envelope;
            int freebody = 0;

            /* use getheader for address, getenvelope for envelope */
            if (t->type == ADDRESS) {
                if (libsieve_do_getheader(context, sl->s, &header) != SIEVE2_OK)
                    continue; /* try next header */
                body = header;
            } else {
                if (libsieve_do_getenvelope(context, sl->s, &envelope) != SIEVE2_OK)
                    continue; /* try next header */
                body = libsieve_malloc(2 * sizeof(char *));
                body[0] = envelope;
                body[1] = NULL;
                freebody = 1;
            }

            // For :count, tally up the instances of the header and then call
            // the comparator with that numeric value in a decimal string.
            int count = 0;

            for (pl = t->u.ae.pl; pl != NULL && !res; pl = pl->next) {
                for (l = 0; body[l] != NULL && !res; l++) {
                    /* loop through each header */
                    struct address *data = NULL;
                    struct addr_marker *marker = NULL;
                    char *val;

                    libsieve_parse_address(body[l], &data, &marker);
                    val = libsieve_get_address(context, addrpart, &marker, 0);
                    while (val != NULL && !res) { 
                        /* loop through each address */
                        if (libsieve_relational_count(t->u.h.comptag)) {
                            count++;
                        } else {
                            res |= t->u.ae.comp(pl->p, val);
                        }
                        val = libsieve_get_address(context, addrpart, &marker, 0);
                           }
                    libsieve_free_address(&data, &marker);
                }

                if (libsieve_relational_count(t->u.h.comptag)) {
                    char countstr[20];
                    snprintf(countstr, 19, "%d", count);
                    TRACE_DEBUG("Count was [%s] compfunc is [%p](%s, %s)",
                            countstr, t->u.ae.comp, (char *)pl->p, countstr);
                    res |= t->u.ae.comp(pl->p, countstr);
                }
            }

            if (freebody)
                libsieve_free(body);
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
            char **headbody = NULL;
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
        TRACE_DEBUG("Doing a header comparison");
        TRACE_DEBUG("Relation is [%d]", t->u.h.comptag);
        for (sl = t->u.h.sl; sl != NULL && !res; sl = sl->next) {
            char **val;
            size_t l;
            TRACE_DEBUG("Asking for header [%s]", sl->s);
            if (libsieve_do_getheader(context, sl->s, &val) != SIEVE2_OK)
                continue;
            for (pl = t->u.h.pl; pl != NULL && !res; pl = pl->next) {
                int count = 0;
                for (l = 0; val[l] != NULL && !res; l++) {
                    TRACE_DEBUG("test HEADER comparing [%s] with [%s]",
                        (char *)pl->p, val[l]);
                    if (libsieve_relational_count(t->u.h.comptag)) {
                        count++;
                    } else {
                        res |= t->u.h.comp(pl->p, val[l]);
                    }
                }

                if (libsieve_relational_count(t->u.h.comptag)) {
                    char countstr[20];
                    snprintf(countstr, 19, "%d", count);
                    TRACE_DEBUG("Count was [%s] compfunc is [%p](%s, %s)",
                        countstr, t->u.h.comp, (char *)pl->p, countstr);
                    res |= t->u.h.comp(pl->p, countstr);
                }
            }
        }
        break;
    case HASFLAG:
        res = 0;
        for (sl = t->u.h.sl; sl != NULL && !res; sl = sl->next) {
            stringlist_t *csl;
            for (csl = context->slflags; csl != NULL; csl = csl->next) {
            // FIXME:    res |= t->u.h.comp(pl->p, val[l]);
                if (strcasecmp(csl->s, sl->s) == 0) {
                    res = 1;
                    break;
                }
            }
            if (res)
                break;
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
// TODO: Can we change this to be iterative, or somehow tail-recursive-optimized?
int libsieve_eval(struct sieve2_context *context,
                  commandlist_t *c, const char **errmsg)
{
    int res = 0;
    stringlist_t *sl;

    TRACE_DEBUG("starting into libsieve_eval");
    
    if (c == NULL)
        TRACE_DEBUG("the commandlist is null");
    else
        TRACE_DEBUG("the commandlist type is [%d]", c->type);

    while (c != NULL) {
        TRACE_DEBUG("top of the eval loop");
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
            TRACE_DEBUG("Doing a reject");
            break;
        case FILEINTO:
            res = libsieve_do_fileinto(context, c->u.f.mailbox, c->u.f.slflags);
            if (res == SIEVE2_ERROR_EXEC)
                *errmsg = "Fileinto can not be used with Reject";
            TRACE_DEBUG("Doing a fileinto");
            break;
        case REDIRECT:
            res = libsieve_do_redirect(context, c->u.str);
            if (res == SIEVE2_ERROR_EXEC)
                *errmsg = "Redirect can not be used with Reject";
            TRACE_DEBUG("Doing a redirect");
            break;
        case KEEP:
            res = libsieve_do_keep(context, c->u.f.slflags);
            if (res == SIEVE2_ERROR_EXEC)
                *errmsg = "Keep can not be used with Reject";
            TRACE_DEBUG("Doing a keep");
            break;
        case VACATION:
            {
                char **body;
                char *fromaddr;
                char *found = NULL;
                char *myaddr = NULL;
                char *reply_to = NULL;
                int l = SIEVE2_OK;
                struct address *data = NULL;
                struct addr_marker *marker = NULL;
                char *tmp;

                TRACE_DEBUG("Starting into a VACATION action.");

                /* is there an Auto-Submitted keyword other than "no"? */
                if (libsieve_do_getheader(context, "auto-submitted", &body) == SIEVE2_OK) {
                    /* we don't deal with comments, etc. here */
                    /* skip leading white-space */
                    while (body[0] && *body[0] && isspace((int) *body[0])) body[0]++;
                    if (strcasecmp(body[0], "no")) l = SIEVE2_DONE;
                }

                if (l == SIEVE2_DONE)
                        TRACE_DEBUG("VACATION aborted by Auto-Submitted header.");

                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Id", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Id header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Help", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Help header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Subscribe", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Subscribe header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Unsubscribe", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Unsubscribe header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Post", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Post header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Owner", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Owner header.");
                }
 
                if (l == SIEVE2_OK && libsieve_do_getheader(context, "List-Archive", &body) == SIEVE2_OK) {
                    l = SIEVE2_DONE;
                    TRACE_DEBUG("VACATION aborted by List-Archive header.");
                }
 
                /* Is there a Precedence keyword of "junk | bulk | list"? */
                if (libsieve_do_getheader(context, "precedence", &body) == SIEVE2_OK) {
                    /* Skip leading white-space */
                    while (body[0] && *body[0] && isspace((int) *body[0])) {
                        body[0]++;
                    }

                    /* We don't deal with comments, etc. here */
                    if (!strcasecmp(body[0], "junk") ||
                        !strcasecmp(body[0], "bulk") ||
                        !strcasecmp(body[0], "list")) {
                        l = SIEVE2_DONE;
                        TRACE_DEBUG("VACATION aborted by Precedence header.");
                    }
                }

                /* Note: the domain-part of all addresses are canonicalized */

                /* grab my address from the envelope */
                if (l == SIEVE2_OK) {
                    l = libsieve_do_getenvelope(context, "to", body);
                    if (body[0]) {
                        libsieve_parse_address(body[0], &data, &marker);
                        tmp = libsieve_get_address(context, ADDRESS_ALL, &marker, 1);
                        myaddr = (tmp != NULL) ? libsieve_strdup(tmp) : NULL;
                        libsieve_free_address(&data, &marker);
                    }
                }
                if (l == SIEVE2_OK) {
                    l = libsieve_do_getenvelope(context, "from", body);
                }
                if (l == SIEVE2_OK && body[0]) {
                    /* we have to parse this address & decide whether we
                       want to respond to it */
                    libsieve_parse_address(body[0], &data, &marker);
                    tmp = libsieve_get_address(context, ADDRESS_ALL, &marker, 1);
                    reply_to = (tmp != NULL) ? libsieve_strdup(tmp) : NULL;
                    libsieve_free_address(&data, &marker);

                    /* first, is there a reply-to address? */
                    if (reply_to == NULL) {
                        TRACE_DEBUG("VACATION aborted by lack of reply-to address.");
                        l = SIEVE2_DONE;
                    }

                    /* first, is it from me? */
                    if (l == SIEVE2_OK && myaddr && !strcmp(myaddr, reply_to)) {
                        TRACE_DEBUG("VACATION aborted because the message is from my primary address.");
                        l = SIEVE2_DONE;
                    }

                    /* ok, is it any of the other addresses i've
                       specified? */
                    if (l == SIEVE2_OK)
                        for (sl = c->u.v.addresses; sl != NULL; sl = sl->next)
                            if (sl->s && !strcmp(sl->s, reply_to))
                                l = SIEVE2_DONE;

                    if (l == SIEVE2_DONE)
                        TRACE_DEBUG("VACATION aborted because the message is from a secondary address.");
                
                    /* ok, is it a system address? */
                    if (l == SIEVE2_OK && sysaddr(reply_to)) {
                        TRACE_DEBUG("VACATION aborted because the message is from a system address.");
                        l = SIEVE2_DONE;
                    }
                }

                if (l == SIEVE2_OK) {
                    /* OK, we're willing to respond to the sender. But is this
                     * message to me? That is, is my address in the TO, Cc, Bcc,
                     * Resent-To, Resent-Cc, or Resent-Bcc fields? But if the
                     * vacation action contains :from directive, then set the
                     * sender address accordingly */

                    if (c->u.v.from != NULL)
                       found = c->u.v.from;
 
                    if (!found && (libsieve_do_getheader(context, "to", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);
                    if (!found && (libsieve_do_getheader(context, "cc", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);
                    if (!found && (libsieve_do_getheader(context, "bcc", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);
                    if (!found && (libsieve_do_getheader(context, "Resent-To", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);
                    if (!found && (libsieve_do_getheader(context, "Resent-Cc", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);
                    if (!found && (libsieve_do_getheader(context, "Resent-Bcc", &body) == SIEVE2_OK))
                       found = look_for_me(myaddr, c->u.v.addresses, body);

                    if (!found) {
                        TRACE_DEBUG("Vacation didn't find my address in To, Cc, Bcc, Resent-To, Resent-Cc or Resent-Bcc.");
                        l = SIEVE2_DONE;
                    }
                }

                if (l == SIEVE2_OK) {
                    /* ok, ok, if we got here maybe we should reply */
                    char buf[128];
                
                    if (c->u.v.subject == NULL) {
                        /* we have to generate a subject */
                        char **s;
                    
                        if (libsieve_do_getheader(context, "subject", &s) != SIEVE2_OK ||
                            s[0] == NULL) {
                            strcpy(buf, "Automated reply");
                        } else {
                            /* s[0] contains the original subject */
                            snprintf(buf, sizeof(buf), "Auto: %s", (const char*)s[0]);
                        }
                    } else {
                        /* user specified subject */
                        strncpy(buf, c->u.v.subject, sizeof(buf)-1);
                        buf[sizeof(buf)-1] = '\0';
                    }

                    /* calculate hash from subject, from, mime and reason, RFC 5230, Section 4.2 */
                    if (c->u.v.handle == NULL) {
                        int j = 0;
                        if (c->u.v.subject) j += strlen(c->u.v.subject);
                        if (c->u.v.from) j+= strlen(c->u.v.from);
                        /* Add 5: 3 for the separators between the items,
                         * 1 for mime value and one for the terminating '\0' */
                        j += strlen(c->u.v.message) + 5;
                        c->u.v.handle = libsieve_malloc(j);
                        sprintf(c->u.v.handle, "%s:%s:%s:%i",
                            c->u.v.subject ? c->u.v.subject : "",
                            c->u.v.from ? c->u.v.from : "",
                            c->u.v.message,
                            c->u.v.mime);
                    }

                    /* who do we want the message coming from? */
                    fromaddr = found;
                
                    res = libsieve_do_vacation(context, reply_to,
                                      libsieve_strdup(fromaddr),
                                      libsieve_strdup(buf),
                                      c->u.v.message, c->u.v.handle,
                                      c->u.v.days, c->u.v.mime);
                
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
            TRACE_DEBUG("Doing a discard");
            break;
        case SETFLAG:
            sl = c->u.sl;
            libsieve_free_sl_only(context->slflags);
            context->slflags = libsieve_new_sl(sl->s, context->slflags);
            TRACE_DEBUG("Doing a setflag");
            break;
        case ADDFLAG:
            for (sl = c->u.sl; sl != NULL; sl = sl->next) {
                stringlist_t *csl;
                int found = 0;
                for (csl = context->slflags; csl != NULL; csl = csl->next) {
                    if (strcasecmp(csl->s, sl->s) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    context->slflags = libsieve_new_sl(sl->s, context->slflags);
                    TRACE_DEBUG("Added flag: [%s]", sl->s);
                }
                TRACE_DEBUG("Doing an addflag: [%s]", sl->s);
            }
            break;
        case REMOVEFLAG:
            for (sl = c->u.sl; sl != NULL; sl = sl->next) {
                stringlist_t *csl, *prev = NULL;
                for (csl = context->slflags; csl != NULL; csl = csl->next) {
                    if (strcasecmp(csl->s, sl->s) == 0) {
                        if (prev) {
                            prev->next = csl->next;
                            csl->next = NULL;
                            libsieve_free_sl_only(csl);
                        } else {
                            libsieve_free_sl_only(context->slflags);
                            context->slflags = NULL;
                        }
                        TRACE_DEBUG("Removed flag: [%s]", sl->s);
                        break; // Once we find a flag we can stop looking.
                    }
                    prev = csl; // Previous item in the list.
                }
                TRACE_DEBUG("Doing a removeflag [%s]", sl->s);
            }
            break;
        case NOTIFY:
            res = libsieve_do_notify(context, c->u.n.id, c->u.n.method,
                            c->u.n.options, c->u.n.priority, c->u.n.message);
            TRACE_DEBUG("Doing a notify");
            break;
        }

        if (res) /* we've either encountered an error or a stop */
            break;

        /* execute next command */
        c = c->next;
    }

    return res;
}

/* vim: set ex ts=4: */

