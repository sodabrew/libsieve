#ifndef PARSER_H
#define PARSER_H

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

struct address *addr_parse_buffer(struct address **data, const char **ptr, char **err);
void addrlexfree(void);
void addrlexalloc(void);

void sievelexfree(void);
void sievelexalloc(void);

typedef struct header {
    char *name;
    size_t count;
    size_t space;
    char **contents;
} header_t;

typedef struct header_list {
    header_t *h;
    struct header_list *next;
} header_list_t;

header_list_t *header_parse_buffer(header_list_t **data, char **ptr, char **err);
void headerlexfree(void);
void headerlexalloc(void);

#endif /* PARSER_H */
