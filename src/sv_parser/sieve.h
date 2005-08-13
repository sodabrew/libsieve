/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     STRING = 259,
     IF = 260,
     ELSIF = 261,
     ELSE = 262,
     REJCT = 263,
     FILEINTO = 264,
     REDIRECT = 265,
     KEEP = 266,
     STOP = 267,
     DISCARD = 268,
     VACATION = 269,
     REQUIRE = 270,
     SETFLAG = 271,
     ADDFLAG = 272,
     REMOVEFLAG = 273,
     MARK = 274,
     UNMARK = 275,
     NOTIFY = 276,
     DENOTIFY = 277,
     ANYOF = 278,
     ALLOF = 279,
     EXISTS = 280,
     SFALSE = 281,
     STRUE = 282,
     HEADER = 283,
     NOT = 284,
     SIZE = 285,
     ADDRESS = 286,
     ENVELOPE = 287,
     COMPARATOR = 288,
     IS = 289,
     CONTAINS = 290,
     MATCHES = 291,
     REGEX = 292,
     OVER = 293,
     UNDER = 294,
     ALL = 295,
     LOCALPART = 296,
     DOMAIN = 297,
     USER = 298,
     DETAIL = 299,
     DAYS = 300,
     ADDRESSES = 301,
     SUBJECT = 302,
     MIME = 303,
     METHOD = 304,
     ID = 305,
     OPTIONS = 306,
     LOW = 307,
     NORMAL = 308,
     HIGH = 309,
     MESSAGE = 310
   };
#endif
#define NUMBER 258
#define STRING 259
#define IF 260
#define ELSIF 261
#define ELSE 262
#define REJCT 263
#define FILEINTO 264
#define REDIRECT 265
#define KEEP 266
#define STOP 267
#define DISCARD 268
#define VACATION 269
#define REQUIRE 270
#define SETFLAG 271
#define ADDFLAG 272
#define REMOVEFLAG 273
#define MARK 274
#define UNMARK 275
#define NOTIFY 276
#define DENOTIFY 277
#define ANYOF 278
#define ALLOF 279
#define EXISTS 280
#define SFALSE 281
#define STRUE 282
#define HEADER 283
#define NOT 284
#define SIZE 285
#define ADDRESS 286
#define ENVELOPE 287
#define COMPARATOR 288
#define IS 289
#define CONTAINS 290
#define MATCHES 291
#define REGEX 292
#define OVER 293
#define UNDER 294
#define ALL 295
#define LOCALPART 296
#define DOMAIN 297
#define USER 298
#define DETAIL 299
#define DAYS 300
#define ADDRESSES 301
#define SUBJECT 302
#define MIME 303
#define METHOD 304
#define ID 305
#define OPTIONS 306
#define LOW 307
#define NORMAL 308
#define HIGH 309
#define MESSAGE 310




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 62 "sieve.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1285 of yacc.c.  */
#line 161 "sieve.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE libsieve_sievelval;



