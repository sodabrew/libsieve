/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

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
     FLAGS = 276,
     HASFLAG = 277,
     NOTIFY = 278,
     VALIDNOTIF = 279,
     IMPORTANCE = 280,
     ANYOF = 281,
     ALLOF = 282,
     EXISTS = 283,
     SFALSE = 284,
     STRUE = 285,
     HEADER = 286,
     NOT = 287,
     SIZE = 288,
     ADDRESS = 289,
     ENVELOPE = 290,
     COMPARATOR = 291,
     IS = 292,
     CONTAINS = 293,
     MATCHES = 294,
     REGEX = 295,
     OVER = 296,
     UNDER = 297,
     COUNT = 298,
     VALUE = 299,
     ALL = 300,
     LOCALPART = 301,
     DOMAIN = 302,
     USER = 303,
     DETAIL = 304,
     DAYS = 305,
     ADDRESSES = 306,
     SUBJECT = 307,
     MIME = 308,
     FROM = 309,
     HANDLE = 310,
     METHOD = 311,
     ID = 312,
     OPTIONS = 313,
     LOW = 314,
     NORMAL = 315,
     HIGH = 316,
     MESSAGE = 317
   };
#endif
/* Tokens.  */
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
#define FLAGS 276
#define HASFLAG 277
#define NOTIFY 278
#define VALIDNOTIF 279
#define IMPORTANCE 280
#define ANYOF 281
#define ALLOF 282
#define EXISTS 283
#define SFALSE 284
#define STRUE 285
#define HEADER 286
#define NOT 287
#define SIZE 288
#define ADDRESS 289
#define ENVELOPE 290
#define COMPARATOR 291
#define IS 292
#define CONTAINS 293
#define MATCHES 294
#define REGEX 295
#define OVER 296
#define UNDER 297
#define COUNT 298
#define VALUE 299
#define ALL 300
#define LOCALPART 301
#define DOMAIN 302
#define USER 303
#define DETAIL 304
#define DAYS 305
#define ADDRESSES 306
#define SUBJECT 307
#define MIME 308
#define FROM 309
#define HANDLE 310
#define METHOD 311
#define ID 312
#define OPTIONS 313
#define LOW 314
#define NORMAL 315
#define HIGH 316
#define MESSAGE 317




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "sieve.y"
{
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
/* Line 1489 of yacc.c.  */
#line 187 "sieve.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE libsieve_sievelval;

