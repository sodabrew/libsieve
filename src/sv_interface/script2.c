/* script2.c -- sieve script functions for version 2 api
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2003, 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* CMU portions. */
#include "tree.h"
#include "script.h"
#include "message.h"

/* libSieve additions. */
#include "callbacks2.h"
#include "message2.h"
#include "context2.h"
#include "sieve2.h"
#include "sieve2_error.h"

/* sv_util */
#include "util.h"

/* sv_parser */
#include "parser.h"

char * sieve2_errstr(int code)
{
    if (code < SIEVE2_OK || code > SIEVE2_ERROR_LAST)
        return "Invalid error code.";
    return (char *)sieve2_error_text[code];
}

int sieve2_alloc(sieve2_context_t **context)
{
    struct sieve2_context *c;

    c = (struct sieve2_context *)
        libsieve_malloc(sizeof(struct sieve2_context));
    if (c == NULL) {
        *context = NULL;
        return SIEVE2_ERROR_NOMEM;
    }
    memset(c, 0, sizeof(struct sieve2_context));

    // TODO: Contextualize the lexer and parser.
    libsieve_addrlexalloc();
    libsieve_sievelexalloc();
    libsieve_headerlexalloc();
    libsieve_headeryaccalloc();

    libsieve_message2_alloc(&c->message);

    libsieve_strbufalloc(&c->strbuf);

    *context = c;

    return SIEVE2_OK;
}

int sieve2_free(sieve2_context_t **context)
{
    struct sieve2_context *c;

    if (context == NULL)
        return SIEVE2_ERROR_BADARGS;
    c = *context;

    /* These used to be in sieve.y, but needed to be higher */
    if (c->script.cmds) {
        libsieve_free_tree(c->script.cmds);
    }

    libsieve_message2_free(&c->message);

    libsieve_addrlexfree();
    libsieve_sievelexfree();
    libsieve_headerlexfree();
    libsieve_headeryaccfree();

    libsieve_strbuffree(&c->strbuf, FREEME);

    if (c->slflags) {
	libsieve_free_sl_only(c->slflags);
    }

    libsieve_free(c);
    *context = NULL;

    return SIEVE2_OK;
}

/* Fill in the support structure based on
 * the registered callbacks. */
static void static_check_support(struct sieve2_context *c)
{
	if (c->callbacks.fileinto)
	    c->support.fileinto = 1;
	
        if (c->callbacks.reject)
	    c->support.reject = 1;

	if (c->callbacks.getenvelope)
	    c->support.envelope = 1;

	if (c->callbacks.getsubaddress)
	    c->support.subaddress = 1;

	if (c->callbacks.vacation)
	    c->support.vacation = 1;

	if (c->callbacks.notify)
	    c->support.notify = 1;
}

/* Register the user's callback functions into the Sieve context.
 * Also set up the support structure based on which actions have
 * callbacks registered for them. */
int sieve2_callbacks(sieve2_context_t *context,
                     sieve2_callback_t *callbacks)
{
    struct sieve2_context *c = (struct sieve2_context *)context;
    sieve2_callback_t *cb;

    if (c == NULL || callbacks == NULL)
        return SIEVE2_ERROR_BADARGS;

    for (cb = callbacks; cb->value; cb++)
      {
        switch(cb->value)
          {
#define   CBCASE(VAL, CB) \
          case VAL: \
              c->callbacks.CB = cb->func; \
              break
          CBCASE(SIEVE2_ACTION_REDIRECT,       redirect);
          CBCASE(SIEVE2_ACTION_REJECT,         reject);
          CBCASE(SIEVE2_ACTION_DISCARD,        discard);
          CBCASE(SIEVE2_ACTION_FILEINTO,       fileinto);
          CBCASE(SIEVE2_ACTION_KEEP,           keep);
          CBCASE(SIEVE2_ACTION_NOTIFY,         notify);
          CBCASE(SIEVE2_ACTION_VACATION,       vacation);

          CBCASE(SIEVE2_ERRCALL_RUNTIME,       err_runtime);
          CBCASE(SIEVE2_ERRCALL_PARSE,         err_parse);
          CBCASE(SIEVE2_DEBUG_TRACE,           debug_trace);

          CBCASE(SIEVE2_SCRIPT_GETSCRIPT,      getscript);

          CBCASE(SIEVE2_MESSAGE_GETHEADER,     getheader);
          CBCASE(SIEVE2_MESSAGE_GETALLHEADERS, getallheaders);
          CBCASE(SIEVE2_MESSAGE_GETSUBADDRESS, getsubaddress);
          CBCASE(SIEVE2_MESSAGE_GETENVELOPE,   getenvelope);
          CBCASE(SIEVE2_MESSAGE_GETSIZE,       getsize);
          CBCASE(SIEVE2_MESSAGE_GETBODY,       getbody);
	  default:
              // FIXME: Also put useful error text into the context.
              return SIEVE2_ERROR_UNSUPPORTED;
	  }
      }

    static_check_support(c);

    return SIEVE2_OK;
}

int sieve2_validate(sieve2_context_t *context, void *user_data)
{
    struct sieve2_context *c = context;

    if (context == NULL)
        return SIEVE2_ERROR_BADARGS;

    c->user_data = user_data;

    c->script.error_count = 0;         /* Reset error count */
    c->script.error_lineno = 1;        /* Reset line number */

    /* First callback already! Get the script! */
    if (libsieve_do_getscript(c, "", "", &c->script.script) != SIEVE2_OK)
        return SIEVE2_ERROR_GETSCRIPT;

    try {
        c->script.cmds = libsieve_sieve_parse_buffer(c);
        libsieve_free_tree(c->script.cmds);
        c->script.cmds = NULL;
    } catch(SIEVE2_ERROR_INTERNAL) {
        return SIEVE2_ERROR_INTERNAL;
    } endtry;

    if (c->script.error_count > 0) {
        return SIEVE2_ERROR_PARSE;
    }

    return SIEVE2_OK;
}

/* This is where we really do it:
 * run a script over a message to produce an action list
 *
 * Error codes:
 * SIEVE2_ERROR_BADARGS if any of the arguments are NULL
 * SIEVE2_ERROR_PARSE for script parse errors
 * SIEVE2_ERROR_EXEC for script evaluation errors
 */
int sieve2_execute(sieve2_context_t *context, void *user_data)
{
    struct sieve2_context *c = context;
    const char *errmsg = NULL;

    if (context == NULL)
        return SIEVE2_ERROR_BADARGS;

    c->user_data = user_data;

    c->script.error_count = 0;         /* Reset error count */
    c->script.error_lineno = 1;        /* Reset line number */

    /* First callback already! Get the script! */
    if (libsieve_do_getscript(c, "", "", &c->script.script) != SIEVE2_OK)
        return SIEVE2_ERROR_GETSCRIPT;

    try {

        /* If the client app doesn't have its own header parser,
         * we will use an internal one. */
        if (!c->callbacks.getheader) {
            if (!c->callbacks.getallheaders) {
                /* Incomplete function registration.
                 * FIXME: Would be nice to give more details. */
                return SIEVE2_ERROR_NOT_FINALIZED;
            } else {
            /* Get the header! FIXME: should have different error codes... */
            if (libsieve_do_getallheaders(c, &(c->message->header)) != SIEVE2_OK)
                return SIEVE2_ERROR_HEADER;
            /* Our "internal callback" instead of the user's getheader. */
            c->callbacks.getheader = libsieve_message2_getheader;
            if (libsieve_message2_parseheader(c->message) != SIEVE2_OK)
                return SIEVE2_ERROR_HEADER;
            }
        }
 
        c->script.cmds = libsieve_sieve_parse_buffer(c);
        if (c->script.error_count > 0) {
            if (c->script.cmds) {
                libsieve_free_tree(c->script.cmds);
            }
            c->script.cmds = NULL;
            return SIEVE2_ERROR_PARSE;
        }

        if (libsieve_eval(c, c->script.cmds, &errmsg) < 0)
            return SIEVE2_ERROR_EXEC;

    } catch(SIEVE2_ERROR_INTERNAL) {
        return SIEVE2_ERROR_INTERNAL;
    } endtry;

    /* If no action was taken, libsieve_eval will have
     * returned > 0. But we're going to hide that and
     * just return SIEVE2_OK. It is up to the client app
     * to notice that no callbacks occurred and therefore
     * a keep MUST be performed.
     * */
    return SIEVE2_OK;
}

char * sieve2_listextensions(sieve2_context_t *sieve2_context)
{
    char *ext;
    struct sieve2_context *c = sieve2_context;

    ext = libsieve_strconcat(     "regex ",
                                  "imap4flags ",
        ( c->support.subaddress ? "subaddress "  : "" ),
        ( c->support.fileinto   ? "fileinto "  : "" ),
        ( c->support.reject     ? "reject "    : "" ),
        ( c->support.envelope   ? "envelope "  : "" ),
        ( c->support.vacation   ? "vacation "  : "" ),
        ( c->support.notify     ? "notify "    : "" ),
	NULL );

    return libsieve_strbuf(c->strbuf, ext, strlen(ext), FREEME);
}

#if (MSDOS || WIN32)
#  define NL "\r\n"
#else
#  define NL "\n"
#endif

char * sieve2_credits(void)
{
    return "libSieve is written and maintained by Aaron Stone"
        " with many thanks to those who have helped to debug"
        " and to secure this fine piece of software."
     NL " " NL
        " Special thanks to:"
        " Timo Sirainen,"
        " Oliver Tappe,"
        " Brandon Knitter."
     NL " " NL
        " Portions of libSieve are based on the Sieve support"
        " of the Cyrus Email Server by Carnegie Mellon University."
        ;
}

char * sieve2_license(void)
{
    return "libSieve is Copyright 2002, 2003, 2005 by Aaron Stone"
        " and is licensed under the GNU Lesser General Public License,"
        " version 2.1 and (at the author's option, not yours)"
        " any later version. A copy of the license should have"
        " been distributed with libSieve, and if not, may be"
        " obtained by writing to the Free Software Foundation:"
     NL "     Free Software Foundation, Inc.    " NL
        "     59 Temple Place, Suite 330        " NL
        "     Boston, MA  02111-1307  USA       " NL
     NL " " NL
        " Portions of libSieve are based on the Sieve support of the"
        " Cyrus Email Server by Carnegie Mellon University and are "
        " Copyright 1994, 1995, 1996, 1999 by Carnegie Mellon University."
     NL " " NL
        " While CMU's license is not the (L)GPL, it does not preclude such"
        " combination in a larger work, such as libSieve, in a manner"
        " which places the work as a whole under the GNU (L)GPL. You may"
        " take CMU-only portions of libSieve and use them without regard"
        " to the GNU (L)GPL, but you may not do so to (L)GPL portions"
        " nor to the work as a whole or in any part in combination with"
        " code that has been licensed under the GNU (L)GPL."
     NL " " NL
        " The GNU LGPL can be briefly summarized as follows: you may use"
        " this software together free software, and you may use this"
        " software together with proprietary software; in both cases"
        " this software must be distributed with full rights to its"
        " source code and redistribution in both source and binary form."
     NL " " NL
        " This program is distributed in the hope that it will be useful,"
        " but WITHOUT ANY WARRANTY; without even the implied warranty of"
        " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
        " GNU Lesser General Public License for more details."
        ;
}

// vim: filetype=c:expandtab:shiftwidth=4:tabstop=4:softtabstop=4:textwidth=99 :
