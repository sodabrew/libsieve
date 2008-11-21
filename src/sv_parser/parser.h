#ifndef PARSER_H
#define PARSER_H

#include "context2.h"
#include <stdlib.h>
#include <sys/types.h>

/* We need this from the flex headers, but we cannot include them lest we break flex. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

int libsieve_lexinput(char **ptr, size_t *ptr_len, char *buf, int max);

/* ADDRESS */
struct address {
  char *name;
  char *route;
  char *domain;
  char *mailbox;
  struct address *next;
};

struct addr_marker {
    struct address *where;
    char *freeme;
};

struct address *libsieve_addr_parse_buffer(struct sieve2_context *context, const char *ptr, struct address **data);

/* SIEVE */
#include "tree.h"
#include "context2.h"
#include "message2.h"

commandlist_t *libsieve_sieve_parse_buffer(struct sieve2_context *context);

int libsieve_sievelex(yyscan_t yyscanner);
int libsieve_addrlex(yyscan_t yyscanner);

int libsieve_sieveerror(struct sieve2_context *context, char *msg);
int libsieve_sieveerror_exec(struct sieve2_context *context, char *msg);

/* HEADER */
header_list_t *libsieve_header_parse_buffer(struct sieve2_context *context, const char *ptr, header_list_t **data);

#endif /* PARSER_H */
