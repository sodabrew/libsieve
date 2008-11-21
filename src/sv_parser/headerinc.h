#ifndef HEADERINC_H
#define HEADERINC_H

/* Structures are here now */
#include "parser.h"

#define HEADERHASHSIZE 1019

int libsieve_headerparse(struct sieve2_context *context);
void libsieve_headererror(struct sieve2_context *context, char *str);
int libsieve_headerappend(struct sieve2_context *context, header_list_t **hl);
void libsieve_headerentry(struct sieve2_context *context, header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
