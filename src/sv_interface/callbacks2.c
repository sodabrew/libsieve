/* callbacks.c -- do the callbacks to the client application.
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

/* sv_include */
#include "sieve2.h"
#include "sieve2_error.h"

/* sv_interface */
#include "sieve2.h"
#include "context2.h"
#include "callbacks2.h"

/* sv_util */
#include "util.h"

/* Reject is incompatible with:
 * fileinto, redirect, keep, reject, vacation,
 * setflag, addflag, removeflag, mark, unmark
 */
int libsieve_do_reject(struct sieve2_context *c, char *msg)
{
    if (c->actions.fileinto
     || c->actions.redirect
     || c->actions.keep
     || c->actions.reject
     || c->actions.vacation
     || c->actions.setflag
     || c->actions.addflag
     || c->actions.removeflag
     || c->actions.mark
     || c->actions.unmark
     )
        return SIEVE2_ERROR_EXEC;

    c->actions.reject = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_REJECT);

    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ACTION_REJECT);
    libsieve_callback_end(c, SIEVE2_ACTION_REJECT);

    return SIEVE2_OK;
}

/* Fileinto is incompatible with: 
 * reject
 */
int libsieve_do_fileinto(struct sieve2_context *c, char *mbox, struct imapflags2 *imapflags)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.fileinto = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_FILEINTO);

    libsieve_setvalue_string(c, "mailbox", mbox);
    libsieve_setvalue_stringlist(c, "imapflags", imapflags->flags);

    libsieve_callback_do(c, SIEVE2_ACTION_FILEINTO);
    libsieve_callback_end(c, SIEVE2_ACTION_FILEINTO);

    return SIEVE2_OK;
}

/* Redirect is incompatible with:
 * reject
 */
int libsieve_do_redirect(struct sieve2_context *c, char *addr)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.redirect = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_REDIRECT);

    libsieve_setvalue_string(c, "address", addr);

    libsieve_callback_do(c, SIEVE2_ACTION_REDIRECT);
    libsieve_callback_end(c, SIEVE2_ACTION_REDIRECT);

    return SIEVE2_OK;
}

/* Keep is incompatible with:
 * reject
 */
int libsieve_do_keep(struct sieve2_context *c, struct imapflags2 *imapflags)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.keep = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_KEEP);

    libsieve_setvalue_stringlist(c, "imapflags", imapflags->flags);

    libsieve_callback_do(c, SIEVE2_ACTION_KEEP);
    libsieve_callback_end(c, SIEVE2_ACTION_KEEP);

    return SIEVE2_OK;
}

/* Discard is incompatible with:
 * nothing
 */
int libsieve_do_discard(struct sieve2_context *c)
{
    c->actions.discard = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_DISCARD);

    libsieve_callback_do(c, SIEVE2_ACTION_DISCARD);
    libsieve_callback_end(c, SIEVE2_ACTION_DISCARD);

    return SIEVE2_OK;
}

/* Vacation is incompatible with:
 * reject
 */
int libsieve_do_vacation(struct sieve2_context *c,
		char *addr, char *fromaddr,
		char *subj, char *msg,
		char *handle,
		int days, int mime)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.vacation = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_VACATION);

    libsieve_setvalue_string(c, "address", addr);
    libsieve_setvalue_string(c, "fromaddr", fromaddr);
    libsieve_setvalue_string(c, "subject", subj);
    libsieve_setvalue_string(c, "message", msg);
    libsieve_setvalue_string(c, "hash", handle);
    libsieve_setvalue_int(c, "days", days);
    libsieve_setvalue_int(c, "mime", mime);

    libsieve_callback_do(c, SIEVE2_ACTION_VACATION);
    libsieve_callback_end(c, SIEVE2_ACTION_VACATION);

    return SIEVE2_OK;
}

/* Setflag is incompatible with:
 * reject
 */
int libsieve_do_setflag(struct sieve2_context *c, char *flag)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.setflag = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_SETFLAG);

    libsieve_setvalue_string(c, "flag", flag);

    libsieve_callback_do(c, SIEVE2_ACTION_SETFLAG);
    libsieve_callback_end(c, SIEVE2_ACTION_SETFLAG);

    return SIEVE2_OK;
}

/* Addflag is incompatible with:
 * reject
 */
int libsieve_do_addflag(struct sieve2_context *c, char *flag)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.addflag = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_ADDFLAG);

    libsieve_setvalue_string(c, "flag", flag);

    libsieve_callback_do(c, SIEVE2_ACTION_ADDFLAG);
    libsieve_callback_end(c, SIEVE2_ACTION_ADDFLAG);

    return SIEVE2_OK;
}

/* Removeflag is incompatible with:
 * reject
 */
int libsieve_do_removeflag(struct sieve2_context *c, char *flag)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.removeflag = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_REMOVEFLAG);

    libsieve_setvalue_string(c, "flag", flag);

    libsieve_callback_do(c, SIEVE2_ACTION_REMOVEFLAG);
    libsieve_callback_end(c, SIEVE2_ACTION_REMOVEFLAG);

    return SIEVE2_OK;
}


/* Mark is incompatible with:
 * reject
 */
int libsieve_do_mark(struct sieve2_context *c)
{
    char *markflags[] = { "\\Flagged", NULL };

    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.mark = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_MARK);

    // FIXME: We're just hardcoding the most common deal;
    // this is only for imapflags, not imap4flags anyways.
    libsieve_setvalue_stringlist(c, "imapflags", markflags);

    libsieve_callback_do(c, SIEVE2_ACTION_MARK);
    libsieve_callback_end(c, SIEVE2_ACTION_MARK);

    return SIEVE2_OK;
}


/* Unmark is incompatible with:
 * reject
 */
int libsieve_do_unmark(struct sieve2_context *c)
{
    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.unmark = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_UNMARK);
    libsieve_callback_do(c, SIEVE2_ACTION_UNMARK);
    libsieve_callback_end(c, SIEVE2_ACTION_UNMARK);

    return SIEVE2_OK;
}

/* Notify is incompatible with:
 * nothing
 */
int libsieve_do_notify(struct sieve2_context *c, char *id,
	      char *method, stringlist_t *options,
	      char *priority, char *message)
{
    char **optionstring;

    c->actions.notify = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_NOTIFY);

    optionstring = libsieve_stringlist_to_chararray(options);
    libsieve_setvalue_stringlist(c, "options", optionstring);
    libsieve_setvalue_string(c, "id", id);
    libsieve_setvalue_string(c, "method", method);
    libsieve_setvalue_string(c, "priority", priority);
    libsieve_setvalue_string(c, "message", message);

    libsieve_callback_do(c, SIEVE2_ACTION_NOTIFY);
    libsieve_callback_end(c, SIEVE2_ACTION_NOTIFY);

    libsieve_free(optionstring);

    return SIEVE2_OK;
}

/* Denotify is incompatible with:
 * nothing
 */
int libsieve_do_denotify(struct sieve2_context *c,
		comparator_t *comp, void *pat, char *priority)
{
    c->actions.denotify = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_DENOTIFY);

    // FIXME: I have no clue what to do here.
//     libsieve_setvalue_string(c, "options", optionstring);

    libsieve_callback_do(c, SIEVE2_ACTION_DENOTIFY);
    libsieve_callback_end(c, SIEVE2_ACTION_DENOTIFY);

    return SIEVE2_OK;
}


/* This isn't really an action; the errors are callbacks, too. */
int libsieve_do_error_exec(struct sieve2_context *c, char *msg)
{
    libsieve_callback_begin(c, SIEVE2_ERRCALL_RUNTIME);

    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ERRCALL_RUNTIME);
    libsieve_callback_end(c, SIEVE2_ERRCALL_RUNTIME);

    return SIEVE2_OK;
}

int libsieve_do_error_parse(struct sieve2_context *c, int lineno, char *msg)
{
    libsieve_callback_begin(c, SIEVE2_ERRCALL_PARSE);

    libsieve_setvalue_int(c, "lineno", lineno);
    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ERRCALL_PARSE);
    libsieve_callback_end(c, SIEVE2_ERRCALL_PARSE);

    return SIEVE2_OK;
}

int libsieve_do_getscript(struct sieve2_context *c,
		const char * const path, const char * const name,
		const char ** script)
{
    libsieve_callback_begin(c, SIEVE2_SCRIPT_GETSCRIPT);

    libsieve_setvalue_string(c, "path", path);
    libsieve_setvalue_string(c, "name", name);

    libsieve_callback_do(c, SIEVE2_SCRIPT_GETSCRIPT);

    *script = libsieve_getvalue_string(c, "script");

    libsieve_callback_end(c, SIEVE2_SCRIPT_GETSCRIPT);

    if (*script)
        return SIEVE2_OK;
    else
        return SIEVE2_ERROR_EXEC;
}

int libsieve_do_getallheaders(struct sieve2_context *c,
		char ** header)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETALLHEADERS);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETALLHEADERS);

    *header = libsieve_getvalue_string(c, "allheaders");

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETALLHEADERS);

    return SIEVE2_OK;
}

static char * notfound[] = { "", NULL };

int libsieve_do_getheader(struct sieve2_context *c,
		const char * const header, char ***body)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETHEADER);

    libsieve_setvalue_string(c, "header", header);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETHEADER);

    *body = libsieve_getvalue_stringlist(c, "body");

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETHEADER);

    if (!*body || !**body) {
        *body = notfound;
        return SIEVE2_DONE;
    }

    return SIEVE2_OK;
}

int libsieve_do_getsize(struct sieve2_context *c, int *sz)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETSIZE);
    libsieve_callback_do(c, SIEVE2_MESSAGE_GETSIZE);

    *sz = libsieve_getvalue_int(c, "size");
    libsieve_callback_end(c, SIEVE2_MESSAGE_GETSIZE);

    return SIEVE2_OK;
}

static const char * toenclosure[] = { "", NULL };
static const char * fromenclosure[] = { "", NULL };

int libsieve_do_getenvelope(struct sieve2_context *c, const char * const f, char **e)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETENVELOPE);

    libsieve_setvalue_string(c, "env", f);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETENVELOPE);

    switch (*f) {
    case 'f':
    case 'F':
        fromenclosure[0] = libsieve_getvalue_string(c, "from");
        *e = fromenclosure;
        break;
    case 't':
    case 'T':
	toenclosure[0] = libsieve_getvalue_string(c, "to");
        *e = toenclosure;
        break;
    }

    if (!*e) *e = notfound;

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETENVELOPE);

    return SIEVE2_OK;
}

