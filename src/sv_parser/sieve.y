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
#include <assert.h>
#include <string.h>
#include <ctype.h>

/* sv_parser */
#include "comparator.h"
#include "sieveinc.h"
#include "addrinc.h"

/* sv_interface */
#include "interp.h"
#include "script.h"
#include "tree.h"

/* sv_util */
#include "util.h"

extern int libsieve_sieveerror(char *msg);
extern int libsieve_sievelex(void);

#define YYERROR_VERBOSE /* i want better error messages! */
%}

%name-prefix="libsieve_sieve"

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
    struct ntags *ntag;
    struct dtags *dtag;
}

%token <nval> NUMBER
%token <sval> STRING
%token IF ELSIF ELSE
%token REJCT FILEINTO REDIRECT KEEP STOP DISCARD VACATION REQUIRE
%token SETFLAG ADDFLAG REMOVEFLAG MARK UNMARK
%token NOTIFY DENOTIFY
%token ANYOF ALLOF EXISTS SFALSE STRUE HEADER NOT SIZE ADDRESS ENVELOPE
%token COMPARATOR IS CONTAINS MATCHES REGEX OVER UNDER
%token ALL LOCALPART DOMAIN USER DETAIL
%token DAYS ADDRESSES SUBJECT MIME
%token METHOD ID OPTIONS LOW NORMAL HIGH MESSAGE

%type <cl> commands command action elsif block
%type <sl> stringlist strings
%type <test> test
%type <nval> comptag sizetag addrparttag addrorenv
%type <testl> testlist tests
%type <htag> htags
%type <aetag> aetags
%type <vtag> vtags
%type <ntag> ntags
%type <dtag> dtags
%type <sval> priority

%%

start: /* empty */		{ ret = NULL; }
	| reqs commands		{ ret = $2; }
	;

reqs: /* empty */
	| require reqs
	;

require: REQUIRE stringlist ';'	{ if (!static_check_reqs($2)) {
                                    libsieve_sieveerror("unsupported feature");
				    YYERROR; 
                                  } }
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

action: REJCT STRING             { if (!parse_script->support.reject) {
				     libsieve_sieveerror("reject not required");
				     YYERROR;
				   }
				   $$ = libsieve_new_command(REJCT); $$->u.str = $2; }
	| FILEINTO STRING	 { if (!parse_script->support.fileinto) {
				     libsieve_sieveerror("fileinto not required");
	                             YYERROR;
                                   }
				   if (!static_verify_mailbox($2)) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           $$ = libsieve_new_command(FILEINTO);
				   $$->u.str = $2; }
	| REDIRECT STRING         { $$ = libsieve_new_command(REDIRECT);
				   if (!static_verify_address($2)) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   $$->u.str = $2; }
	| KEEP			 { $$ = libsieve_new_command(KEEP); }
	| STOP			 { $$ = libsieve_new_command(STOP); }
	| DISCARD		 { $$ = libsieve_new_command(DISCARD); }
	| VACATION vtags STRING  { if (!parse_script->support.vacation) {
				     libsieve_sieveerror("vacation not required");
				     $$ = libsieve_new_command(VACATION);
				     YYERROR;
				   } else {
  				     $$ = static_build_vacation(VACATION,
					    static_canon_vtags($2), $3);
				   } }
        | SETFLAG stringlist     { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                   }
                                  if (!static_verify_stringlist($2, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  $$ = libsieve_new_command(SETFLAG);
                                  $$->u.sl = $2; }
         | ADDFLAG stringlist     { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist($2, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  $$ = libsieve_new_command(ADDFLAG);
                                  $$->u.sl = $2; }
         | REMOVEFLAG stringlist  { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist($2, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  $$ = libsieve_new_command(REMOVEFLAG);
                                  $$->u.sl = $2; }
         | MARK                   { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  $$ = libsieve_new_command(MARK); }
         | UNMARK                 { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  $$ = libsieve_new_command(UNMARK); }

         | NOTIFY ntags           { if (!parse_script->support.notify) {
				       libsieve_sieveerror("notify not required");
				       $$ = libsieve_new_command(NOTIFY); 
				       YYERROR;
	 			    } else {
				      $$ = static_build_notify(NOTIFY,
				             static_canon_ntags($2));
				    } }
         | DENOTIFY dtags         { if (!parse_script->support.notify) {
                                       libsieve_sieveerror("notify not required");
				       $$ = libsieve_new_command(DENOTIFY);
				       YYERROR;
				    } else {
					$$ = static_build_denotify(DENOTIFY, $2);
				    } }
	;

ntags: /* empty */		 { $$ = static_new_ntags(); }
	| ntags ID STRING	 { if ($$->id != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { $$->id = $3; } }
	| ntags METHOD STRING	 { if ($$->method != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { $$->method = $3; } }
	| ntags OPTIONS stringlist { if ($$->options != NULL) { 
					libsieve_sieveerror("duplicate :options"); YYERROR; }
				     else { $$->options = $3; } }
	| ntags priority	 { if ($$->priority != NULL) { 
					libsieve_sieveerror("duplicate :priority"); YYERROR; }
				   else { $$->priority = $2; } }
	| ntags MESSAGE STRING	 { if ($$->message != NULL) { 
					libsieve_sieveerror("duplicate :message"); YYERROR; }
				   else { $$->message = $3; } }
	;

dtags: /* empty */		 { $$ = static_new_dtags(); }
	| dtags priority	 { if ($$->priority != NULL) { 
				libsieve_sieveerror("duplicate priority level"); YYERROR; }
				   else { $$->priority = $2; } }
	| dtags comptag STRING 	 { if ($$->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR;
				   } else {
				       $$->comptag = $2;
#ifdef ENABLE_REGEX
				       if ($$->comptag == REGEX) {
					   int cflags = REG_EXTENDED |
					       REG_NOSUB | REG_ICASE;
					   $$->pattern =
					       (void*) verify_regex($3, cflags);
					   if (!$$->pattern) { YYERROR; }
				       }
				       else
#endif
					   $$->pattern = $3;
				   } }
	;

priority: LOW    { $$ = "low"; }
        | NORMAL { $$ = "normal"; }
        | HIGH   { $$ = "high"; }
        ;

vtags: /* empty */		 { $$ = static_new_vtags(); }
	| vtags DAYS NUMBER	 { if ($$->days != -1) { 
					libsieve_sieveerror("duplicate :days"); YYERROR; }
				   else { $$->days = $3; } }
	| vtags ADDRESSES stringlist { if ($$->addresses != NULL) { 
					libsieve_sieveerror("duplicate :addresses"); 
					YYERROR;
				       } else if (!static_verify_stringlist($3,
							static_verify_address)) {
					  YYERROR;
				       } else {
					 $$->addresses = $3; } }
	| vtags SUBJECT STRING	 { if ($$->subject != NULL) { 
					libsieve_sieveerror("duplicate :subject"); 
					YYERROR;
				   } else if (!static_ok_header($3)) {
					YYERROR;
				   } else { $$->subject = $3; } }
	| vtags MIME		 { if ($$->mime != -1) { 
					libsieve_sieveerror("duplicate :mime"); 
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
	| HEADER htags stringlist stringlist
				 { patternlist_t *pl;
                                   if (!static_verify_stringlist($3, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   $2 = static_canon_htags($2);
#ifdef ENABLE_REGEX
				   if ($2->comptag == REGEX) {
				     pl = verify_regexs($4, $2->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) $4;
				       
				   $$ = static_build_header(HEADER, $2, $3, pl);
				   if ($$ == NULL) { YYERROR; } }
	| addrorenv aetags stringlist stringlist
				 { patternlist_t *pl;
                                   if (!static_verify_stringlist($3, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   $2 = static_canon_aetags($2);
#ifdef ENABLE_REGEX
				   if ($2->comptag == REGEX) {
				     pl = verify_regexs($4, $2->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) $4;
				       
				   $$ = static_build_address($1, $2, $3, pl);
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
			libsieve_sieveerror("duplicate or conflicting address part tag");
			YYERROR; }
				   else { $$->addrtag = $2; } }
	| aetags comptag         { $$ = $1;
				   if ($$->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { $$->comptag = $2; } }
	| aetags COMPARATOR STRING { $$ = $1;
				   if ($$->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag"); YYERROR; }
				   else { $$->comparator = $3; } }
	;

htags: /* empty */		 { $$ = static_new_htags(); }
	| htags comptag		 { $$ = $1;
				   if ($$->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { $$->comptag = $2; } }
	| htags COMPARATOR STRING { $$ = $1;
				   if ($$->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag");
					YYERROR; }
				   else { $$->comparator = $3; } }
	;

addrparttag: ALL                 { $$ = ALL; }
	| LOCALPART		 { $$ = LOCALPART; }
	| DOMAIN                 { $$ = DOMAIN; }
	| USER                   { if (!parse_script->support.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   $$ = USER; }
	| DETAIL                { if (!parse_script->support.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   $$ = DETAIL; }
	;

comptag: IS			 { $$ = IS; }
	| CONTAINS		 { $$ = CONTAINS; }
	| MATCHES		 { $$ = MATCHES; }
	| REGEX			 { if (!parse_script->support.regex) {
				     libsieve_sieveerror("regex not required");
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

char *libsieve_sieveptr;         /* pointer to sieve string for address lexer */
char *libsieve_sieveerr;         /* buffer for sieve parser error messages */

commandlist_t *libsieve_sieve_parse_buffer(sieve_script_t *script, char *b)
{
    commandlist_t *t;

    parse_script = script;

    libsieve_sieveptr = b;
    libsieve_sieveerr = NULL;

    /* These are being moved all the way up to script[2].c */
    // addrlexalloc();
    // sievelexalloc();
    if (libsieve_sieveparse()) {
    /*
        err = libsieve_strconcat("address '", s, "': ", addrerr, NULL);
        sieveerror(err);
        libsieve_free(addrerr);
        libsieve_free(err);
    */
        t = NULL;
    } else {
        t = ret;
    }

    /* Free both lexers */
    /* These are being moved all the way up to script[2].c */
    // sievelexfree();
    // addrlexfree();
    ret = NULL;
    return t;
}

commandlist_t *libsieve_sieve_parse(sieve_script_t *script, FILE *f)
{
    commandlist_t *t;
    size_t f_pos = 0, f_len = 0;
    char *f_buf;
    char *tmp_buf;

    f_buf = NULL; // If null, realloc() behaves as malloc()
    while(!feof(f)) {
        if( f_pos + 1 >= f_len ) {
            tmp_buf = libsieve_realloc(f_buf, sizeof(char) * (f_len+=200));
            if( tmp_buf )
    	        f_buf = tmp_buf;
            else
                // Value may need tweaking to match commandlist_t
                return 0;
        }
        f_buf[f_pos] = fgetc(f);
        f_pos++;
    }
    // This is safe because of the f_pos + 1 above
    f_buf[f_pos] = '\0';

   t = libsieve_sieve_parse_buffer(script, f_buf);
   libsieve_free(f_buf);

   return t;
}

int libsieve_sieveerror(char *msg)
{
    extern int libsieve_sievelineno;
    char *tmperr;
    int ret;

    parse_script->err++;
    /* We're in the Sieve 1 API */
    if (parse_script->interp.err) {
	ret = parse_script->interp.err(libsieve_sievelineno, msg, 
				       parse_script->interp.interp_context,
				       parse_script->script_context);
    } else {
    /* We're in the Sieve 2 API */
        if( libsieve_sieveerr )
            tmperr = libsieve_strconcat(libsieve_sieveerr, ", ", msg, NULL);
        else
            tmperr = libsieve_strconcat(msg, NULL);
        if( tmperr )
            libsieve_sieveerr = libsieve_strdup(tmperr, strlen(tmperr));
        libsieve_free(tmperr);
    }

    return 0;
}

static int static_check_reqs(stringlist_t *sl)
{
    int i = 1;
    stringlist_t *s;
    
    while (sl != NULL) {
	s = sl;
	sl = sl->next;

	i &= script_require(parse_script, s->s);

	libsieve_free(s->s);
	libsieve_free(s);
    }
    return i;
}

static test_t *static_build_address(int t, struct aetags *ae,
			     stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be either ADDRESS or ENVELOPE */

    assert((t == ADDRESS) || (t == ENVELOPE));

    if (ret) {
	ret->u.ae.comptag = ae->comptag;
	ret->u.ae.comp = libsieve_comparator_lookup(ae->comparator, ae->comptag);
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

static test_t *static_build_header(int t, struct htags *h,
			    stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be HEADER */

    assert(t == HEADER);

    if (ret) {
	ret->u.h.comptag = h->comptag;
	ret->u.h.comp = libsieve_comparator_lookup(h->comparator, h->comptag);
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

static commandlist_t *static_build_vacation(int t, struct vtags *v, char *reason)
{
    commandlist_t *ret = libsieve_new_command(t);

    assert(t == VACATION);

    if (ret) {
	ret->u.v.subject = v->subject; v->subject = NULL;
	ret->u.v.days = v->days;
	ret->u.v.mime = v->mime;
	ret->u.v.addresses = v->addresses; v->addresses = NULL;
	static_free_vtags(v);
	ret->u.v.message = reason;
    }
    return ret;
}

static commandlist_t *static_build_notify(int t, struct ntags *n)
{
    commandlist_t *ret = libsieve_new_command(t);

    assert(t == NOTIFY);

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

static commandlist_t *static_build_denotify(int t, struct dtags *d)
{
    commandlist_t *ret = libsieve_new_command(t);

    assert(t == DENOTIFY);

    if (ret) {
	ret->u.d.comptag = d->comptag;
	ret->u.d.comp = libsieve_comparator_lookup("i;ascii-casemap", d->comptag);
	ret->u.d.pattern = d->pattern; d->pattern = NULL;
	ret->u.d.priority = d->priority;
	static_free_dtags(d);
    }
    return ret;
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
    if (ae->comparator == NULL) { ae->comparator = libsieve_strdup(map, strlen(map)); }
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
    if (h->comparator == NULL) { h->comparator = libsieve_strdup(map, strlen(map)); }
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
    r->mime = -1;

    return r;
}

static struct vtags *static_canon_vtags(struct vtags *v)
{
    assert(parse_script->interp.vacation != NULL);

    if (v->days == -1) { v->days = 7; }
    if (v->days < parse_script->interp.vacation->min_response) 
       { v->days = parse_script->interp.vacation->min_response; }
    if (v->days > parse_script->interp.vacation->max_response)
       { v->days = parse_script->interp.vacation->max_response; }
    if (v->mime == -1) { v->mime = 0; }

    return v;
}

static void static_free_vtags(struct vtags *v)
{
    if (v->addresses) { libsieve_free_sl(v->addresses); }
    libsieve_free(v->subject);
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
    if (n->message == NULL) { n->message = libsieve_strdup(from, strlen(from)); }

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

static struct dtags *static_new_dtags(void)
{
    struct dtags *r = (struct dtags *) libsieve_malloc(sizeof(struct dtags));

    r->comptag = -1;
    r->pattern = NULL;
    r->priority = NULL;

    return r;
}

static void static_free_dtags(struct dtags *d)
{
    libsieve_free(d->pattern);
    libsieve_free(d);
}

static int static_verify_stringlist(stringlist_t *sl, int (*verify)(const char *))
{
    for (; sl != NULL && verify(sl->s); sl = sl->next) ;
    return (sl == NULL);
}

char *addrptr;		/* pointer to sieve string for address lexer */
char *addrerr;		/* buffer for sieve parser error messages */

static int static_verify_address(const char *s)
{
    char *aerr = NULL;
    char *serr = NULL;
    struct address *addr = NULL;

    addr = libsieve_addr_parse_buffer(&addr, &s, &aerr);
    if (addr == NULL) {
        serr = libsieve_strconcat("address '", s, "': ", aerr, NULL);
        libsieve_sieveerror(serr);
        libsieve_free(serr);
        libsieve_free(aerr);
        return 0;
    }
    libsieve_addrstructfree(addr, CHARSALSO);
    return 1;
}

static int static_verify_mailbox(const char *s __attribute__((unused)))
{
    /* xxx if not a mailbox, call sieveerror */
    return 1;
}

static int static_verify_header(const char *hdr)
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
	    libsieve_sieveerror(err);
	    libsieve_free(err);
	    return 0;
	}
	h++;
    }
    return 1;
}
 
/* Was this supposed to be modifying its argument?! */
static int static_verify_flag(const char *flag)
{
    int ret;
    char *f, *err;

    /* Make ourselves a local copy to change the case */
    f = libsieve_strdup(flag, strlen(flag));
 
    if (f[0] == '\\') {
	libsieve_strtolower(f,strlen(f));
	if (strcmp(f, "\\seen") && strcmp(f, "\\answered") &&
	    strcmp(f, "\\flagged") && strcmp(f, "\\draft") &&
	    strcmp(f, "\\deleted")) {
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
 
#ifdef ENABLE_REGEX
static regex_t *static_verify_regex(const char *s, int cflags)
{
    int ret;
    char errbuf[100];
    regex_t *reg = (regex_t *) libsieve_malloc(sizeof(regex_t));

    if ((ret = regcomp(reg, s, cflags)) != 0) {
	(void) regerror(ret, reg, errbuf, sizeof(errbuf));
	libsieve_sieveerror(errbuf);
	libsieve_free(reg);
	return NULL;
    }
    return reg;
}

static patternlist_t *static_verify_regexs(stringlist_t *sl, char *comp)
{
    stringlist_t *sl2;
    patternlist_t *pl = NULL;
    int cflags = REG_EXTENDED | REG_NOSUB;
    regex_t *reg;

    if (!strcmp(comp, "i;ascii-casemap")) {
	cflags |= REG_ICASE;
    }

    for (sl2 = sl; sl2 != NULL; sl2 = sl2->next) {
	if ((reg = verify_regex(sl2->s, cflags)) == NULL) {
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
#endif

/* xxx is it ok to put this in an RFC822 header body? */
static int static_ok_header(char *s __attribute__((unused)))
{
    return 1;
}
