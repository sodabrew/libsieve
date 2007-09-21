#ifndef ADDRINC_H
#define ADDRINC_H

/* Structures are here now */
#include "parser.h"

int libsieve_addrlex(void *scanner);
//int libsieve_addrparse(struct sieve2_context *context);
void libsieve_addrerror(struct sieve2_context *context, struct address *addr, char *str);
void libsieve_addrappend(struct sieve2_context *context, struct address **a);

#define STRUCTONLY 0
#define CHARSALSO 1
void libsieve_addrstructfree(struct sieve2_context *context, struct address *addr, int freeall);
struct address *libsieve_addrstructcopy(struct sieve2_context *context, struct address *addr, int copyall);

#endif /* ADDRINC_H */
