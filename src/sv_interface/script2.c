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
#include "thread2.h"
#include "message.h"
#include "message2.h"

/* sv_util */
#include "util.h"

/* sv_parser */
#include "parser.h"

const char *sieve2_errstr(const int code, char **free)
{
    char *ret;
    /* Comes from the Sieve Parser */
    extern int libsieve_sievelineno;
    extern char *libsieve_sieveerr;
    char lineno[50];
    *free = NULL;

    if( code == SIEVE2_ERROR_PARSE )
      {
        /* The caller must free free! */
        libsieve_memset(lineno, '\0', 50);
        snprintf(lineno, 49, "%d", libsieve_sievelineno);
        ret = libsieve_strconcat(sieve2_error_text[code], ": ", libsieve_sieveerr, " on line ", lineno, NULL);
	*free = ret;
	libsieve_free(libsieve_sieveerr);
	return ret;
      }

    return sieve2_error_text[code];
}

static unsigned sieve2_thread_count = 0;

/* A threaded client absolutely MUST
 * call this function to see if we're compiled threadsafe.
 * */
int sieve2_thread_safetycheck(void)
{
#ifdef REENTRANT_PARSER
    return 0;
#else
    return 0;
#endif
}

int sieve2_thread_alloc(sieve2_thread_t **t)
{
    sieve2_thread *thread;

/* If we're not reentrant, then we can't allocate more than one parser.
 * Note that this sanity check isn't reentrant itself!
 * */
#ifndef REENTRANT_PARSER
    if (sieve2_thread_count >= 1)
      {
        *t = NULL;
        return SIEVE2_ERROR_NOTHREADS;
      }
#endif

    /* Even if we're not running a threaded parser,
     * still allocate and return a valid structure.
     * What we do with it will surely become important
     * and prematurely assuming that non-threaded should
     * return NULL will preclude that ability.
     * */
    thread = (sieve2_thread *)libsieve_malloc(sizeof(sieve2_thread));
    if (thread == NULL)
      {
        *t = NULL;
        return SIEVE2_ERROR_NOMEM;
      }

    *t = (sieve2_thread_t *)thread;

#ifdef REENTRANT_PARSER
    libsieve_addr_create(t);
    libsieve_sieve_create(t);
    libsieve_header_create(t);
#else
    libsieve_addrlexalloc();
    libsieve_sievelexalloc();
    libsieve_headerlexalloc();
    libsieve_headeryaccalloc();
#endif

    /* FIXME: This is not an atomic operation,
     * but we're only talking about lost memory,
     * not corruption of the parsers, so it will
     * tide us over until we have real threading.
     * */
    sieve2_thread_count++;

    return SIEVE2_OK;
}

int sieve2_thread_free(sieve2_thread_t *t)
{
    if (t == NULL)
        return SIEVE2_ERROR_BADARG;

    if (sieve2_thread_count > 0)
        sieve2_thread_count--;
    else
        /* FIXME: I'm not sure how to handle this. */;

#ifdef REENTRANT_PARSER
    libsieve_addr_destroy(t);
    libsieve_sieve_destroy(t);
    libsieve_header_destroy(t);
#else
    libsieve_addrlexfree();
    libsieve_sievelexfree();
    libsieve_headerlexfree();
    libsieve_headeryaccfree();
#endif

    libsieve_free(t);

    return SIEVE2_OK;
}

int sieve2_support_alloc(sieve2_support_t **p)
{
    sieve2_support_t *support;

    support = (sieve2_support_t *)libsieve_malloc(sizeof(sieve_support_t));
    if(support == NULL)
        return SIEVE2_ERROR_NOMEM;

    *p = support;
    return SIEVE2_OK;
}

int sieve2_support_free(sieve2_support_t *p)
{
    libsieve_free((sieve_support_t *)p);
    return SIEVE2_OK;
}

int sieve2_support_register(sieve2_support_t *p, int support)
{
    sieve_support_t *q = (sieve_support_t *)p;
    if(!(support & SIEVE2_ACTION_ALL))
        return SIEVE2_ERROR_UNSUPPORTED;
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

int sieve2_validate(sieve2_thread_t *t, sieve2_script_t *s, sieve2_support_t *p)
{
    sieve_script_t *script = (sieve_script_t *)s;
    sieve_support_t *support = (sieve_support_t *)p;
    sieve2_thread *thread = (sieve2_thread *)t;

    /* The thread should be non-null regardless
     * of whether we're building reentrant or not. */
    if (script == NULL || support == NULL || thread == NULL) {
        return SIEVE2_ERROR_BADARG;
    }

    script->support = *support; /* Yes, really make a copy */

    script->cmds = libsieve_sieve_parse_buffer(script, script->char_array);
    libsieve_free_tree(script->cmds);
    script->cmds = NULL;

    if (script->err > 0) {
        return SIEVE2_ERROR_PARSE;
    }

    return SIEVE2_OK;
}

/* This is where we really do it:
 * run a script over a message to produce an action list
 *
 * Error codes:
 * SIEVE2_ERROR_BADARG if any of the arguments are NULL
 * SIEVE2_ERROR_PARSE for script parse errors
 * SIEVE2_ERROR_EXEC for script evaluation errors
 */
int sieve2_execute(sieve2_thread_t *t, sieve2_script_t *s, sieve2_support_t *p,
		sieve2_message_t *m, sieve2_action_t *a)
{
    int ret;
    const char *errmsg = NULL;
    sieve_script_t *script = (sieve_script_t *)s;
    sieve2_message *message = (sieve2_message *)m;
    sieve2_thread *thread = (sieve2_thread *)t;
    sieve_support_t *support = (sieve_support_t *)p;
    action_list_t *action = (action_list_t *)a;

    if (script == NULL || message == NULL ||
        support == NULL || action == NULL || thread == NULL) {
        return SIEVE2_ERROR_BADARG;
    }

    /* Generate a hash cache
     * There is a call to header_parse_buffer()
     * a bit further down the stack from here. */
    message2_headercache(message);

    script->support = *support; /* Yes, really make a copy */

    script->cmds = libsieve_sieve_parse_buffer(script, script->char_array);
    if (script->err > 0) {
        if (script->cmds) {
            libsieve_free_tree(script->cmds);
        }
        script->cmds = NULL;
        return SIEVE2_ERROR_PARSE;
    }

    if (eval(&script->interp, script->cmds, message, action, &errmsg) < 0)
        ret = SIEVE2_ERROR_EXEC;

    ret = SIEVE2_OK;

    return ret;
}

int sieve2_action_alloc(sieve2_action_t **in)
{
    action_list_t **a = (action_list_t **)in;
    action_list_t *actions;

    actions = libsieve_new_action_list();
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
                // libsieve_free(c->msg);
                libsieve_free(c);
                break;
                }
            case ACTION_FILEINTO:
                {
                sieve2_fileinto_context_t *c = (sieve2_fileinto_context_t *)(a->u);
                /* This is free()'d for us by free_tree */
                // libsieve_free(c->mailbox);
                libsieve_free(c);
                break;
                }
            case ACTION_REDIRECT:
                {
                sieve2_redirect_context_t *c = (sieve2_redirect_context_t *)(a->u);
                /* This is free()'d for us by free_tree */
                // libsieve_free(c->addr);
                libsieve_free(c);
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
                libsieve_free_notify_list(c);
                /* Since we'll just free it right here */
                libsieve_free(c);
                break;
                }
            default:
                /* FIXME: Should we add all the other codes back in, to
                 * be able to be certain that we're not missing anything? */
//                return SIEVE2_ERROR_EXEC;
                /* TODO: I believe that simply returning SIEVE2_ERROR_UNSUPPORTED
                 * will do the trick... but does that make sense? We're generating
                 * something that we ourselves don't support!? Hmm... */
                break;
        }
        a = b->next;
        libsieve_free(b);
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

    script = (sieve_script_t *)libsieve_malloc(sizeof(sieve_script_t));
    if(script == NULL)
        return SIEVE2_ERROR_NOMEM;

    /* Be sure to NULL the interpreter, otherwise some of
     * the internals will start calling random addresses! */
    libsieve_interp_reset(&script->interp, NULL);

    /* These used to be in sieve.y, but needed to be higher */
    *(sieve_script_t **)s = script;
    return SIEVE2_OK;
}

int sieve2_script_free(sieve2_script_t *s)
{
    sieve_script_t *t = (sieve_script_t *)s;

    if (t) {
	if (t->cmds) {
	    libsieve_free_tree(t->cmds);
	}
	libsieve_free(t);
    }

    /* These used to be in sieve.y, but needed to be higher */
    return SIEVE2_OK;
}

/* Given a script, produce an opaque struct holding the executable code */
/* The internal structure to which these items have to be added
 * is sieve_script in script.h. Make changes in both places!
 * */
int sieve2_script_register(sieve2_script_t *s, void *thing, int type)
{
    sieve_script_t *t = (sieve_script_t *)s;

    if (thing == NULL)
        return SIEVE2_ERROR_EXEC;

    t->err = 0;       /* Reset error count */
    t->lineno = 1;    /* Reset line number */

    switch(type) {
        case SIEVE2_SCRIPT_CHAR_ARRAY:
            t->char_array = (char *)thing;
            break;
        case SIEVE2_SCRIPT_SIZE:
        case SIEVE2_SCRIPT_CALLBACK:
        case SIEVE2_SCRIPT_INCLUDE_CALLBACK:
        case SIEVE2_SCRIPT_FILE_POINTER:
            /* Since we don't support these yet... */
        default:
            return SIEVE2_ERROR_UNSUPPORTED;
            break;
    }

    return SIEVE2_OK;
}

int sieve2_message_alloc(sieve2_message_t **m)
{
    int i;
    sieve2_message *n = NULL;

    n = (sieve2_message *)libsieve_malloc(sizeof(sieve2_message));
    if (n == NULL)
        return SIEVE2_ERROR_NOMEM;

    n->hash = (header_t **)libsieve_malloc(sizeof(header_t) * HEADERHASHSIZE);
    if (n->hash == NULL) {
        /* No leaking just because there's no memory! */
        libsieve_free(n);
        return SIEVE2_ERROR_NOMEM;
    }
    n->hashfull = 0;
    n->hashsize = HEADERHASHSIZE;
    for (i = 0; i < HEADERHASHSIZE; i++) {
        n->hash[i] = NULL;
    }

    *(sieve2_message **)m = n;
    return SIEVE2_OK;
}

int sieve2_message_free(sieve2_message_t *m)
{
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
            break;
        case SIEVE2_MESSAGE_ENVELOPE:
            n->envelope = (char *)thing;
            break;
        default:
            return SIEVE2_ERROR_UNSUPPORTED;
            break;
    }

    return SIEVE2_OK;
}

const char *sieve2_extensions_listconst(void)
{
    /* This is defined in interp.c */
    extern const char *sieve_extensions;
    return sieve_extensions;
}

/* Caller must free the return pointer */
char *sieve2_extensions_listsupport(sieve2_support_t *p)
{
    /* This is defined in interp.c */
    extern const char *sieve_extensions;
    return sieve_extensions;
}

#if (MSDOS || WIN32)
#define NL "\r\n"
#else
#define NL "\n"
#endif

const char *sieve2_credits(void)
{
    return "libSieve is written and maintained by Aaron Stone"
        " with many thanks to those who have helped to debug"
        " and to secure this fine piece of software."
     NL " " NL
	" Specific thanks to:"
     NL " " NL
        " Portions of libSieve are based on the Sieve support"
        " of the Cyrus Email Server by Carnegie Mellon University."
        ;
}

const char *sieve2_license(void)
{
    return "libSieve is Copyright 2002, 2003 Aaron Stone, CA, USA"
        " and is licensed under the GNU General Public License,"
        " version 2 and (at the author's option, not yours)"
        " any later version. A copy of the license should have"
        " been distributed with libSieve, and if not, may be"
        " obtained by writing to the Free Software Foundation:"
     NL " Free Software Foundation, Inc.    " NL
        " 59 Temple Place, Suite 330        " NL
        " Boston, MA  02111-1307  USA       " NL
     NL " " NL
        " Portions based on the Sieve support of the"
        " Cyrus Email Server by Carnegie Mellon University"
        " are Copyright 1994, 1995, 1996 CMU, PA, USA."
        " While CMU's license is not the GPL, it does not preclude such"
        " combination in a larger work, such as libSieve, in a manner"
        " which places the work as a whole under the GNU GPL."
     NL " " NL
        " This program is distributed in the hope that it will be useful,"
        " but WITHOUT ANY WARRANTY; without even the implied warranty of"
        " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
        " GNU General Public License for more details."
        ;
}

