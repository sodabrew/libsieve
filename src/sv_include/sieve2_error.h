/* sieve2_error.h -- new libSieve v2.2 error codes
 * $Id$
 */

/***********************************************************
 * Copyright 2003 libSieve Development Team by Aaron Stone
 *
 * Licensed under LPGL and CMU's "MIT style" license.
 *
 * This is an original work modelled after CMU concepts.
 * It does not contain code written by or derived from CMU.
 ***********************************************************/

#ifndef SIEVE2_ERROR_H
#define SIEVE2_ERROR_H

#define SIEVE2_OK                      0
#define SIEVE2_DONE                    1
#define SIEVE2_ERROR_FAIL              2
#define SIEVE2_ERROR_NOT_FINALIZED     3
#define SIEVE2_ERROR_PARSE	       4
#define SIEVE2_ERROR_EXEC              5
#define SIEVE2_ERROR_INTERNAL          6
#define SIEVE2_ERROR_NOMEM             7
#define SIEVE2_ERROR_UNSUPPORTED       8
#define SIEVE2_ERROR_BADARG	       9

static const char * const sieve2_error_text[] = {
    "Sieve OK: no trouble at all",
    "Sieve DONE: did that already",
    "Sieve Error: generic error",
    "Sieve Error: interpreter not ready",
    "Sieve Error: parse error",
    "Sieve Error: execution error",
    "Sieve Error: internal error",
    "Sieve Error: out of memory",
    "Sieve Error: unsupported feature",
    "Sieve Error: incorrect argument passed",
    0
};
#endif /* SIEVE2_ERROR_H */
