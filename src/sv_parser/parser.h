#ifndef PARSER_H
#define PARSER_H

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

/* SIEVE */
#include "src/sv_interface/context2.h"
#include "src/sv_interface/message2.h"

struct address *libsieve_addr_parse_buffer(struct sieve2_context *context, struct address **data, const char **ptr);
int libsieve_addrlex_destroy(void *yyscanner);
int libsieve_addrlex_init(void **yyscanner);

commandlist_t *libsieve_sieve_parse_buffer(struct sieve2_context *context);

int libsieve_sievelex_destroy(void *yyscanner);
int libsieve_sievelex_init(void **yyscanner);

header_list_t *libsieve_header_parse_buffer(struct sieve2_context *context, header_list_t **data, char **ptr);
int libsieve_headerlex_destroy(void* yyscanner);
int libsieve_headerlex_init(void** yyscanner);

#endif /* PARSER_H */
