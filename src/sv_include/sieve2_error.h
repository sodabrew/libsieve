/* sieve2_error.h -- new libSieve v2.2 error codes
 * $Id$
 */

/* * * *
 * Copyright 2003, 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

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
#define SIEVE2_ERROR_BADARGS	       9
#define SIEVE2_ERROR_NOINTERPS         10
#define SIEVE2_ERROR_HEADER            11
#define SIEVE2_ERROR_GETSCRIPT         12
#define SIEVE2_ERROR_LAST              13

static const char * const sieve2_error_text[] = {
    "Sieve OK",
    "Sieve DONE",
    "Sieve Error: unspecified error",
    "Sieve Error: incomplete callbacks",
    "Sieve Error: parse error",
    "Sieve Error: execution error",
    "Sieve Error: internal error",
    "Sieve Error: out of memory",
    "Sieve Error: unsupported feature",
    "Sieve Error: incorrect argument passed",
    "Sieve Error: no more interpreters available",
    "Sieve Error: header could not be parsed",
    "Sieve Error: script was not retrieved",
    NULL
};

#endif /* SIEVE2_ERROR_H */
