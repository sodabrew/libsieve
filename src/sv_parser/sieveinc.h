#ifndef SIEVEINC_H
#define SIEVEINC_H

#include "tree.h"
#include "script.h"
#include "context2.h"

struct vtags {
    int days;
    stringlist_t *addresses;
    char *subject;
    int mime;
    char *from;
    char *handle;
};

struct hftags {
    char *comparator;
    int comptag;
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
    char *priority;
    char *message;
};

static test_t *static_build_address(struct sieve2_context *context, int t, struct aetags *ae,
			     stringlist_t *sl, patternlist_t *pl);
static test_t *static_build_header(struct sieve2_context *context, int t, struct htags *h,
			    stringlist_t *sl, patternlist_t *pl);
static commandlist_t *static_build_vacation(struct sieve2_context *context, int t, struct vtags *h, char *s);
static commandlist_t *static_build_notify(struct sieve2_context *context, int t, struct ntags *n);
static commandlist_t *static_build_validnotif(struct sieve2_context *context, int t, stringlist_t *sl);
static struct aetags *static_new_aetags(void);
static struct aetags *static_canon_aetags(struct aetags *ae);
static void static_free_aetags(struct aetags *ae);
static struct hftags *static_new_hftags(void);
static struct htags *static_new_htags(void);
static struct htags *static_canon_htags(struct htags *h);
static void static_free_htags(struct htags *h);
static struct vtags *static_new_vtags(void);
static struct vtags *static_canon_vtags(struct vtags *v);
static void static_free_vtags(struct vtags *v);
static struct ntags *static_new_ntags(void);
static struct ntags *static_canon_ntags(struct ntags *n);
static void static_free_ntags(struct ntags *n);

static int static_verify_stringlist(struct sieve2_context *context, stringlist_t *sl,
                                    int (*verify)(struct sieve2_context *, const char *));
static int static_verify_mailbox(struct sieve2_context *context, const char *s);
static int static_verify_address(struct sieve2_context *context, const char *s);
static int static_verify_header(struct sieve2_context *context, const char *s);
static int static_verify_flag(struct sieve2_context *context, const char *s);
static regex_t *static_verify_regex(struct sieve2_context *context, const char *s, int cflags);
static patternlist_t *static_verify_regexs(struct sieve2_context *context, stringlist_t *sl, char *comp);
static int static_ok_header(char *s);

static int static_check_reqs(struct sieve2_context *context, char *req);

#endif /* SIEVEINC_H */
