/* util.c -- utility routines for useful things
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

#include <config.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"

/* Wrapper around memset() */
void *sv_memset(void *ptr, int c, size_t len)
{
    if(ptr != NULL && c >= 0 && c < 254 && len > 0)
        return memset(ptr, c, len);
    return NULL;
}

/* Wrapper around free() */
void sv_free(void *ptr)
{
    if(ptr)
        free(ptr);
    ptr = NULL;
}

/* Wrapper around malloc() */
void *sv_malloc (size_t size)
{
    void *ret;

    ret = (void *)malloc(size);
    if (ret != NULL)
        return ret;

    return 0;
}

/* Wrapper around realloc() */
void *sv_realloc (void *ptr, size_t size)
{
    void *ret;

    ret = (!ptr ? (void *)malloc(size) : (void *)realloc(ptr, size));
    if (ret != NULL)
        return ret;

    return 0;
}

/* Convert a string to lower case
 * (translate from 65-90 to 97-122)
 */
char *sv_strtolower (char *str, size_t len)
  {
    size_t i;

    for (i=0; i<len; i++ ) {
        str[i] = tolower(str[i]);
    }

    return str;
  }

/* Convert a string to upper case
 * (translate from 97-122 to 65-90)
 */
char *sv_strtoupper (char *str, size_t len)
  {
    size_t i;

    for (i=0; i<len; i++ ) {
        str[i] = toupper(str[i]);
    }

    return str;
  }

int sv_strisatom (const char *str, size_t len)
  {
    size_t i;

    /* The spec for this function says that
     * something this long is good enough
     */
    if (len > 1023 )
        return 0;

    for (i=0; i<len; i++, str++ )
      {
        if (*str < 31
         || *str >= 127
         || *str == ' '
         || *str == '{'
         || *str == '('
         || *str == ')'
         || *str == '%'
         || *str == '*'
         || *str == '\\'
         || *str == '\"')
            return 0;
      }

    return 1;
  }

/* Convert a common human format to actual byte count */
int sv_strtonum(const char *str)
  {
    int val = 0;
    char *tail = NULL;

    /* Explicit cast to maintain sanity */
    val = (int)strtol(str, &tail, 10);
    /* See if we got something that's NaN */
    if(tail != NULL) {
        switch (tail[0]) {
            case 'K': val *= (1 << 10); break;
            case 'M': val *= (1 << 20); break;
            case 'G': val *= (1 << 30); break;
            default: break;
        }
    }

    /* Sieve has no need for negative numbers! */
    if(val < 0) return 0;
    else return val;
  }

char *sv_strdup(const char *str, size_t len)
  {
    char *p = NULL;
    
    if ((p = sv_memset((char *)sv_malloc(len+1), 0, len+1)) != NULL) {
        /* The NULL is not be copied */
        strncpy(p, str, len);
        /* A new NULL is thus added */
        // *(p+len+1) = '\0';
	// Because of the memset,
	// we don't need this NULL
    }

    return p;
  }

/* Contributed by Timo Sirainen, December 2002 */
char *sv_strconcat (const char *str, ...)
  {
    va_list va;
    char *buf;
    size_t len, pos, size;

    if (str == NULL)
	return NULL;

    va_start(va, str);

    buf = NULL; pos = size = 0;
    do {
	len = strlen(str);
	if (size-pos < len) {
	    size += len + 256;
	    buf = sv_realloc(buf, size);
	}
	memcpy(buf+pos, str, len);
        pos += len;
	str = va_arg(va, const char *);
    } while (str != NULL);
    buf[pos] = '\0';

    va_end(va);
    return buf;
  }

/* This is a spiffy function that helps to maintain
 * a single buffer holding multiple separate strings.
 *
 * The caller must have the ml... variables declared
 * and in scope and is responsible for freeing mlbuf. */
char *sv_strbuf(struct mlbuf *ml, char *str, size_t len, int freeme)
{
    char *stmp; /* Temporary for a pointer */
    char **sstmp; /* Temporary for a pointer to a pointer */

    if (ml->pos + 1 >= ml->siz)
      {
        sstmp = (char **)sv_malloc(sizeof(char *) * (ml->siz += 200));
        /* Point to the new memory */
        if (sstmp != NULL)
            ml->buf = sstmp;
        /* Get out of here if there's no memory */
        else
            return NULL;
      }

    stmp = (char *)sv_strdup(str, len);
    /* Point to the new memory */
    if (stmp != NULL)
        ml->buf[ml->pos] = stmp;
    /* Get out of here if there's no memory */
    else
        return NULL;

    /* Advance the pointer to the next free space */
    ml->pos += 1;

    /* NULL terminate it, too! */
    ml->buf[ml->pos] = NULL;

    /* Free the incoming string, if requested */
    if (freeme)
        sv_free(str);

    return ml->buf[ml->pos-1];
}

void sv_strbuffree(struct mlbuf **ml, int freeall)
{
    size_t i;

    /* Loop through and free the allocated strings */
    if (freeall)
      {
        for (i = 0; i < (*ml)->pos; i++)
          {
            sv_free((*ml)->buf[i]);
          }
      }
    /* Free the buf array */
    sv_free((*ml)->buf);
    /* Free the mlbuf itself */
    sv_free((*ml));
    /* NULLify the free()'d pointer */
    *ml = NULL;
}

void sv_strbufalloc(struct mlbuf **ml)
{
    *ml = (struct mlbuf *)sv_malloc(sizeof(struct mlbuf));
    (*ml)->buf = NULL;
    (*ml)->siz = (*ml)->pos = 0;
}
