#ifndef HEADERINC_H
#define HEADERINC_H

/* Structures are here now */
#include "parser.h"

#define HEADERHASHSIZE 1019

int headerlex(void);
int headerparse(void);
int headerinput(char *buf, int max_size);
void headererror(const char *str);
int headerappend(header_list_t **hl);
void headerentry(header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
