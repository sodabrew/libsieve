/* util.h -- utility routines for useful things
 * $Id$
 */

/***********************************************************
 * Copyright 2003 libSieve Development Team by Aaron Stone
 *
 * Licensed under LPGL and CMU's "MIT style" license.
 *
 * This is an original work modelled after CMU concepts.
 * It does not contain code written by or derived from CMU.
 ***********************************************************/

#ifndef INCLUDED_UTIL_H
#define INCLUDED_UTIL_H

/* These are the memory oriented functions */

void libsieve_free(void *ptr);
void *libsieve_malloc(size_t size);
void *libsieve_realloc(void *ptr, size_t size);
void *libsieve_memset(void *ptr, int c, size_t len);

/* These are the string oriented functions */

char *libsieve_strtolower(char *str, size_t len);
char *libsieve_strtoupper(char *str, size_t len);

char *libsieve_strdup(const char *str, size_t len);
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
void libsieve_strbufalloc(struct mlbuf **ml);

#endif /* INCLUDED_UTIL_H */
