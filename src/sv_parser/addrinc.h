#ifndef ADDRINC_H
#define ADDRINC_H

/* Structures are here now */
#include "parser.h"

int addrlex(void);
int addrparse(void);
int addrinput(char *buf, int max_size);
void addrerror(const char *str);
void addrappend(struct address **a);

#define STRUCTONLY 0
#define CHARSALSO 1
void addrstructfree(struct address *addr, int freeall);
struct address *addrstructcopy(struct address *addr, int copyall);

#endif /* ADDRINC_H */
