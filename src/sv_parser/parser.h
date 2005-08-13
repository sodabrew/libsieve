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

struct address *libsieve_addr_parse_buffer(struct address **data, const char **ptr, char **err);
void libsieve_addrlexfree(void);
void libsieve_addrlexalloc(void);

/* SIEVE */
#include "tree.h"
#include "context2.h"
#include "message2.h"

commandlist_t *libsieve_sieve_parse_buffer(struct sieve2_context *context);

void libsieve_sievelexfree(void);
void libsieve_sievelexalloc(void);

header_list_t *libsieve_header_parse_buffer(header_list_t **data, char **ptr, char **err);
void libsieve_headerlexfree(void);
void libsieve_headerlexalloc(void);
void libsieve_headeryaccfree(void);
void libsieve_headeryaccalloc(void);

#endif /* PARSER_H */
