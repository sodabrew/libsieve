/* script2.c -- sieve script functions for version 2 api
 * Aaron Stone
 * $Id$
 */
/***********************************************************
 * FIXME: needs license
******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "md5global.h"
#include "md5.h"

#include "sieve_interface.h"
#include "sieve2_interface.h"
#include "interp.h"
#include "script.h"
#include "tree.h"
#include "message.h"
#include "message2.h"

/* sv_util */
#include "util.h"

/* sv_parser */
#include "sieve.h"
//#include "sieveinc.h"

const char *sieve2_errstr(const int code)
{
    /* Comes from the Sieve Parser */
    extern int sievelineno;
    extern char *sieveerr;
    char lineno[50];
    if( code == SIEVE2_ERROR_PARSE )
        /* FIXME: this is a memory leak since
         * the caller likely won't free it */
        memset(lineno, 0, 50);
        snprintf(lineno, 49, "%d", sievelineno);
        return sv_strconcat(sieve2_error_text[code], ": ", sieveerr, " on line ", lineno, NULL);
    return sieve2_error_text[code];
}

int sieve2_support_alloc(sieve2_support_t **p)
{
    sieve2_support_t *support;

    support = (sieve2_support_t *)sv_malloc(sizeof(sieve_support_t));
    if(support == NULL)
        return SIEVE2_ERROR_NOMEM;

    *p = support;
    return SIEVE2_OK;
}

int sieve2_support_free(sieve2_support_t *p)
{
    sv_free((sieve_support_t *)p);
    return SIEVE2_OK;
}

int sieve2_support_bind(sieve2_support_t *p, sieve2_script_t *s)
{
    ((sieve_script_t *)s)->support = *(sieve_support_t *)p;
    return SIEVE2_OK;
}

int sieve2_support_register(sieve2_support_t *p, int support)
{
    sieve_support_t *q = (sieve_support_t *)p;
    /* FIXME: If the client program supports something that the 
     * interpreter doesn't then we've got a problem, right? */
    if(!(support & SIEVE2_ACTION_ALL))
        return SIEVE2_ERROR_EXEC;
    if(support & SIEVE2_ACTION_REJECT)
        q->reject = 1;
    if(support & SIEVE2_ACTION_FILEINTO)
        q->fileinto = 1;
    if(support & SIEVE2_ACTION_VACATION)
        q->vacation = 1;
    if(support & SIEVE2_ACTION_SETFLAG)
        q->imapflags = 1;
    if(support & SIEVE2_ACTION_NOTIFY)
        q->notify= 1;
    return SIEVE2_OK;
}

/* Main entry point for script execution in the version 2 api
 */
int sieve2_script_exec(sieve2_script_t *s, sieve2_message_t *m, sieve2_action_t *a)
{
    int ret;
    const char *errmsg = NULL;
    sieve_script_t *r = (sieve_script_t *)s;
    action_list_t *b = (action_list_t *)a;

    if (eval(&r->interp, r->cmds, m, b, &errmsg) < 0)
        ret = SIEVE2_ERROR_EXEC;

    ret = SIEVE2_OK;

    return ret;
}

int sieve2_notify_alloc(notify_list_t **n)
{
    notify_list_t *notify;

    notify = new_notify_list();
    if (notify == NULL)
        return SIEVE2_ERROR_NOMEM;

    *n = notify;
    return SIEVE2_OK;
}

int sieve2_action_alloc(sieve2_action_t **in)
{
    action_list_t **a = (action_list_t **)in;
    action_list_t *actions;

    actions = new_action_list();
    if (actions == NULL)
        return SIEVE2_ERROR_NOMEM;

    *a = actions;
    return SIEVE2_OK;
}

/* Free the action list, and also free any
 * action contexts that have been allocated. */
int sieve2_action_free(sieve2_action_t *in)
{
    action_list_t *a = (action_list_t *)in;
    action_list_t *b;

    while(a) {
        b = a;
        switch(b->a) {
            case ACTION_REJECT:
                {
                sieve2_reject_context_t *c = (sieve2_reject_context_t *)(a->u);
                /* This is free()'d for us by free_tree */
                // sv_free(c->msg);
                sv_free(c);
                break;
                }
            case ACTION_FILEINTO:
                {
                sieve2_fileinto_context_t *c = (sieve2_fileinto_context_t *)(a->u);
                /* This is free()'d for us by free_tree */
                // sv_free(c->mailbox);
                sv_free(c);
                break;
                }
            case ACTION_REDIRECT:
                {
                sieve2_redirect_context_t *c = (sieve2_redirect_context_t *)(a->u);
                /* This is free()'d for us by free_tree */
                // sv_free(c->addr);
                sv_free(c);
                break;
                }
            case ACTION_VACATION:
                break;
            case ACTION_SETFLAG:
                break;
            case ACTION_ADDFLAG:
                break;
            case ACTION_REMOVEFLAG:
                break;
            case ACTION_MARK:
                break;
            case ACTION_UNMARK:
                break;
            case ACTION_NOTIFY:
                {
                notify_list_t *c = (notify_list_t *)(a->u);
                /* This won't free the top, which is fine */
                free_notify_list(c);
                /* Since we'll just free it right here */
                sv_free(c);
                break;
                }
            default:
                /* FIXME: Should we add all the other codes back in, to
                 * be able to be certain that we're not missing anything? */
//                return SIEVE2_ERROR_EXEC;
                break;
        }
        a = b->next;
        sv_free(b);
    }

    return SIEVE2_OK;
}

/* Grab the current call code and action context,
 * then advance the list pointer to the next action */
int sieve2_action_next(sieve2_action_t **in, int *code, void **action_context)
{
    action_list_t **a = (action_list_t **)in;
    action_list_t *b = *a;

    if(b != NULL) {
        switch( b->a ) {
            case ACTION_NULL:
                *code = SIEVE2_ACTION_NULL;
                break;
            case ACTION_NONE:
                *code = SIEVE2_ACTION_NONE;
                break;
            case ACTION_REJECT:
                *code = SIEVE2_ACTION_REJECT;
                break;
            case ACTION_FILEINTO:
                *code = SIEVE2_ACTION_FILEINTO;
                break;
            case ACTION_KEEP:
                *code = SIEVE2_ACTION_KEEP;
                break;
            case ACTION_REDIRECT:
                *code = SIEVE2_ACTION_REDIRECT;
                break;
            case ACTION_DISCARD:
                *code = SIEVE2_ACTION_DISCARD;
                break;
            case ACTION_VACATION:
                *code = SIEVE2_ACTION_VACATION;
                break;
            case ACTION_SETFLAG:
                *code = SIEVE2_ACTION_SETFLAG;
                break;
            case ACTION_ADDFLAG:
                *code = SIEVE2_ACTION_ADDFLAG;
                break;
            case ACTION_REMOVEFLAG:
                *code = SIEVE2_ACTION_REMOVEFLAG;
                break;
            case ACTION_MARK:
                *code = SIEVE2_ACTION_MARK;
                break;
            case ACTION_UNMARK:
                *code = SIEVE2_ACTION_UNMARK;
                break;
            case ACTION_NOTIFY:
                *code = SIEVE2_ACTION_NOTIFY;
                break;
            case ACTION_DENOTIFY:
                *code = SIEVE2_ACTION_DENOTIFY;
                break;
            default:
                return SIEVE2_ERROR_EXEC;
                break;
        }
        *action_context = b->u;
    } else {
        return SIEVE2_DONE;
    }

    *a = b->next;
    return SIEVE2_OK;
}

int sieve2_script_alloc(sieve2_script_t **s)
{
    sieve_script_t *script;

    script = (sieve_script_t *)sv_malloc(sizeof(sieve_script_t));
    if(script == NULL)
        return SIEVE2_ERROR_NOMEM;

    /* Be sure to NULL the interpreter, otherwise some of
     * the internals will start calling random addresses! */
    interp_reset(&script->interp, NULL);

    /* These used to be in sieve.y, but needed to be higher */
    addrlexalloc();
    sievelexalloc();

    *(sieve_script_t **)s = script;
    return SIEVE2_OK;
}

int sieve2_script_free(sieve2_script_t *s)
{
    sieve_script_t *t = (sieve_script_t *)s;

    if (t) {
	if (t->cmds) {
	    free_tree(t->cmds);
	}
	sv_free(t);
    }

    /* These used to be in sieve.y, but needed to be higher */
    addrlexfree();
    sievelexfree();

    return SIEVE2_OK;
}

/* Given a script, produce an opaque struct holding the executable code */
int sieve2_script_parse(sieve2_script_t *s, char *script)
{
    extern int sievelineno;
    sieve_script_t *t = (sieve_script_t *)s;

    t->err = 0;
    sievelineno = 1;    /* reset line number */
    t->cmds = sieve_parse_buffer(t, script);
    if (t->err > 0) {
	if (t->cmds) {
	    free_tree(t->cmds);
	}
	t->cmds = NULL;
	return SIEVE2_ERROR_PARSE;
    }
    return SIEVE2_OK;
}

int sieve2_message_alloc(sieve2_message_t **m)
{
    int i;
    sieve2_message *n = NULL;

    n = (sieve2_message *)sv_malloc(sizeof(sieve2_message));
    if (n == NULL)
        return SIEVE2_ERROR_NOMEM;

    n->hash = (header_t **)sv_malloc(sizeof(header_t) * HEADERHASHSIZE);
    if (n->hash == NULL) {
        /* No leaking just because there's no memory! */
        sv_free(n);
        return SIEVE2_ERROR_NOMEM;
    }
    n->hashfull = 0;
    n->hashsize = HEADERHASHSIZE;
    for (i = 0; i < HEADERHASHSIZE; i++) {
        n->hash[i] = NULL;
    }

    headerlexalloc();

    *(sieve2_message **)m = n;
    return SIEVE2_OK;
}

int sieve2_message_free(sieve2_message_t *m)
{
    headerlexfree();
    return message2_freecache((sieve2_message *)m);
}

int sieve2_message_register(sieve2_message_t *m, void *thing, int type)
{
    sieve2_message *n = (sieve2_message *)m;

    if (thing == NULL)
        return SIEVE2_ERROR_EXEC;

    switch(type) {
        case SIEVE2_MESSAGE_SIZE:
            /* No pointers, thanks */
            n->size = *(int *)thing;
            break;
        case SIEVE2_MESSAGE_HEADER:
            n->header = (char *)thing;
            /* Generate a hash cache */
            message2_headercache(n);
            break;
        case SIEVE2_MESSAGE_ENVELOPE:
            n->envelope = (char *)thing;
            break;
        default:
            /* FIXME: Or should we just quietly ignore this? */
            return SIEVE2_ERROR_EXEC;
            break;
    }

    return SIEVE2_OK;
}

