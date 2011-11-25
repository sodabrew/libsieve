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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* sv_include */
#include "sieve2.h"
#include "sieve2_error.h"

/* sv_interface */
#include "sieve2.h"
#include "context2.h"
#include "callbacks2.h"

/* sv_util */
#include "src/sv_util/util.h"

/* Reject is incompatible with:
 * fileinto, redirect, keep, reject, vacation,
 * setflag, addflag, removeflag
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
int libsieve_do_fileinto(struct sieve2_context *c, char *mbox, stringlist_t *slflags)
{
    char **flags;

    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.fileinto = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_FILEINTO);

    libsieve_setvalue_string(c, "mailbox", mbox);

    if (slflags) {
	flags = libsieve_stringlist_to_chararray(slflags);
    } else {
	flags = libsieve_stringlist_to_chararray(c->slflags);
    }
    libsieve_setvalue_stringlist(c, "flags", flags);

    libsieve_callback_do(c, SIEVE2_ACTION_FILEINTO);
    libsieve_callback_end(c, SIEVE2_ACTION_FILEINTO);

    // FIXME: Add flags, but not its contents, to the context freelist.
    libsieve_free(flags);

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
int libsieve_do_keep(struct sieve2_context *c, stringlist_t *slflags)
{
    char **flags;

    if (c->actions.reject)
        return SIEVE2_ERROR_EXEC;

    c->actions.keep = TRUE;

    libsieve_callback_begin(c, SIEVE2_ACTION_KEEP);

    if (slflags) {
	flags = libsieve_stringlist_to_chararray(slflags);
    } else {
	flags = libsieve_stringlist_to_chararray(c->slflags);
    }
    libsieve_setvalue_stringlist(c, "flags", flags);

    libsieve_callback_do(c, SIEVE2_ACTION_KEEP);
    libsieve_callback_end(c, SIEVE2_ACTION_KEEP);

    // FIXME: Add flags, but not its contents, to the context freelist.
    libsieve_free(flags);

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

    // FIXME: add optionstring, but not its contents, to a freelist.
    libsieve_free(optionstring);

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

int libsieve_do_error_parse(struct sieve2_context *c, int lineno, const char *msg)
{
    libsieve_callback_begin(c, SIEVE2_ERRCALL_PARSE);

    libsieve_setvalue_int(c, "lineno", lineno);
    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ERRCALL_PARSE);
    libsieve_callback_end(c, SIEVE2_ERRCALL_PARSE);

    return SIEVE2_OK;
}

int libsieve_do_error_address(struct sieve2_context *c, const char *msg)
{
    libsieve_callback_begin(c, SIEVE2_ERRCALL_ADDRESS);

    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ERRCALL_ADDRESS);
    libsieve_callback_end(c, SIEVE2_ERRCALL_ADDRESS);

    return SIEVE2_OK;
}

int libsieve_do_error_header(struct sieve2_context *c, int lineno, const char *msg)
{
    libsieve_callback_begin(c, SIEVE2_ERRCALL_HEADER);

    libsieve_setvalue_int(c, "lineno", lineno);
    libsieve_setvalue_string(c, "message", msg);

    libsieve_callback_do(c, SIEVE2_ERRCALL_HEADER);
    libsieve_callback_end(c, SIEVE2_ERRCALL_HEADER);

    return SIEVE2_OK;
}

int libsieve_do_debug_trace(struct sieve2_context *c, int level,
		const char *module, const char *file, const char *function,
		const char *formatstring, ...)
{
    char message[1024];
    va_list argp;
    int len;

    // Check if tracing has been registered
    // because vsprintf is relatively expensive.
    // NOTE: Remind implementations that they should
    // only register a trace function if it is needed.

    // Petri Lane says that sometimes c comes in as NULL.
    if (c && c->callbacks.debug_trace) {
        libsieve_callback_begin(c, SIEVE2_DEBUG_TRACE);

        libsieve_setvalue_int(c, "level", level);

        libsieve_setvalue_string(c, "module", (char *)module);
        libsieve_setvalue_string(c, "file", (char *)file);
        libsieve_setvalue_string(c, "function", (char *)function);

	va_start(argp, formatstring);
	// This used to be vasnprintf, but it's not availabe in Solaris < 10
	// or any other commercial Unices, and including equiv. code from
	// gnulib was an absurd amount of overhead for a little library.
	memset(message, 0, 1024);
        len = vsnprintf(message, 1023, formatstring, argp);
	if (len < 0 || len > 1023) {
		snprintf(message, 1023, "A Sieve error occurred, but the error message is not available.");
	}
        libsieve_setvalue_string(c, "message", message);
	va_end(argp);

        libsieve_callback_do(c, SIEVE2_DEBUG_TRACE);
        libsieve_callback_end(c, SIEVE2_DEBUG_TRACE);
    }

    return SIEVE2_OK;
}

int libsieve_do_getscript(struct sieve2_context *c,
		const char * const path, const char * const name,
		const char ** script, int * scriptlen)
{
    libsieve_callback_begin(c, SIEVE2_SCRIPT_GETSCRIPT);

    libsieve_setvalue_string(c, "path", (char *)path);
    libsieve_setvalue_string(c, "name", (char *)name);

    libsieve_callback_do(c, SIEVE2_SCRIPT_GETSCRIPT);

    *script = libsieve_getvalue_string(c, "script");

    if (*script)
        *scriptlen = strlen(*script);
    else
        *scriptlen = 0;

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

    *header = (char *)libsieve_getvalue_string(c, "allheaders");

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETALLHEADERS);

    return SIEVE2_OK;
}

static char * notfound[] = { "", NULL };

int libsieve_do_getheader(struct sieve2_context *c,
		const char * const header, char ***body)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETHEADER);

    libsieve_setvalue_string(c, "header", (char *)header);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETHEADER);

    *body = (char **)libsieve_getvalue_stringlist(c, "body");

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

int libsieve_do_getenvelope(struct sieve2_context *c, const char * const f, char **e)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETENVELOPE);

    libsieve_setvalue_string(c, "env", (char *)f);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETENVELOPE);

    switch (*f) {
    case 'f':
    case 'F':
        *e = (char *)libsieve_getvalue_string(c, "from");
        break;
    case 't':
    case 'T':
        *e = (char *)libsieve_getvalue_string(c, "to");
        break;
    }

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETENVELOPE);

    return SIEVE2_OK;
}

int libsieve_do_getsubaddress(struct sieve2_context *c, char *address,
		char **user, char **detail, char **localpart, char **domain)
{
    libsieve_callback_begin(c, SIEVE2_MESSAGE_GETSUBADDRESS);

    libsieve_setvalue_string(c, "address", address);

    libsieve_callback_do(c, SIEVE2_MESSAGE_GETSUBADDRESS);

    *user = (char *)libsieve_getvalue_string(c, "user");
    *detail = (char *)libsieve_getvalue_string(c, "detail");
    *localpart = (char *)libsieve_getvalue_string(c, "localpart");
    *domain = (char *)libsieve_getvalue_string(c, "domain");

    libsieve_callback_end(c, SIEVE2_MESSAGE_GETSUBADDRESS);

    return SIEVE2_OK;
}

