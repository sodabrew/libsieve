/* context2.h -- manages the libSieve opaque context and callbacks.
 * Aaron Stone
 * $Id$
 */
/* * * *
 * Copyright 2005 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifndef CONTEXT2_H
#define CONTEXT2_H

#include "tree.h"		/* for commandlist_t */
#include "message2.h"
#include "sieve2.h"

struct callbacks2 {
    sieve2_callback_func redirect;
    sieve2_callback_func reject;
    sieve2_callback_func discard;
    sieve2_callback_func fileinto;
    sieve2_callback_func keep;
    sieve2_callback_func notify;
    sieve2_callback_func denotify;
    sieve2_callback_func vacation;
    sieve2_callback_func setflag;
    sieve2_callback_func addflag;
    sieve2_callback_func removeflag;

    sieve2_callback_func err_runtime;
    sieve2_callback_func err_parse;
    sieve2_callback_func debug_trace;

    sieve2_callback_func getscript;

    sieve2_callback_func getheader;
    sieve2_callback_func getallheaders;
    sieve2_callback_func getenvelope;
    sieve2_callback_func getsize;
    sieve2_callback_func getbody;
    sieve2_callback_func getsubaddress;
};

enum boolean { FALSE = 0, TRUE = 1 };

struct support2 {
    /* These are callback based. */
    enum boolean          reject;
    enum boolean          notify;
    enum boolean          fileinto;
    enum boolean          vacation;
    enum boolean          envelope;
    enum boolean          imap4flags;

    /* These are more like built-ins. */
    enum boolean          regex;
    enum boolean          subaddress;
};

struct actions2 {
    /* We'll use these to check for
     * incompatible actions in callbacks2.c. */
    enum boolean          redirect;
    enum boolean          reject;
    enum boolean          discard;
    enum boolean          fileinto;
    enum boolean          keep;
    enum boolean          notify;
    enum boolean          denotify;
    enum boolean          vacation;
    enum boolean          setflag;
    enum boolean          addflag;
    enum boolean          removeflag;
};

struct script2 {
    int error_count;
    int error_lineno;
    const char *script;
    commandlist_t *cmds;
};

/* I don't anticipate needing more
 * than 10 of these; but watch out
 * for overflow if the user tries
 * to put in too many values. */
#define MAX_VALUES 10
struct cur_call {
    enum boolean begin, end;
    sieve2_values_t code;
    struct {
        char *name;
        enum {
            VAL_INT, VAL_STRING, VAL_STRINGLIST
        } type;
        union {
            int i;
            char *s;
            char **sl;
        } value;
    } values [MAX_VALUES];
};

struct sieve2_context {
    sieve2_message_t *message;
    stringlist_t *slflags;
    struct mlbuf *strbuf;

    int parse_errors;
    int exec_errors;

    struct cur_call cur_call;

    /* These aren't pointers, they're right here.
     * I'd like to do this with all of the context
     * structs -- makes my life easier not to malloc
     * so much separate junk all over the place. */
    struct callbacks2 callbacks;
    struct support2 support;
    struct support2 require;
    struct actions2 actions;
    struct script2 script;

    void *user_data;
};

#endif
