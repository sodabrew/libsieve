/* tree.c -- abstract syntax tree handling
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
#include "memory.h"

#include "tree.h"
#include "sieve.h"

/* sv_util */
#include "util.h"

stringlist_t *libsieve_new_sl(char *s, stringlist_t *n)
{
    stringlist_t *p = (stringlist_t *) libsieve_malloc(sizeof(stringlist_t));
    p->s = s;
    p->next = n;
    return p;
}

patternlist_t *libsieve_new_pl(regex_t *pat, patternlist_t *n)
{
    patternlist_t *p = (patternlist_t *) libsieve_malloc(sizeof(patternlist_t));
    p->p = pat;
    p->next = n;
    return p;
}

tag_t *libsieve_new_tag(int type, char *s)
{
    tag_t *p = (tag_t *) libsieve_malloc(sizeof(tag_t));
    p->type = type;
    p->arg = s;
    return p;
}

taglist_t *libsieve_new_taglist(tag_t *t, taglist_t *n)
{
    taglist_t *p = (taglist_t *) libsieve_malloc(sizeof(taglist_t));
    p->t = t;
    p->next = n;
    return p;
}

test_t *libsieve_new_test(int type) 
{
    test_t *p = (test_t *) libsieve_malloc(sizeof(test_t));
    p->type = type;
    return p;
}

testlist_t *libsieve_new_testlist(test_t *t, testlist_t *n)
{
    testlist_t *p = (testlist_t *) libsieve_malloc(sizeof(testlist_t));
    p->t = t;
    p->next = n;
    return p;
}

commandlist_t *libsieve_new_command(int type)
{
    commandlist_t *p = (commandlist_t *) libsieve_malloc(sizeof(commandlist_t));
    p->type = type;
    p->next = NULL;
    return p;
}

commandlist_t *libsieve_new_if(test_t *t, commandlist_t *y, commandlist_t *n)
{
    commandlist_t *p = (commandlist_t *) libsieve_malloc(sizeof(commandlist_t));
    p->type = IF;
    p->u.i.t = t;
    p->u.i.do_then = y;
    p->u.i.do_else = n;
    p->next = NULL;
    return p;
}

void libsieve_free_sl(stringlist_t *sl) 
{
    stringlist_t *sl2;
    
    while (sl != NULL) {
	libsieve_free(sl->s);
	sl2 = sl->next;
	libsieve_free(sl);
	sl = sl2;
    }
}

void libsieve_free_pl(patternlist_t *pl, int comptag) 
{
    patternlist_t *pl2;

    while (pl != NULL) {
	if (pl->p) {
#ifdef ENABLE_REGEX
	    if (comptag == REGEX) {
		regfree((regex_t *) pl->p);
	    }
#endif
	    libsieve_free(pl->p);
	}
	pl2 = pl->next;
	libsieve_free(pl);
	pl = pl2;
    }
}

void libsieve_free_tl(testlist_t *tl)
{
    testlist_t *tl2;

    while (tl) {
	libsieve_free_test(tl->t);
	tl2 = tl->next;
	libsieve_free(tl);
	tl = tl2;
    }
}

void libsieve_free_test(test_t *t)
{
    if (t == NULL) return;

    switch (t->type) {
    case ANYOF:
    case ALLOF:
	libsieve_free_tl(t->u.tl);
	break;

    case EXISTS:
	libsieve_free_sl(t->u.sl);
	break;

    case SIZE:
    case SFALSE:
    case STRUE:
	break;

    case HEADER:
	libsieve_free_sl(t->u.h.sl);
	libsieve_free_pl(t->u.h.pl, t->u.h.comptag);
	break;

    case ADDRESS:
	libsieve_free_sl(t->u.ae.sl);
	libsieve_free_pl(t->u.ae.pl, t->u.ae.comptag);
	break;

    case NOT:
	libsieve_free_test(t->u.t);
	break;
    }

    libsieve_free(t);
}

void libsieve_free_tree(commandlist_t *cl)
{
    commandlist_t *cl2;

    while (cl != NULL) {
	cl2 = cl->next;
	switch (cl->type) {
	case IF:
	    libsieve_free_test(cl->u.i.t);
	    libsieve_free_tree(cl->u.i.do_then);
	    libsieve_free_tree(cl->u.i.do_else);
	    break;

	case FILEINTO:
	case REDIRECT:
	case REJCT:
	    if (cl->u.str) libsieve_free(cl->u.str);
	    break;

	case VACATION:
	    if (cl->u.v.subject) libsieve_free(cl->u.v.subject);
	    if (cl->u.v.addresses) libsieve_free_sl(cl->u.v.addresses);
	    if (cl->u.v.message) libsieve_free(cl->u.v.message);
	    break;
	    
	case SETFLAG:
	case ADDFLAG:
	case REMOVEFLAG:
	    libsieve_free_sl(cl->u.sl);
	    break;

	case KEEP:
	case STOP:
	case DISCARD:
	    break;

	case NOTIFY:
	    if (cl->u.n.method) libsieve_free(cl->u.n.method);
	    if (cl->u.n.id) libsieve_free(cl->u.n.id);
	    if (cl->u.n.options) libsieve_free_sl(cl->u.n.options);
	    if (cl->u.n.message) libsieve_free(cl->u.n.message);
	    break;

	case DENOTIFY:
	    if (cl->u.d.pattern) {
#ifdef ENABLE_REGEX
		if (cl->u.d.comptag == REGEX) {
		    regfree((regex_t *) cl->u.d.pattern);
		}
#endif
		libsieve_free(cl->u.d.pattern);
	    }
	    break;
	}

	libsieve_free(cl);
	cl = cl2;
    }
}

char **libsieve_stringlist_to_chararray(stringlist_t *list)
{
    size_t space = 0, count = 0;
    char **tmp = NULL, **ret = NULL;

    while(list != NULL) {
        if(count < space) {
            ret[count++] = list->s;
            ret[count] = NULL;
        } else {
            tmp = (char **)libsieve_realloc(ret, (space+=4) * sizeof(char *));
            if(tmp == NULL) {
                libsieve_free(ret);
                return NULL;
            } else {
                ret = tmp;
            }
            ret[count++] = list->s;
            ret[count] = NULL;
        }
        list = list->next;
    }

    return ret;
}

