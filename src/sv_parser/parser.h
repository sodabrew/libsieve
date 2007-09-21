#ifndef PARSER_H
#define PARSER_H

#include "context2.h"
#include <stdlib.h>
#include <sys/types.h>

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

struct address *libsieve_addr_parse_buffer(struct sieve2_context *context, struct address **data, const char **ptr, char **err);

/* SIEVE */
#include "tree.h"
#include "context2.h"
#include "message2.h"

void libsieve_sieve_parse_buffer(struct sieve2_context *context);

int libsieve_sievelex(void *yyscanner);

int libsieve_sieveerror(struct sieve2_context *context, char *msg);
int libsieve_sieveerror_exec(struct sieve2_context *context, char *msg);

/* HEADER */
header_list_t *libsieve_header_parse_buffer(struct sieve2_context *context, header_list_t **data, char **ptr, char **err);

#endif /* PARSER_H */
