#ifndef ADDRINC_H
#define ADDRINC_H

/* Structures are here now */
#include "parser.h"

int libsieve_addrlex(void);
int libsieve_addrparse(struct sieve2_context *context);
int libsieve_addrinput(char *buf, int max_size);
void libsieve_addrerror(struct sieve2_context *context, char *str);
void libsieve_addrappend(struct address **a);

#define STRUCTONLY 0
#define CHARSALSO 1
void libsieve_addrstructfree(struct address *addr, int freeall);
struct address *libsieve_addrstructcopy(struct address *addr, int copyall);

#endif /* ADDRINC_H */
