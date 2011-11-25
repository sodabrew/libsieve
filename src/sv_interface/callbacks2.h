/* callbacks2.h -- manages the libSieve opaque context and callbacks.
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifndef CALLBACKS2_H
#define CALLBACKS2_H

#include "src/sv_util/util.h"
#include "context2.h"

int libsieve_callback_begin(
    struct sieve2_context *context,
    sieve2_values_t callback);

int libsieve_callback_do(
    struct sieve2_context *context,
    sieve2_values_t callback);

int libsieve_callback_end(
    struct sieve2_context *context,
    sieve2_values_t callback);

#define libsieve_setvalue_int sieve2_setvalue_int
#define libsieve_setvalue_string sieve2_setvalue_string
#define libsieve_setvalue_stringlist sieve2_setvalue_stringlist
#define libsieve_getvalue_int sieve2_getvalue_int
#define libsieve_getvalue_string sieve2_getvalue_string
#define libsieve_getvalue_stringlist sieve2_getvalue_stringlist

/* Callback actions; return negative on failure. */
/* These have been rewritten and moved into callbacks2.c... */
int libsieve_do_reject(struct sieve2_context *c, char *msg);
int libsieve_do_fileinto(struct sieve2_context *c, char *mbox, stringlist_t *slflags);
int libsieve_do_redirect(struct sieve2_context *c, char *addr);
int libsieve_do_keep(struct sieve2_context *c, stringlist_t *slflags);
int libsieve_do_discard(struct sieve2_context *c);
int libsieve_do_vacation(struct sieve2_context *c, char *addr, char *fromaddr,
		char *subj, char *msg, char *handle,
		int days, int mime);
int libsieve_do_notify(struct sieve2_context *c, char *id,
		char *method, stringlist_t *options,
		char *priority, char *message);

/* Reporting parse and runtime errors. */
int libsieve_do_error_parse(struct sieve2_context *c, int lineno, const char *msg);
int libsieve_do_error_exec(struct sieve2_context *c, char *msg);
int libsieve_do_error_header(struct sieve2_context *c, int lineno, const char *msg);
int libsieve_do_error_address(struct sieve2_context *c, const char *msg);

/* The TRACE macros are defined in util.h, which is universally included. */
int libsieve_do_debug_trace(struct sieve2_context *c, int level,
		const char *module, const char *file, const char *function,
		const char *formatstring, ...) PRINTF_ARGS(6, 7);

/* Ask the user app for information about the script & message. */
int libsieve_do_getscript(struct sieve2_context *context,
		const char * const path, const char * const name,
		const char ** script, int * scriptlen);
int libsieve_do_getallheaders(struct sieve2_context *context,
		char ** header);
int libsieve_do_getheader(struct sieve2_context *context,
		const char * const s, char *** val);
int libsieve_do_getenvelope(struct sieve2_context * context,
		const char * const f, char ** c);
int libsieve_do_getsize(struct sieve2_context *context,
		int *sz);
int libsieve_do_getsubaddress(struct sieve2_context *context, char *address,
		char **user, char **detail, char **localpart, char **domain);

/* Emulate the user callback; function located in message2.h */
int libsieve_message2_getheader(struct sieve2_context *c, void *user_data);

#endif
