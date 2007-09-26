/* message2.h
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */


#ifndef MESSAGE2_H
#define MESSAGE2_H

/* HEADER */
typedef struct header {
    char *name;
    size_t count;
    size_t space;
    char **contents;
} header_t;

typedef struct header_list {
    header_t *h;
    struct header_list *next;
} header_list_t;

typedef struct message {
    int size;
    int hashsize;
    int hashfull;
    int listfull;
    /* Contains the entire unparsed message header. */
    char *header;
    /* These two will share pointers to their header_t
     * members, but the list is filled by the parser
     * and latter sorted and hashed into the hash table. */
    header_t **hash;
    header_list_t *list;
} sieve2_message_t;

int libsieve_message2_parseheader(sieve2_message_t *m);
int libsieve_message2_alloc(sieve2_message_t **m);
int libsieve_message2_free(sieve2_message_t **m);

/* This follows the sieve2_callback_t interface. */
//int libsieve_message2_getheader(struct sieve2_context *m, void *user_data);

#endif /* MESSAGE2_H */
