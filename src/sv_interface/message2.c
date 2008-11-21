/* message2.c -- Sieve 2 API Message Parsing Functions
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

/* isnctrl() */
#include <ctype.h>
/* strlen() */
#include <string.h>

/* sv_parser */
#include "headerinc.h"

/* sv_interface */
#include "message2.h"
#include "context2.h"
#include "callbacks2.h"

/* sv_util */
#include "util.h"

#define THIS_MODULE "sv_interface"
#define THIS_CONTEXT c

static int hashheader(char *header, int hashsize)
{
    int x = 0;

    /* Any char except ' ', :, or a cntrl char */
    for (; !iscntrl(*header) && (*header != ' ') && (*header != ':'); header++) {
        x *= 256;
        x += *header;
        x %= hashsize;
    }

    return x;
}

static int freecache(sieve2_message_t *m)
{
    int i; /*, j; */

    /* Free the header hash cache entries */
    for (i = 0; i < m->hashsize; i++) {
        if (m->hash[i]) {
	    /* The individual contents were allocated by the lex/yacc parser,
	     * and so they are freed by headerlexfree() and headeryaccfree().
	     * */
            libsieve_free(m->hash[i]->contents);
        }
        libsieve_free(m->hash[i]);
    }
    libsieve_free(m->hash);
    libsieve_free(m);

    return SIEVE2_OK;
}

int libsieve_message2_alloc(sieve2_message_t **m)
{
    int i;
    sieve2_message_t *n = NULL;

    n = (sieve2_message_t *)libsieve_malloc(sizeof(sieve2_message_t));
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

    *(sieve2_message_t **)m = n;
    return SIEVE2_OK;
}

int libsieve_message2_free(sieve2_message_t **m)
{
    int res;

    if (m) 
        res = freecache(*m);

    *m = NULL;

    return res;
}

/* This function takes the header in m->message and 
 * then uses the header parser to work at filling
 * the header hash in m->hash
 */
int libsieve_message2_parseheader(void *context, sieve2_message_t *m)
{
    size_t c, cl;
    header_list_t *hl = NULL, *hlfree;

    if ((hl = libsieve_header_parse_buffer(context, m->header, &hl)) == NULL) {
        /* That's a shame, we didn't find anything, or worse! */
        return SIEVE2_ERROR_HEADER;
    }

    while (hl != NULL) {
        /* Get a hash number of the header name */
        cl = c = hashheader(hl->h->name, m->hashsize);
        while (m->hash[c] != NULL && strcmp(hl->h->name, m->hash[c]->name) != 0) {
            c++;
            c %= m->hashsize;
            /* If we've skipped back to the beginning,
             * give up and we'll just realloc a larger space */
            if (c == cl) break;
        }

        if (m->hash[c]) {
            /* Looks like someone's already home */
            if (m->hash[c]->count < m->hash[c]->space) {
                /* We have room for one more header */
                m->hash[c]->contents[m->hash[c]->count++] = hl->h->contents[0];
                /* Followed by a terminating NULL */
                m->hash[c]->contents[m->hash[c]->count] = NULL;
            } else {
                /* Need to make some more space in here, plus one for the NULL. */
                char **tmp;
                tmp = (char **)libsieve_realloc(m->hash[c]->contents, sizeof(char *) * ((m->hash[c]->space+=8) + 1));
                if (tmp == NULL) {
                    return SIEVE2_ERROR_NOMEM;
		} else {
                    m->hash[c]->contents = tmp;
		}
                /* OK, now we can put that body in here */
                m->hash[c]->contents[m->hash[c]->count++] = hl->h->contents[0];
                /* Followed by a terminating NULL */
                m->hash[c]->contents[m->hash[c]->count] = NULL;
            }
          /* Since we're not using this header_t struct, free it.
           * Note that we're not freeing each of contents, we need those. */
          libsieve_free(hl->h->contents);
          libsieve_free(hl->h);
        } else {
            /* Make of copy of the pointer */
            m->hash[c] = hl->h;
        }

	/* Advance the cursor and cleanup as we go */
	hlfree = hl;
        hl = hl->next;
	libsieve_free(hlfree);
    }

    m->hashfull = 1;
    return SIEVE2_OK;
}

/* Places the contents of the header specified by chead into body */
static int getheader(sieve2_message_t *m, const char *chead, const char ***body)
{
    int c, cl;
    char *head = NULL;

    /* Make sure there's nothing in the way */
    *body = NULL;

    /* Make a local copy of the header */
    head = libsieve_strdup(chead);
    if (head == NULL)
        return SIEVE2_ERROR_NOMEM;

    head = libsieve_strtolower(head, strlen(head));

    /* Get a hash number of the header name */
    cl = c = hashheader(head, m->hashsize);
    while (m->hash[c] != NULL) {
        if (strcmp(head, m->hash[c]->name) == 0) {
            *body = (const char **) m->hash[c]->contents;
            break;
        }
        c++;
        c %= m->hashsize;
        /* If we've skipped back to the beginning,
         * give up; we'll throw an error below. */
        if (c == cl) break;
    }

    libsieve_free(head);

    if (*body) {
        return SIEVE2_OK;
    } else {
        return SIEVE2_ERROR_FAIL;
    }
}

/* Emulate the user getheader callback. */
int libsieve_message2_getheader(struct sieve2_context *c, void *user_data UNUSED)
{
    int res;
    const char *header, **body;

    header = libsieve_getvalue_string(c, "header");

    res = getheader(c->message, header, &body);

    libsieve_setvalue_stringlist(c, "body", (char **)body);

    return res;
}

