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
     ANYOF = 280,
     ALLOF = 281,
     EXISTS = 282,
     SFALSE = 283,
     STRUE = 284,
     HEADER = 285,
     NOT = 286,
     SIZE = 287,
     ADDRESS = 288,
     ENVELOPE = 289,
     COMPARATOR = 290,
     IS = 291,
     CONTAINS = 292,
     MATCHES = 293,
     REGEX = 294,
     OVER = 295,
     UNDER = 296,
     COUNT = 297,
     VALUE = 298,
     ALL = 299,
     LOCALPART = 300,
     DOMAIN = 301,
     USER = 302,
     DETAIL = 303,
     DAYS = 304,
     ADDRESSES = 305,
     SUBJECT = 306,
     MIME = 307,
     FROM = 308,
     HANDLE = 309,
     METHOD = 310,
     IMPORTANCE = 311,
     OPTIONS = 312,
     LOW = 313,
     NORMAL = 314,
     HIGH = 315,
     MESSAGE = 316
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
#define ANYOF 280
#define ALLOF 281
#define EXISTS 282
#define SFALSE 283
#define STRUE 284
#define HEADER 285
#define NOT 286
#define SIZE 287
#define ADDRESS 288
#define ENVELOPE 289
#define COMPARATOR 290
#define IS 291
#define CONTAINS 292
#define MATCHES 293
#define REGEX 294
#define OVER 295
#define UNDER 296
#define COUNT 297
#define VALUE 298
#define ALL 299
#define LOCALPART 300
#define DOMAIN 301
#define USER 302
#define DETAIL 303
#define DAYS 304
#define ADDRESSES 305
#define SUBJECT 306
#define MIME 307
#define FROM 308
#define HANDLE 309
#define METHOD 310
#define IMPORTANCE 311
#define OPTIONS 312
#define LOW 313
#define NORMAL 314
#define HIGH 315
#define MESSAGE 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 67 "sieve.y"
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
#line 185 "sieve.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE libsieve_sievelval;

