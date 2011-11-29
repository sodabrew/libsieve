/* comparator.h
 * Larry Greenfield
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

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "src/sv_regex/regex.h"
#include "src/sv_include/sieve2.h"

/* compares pat to text; returns 1 if it's true, 0 otherwise 
   first arg is pat, second arg is text */
typedef int comparator_t(struct sieve2_context *context, const char *, const char *);

/* returns a pointer to a comparator function given it's name */
comparator_t *libsieve_comparator_lookup(struct sieve2_context *context, const char *comp, int mode);

enum num {
    gt = 1, // >
    ge    , // >=
    lt    , // <
    le    , // <=
    eq    , // ==
    ne      // !=
};

/* returns a magic number of the relational comparator. */
int libsieve_relational_lookup(const char *rel);
int libsieve_relational_count(struct sieve2_context *context, int mode);

#endif
