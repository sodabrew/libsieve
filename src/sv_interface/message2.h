/* message2.h
 * Aaron Stone
 * $Id$
 */
/**********************************************************
 *      FIXME: Copyright needed
 **********************************************************/

#ifndef MESSAGE2_H
#define MESSAGE2_H

/* sv_parser */
#include "headerinc.h"

typedef struct message {
    int size;
    int hashsize;
    int hashfull;
    int listfull;
    char *envelope;
    char *header;
    /* These two will share pointers to their header_t
     * members, but the list is filled by the parser
     * and later sorted and hashed into the hash table */
    header_t **hash;
    header_list_t *list;
} sieve2_message;

extern int message2_getsize(sieve2_message *m, int *sz);
extern int message2_getheader(sieve2_message *m, const char *chead, const char ***body);
extern int message2_getenvelope(sieve2_message *m, const char *chead, const char ***body);
extern int message2_parseheader(sieve2_message *m);
static int message2_hashheader(char *header, int hashsize);

#endif /* MESSAGE2_H */
