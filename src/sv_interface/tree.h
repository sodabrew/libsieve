/* tree.h -- abstract syntax tree
 * Larry Greenfield
 * $Id$
 */
/***********************************************************
        Copyright 1999 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Carnegie Mellon
University not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR
ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
******************************************************************/

#ifndef TREE_H
#define TREE_H

#include "comparator.h"

#ifdef HAVE_RX
#include <rxposix.h>
#else
#include <sys/types.h>
#include <regex.h>
#endif


/* abstract syntax tree for sieve */
typedef struct Stringlist stringlist_t;
typedef struct Patternlist patternlist_t;
typedef struct Commandlist commandlist_t;
typedef struct Test test_t;
typedef struct Testlist testlist_t;
typedef struct Tag tag_t;
typedef struct Taglist taglist_t;

struct Stringlist {
    char *s;
    stringlist_t *next;
};

struct Patternlist {
    void *p;
    patternlist_t *next;
};

struct Tag {
    int type;
    char *arg;
};

struct Taglist {
    tag_t *t;
    taglist_t *next;
};

struct Test {
    int type;
    union {
	testlist_t *tl; /* anyof, allof */
	stringlist_t *sl; /* exists */
	struct { /* it's a header test */
	    int comptag;
	    comparator_t *comp;
	    stringlist_t *sl;
	    patternlist_t *pl;
	} h;
	struct { /* it's an address or envelope test */
	    int comptag;
	    comparator_t *comp;
	    stringlist_t *sl;
	    patternlist_t *pl;
            int addrpart;
	} ae; 
	test_t *t; /* not */
	struct { /* size */
	    int t; /* tag */
	    int n; /* param */
	} sz;
    } u;
};

struct Testlist {
    test_t *t;
    testlist_t *next;
};

struct Commandlist {
    int type;
    union {
        char *str;
	stringlist_t *sl; /* the parameters */
	struct { /* it's an if statement */
	    test_t *t;
	    commandlist_t *do_then;
	    commandlist_t *do_else;
	} i;
	struct { /* it's a vacation action */
	    char *subject;
	    int days;
	    stringlist_t *addresses;
	    char *message;
	    int mime;
	} v;
	struct { /* it's a notify action */
	    char *method;
	    char *id;
	    stringlist_t *options;
	    const char *priority;
	    char *message;
	} n;
	struct { /* it's a denotify action */
	    int comptag;
	    comparator_t *comp;
	    void *pattern;
	    const char *priority;
	} d;
    } u;
    struct Commandlist *next;
};

stringlist_t *libsieve_new_sl(char *s, stringlist_t *n);
patternlist_t *libsieve_new_pl(regex_t *pat, patternlist_t *n);
tag_t *libsieve_new_tag(int type, char *s);
taglist_t *libsieve_new_taglist(tag_t *t, taglist_t *n);
test_t *libsieve_new_test(int type);
testlist_t *libsieve_new_testlist(test_t *t, testlist_t *n);
commandlist_t *libsieve_new_command(int type);
commandlist_t *libsieve_new_if(test_t *t, commandlist_t *y, commandlist_t *n);

void libsieve_free_sl(stringlist_t *sl);
void libsieve_free_pl(patternlist_t *pl, int comptag);
void libsieve_free_test(test_t *t);
void libsieve_free_tree(commandlist_t *cl);

char **stringlist_to_chararray(stringlist_t *list);

#endif
