#ifndef SIEVEINC_H
#define SIEVEINC_H

#include "tree.h"
#include "script.h"

struct vtags {
    int days;
    stringlist_t *addresses;
    char *subject;
    int mime;
};

struct htags {
    char *comparator;
    int comptag;
};

struct aetags {
    int addrtag;
    char *comparator;
    int comptag;
};

struct ntags {
    char *method;
    char *id;
    stringlist_t *options;
    const char *priority;
    char *message;
};

struct dtags {
    int comptag;
    void *pattern;
    char *priority;
};

static commandlist_t *ret;
static sieve_script_t *parse_script;
static int check_reqs(stringlist_t *sl);
static test_t *build_address(int t, struct aetags *ae,
			     stringlist_t *sl, patternlist_t *pl);
static test_t *build_header(int t, struct htags *h,
			    stringlist_t *sl, patternlist_t *pl);
static commandlist_t *build_vacation(int t, struct vtags *h, char *s);
static commandlist_t *build_notify(int t, struct ntags *n);
static commandlist_t *build_denotify(int t, struct dtags *n);
static struct aetags *new_aetags(void);
static struct aetags *canon_aetags(struct aetags *ae);
static void free_aetags(struct aetags *ae);
static struct htags *new_htags(void);
static struct htags *canon_htags(struct htags *h);
static void free_htags(struct htags *h);
static struct vtags *new_vtags(void);
static struct vtags *canon_vtags(struct vtags *v);
static void free_vtags(struct vtags *v);
static struct ntags *new_ntags(void);
static struct ntags *canon_ntags(struct ntags *n);
static void free_ntags(struct ntags *n);
static struct dtags *new_dtags(void);
static void free_dtags(struct dtags *d);

static int verify_stringlist(stringlist_t *sl, int (*verify)(const char *));
static int verify_mailbox(const char *s);
static int verify_address(const char *s);
static int verify_header(const char *s);
static int verify_flag(const char *s);
#ifdef ENABLE_REGEX
static regex_t *verify_regex(const char *s, int cflags);
static patternlist_t *verify_regexs(stringlist_t *sl, char *comp);
#endif
static int ok_header(char *s);

#endif /* SIEVEINC_H */
