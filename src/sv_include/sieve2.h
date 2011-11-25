
/* * * *
 * Copyright 2003, 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifndef SIEVE2_H
#define SIEVE2_H

#include "sieve2_error.h"

typedef struct sieve2_context sieve2_context_t;

/* At a minimum, you must register redirect, keep,
 * getsize and either getheader or getallheaders.
 * If not, you will receive SIEVE2_ERROR_NOT_FINALIZED.
 * */

typedef enum {
	SIEVE2_VALUE_FIRST,

	SIEVE2_ACTION_REDIRECT,
	SIEVE2_ACTION_REJECT,
	SIEVE2_ACTION_DISCARD,
	SIEVE2_ACTION_FILEINTO,
	SIEVE2_ACTION_KEEP,
	SIEVE2_ACTION_NOTIFY,
	SIEVE2_ACTION_DENOTIFY,       // DEPRECATED since 2.1.11
	SIEVE2_ACTION_VACATION,
	SIEVE2_ACTION_SETFLAG,        // DEPRECATED since 2.1.11
	SIEVE2_ACTION_ADDFLAG,        // DEPRECATED since 2.1.11
	SIEVE2_ACTION_REMOVEFLAG,     // DEPRECATED since 2.1.11
	SIEVE2_ACTION_MARK,           // DEPRECATED since 2.1.11
	SIEVE2_ACTION_UNMARK,         // DEPRECATED since 2.1.11

	SIEVE2_ERRCALL_RUNTIME,
	SIEVE2_ERRCALL_PARSE,
	SIEVE2_DEBUG_TRACE,           // NEW in 2.1.11

	SIEVE2_SCRIPT_GETSCRIPT,
	SIEVE2_SCRIPT_GETSIZE,        // DEPRECATED since 2.2.6 (was never implemented!)

	SIEVE2_MESSAGE_GETHEADER,
	SIEVE2_MESSAGE_GETALLHEADERS,
	SIEVE2_MESSAGE_GETENVELOPE,
	SIEVE2_MESSAGE_GETSIZE,
	SIEVE2_MESSAGE_GETBODY,
	SIEVE2_MESSAGE_GETSUBADDRESS, // NEW in 2.1.11

	SIEVE2_ERRCALL_HEADER,        // NEW in 2.2.6
	SIEVE2_ERRCALL_ADDRESS,       // NEW in 2.2.6

	SIEVE2_VALUE_LAST             // Use this as an API version check
} sieve2_values_t;

typedef int (*sieve2_callback_func) (
	sieve2_context_t * sieve2_context,
	void * user_data
);

typedef struct {
	sieve2_values_t value;
	sieve2_callback_func func;
} sieve2_callback_t;


/* From here below only functions thar be! */
#if defined(c_plusplus) || defined(__cplusplus)
 extern "C" {
#endif

/* Allocate and free your libSieve context. Any memory that
 * libSieve allocated along the way will be freed here. */
/* Pass the pointer by reference for both of these;
 * it will be set to NULL when it's freed. */
extern int sieve2_alloc(sieve2_context_t **sieve2_context);
extern int sieve2_free(sieve2_context_t **sieve2_context);

/* Attach the callbacks array to the libSieve context. */
extern int sieve2_callbacks(sieve2_context_t *sieve2_context,
                            sieve2_callback_t *callbacks);

/* Get a space separated list of extensions that libSieve
 * supports and for which you have registered a callback. */
/* libSieve will free this memory for you, don't worry about it. */
extern char * sieve2_listextensions(sieve2_context_t *sieve2_context);

/* Validate a script for syntax and feature support */
extern int sieve2_validate(sieve2_context_t *sieve2_context,
                           void *user_data);

/* Execute a script on a message, producing an action list */
extern int sieve2_execute(sieve2_context_t *sieve2_context,
                          void *user_data);

/* libSieve will free this memory for you, don't worry about it. */
extern const char * 
sieve2_getvalue_string(
	sieve2_context_t *sieve2_context,
	char const * const value);

/* libSieve will free this memory for you, don't worry about it. */
extern char * * 
sieve2_getvalue_stringlist(
	sieve2_context_t *sieve2_context,
	char const * const name);

extern int sieve2_getvalue_int(
	sieve2_context_t *sieve2_context,
	char *name);

/* If you allocated the memory, you have to free it. */
extern int sieve2_setvalue_string(
	sieve2_context_t *sieve2_context,
	char const * const name, char* const value);

/* If you allocated the memory, you have to free it. */
extern int sieve2_setvalue_stringlist(
	sieve2_context_t *sieve2_context,
	char const * const name, char **value);

extern int sieve2_setvalue_int(
	sieve2_context_t *sieve2_context,
	char *name, int value);

/* This translates the error numbers into static strings.
 * For fancier errors, callbacks from the context are used,
 * and that allows the context to manage the memory. */
extern char * sieve2_errstr(int errval);

/* Get a list of Credits about who writes libSieve. */
/* Does not allocate memory; points to static strings. */
extern char * sieve2_credits(void);

/* Get the License under which libSieve is distributed. */
/* Does not allocate memory; points to static strings. */
extern char * sieve2_license(void);

#if defined(c_plusplus) || defined(__cplusplus)
 } /* extern "C" */
#endif

#endif /* SIEVE2_H */
