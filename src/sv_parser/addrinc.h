#ifndef ADDRINC_H
#define ADDRINC_H

int addrlex(void);
int addrparse(void);
struct address *addr_parse_buffer(struct address **data, const char **ptr, char **err);
int addrinput(char *buf, int max_size);
void addrerror(const char *str);
void addrlexfree(void);
void addrlexalloc(void);
void addrappend(struct address **a);

#define STRUCTONLY 0
#define CHARSALSO 1
void addrstructfree(struct address *addr, int freeall);
struct address *addrstructcopy(struct address *addr, int copyall);

struct address {
  char *name;
  char *route;
  char *domain;
  char *mailbox;
//  int freeme;  /* Free if 1 */
  struct address *next;
};

struct addr_marker {
    struct address *where;
    char *freeme;
};

#endif /* ADDRINC_H */
