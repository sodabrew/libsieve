%{
/* sieve.y -- sieve parser
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* sv_regex */
#include "src/sv_regex/regex.h"

/* sv_parser */
#include "comparator.h"
#include "addrinc.h"
#include "sieveinc.h"

/* sv_interface */
#include "src/sv_interface/callbacks2.h"

/* sv_util */
#include "src/sv_util/util.h"
#include "sieve.h"
#include "sieve-lex.h"
#define THIS_MODULE "sv_parser"

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

static test_t *static_build_address(struct sieve2_context *context, int t,
                     struct aetags *ae, stringlist_t *sl, patternlist_t *pl);
static test_t *static_build_header(struct sieve2_context *context, int t,
                     struct htags *h, stringlist_t *sl, patternlist_t *pl);
static commandlist_t *static_build_vacation(struct sieve2_context *context, int t, struct vtags *h, char *s);
static commandlist_t *static_build_notify(struct sieve2_context *context,
					  int t, struct ntags *n);
static commandlist_t *static_build_validnotif(struct sieve2_context *context,
					      int t, stringlist_t *sl);
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

static int static_verify_stringlist(struct sieve2_context *context, stringlist_t *sl, int (*verify)(struct sieve2_context *context, const char *));
static int static_verify_mailbox(const char *s);
static int static_verify_address(struct sieve2_context *context, const char *s);
static int static_verify_header(struct sieve2_context *context, const char *s);
static int static_verify_flag(struct sieve2_context *context, const char *s);
static regex_t *static_verify_regex(struct sieve2_context *context, const char *s, int cflags);
static patternlist_t *static_verify_regexs(struct sieve2_context *context, stringlist_t *sl, char *comp);
static int static_ok_header(char *s);

static int static_check_reqs(struct sieve2_context *context, char *req);

extern YY_DECL;

#define YYERROR_VERBOSE /* i want better error messages! */
%}

%defines "sieve.h"
%output "sieve.c"
%name-prefix="libsieve_sieve"

%define api.pure
%lex-param {struct sieve2_context *context}
%lex-param {void *yyscanner}
%parse-param {struct sieve2_context *context}
%parse-param {void *yyscanner}
%union {
    int nval;
    char *sval;
    stringlist_t *sl;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;
    struct vtags *vtag;
    struct aetags *aetag;
    struct htags *htag;
    struct hftags *hftag;
    struct ntags *ntag;
}

%token <nval> NUMBER
%token <sval> STRING
%token IF ELSIF ELSE
%token REJCT FILEINTO REDIRECT KEEP STOP DISCARD VACATION REQUIRE
%token SETFLAG ADDFLAG REMOVEFLAG MARK UNMARK FLAGS HASFLAG
%token NOTIFY VALIDNOTIF
%token ANYOF ALLOF EXISTS SFALSE STRUE HEADER NOT SIZE ADDRESS ENVELOPE
%token COMPARATOR IS CONTAINS MATCHES REGEX OVER UNDER COUNT VALUE
%token ALL LOCALPART DOMAIN USER DETAIL
%token DAYS ADDRESSES SUBJECT MIME FROM HANDLE
%token METHOD ID OPTIONS LOW NORMAL HIGH MESSAGE

%type <cl> commands command action elsif block
%type <sl> stringlist strings
%type <test> test
%type <nval> comptag sizetag addrparttag addrorenv
%type <testl> testlist tests
%type <htag> htags
%type <hftag> hftags
%type <aetag> aetags
%type <vtag> vtags
%type <ntag> ntags
%type <sval> priority

%%

start: /* empty */		{ context->sieve_ret = NULL; }
	| reqs commands		{ context->sieve_ret = $2; }
	;

reqs: /* empty */
	| require reqs
	;

require: REQUIRE stringlist ';'	{
                                    int unsupp = 0;
                                    char *msg;
                                    char *freemsg;
                                    stringlist_t *s;
                                    stringlist_t *sl = $2;

                                    msg = libsieve_strconcat("unsupported feature:", NULL);

                                    while (sl != NULL) {
                                        s = sl;
                                        sl = sl->next;

					/* Returns 1 if supported, 0 if not. */
                                        if (!static_check_reqs(context, s->s)) {
					    unsupp = 1;
                                            freemsg = msg;
                                            msg = libsieve_strconcat(freemsg, " ", s->s, NULL);
                                            libsieve_free(freemsg);
                                        }

                                        libsieve_free(s->s);
                                        libsieve_free(s);
                                    }

				    /* If something wasn't supported, bomb out with msg. */
                                    if (unsupp) {
                                        libsieve_sieveerror(context, yyscanner, msg);
                                        libsieve_free(msg);
                                        YYERROR; 
                                    }

                                    /* This needs to be free'd regardless of error */
                                    libsieve_free(msg);
                                }
	;

commands: command		{ $$ = $1; }
	| command commands	{ $1->next = $2; $$ = $1; }
	;

command: action ';'		{ $$ = $1; }
	| IF test block elsif   { $$ = libsieve_new_if($2, $3, $4); }
	| error ';'		{ $$ = libsieve_new_command(STOP); }
	;

elsif: /* empty */               { $$ = NULL; }
	| ELSIF test block elsif { $$ = libsieve_new_if($2, $3, $4); }
	| ELSE block             { $$ = $2; }
	;

action: REJCT STRING             { if (!context->require.reject) {
	                             libsieve_sieveerror(context, yyscanner, "reject not required");
				     YYERROR;
				   }
				   $$ = libsieve_new_command(REJCT); $$->u.str = $2; }
	| KEEP FLAGS stringlist	 { if (!context->require.imap4flags) {
	                             libsieve_sieveerror(context, yyscanner, "imap4flags not required");
	                             YYERROR;
                                   }
	                           $$ = libsieve_new_command(KEEP);
                                   $$->u.f.mailbox = NULL; 
				   $$->u.f.slflags = $3; }
	| KEEP			 { $$ = libsieve_new_command(KEEP);
	                           $$->u.f.mailbox = NULL;
				   $$->u.f.slflags = NULL; }
	| FILEINTO FLAGS stringlist STRING	 { if (!context->require.fileinto) {
	                             libsieve_sieveerror(context, yyscanner, "fileinto not required");
	                             YYERROR;
                                   } if (!context->require.imap4flags) {
	                             libsieve_sieveerror(context, yyscanner, "imap4flags not required");
	                             YYERROR;
                                   }

                                   if (!static_verify_stringlist(context, $3, static_verify_flag)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   if (!static_verify_mailbox($4)) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           $$ = libsieve_new_command(FILEINTO);
				   $$->u.f.slflags = $3;
				   $$->u.f.mailbox = $4; }
	| FILEINTO STRING	 { if (!context->require.fileinto) {
	                             libsieve_sieveerror(context, yyscanner, "fileinto not required");
	                             YYERROR;
                                   }
				   if (!static_verify_mailbox($2)) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           $$ = libsieve_new_command(FILEINTO);
				   $$->u.f.slflags = NULL;
				   $$->u.f.mailbox = $2; }
	| REDIRECT STRING         { $$ = libsieve_new_command(REDIRECT);
                                  if (!static_verify_address(context, $2)) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   $$->u.str = $2; }
	| STOP			 { $$ = libsieve_new_command(STOP); }
	| DISCARD		 { $$ = libsieve_new_command(DISCARD); }
	| VACATION vtags STRING  { if (!context->require.vacation) {
	                             libsieve_sieveerror(context, yyscanner, "vacation not required");
				     $$ = libsieve_new_command(VACATION);
				     YYERROR;
				   } else {
	                             $$ = static_build_vacation(context,
                                       VACATION, static_canon_vtags($2), $3);
				   } }
        | SETFLAG stringlist     { if (!context->require.imap4flags) {
                                    libsieve_sieveerror(context, yyscanner, "imap4flags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist(context, $2, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
				    }
                                 $$ = libsieve_new_command(SETFLAG);
                                 $$->u.sl = $2; }
        | ADDFLAG stringlist     { if (!context->require.imap4flags) {
                                    libsieve_sieveerror(context, yyscanner, "imap4flags not required");
                                    YYERROR;
                                    }
                                 if (!static_verify_stringlist(context, $2, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                    }
                                 $$ = libsieve_new_command(ADDFLAG);
                                 $$->u.sl = $2; }
        | REMOVEFLAG stringlist  { if (!context->require.imap4flags) {
                                     libsieve_sieveerror(context, yyscanner, "imap4flags not required");
                                     YYERROR;
                                     }
                                 if (!static_verify_stringlist(context, $2, static_verify_flag)) {
                                     YYERROR; /* vf should call sieveerror() */
                                     }
                                 $$ = libsieve_new_command(REMOVEFLAG);
                                 $$->u.sl = $2; }
        | NOTIFY ntags           { if (!context->require.notify) {
	                             libsieve_sieveerror(context, yyscanner, "notify not required");
	       		             $$ = libsieve_new_command(NOTIFY); 
	       		             YYERROR;
				 } else {
	                             $$ = static_build_notify(context, NOTIFY,
	       		             static_canon_ntags($2));
	       		         } }
        | VALIDNOTIF stringlist  { if (!context->require.notify) {
                                     libsieve_sieveerror(context, yyscanner, "notify not required");
				     $$ = libsieve_new_command(VALIDNOTIF);
				     YYERROR;
				 } else {
	                             $$ = static_build_validnotif(context, VALIDNOTIF, $2);
				 } }
	;

ntags: /* empty */		 { $$ = static_new_ntags(); }
	| ntags ID STRING	 { if ($$->id != NULL) { 
	                                libsieve_sieveerror(context, yyscanner, "duplicate :method"); YYERROR; }
				   else { $$->id = $3; } }
	| ntags METHOD STRING	 { if ($$->method != NULL) { 
	                                libsieve_sieveerror(context, yyscanner, "duplicate :method"); YYERROR; }
				   else { $$->method = $3; } }
	| ntags OPTIONS stringlist { if ($$->options != NULL) { 
	                                libsieve_sieveerror(context, yyscanner, "duplicate :options"); YYERROR; }
				     else { $$->options = $3; } }
	| ntags priority	 { if ($$->priority != NULL) { 
	                                libsieve_sieveerror(context, yyscanner,"duplicate :priority"); YYERROR; }
				   else { $$->priority = $2; } }
	| ntags MESSAGE STRING	 { if ($$->message != NULL) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :message"); YYERROR; }
				   else { $$->message = $3; } }
	;

hftags: /*empty */               { $$ = static_new_hftags(); }
	| hftags comptag         { $$->comptag = $2; }
	| hftags COMPARATOR STRING { if ($$->comparator != NULL) { 
				   libsieve_sieveerror(context, yyscanner, "duplicate comparator tag"); YYERROR; }
				   else { $$->comparator = $3; } }
	;

priority: LOW    { $$ = "low"; }
        | NORMAL { $$ = "normal"; }
        | HIGH   { $$ = "high"; }
        ;

vtags: /* empty */		 { $$ = static_new_vtags(); }
	| vtags DAYS NUMBER	 { if ($$->days != -1) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :days");
					YYERROR; }
				   else { $$->days = $3; } }
	| vtags ADDRESSES stringlist { if ($$->addresses != NULL) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :addresses");
					YYERROR;
				       } else if (!static_verify_stringlist(context, $3,
							static_verify_address)) {
					  YYERROR;
				       } else {
					 $$->addresses = $3; } }
	| vtags SUBJECT STRING	 { if ($$->subject != NULL) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :subject");
					YYERROR;
				   } else if (!static_ok_header($3)) {
					YYERROR;
				   } else { $$->subject = $3; } }
	| vtags HANDLE STRING	 { if ($$->handle != NULL) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :handle");
					YYERROR;
				   } else if (!static_ok_header($3)) {
					YYERROR;
				   } else { $$->handle = $3; } }
	| vtags FROM STRING	 { if ($$->from != NULL) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :from");
					YYERROR;
				   } else if (!static_ok_header($3)) {
					YYERROR;
				   } else { $$->from = $3; } }
	| vtags MIME		 { if ($$->mime != -1) { 
					libsieve_sieveerror(context, yyscanner, "duplicate :mime");
					YYERROR; }
				   else { $$->mime = MIME; } }
	;

stringlist: '[' strings ']'      { $$ = $2; }
	| STRING		 { $$ = libsieve_new_sl($1, NULL); }
	;

strings: STRING			 { $$ = libsieve_new_sl($1, NULL); }
	| STRING ',' strings	 { $$ = libsieve_new_sl($1, $3); }
	;

block: '{' commands '}'		 { $$ = $2; }
	| '{' '}'		 { $$ = NULL; }
	;

test: ANYOF testlist		 { $$ = libsieve_new_test(ANYOF); $$->u.tl = $2; }
	| ALLOF testlist	 { $$ = libsieve_new_test(ALLOF); $$->u.tl = $2; }
	| EXISTS stringlist      { $$ = libsieve_new_test(EXISTS); $$->u.sl = $2; }
	| SFALSE		 { $$ = libsieve_new_test(SFALSE); }
	| STRUE			 { $$ = libsieve_new_test(STRUE); }
        | HASFLAG hftags stringlist { if (!context->require.imap4flags) {
                                       libsieve_sieveerror(context, yyscanner, "imap4flags not required");
                                       YYERROR;
                                    }
                                    if (!static_verify_stringlist(context, $3, static_verify_flag)) {
                                       YYERROR; /* vf should call sieveerror() */
				    }
                                    $$ = libsieve_new_test(HASFLAG);
				    if ($2->comptag != -1) { 
				       $$->u.hf.comp = libsieve_comparator_lookup(context, $2->comparator, $2->comptag);
				       $$->u.hf.comptag = $2->comptag;
				    }
				    if ($2) {
				       libsieve_free($2);
				    }
                                    $$->u.hf.sl = $3; }
	| HEADER htags stringlist stringlist
				 { patternlist_t *pl;
                                   if (!static_verify_stringlist(context, $3, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   $2 = static_canon_htags($2);
				   if ($2->comptag == REGEX) {
				     pl = static_verify_regexs(context, $4, $2->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
				     pl = (patternlist_t *) $4;
				       
				   $$ = static_build_header(context, HEADER, $2, $3, pl);
				   if ($$ == NULL) { YYERROR; } }
	| addrorenv aetags stringlist stringlist
				 { patternlist_t *pl;
                                   if (!static_verify_stringlist(context, $3, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   $2 = static_canon_aetags($2);
				   if ($2->comptag == REGEX) {
				     pl = static_verify_regexs(context, $4, $2->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
				     pl = (patternlist_t *) $4;
				       
				   $$ = static_build_address(context, $1, $2, $3, pl);
				   if ($$ == NULL) { YYERROR; } }
	| NOT test		 { $$ = libsieve_new_test(NOT); $$->u.t = $2; }
	| SIZE sizetag NUMBER    { $$ = libsieve_new_test(SIZE); $$->u.sz.t = $2;
		                   $$->u.sz.n = $3; }
	| error			 { $$ = NULL; }
	;

addrorenv: ADDRESS		 { $$ = ADDRESS; }
	| ENVELOPE		 { $$ = ENVELOPE; }
	;

aetags: /* empty */              { $$ = static_new_aetags(); }
        | aetags addrparttag	 { $$ = $1;
				   if ($$->addrtag != -1) { 
		        libsieve_sieveerror(context, yyscanner, "duplicate or conflicting address part tag");
			YYERROR; }
				   else { $$->addrtag = $2; } }
	| aetags comptag         { $$ = $1;
				   if ($$->comptag != -1) { 
		        libsieve_sieveerror(context, yyscanner, "duplicate comparator type tag"); YYERROR; }
				   else { $$->comptag = $2; } }
	| aetags COMPARATOR STRING { $$ = $1;
				   if ($$->comparator != NULL) { 
		        libsieve_sieveerror(context, yyscanner, "duplicate comparator tag"); YYERROR; }
				   else { $$->comparator = $3; } }
	;

htags: /* empty */		 { $$ = static_new_htags(); }
	| htags comptag		 { $$ = $1;
				   if ($$->comptag != -1) { 
		        libsieve_sieveerror(context, yyscanner, "duplicate comparator type tag"); YYERROR; }
				   else { $$->comptag = $2; } }
	| htags COMPARATOR STRING { $$ = $1;
				   if ($$->comparator != NULL) { 
 		        libsieve_sieveerror(context, yyscanner, "duplicate comparator tag");
					YYERROR; }
				   else { $$->comparator = $3; } }
	;

addrparttag: ALL                 { $$ = ALL; }
	| LOCALPART		 { $$ = LOCALPART; }
	| DOMAIN                 { $$ = DOMAIN; }
	| USER                   { if (!context->require.subaddress) {
				     libsieve_sieveerror(context, yyscanner, "subaddress not required");
				     YYERROR;
				   }
				   $$ = USER; }
	| DETAIL                { if (!context->require.subaddress) {
				     libsieve_sieveerror(context, yyscanner, "subaddress not required");
				     YYERROR;
				   }
				   $$ = DETAIL; }
	;

comptag: IS			 { $$ = IS; }
	| VALUE	STRING		 { $$ = VALUE | libsieve_relational_lookup($2); libsieve_free($2); /* HACK: bits above 10 carry the relational. And we don't need this string anymore, either. */ }
	| COUNT	STRING		 { $$ = COUNT | libsieve_relational_lookup($2); libsieve_free($2); /* HACK: bits above 10 carry the relational. And we don't need this string anymore, either. */ }
	| CONTAINS		 { $$ = CONTAINS; }
	| MATCHES		 { $$ = MATCHES; }
	| REGEX			 { if (!context->require.regex) {
	                             libsieve_sieveerror(context, yyscanner, "regex not required");
				     YYERROR;
				     }
				   $$ = REGEX; }
	;

sizetag: OVER			 { $$ = OVER; }
	| UNDER			 { $$ = UNDER; }
	;

testlist: '(' tests ')'		 { $$ = $2; }
	;

tests: test                      { $$ = libsieve_new_testlist($1, NULL); }
	| test ',' tests         { $$ = libsieve_new_testlist($1, $3); }
	;

%%

commandlist_t *libsieve_sieve_parse_buffer(struct sieve2_context *context)
{
    commandlist_t *t;
    void *sieve_scan = context->sieve_scan;
    YY_BUFFER_STATE buf = libsieve_sieve_scan_string(context->script.script, sieve_scan);
    if (libsieve_sieveparse(context, sieve_scan)) {
	return NULL;
    } else {
	libsieve_sieve_delete_buffer(buf, sieve_scan);
	t = context->sieve_ret;
	context->sieve_ret = NULL;
	return t;
    }
}

int libsieve_sieveerror(struct sieve2_context *context, void* yyscanner, const char *msg)
{
    context->parse_errors++;

    libsieve_do_error_parse(context, libsieve_sieveget_lineno(context->sieve_scan), msg);

    return 0;
}

static test_t *static_build_address(struct sieve2_context *context, int t,
			struct aetags *ae, stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be either ADDRESS or ENVELOPE */

    libsieve_assert((t == ADDRESS) || (t == ENVELOPE));

    if (ret) {
	ret->u.ae.comptag = ae->comptag;
	ret->u.ae.comp = libsieve_comparator_lookup(context, ae->comparator, ae->comptag);
	ret->u.ae.sl = sl;
	ret->u.ae.pl = pl;
	ret->u.ae.addrpart = ae->addrtag;
	static_free_aetags(ae);
	if (ret->u.ae.comp == NULL) {
	    libsieve_free_test(ret);
	    ret = NULL;
	}
    }
    return ret;
}

static test_t *static_build_header(struct sieve2_context *context, int t, struct htags *h, stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be HEADER */

    libsieve_assert(t == HEADER);

    if (ret) {
	ret->u.h.comptag = h->comptag;
	ret->u.h.comp = libsieve_comparator_lookup(context, h->comparator, h->comptag);
	ret->u.h.sl = sl;
	ret->u.h.pl = pl;
	static_free_htags(h);
	if (ret->u.h.comp == NULL) {
	    libsieve_free_test(ret);
	    ret = NULL;
	}
    }
    return ret;
}

static commandlist_t *static_build_vacation(struct sieve2_context *context, int t, struct vtags *v, char *reason)
{
    commandlist_t *ret = libsieve_new_command(t);

    libsieve_assert(t == VACATION);

    if (ret) {
	ret->u.v.subject = v->subject; v->subject = NULL;
	ret->u.v.handle = v->handle; v->handle = NULL;
	ret->u.v.from = v->from; v->from = NULL;
	ret->u.v.days = v->days;
	ret->u.v.mime = v->mime;
	ret->u.v.addresses = v->addresses; v->addresses = NULL;
	static_free_vtags(v);
	ret->u.v.message = reason;
    }
    return ret;
}

static commandlist_t *static_build_notify(struct sieve2_context *context, int t, struct ntags *n)
{
    commandlist_t *ret = libsieve_new_command(t);

    libsieve_assert(t == NOTIFY);

    if (ret) {
	ret->u.n.method = n->method; n->method = NULL;
	ret->u.n.id = n->id; n->id = NULL;
	ret->u.n.options = n->options; n->options = NULL;
	ret->u.n.priority = n->priority;
	ret->u.n.message = n->message; n->message = NULL;
	static_free_ntags(n);
    }
    return ret;
}

// FIXME: I think we just test and return true or false... check around.
static commandlist_t *static_build_validnotif(struct sieve2_context *context, int t, stringlist_t *sl)
{
    commandlist_t *ret = libsieve_new_command(t);

    libsieve_assert(t == VALIDNOTIF);

/*
    if (ret) {
	ret->u.d.comptag = d->comptag;
	ret->u.d.comp = libsieve_comparator_lookup(context, "i;ascii-casemap", d->comptag);
	ret->u.d.pattern = d->pattern; d->pattern = NULL;
	ret->u.d.priority = d->priority;
	static_free_dtags(d);
    }*/
    return ret;
}

static struct hftags *static_new_hftags(void)
{
    struct hftags *r = (struct hftags *) libsieve_malloc(sizeof(struct hftags));

    r->comptag = -1;
    r->comparator = NULL;

    return r;
}

static struct aetags *static_new_aetags(void)
{
    struct aetags *r = (struct aetags *) libsieve_malloc(sizeof(struct aetags));

    r->addrtag = r->comptag = -1;
    r->comparator = NULL;

    return r;
}

static struct aetags *static_canon_aetags(struct aetags *ae)
{
    char *map = "i;ascii-casemap";
    if (ae->addrtag == -1) { ae->addrtag = ALL; }
    if (ae->comparator == NULL) { ae->comparator = libsieve_strdup(map); }
    if (ae->comptag == -1) { ae->comptag = IS; }
    return ae;
}

static void static_free_aetags(struct aetags *ae)
{
    libsieve_free(ae->comparator);
    libsieve_free(ae);
}

static struct htags *static_new_htags(void)
{
    struct htags *r = (struct htags *) libsieve_malloc(sizeof(struct htags));

    r->comptag = -1;
    r->comparator = NULL;

    return r;
}

static struct htags *static_canon_htags(struct htags *h)
{
    char *map = "i;ascii-casemap";
    if (h->comparator == NULL) { h->comparator = libsieve_strdup(map); }
    if (h->comptag == -1) { h->comptag = IS; }
    return h;
}

static void static_free_htags(struct htags *h)
{
    libsieve_free(h->comparator);
    libsieve_free(h);
}

static struct vtags *static_new_vtags(void)
{
    struct vtags *r = (struct vtags *) libsieve_malloc(sizeof(struct vtags));

    r->days = -1;
    r->addresses = NULL;
    r->subject = NULL;
    r->handle = NULL;
    r->from = NULL;
    r->mime = -1;

    return r;
}

static struct vtags *static_canon_vtags(struct vtags *v)
{
/* TODO: Change this to an *in*sane default, and specify that the
 * client app has to check for boundaries.  That would be much
 * simpler than having a context registration for something that
 * the user cannot test/check for at all.
 */

    if (v->days == -1) { v->days = 7; }
    if (v->mime == -1) { v->mime = 0; }

    return v;
}

static void static_free_vtags(struct vtags *v)
{
    if (v->addresses) { libsieve_free_sl(v->addresses); }
    libsieve_free(v->subject);
    libsieve_free(v->handle);
    libsieve_free(v->from);
    libsieve_free(v);
}

static struct ntags *static_new_ntags(void)
{
    struct ntags *r = (struct ntags *) libsieve_malloc(sizeof(struct ntags));

    r->method = NULL;
    r->id = NULL;
    r->options = NULL;
    r->priority = NULL;
    r->message = NULL;

    return r;
}

static struct ntags *static_canon_ntags(struct ntags *n)
{
    char *from = "$from$: $subject$";
    if (n->priority == NULL) { n->priority = "normal"; }
    if (n->message == NULL) { n->message = libsieve_strdup(from); }

    return n;
}

static void static_free_ntags(struct ntags *n)
{
    libsieve_free(n->method);
    libsieve_free(n->id);
    if (n->options) libsieve_free_sl(n->options);
    libsieve_free(n->message);
    libsieve_free(n);
}

static int static_verify_stringlist(struct sieve2_context *context, stringlist_t *sl, int (*verify)(struct sieve2_context*, const char *))
{
    for (; sl != NULL && verify(context, sl->s); sl = sl->next) ;
    return (sl == NULL);
}

static int static_verify_flag(struct sieve2_context *context, const char *s)
{
    /* xxx if not a flag, call sieveerror */
    return 1;
}

static int static_verify_address(struct sieve2_context *context, const char *s)
{
    struct address *addr = NULL;

    addr = libsieve_addr_parse_buffer(context, &addr, &s);
    if (addr == NULL) {
        return 0;
    }
    libsieve_addrstructfree(context, addr, CHARSALSO);
    return 1;
}

static int static_verify_mailbox(const char *s UNUSED)
{
    /* xxx if not a mailbox, call sieveerror */
    return 1;
}

static int static_verify_header(struct sieve2_context *context, const char *hdr)
{
    const char *h = hdr;
    char *err;

    while (*h) {
	/* field-name      =       1*ftext
	   ftext           =       %d33-57 / %d59-126         
	   ; Any character except
	   ;  controls, SP, and
	   ;  ":". */
	if (!((*h >= 33 && *h <= 57) || (*h >= 59 && *h <= 126))) {
	    err = libsieve_strconcat("header '", hdr, "': not a valid header", NULL);
	    libsieve_sieveerror(context, context->sieve_scan, err);
	    libsieve_free(err);
	    return 0;
	}
	h++;
    }
    return 1;
}
 
/* Was this supposed to be modifying its argument?! */
/*
static int static_verify_flag(const char *flag)
{
    int ret;
    char *f, *err;

    // Make ourselves a local copy to change the case
    f = libsieve_strdup(flag);
 
    if (f[0] == '\\') {
	libsieve_strtolower(f,strlen(f));
	if (strcmp(f, "\\\\seen") && strcmp(f, "\\\\answered") &&
	    strcmp(f, "\\\\flagged") && strcmp(f, "\\\\draft") &&
	    strcmp(f, "\\\\deleted")) {
            err = libsieve_strconcat("flag '", f, "': not a system flag", NULL);
	    libsieve_sieveerror(err);
	    libsieve_free(err);
	    ret = 0;
	}
	ret = 1;
    }
    else if (!libsieve_strisatom(f,strlen(f))) {
	err = libsieve_strconcat("flag '", f, "': not a valid keyword", NULL);
	libsieve_sieveerror(err);
	libsieve_free(err);
	ret = 0;
    }
    ret = 1;

    libsieve_free(f);
    return ret;
}
*/

static regex_t *static_verify_regex(struct sieve2_context *context, const char *s, int cflags)
{
    int ret;
    char errbuf[100];
    regex_t *reg = (regex_t *) libsieve_malloc(sizeof(regex_t));

    if ((ret = libsieve_regcomp(reg, s, cflags)) != 0) {
	(void) libsieve_regerror(ret, reg, errbuf, sizeof(errbuf));
	libsieve_sieveerror(context, context->sieve_scan, errbuf);
	libsieve_free(reg);
	return NULL;
    }
    return reg;
}

static patternlist_t *static_verify_regexs(struct sieve2_context *context, stringlist_t *sl, char *comp)
{
    stringlist_t *sl2;
    patternlist_t *pl = NULL;
    int cflags = REG_EXTENDED | REG_NOSUB;
    regex_t *reg;

    if (!strcmp(comp, "i;ascii-casemap")) {
	cflags |= REG_ICASE;
    }

    for (sl2 = sl; sl2 != NULL; sl2 = sl2->next) {
        if ((reg = static_verify_regex(context, sl2->s, cflags)) == NULL) {
	    libsieve_free_pl(pl, REGEX);
	    break;
	}
	pl = libsieve_new_pl(reg, pl);
    }
    if (sl2 == NULL) {
	libsieve_free_sl(sl);
	return pl;
    }
    return NULL;
}

/* xxx is it ok to put this in an RFC822 header body? */
static int static_ok_header(char *s UNUSED)
{
    return 1;
}

/* Checks if interpreter supports specified action
 * */
static int static_check_reqs(struct sieve2_context *c, char *req)
{
    if (0 == strcmp("fileinto", req)) {
        return c->require.fileinto = c->support.fileinto;
    } else if (0 == strcmp("reject", req)) {
        return c->require.reject = c->support.reject;
    } else if (!strcmp("envelope", req)) {
        return c->require.envelope = c->support.envelope;
    } else if (!strcmp("vacation", req)) {
        return c->require.vacation = c->support.vacation;
    } else if (!strcmp("notify",req)) {
        return c->require.notify = c->support.notify;
    } else if (!strcmp("subaddress", req)) {
	return c->require.subaddress = c->support.subaddress;
    /* imap4flags is built into the parser. */
    } else if (!strcmp("imap4flags", req)) {
        return c->require.imap4flags = 1;
    /* regex is built into the parser. */
    } else if (!strcmp("regex", req)) {
	return c->require.regex = 1;
    /* relational is built into the parser. */
    } else if (!strcmp("relational", req)) {
	return c->require.relational = 1;
    /* These comparators are built into the parser. */
    } else if (!strcmp("comparator-i;octet", req)) {
	return 1;
    } else if (!strcmp("comparator-i;ascii-casemap", req)) {
	return 1;
    } else if (!strcmp("comparator-i;ascii-numeric", req)) {
	return 1;
    }
    /* If we don't recognize it, then we don't support it! */
    return 0;
}
