#ifndef HEADERINC_H
#define HEADERINC_H

/* Structures are here now */
#include "parser.h"

#define HEADERHASHSIZE 1019

int libsieve_headerlex(void);
int libsieve_headerparse(void);
int libsieve_headerinput(char *buf, int max_size);
void libsieve_headererror(char *str);
int libsieve_headerappend(header_list_t **hl);
void libsieve_headerentry(header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
