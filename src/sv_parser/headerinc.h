#ifndef HEADERINC_H
#define HEADERINC_H

#define HEADERHASHSIZE 1019

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

int headerlex(void);
int headerparse(void);
header_list_t *header_parse_buffer(header_list_t **data, char **ptr, char **err);
int headerinput(char *buf, int max_size);
void headererror(const char *str);
void headerlexfree(void);
void headerlexalloc(void);
int headerappend(header_list_t **hl);
void headerentry(header_t *h, char *name, char *body);

#endif /* HEADERINC_H */
