#ifndef ADDRINC_H
#define ADDRINC_H

/* Structures are here now */
#include "parser.h"

#define YY_DECL int libsieve_addrlex (YYSTYPE *yylval_param, struct sieve2_context *context, void *yyscanner)
int libsieve_addrparse(struct sieve2_context *context, void *yyscanner);
void libsieve_addrerror(struct sieve2_context *context, void *yyscanner, const char *str);

#define STRUCTONLY 0
#define CHARSALSO 1
void libsieve_addrstructfree(struct sieve2_context *context, struct address *addr, int freeall);

#endif /* ADDRINC_H */
