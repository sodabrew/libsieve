/* util.h -- utility routines for useful things
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifndef INCLUDED_UTIL_H
#define INCLUDED_UTIL_H

#include "exception.h"

/* Define several macros for GCC specific attributes.
 * Although the __attribute__ macro can be easily defined
 * to nothing, these macros make them a little prettier.
 * */
#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#define PRINTF_ARGS(X, Y) __attribute__((format(printf, X, Y)))
#else
#define UNUSED
#define PRINTF_ARGS(X, Y)
#endif

/* Things that are happening normally. */
#define TRACE_DEBUG(fmt...) libsieve_do_debug_trace(THIS_CONTEXT, 4, THIS_MODULE, __FILE__, __func__, fmt)
/* Bad things that will result in a failure code. */
#define TRACE_ERROR(fmt...) libsieve_do_debug_trace(THIS_CONTEXT, 2, THIS_MODULE, __FILE__, __func__, fmt)
/* All assertions are always tested, and errors thrown upwards. */
#define libsieve_assert(cond) ( (cond) ? 0 : ( TRACE_ERROR("Assertion failed: [%s]", #cond), throw(SIEVE2_ERROR_INTERNAL) ) )

/* These are the memory oriented functions */

void libsieve_free(void *ptr);
void libsieve_freev(void **ptr);
void *libsieve_malloc(size_t size);
void *libsieve_realloc(void *ptr, size_t size);
void *libsieve_memset(void *ptr, int c, size_t len);

/* These are the string oriented functions */

char *libsieve_strtolower(char *str, size_t len);
char *libsieve_strtoupper(char *str, size_t len);

char *libsieve_strdup(const char *str);
char *libsieve_strndup(const char *str, size_t len);
char *libsieve_strconcat(const char *str, ...);

int libsieve_strisatom(const char *str, size_t len);
int libsieve_strtonum(const char *str);

/* These functions hold onto many strings at once */

struct mlbuf {
    char **buf; /* The buffer! */
    size_t siz; /* Total size */
    size_t pos; /* Current position */
};

#define FREEME 1
#define NOFREE 0

char *libsieve_strbuf(struct mlbuf *ml, char *str, size_t len, int freeme);
void libsieve_strbuffree(struct mlbuf **ml, int freeall);
int libsieve_strbufalloc(struct mlbuf **ml);

/* This function holds one string built from many calls. */

struct catbuf {
    char *str;
    size_t pos;
    size_t len;
};

char *libsieve_catbuf_simple(struct catbuf *s, char *str);
char *libsieve_catbuf(struct catbuf *s, char *str, size_t len);
struct catbuf *libsieve_catbuf_alloc(void);
char *libsieve_catbuf_free(struct catbuf *s);

/* The MD5 implementation is in md5.c */
char *libsieve_makehash(char *s1, char *s2);


#endif /* INCLUDED_UTIL_H */
