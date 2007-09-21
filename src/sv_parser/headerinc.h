#ifndef HEADERINC_H
#define HEADERINC_H

/* Structures are here now */
#include "parser.h"

//int libsieve_headerlex(struct sieve2_context *context, void *yyscanner);
// int libsieve_headerparse(struct sieve2_context *context);
void libsieve_headererror(struct sieve2_context *context, const char *str);
int libsieve_headerappend(struct sieve2_context *context, header_list_t **hl);
void libsieve_headerentry(struct sieve2_context *context, header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
