#ifndef HEADERINC_H
#define HEADERINC_H

/* Structures are here now */
#include "parser.h"

#define HEADERHASHSIZE 1019

int libsieve_headerlex(void);
int libsieve_headerparse(struct sieve2_context *context);
void libsieve_headererror(struct sieve2_context *context, const char *str);
int libsieve_headerinput(char *buf, int max_size);
int libsieve_headerappend(header_list_t **hl);
void libsieve_headerentry(header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
