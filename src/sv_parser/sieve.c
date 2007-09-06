/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse libsieve_sieveparse
#define yylex   libsieve_sievelex
#define yyerror libsieve_sieveerror
#define yylval  libsieve_sievelval
#define yychar  libsieve_sievechar
#define yydebug libsieve_sievedebug
#define yynerrs libsieve_sievenerrs


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




/* Copy the first part of user declarations.  */
#line 1 "sieve.y"

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
#include "regex.h"

/* sv_parser */
#include "comparator.h"
#include "sieveinc.h"
#include "addrinc.h"

/* sv_interface */
#include "callbacks2.h"
#include "script.h"
#include "tree.h"

/* sv_util */
#include "util.h"

#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT context

/* Better yacc error messages please */
#define YYERROR_VERBOSE

struct sieve2_context *libsieve_parse_context;
extern int libsieve_sieveerror(struct sieve2_context *context, char *msg);
extern int libsieve_sievelex(void);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 68 "sieve.y"
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
/* Line 187 of yacc.c.  */
#line 304 "sieve.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 317 "sieve.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      68,    69,     2,     2,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    62,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    64,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    11,    15,    17,    20,
      23,    28,    31,    32,    37,    40,    43,    47,    49,    54,
      57,    60,    62,    64,    68,    71,    74,    77,    80,    83,
      84,    88,    92,    96,   100,   103,   104,   107,   111,   112,
     116,   120,   124,   128,   132,   135,   139,   141,   143,   147,
     151,   154,   157,   160,   163,   165,   167,   171,   176,   181,
     184,   188,   190,   192,   194,   195,   198,   201,   205,   206,
     209,   213,   215,   217,   219,   221,   223,   225,   228,   231,
     233,   235,   237,   239,   241,   245,   247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      71,     0,    -1,    -1,    72,    74,    -1,    -1,    73,    72,
      -1,    15,    81,    62,    -1,    75,    -1,    74,    75,    -1,
      77,    62,    -1,     5,    84,    83,    76,    -1,     1,    62,
      -1,    -1,     6,    84,    83,    76,    -1,     7,    83,    -1,
       8,     4,    -1,    11,    21,    81,    -1,    11,    -1,     9,
      21,    81,     4,    -1,     9,     4,    -1,    10,     4,    -1,
      12,    -1,    13,    -1,    14,    80,     4,    -1,    16,    81,
      -1,    17,    81,    -1,    18,    81,    -1,    23,    78,    -1,
      24,    81,    -1,    -1,    78,    57,    81,    -1,    78,    56,
       3,    -1,    78,    61,     4,    -1,    78,    55,     4,    -1,
      78,     4,    -1,    -1,    79,    89,    -1,    79,    35,     4,
      -1,    -1,    80,    49,     3,    -1,    80,    50,    81,    -1,
      80,    51,     4,    -1,    80,    54,     4,    -1,    80,    53,
       4,    -1,    80,    52,    -1,    63,    82,    64,    -1,     4,
      -1,     4,    -1,     4,    65,    82,    -1,    66,    74,    67,
      -1,    66,    67,    -1,    25,    91,    -1,    26,    91,    -1,
      27,    81,    -1,    28,    -1,    29,    -1,    22,    79,    81,
      -1,    30,    87,    81,    81,    -1,    85,    86,    81,    81,
      -1,    31,    84,    -1,    32,    90,     3,    -1,     1,    -1,
      33,    -1,    34,    -1,    -1,    86,    88,    -1,    86,    89,
      -1,    86,    35,     4,    -1,    -1,    87,    89,    -1,    87,
      35,     4,    -1,    44,    -1,    45,    -1,    46,    -1,    47,
      -1,    48,    -1,    36,    -1,    43,     4,    -1,    42,     4,
      -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,
      -1,    68,    92,    69,    -1,    84,    -1,    84,    65,    92,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   108,   111,   112,   115,   152,   153,   156,
     157,   158,   161,   162,   163,   166,   171,   178,   181,   199,
     209,   214,   215,   216,   224,   233,   242,   251,   259,   268,
     269,   272,   275,   278,   281,   286,   287,   288,   293,   294,
     298,   306,   312,   318,   324,   330,   331,   334,   335,   338,
     339,   342,   343,   344,   345,   346,   347,   363,   379,   395,
     396,   398,   401,   402,   405,   406,   411,   415,   421,   422,
     426,   433,   434,   435,   436,   441,   448,   449,   450,   451,
     452,   453,   460,   461,   464,   467,   468
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IF", "ELSIF",
  "ELSE", "REJCT", "FILEINTO", "REDIRECT", "KEEP", "STOP", "DISCARD",
  "VACATION", "REQUIRE", "SETFLAG", "ADDFLAG", "REMOVEFLAG", "MARK",
  "UNMARK", "FLAGS", "HASFLAG", "NOTIFY", "VALIDNOTIF", "ANYOF", "ALLOF",
  "EXISTS", "SFALSE", "STRUE", "HEADER", "NOT", "SIZE", "ADDRESS",
  "ENVELOPE", "COMPARATOR", "IS", "CONTAINS", "MATCHES", "REGEX", "OVER",
  "UNDER", "COUNT", "VALUE", "ALL", "LOCALPART", "DOMAIN", "USER",
  "DETAIL", "DAYS", "ADDRESSES", "SUBJECT", "MIME", "FROM", "HANDLE",
  "METHOD", "IMPORTANCE", "OPTIONS", "LOW", "NORMAL", "HIGH", "MESSAGE",
  "';'", "'['", "']'", "','", "'{'", "'}'", "'('", "')'", "$accept",
  "start", "reqs", "require", "commands", "command", "elsif", "action",
  "ntags", "hftags", "vtags", "stringlist", "strings", "block", "test",
  "addrorenv", "aetags", "htags", "addrparttag", "comptag", "sizetag",
  "testlist", "tests", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,    59,    91,    93,    44,   123,   125,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    73,    74,    74,    75,
      75,    75,    76,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    78,    78,    78,    78,    79,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    86,    86,    87,    87,
      87,    88,    88,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     3,     1,     2,     2,
       4,     2,     0,     4,     2,     2,     3,     1,     4,     2,
       2,     1,     1,     3,     2,     2,     2,     2,     2,     0,
       3,     3,     3,     3,     2,     0,     2,     3,     0,     3,
       3,     3,     3,     3,     2,     3,     1,     1,     3,     3,
       2,     2,     2,     2,     1,     1,     3,     4,     4,     2,
       3,     1,     1,     1,     0,     2,     2,     3,     0,     2,
       3,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     4,    46,     0,     0,     1,     0,
       0,     0,     0,     0,    17,    21,    22,    38,     0,     0,
       0,    29,     0,     0,     7,     0,     5,    47,     0,     6,
      11,    61,    35,     0,     0,     0,    54,    55,    68,     0,
       0,    62,    63,     0,    64,    15,    19,     0,    20,     0,
       0,    24,    25,    26,    27,    28,     8,     9,     0,    45,
       0,     0,    51,    52,    53,     0,    59,    82,    83,     0,
       0,    12,     0,     0,    16,    23,     0,     0,     0,    44,
       0,     0,    34,     0,     0,     0,     0,    48,     0,    76,
      79,    80,    81,     0,     0,    56,    36,    85,     0,     0,
       0,    69,    60,    50,     0,     0,     0,    10,     0,    71,
      72,    73,    74,    75,     0,    65,    66,    18,    39,    40,
      41,    43,    42,    33,    31,    30,    32,    37,    78,    77,
       0,    84,    70,    57,    49,     0,    14,    67,    58,    86,
      12,    13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    23,    24,   107,    25,    54,    60,
      50,     7,    28,    71,    97,    44,    72,    65,   115,    96,
      69,    62,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const yytype_int16 yypact[] =
{
      30,     9,    14,   180,     1,  -100,    35,   -27,  -100,   -21,
     124,    39,     4,    40,    25,  -100,  -100,  -100,     9,     9,
       9,  -100,     9,   160,  -100,   -14,  -100,   -16,   -13,  -100,
    -100,  -100,  -100,   -12,   -12,     9,  -100,  -100,  -100,   124,
     -31,  -100,  -100,   -11,  -100,  -100,  -100,     9,  -100,     9,
      91,  -100,  -100,  -100,    36,  -100,  -100,  -100,    35,  -100,
      85,   124,  -100,  -100,  -100,    96,  -100,  -100,  -100,    47,
      10,    31,    67,    48,  -100,  -100,    55,     9,    69,  -100,
      70,    74,  -100,    75,    77,     9,    79,  -100,    80,  -100,
    -100,  -100,  -100,    81,    82,  -100,  -100,    16,    19,    86,
       9,  -100,  -100,  -100,    52,   124,   -11,  -100,    90,  -100,
    -100,  -100,  -100,  -100,     9,  -100,  -100,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,  -100,
     124,  -100,  -100,  -100,  -100,   -11,  -100,  -100,  -100,  -100,
      31,  -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,    95,  -100,    37,   -17,   -39,  -100,  -100,  -100,
    -100,   -18,    50,   -99,    -7,  -100,  -100,  -100,  -100,   -60,
    -100,    83,    -4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -4
static const yytype_int16 yytable[] =
{
      51,    52,    53,    43,    55,   101,    56,   136,    46,    67,
      68,     9,   116,     5,     8,    10,     1,    64,    11,    12,
      13,    14,    15,    16,    17,    47,    18,    19,    20,    73,
      -2,    74,    66,    21,    22,    29,   140,   105,   106,    27,
      82,    30,    95,    45,    48,     1,    49,   100,    57,    58,
     102,    59,   117,     9,   114,    70,    61,    10,   118,   119,
      11,    12,    13,    14,    15,    16,    17,   125,    18,    19,
      20,     5,     6,   120,   121,    21,    22,   103,   122,   123,
     124,   130,   133,   126,   127,   128,   129,    56,   131,     5,
     132,    83,    84,    85,   137,    75,   138,    86,   135,    26,
       5,   141,   108,    89,    90,    91,    92,   104,    87,    93,
      94,   109,   110,   111,   112,   113,     0,    63,     0,   134,
      88,    89,    90,    91,    92,    31,   139,    93,    94,     0,
       6,    99,    89,    90,    91,    92,     0,     0,    93,    94,
      76,    77,    78,    79,    80,    81,    32,     0,     6,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     6,
      -3,     9,     0,     0,     0,    10,     0,     0,    11,    12,
      13,    14,    15,    16,    17,     0,    18,    19,    20,     0,
       0,     9,     0,    21,    22,    10,     0,     0,    11,    12,
      13,    14,    15,    16,    17,     0,    18,    19,    20,     0,
       0,     0,     0,    21,    22
};

static const yytype_int16 yycheck[] =
{
      18,    19,    20,    10,    22,    65,    23,   106,     4,    40,
      41,     1,    72,     4,     0,     5,    15,    35,     8,     9,
      10,    11,    12,    13,    14,    21,    16,    17,    18,    47,
       0,    49,    39,    23,    24,    62,   135,     6,     7,     4,
       4,    62,    60,     4,     4,    15,    21,    65,    62,    65,
       3,    64,     4,     1,    72,    66,    68,     5,     3,    77,
       8,     9,    10,    11,    12,    13,    14,    85,    16,    17,
      18,     4,    63,     4,     4,    23,    24,    67,     4,     4,
       3,    65,   100,     4,     4,     4,     4,   104,    69,     4,
       4,    55,    56,    57,     4,     4,   114,    61,   105,     4,
       4,   140,    35,    36,    37,    38,    39,    70,    58,    42,
      43,    44,    45,    46,    47,    48,    -1,    34,    -1,    67,
      35,    36,    37,    38,    39,     1,   130,    42,    43,    -1,
      63,    35,    36,    37,    38,    39,    -1,    -1,    42,    43,
      49,    50,    51,    52,    53,    54,    22,    -1,    63,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    63,
       0,     1,    -1,    -1,    -1,     5,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    -1,
      -1,     1,    -1,    23,    24,     5,    -1,    -1,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    -1,
      -1,    -1,    -1,    23,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    71,    72,    73,     4,    63,    81,     0,     1,
       5,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      18,    23,    24,    74,    75,    77,    72,     4,    82,    62,
      62,     1,    22,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    84,    85,     4,     4,    21,     4,    21,
      80,    81,    81,    81,    78,    81,    75,    62,    65,    64,
      79,    68,    91,    91,    81,    87,    84,    40,    41,    90,
      66,    83,    86,    81,    81,     4,    49,    50,    51,    52,
      53,    54,     4,    55,    56,    57,    61,    82,    35,    36,
      37,    38,    39,    42,    43,    81,    89,    84,    92,    35,
      81,    89,     3,    67,    74,     6,     7,    76,    35,    44,
      45,    46,    47,    48,    81,    88,    89,     4,     3,    81,
       4,     4,     4,     4,     3,    81,     4,     4,     4,     4,
      65,    69,     4,    81,    67,    84,    83,     4,    81,    92,
      83,    76
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (context, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, context); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct sieve2_context *context)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct sieve2_context *context;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (context);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct sieve2_context *context)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct sieve2_context *context;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, context);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct sieve2_context *context)
#else
static void
yy_reduce_print (yyvsp, yyrule, context)
    YYSTYPE *yyvsp;
    int yyrule;
    struct sieve2_context *context;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , context);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, context); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct sieve2_context *context)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, context)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct sieve2_context *context;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (context);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct sieve2_context *context);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct sieve2_context *context)
#else
int
yyparse (context)
    struct sieve2_context *context;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 107 "sieve.y"
    { context->script.cmds = NULL; }
    break;

  case 3:
#line 108 "sieve.y"
    { context->script.cmds = (yyvsp[(2) - (2)].cl); }
    break;

  case 6:
#line 115 "sieve.y"
    {
                                    int unsupp = 0;
                                    char *msg;
                                    char *freemsg;
                                    stringlist_t *s;
                                    stringlist_t *sl = (yyvsp[(2) - (3)].sl);

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
                                        libsieve_sieveerror(context, msg);
                                        libsieve_free(msg);
                                        YYERROR; 
                                    }

                                    /* This needs to be free'd regardless of error */
                                    libsieve_free(msg);
                                }
    break;

  case 7:
#line 152 "sieve.y"
    { (yyval.cl) = (yyvsp[(1) - (1)].cl); }
    break;

  case 8:
#line 153 "sieve.y"
    { (yyvsp[(2) - (2)].cl)->next = (yyvsp[(1) - (2)].cl); (yyval.cl) = (yyvsp[(2) - (2)].cl); }
    break;

  case 9:
#line 156 "sieve.y"
    { (yyval.cl) = (yyvsp[(1) - (2)].cl); }
    break;

  case 10:
#line 157 "sieve.y"
    { (yyval.cl) = libsieve_new_if((yyvsp[(2) - (4)].test), (yyvsp[(3) - (4)].cl), (yyvsp[(4) - (4)].cl)); }
    break;

  case 11:
#line 158 "sieve.y"
    { (yyval.cl) = libsieve_new_command(STOP); }
    break;

  case 12:
#line 161 "sieve.y"
    { (yyval.cl) = NULL; }
    break;

  case 13:
#line 162 "sieve.y"
    { (yyval.cl) = libsieve_new_if((yyvsp[(2) - (4)].test), (yyvsp[(3) - (4)].cl), (yyvsp[(4) - (4)].cl)); }
    break;

  case 14:
#line 163 "sieve.y"
    { (yyval.cl) = (yyvsp[(2) - (2)].cl); }
    break;

  case 15:
#line 166 "sieve.y"
    { if (!context->require.reject) {
				     libsieve_sieveerror(context, "reject not required");
				     YYERROR;
				   }
				   (yyval.cl) = libsieve_new_command(REJCT); (yyval.cl)->u.str = (yyvsp[(2) - (2)].sval); }
    break;

  case 16:
#line 171 "sieve.y"
    { if (!context->require.imap4flags) {
				     libsieve_sieveerror(context, "imap4flags not required");
	                             YYERROR;
                                   }
	                           (yyval.cl) = libsieve_new_command(KEEP);
                                   (yyval.cl)->u.f.mailbox = NULL; 
				   (yyval.cl)->u.f.slflags = (yyvsp[(3) - (3)].sl); }
    break;

  case 17:
#line 178 "sieve.y"
    { (yyval.cl) = libsieve_new_command(KEEP);
	                           (yyval.cl)->u.f.mailbox = NULL;
				   (yyval.cl)->u.f.slflags = NULL; }
    break;

  case 18:
#line 181 "sieve.y"
    { if (!context->require.fileinto) {
				     libsieve_sieveerror(context, "fileinto not required");
	                             YYERROR;
                                   } if (!context->require.imap4flags) {
				     libsieve_sieveerror(context, "imap4flags not required");
	                             YYERROR;
                                   }

                                   if (!static_verify_stringlist(context, (yyvsp[(3) - (4)].sl), static_verify_flag)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   if (!static_verify_mailbox(context, (yyvsp[(4) - (4)].sval))) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           (yyval.cl) = libsieve_new_command(FILEINTO);
				   (yyval.cl)->u.f.slflags = (yyvsp[(3) - (4)].sl);
				   (yyval.cl)->u.f.mailbox = (yyvsp[(4) - (4)].sval); }
    break;

  case 19:
#line 199 "sieve.y"
    { if (!context->require.fileinto) {
				     libsieve_sieveerror(context, "fileinto not required");
	                             YYERROR;
                                   }
				   if (!static_verify_mailbox(context, (yyvsp[(2) - (2)].sval))) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           (yyval.cl) = libsieve_new_command(FILEINTO);
				   (yyval.cl)->u.f.slflags = NULL;
				   (yyval.cl)->u.f.mailbox = (yyvsp[(2) - (2)].sval); }
    break;

  case 20:
#line 209 "sieve.y"
    { (yyval.cl) = libsieve_new_command(REDIRECT);
				   if (!static_verify_address(context, (yyvsp[(2) - (2)].sval))) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   (yyval.cl)->u.str = (yyvsp[(2) - (2)].sval); }
    break;

  case 21:
#line 214 "sieve.y"
    { (yyval.cl) = libsieve_new_command(STOP); }
    break;

  case 22:
#line 215 "sieve.y"
    { (yyval.cl) = libsieve_new_command(DISCARD); }
    break;

  case 23:
#line 216 "sieve.y"
    { if (!context->require.vacation) {
				     libsieve_sieveerror(context, "vacation not required");
				     (yyval.cl) = libsieve_new_command(VACATION);
				     YYERROR;
				   } else {
  				     (yyval.cl) = static_build_vacation(context, VACATION,
					    static_canon_vtags((yyvsp[(2) - (3)].vtag)), (yyvsp[(3) - (3)].sval));
				   } }
    break;

  case 24:
#line 224 "sieve.y"
    { if (!libsieve_parse_context->require.imap4flags) {
                                    libsieve_sieveerror(context, "imap4flags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist(context, (yyvsp[(2) - (2)].sl), static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
				    }
                                 (yyval.cl) = libsieve_new_command(SETFLAG);
                                 (yyval.cl)->u.sl = (yyvsp[(2) - (2)].sl); }
    break;

  case 25:
#line 233 "sieve.y"
    { if (!libsieve_parse_context->require.imap4flags) {
                                    libsieve_sieveerror(context, "imap4flags not required");
                                    YYERROR;
                                    }
                                 if (!static_verify_stringlist(context, (yyvsp[(2) - (2)].sl), static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                    }
                                 (yyval.cl) = libsieve_new_command(ADDFLAG);
                                 (yyval.cl)->u.sl = (yyvsp[(2) - (2)].sl); }
    break;

  case 26:
#line 242 "sieve.y"
    { if (!libsieve_parse_context->require.imap4flags) {
                                     libsieve_sieveerror(context, "imap4flags not required");
                                     YYERROR;
                                     }
                                 if (!static_verify_stringlist(context, (yyvsp[(2) - (2)].sl), static_verify_flag)) {
                                     YYERROR; /* vf should call sieveerror() */
                                     }
                                 (yyval.cl) = libsieve_new_command(REMOVEFLAG);
                                 (yyval.cl)->u.sl = (yyvsp[(2) - (2)].sl); }
    break;

  case 27:
#line 251 "sieve.y"
    { if (!libsieve_parse_context->require.notify) {
	       		             libsieve_sieveerror(context, "notify not required");
	       		             (yyval.cl) = libsieve_new_command(NOTIFY); 
	       		             YYERROR;
				 } else {
				     (yyval.cl) = static_build_notify(context, NOTIFY,
	       		             static_canon_ntags((yyvsp[(2) - (2)].ntag)));
	       		         } }
    break;

  case 28:
#line 259 "sieve.y"
    { if (!libsieve_parse_context->require.notify) {
                                     libsieve_sieveerror(context, "notify not required");
				     (yyval.cl) = libsieve_new_command(VALIDNOTIF);
				     YYERROR;
				 } else {
				     (yyval.cl) = static_build_validnotif(context, VALIDNOTIF, (yyvsp[(2) - (2)].sl));
				 } }
    break;

  case 29:
#line 268 "sieve.y"
    { (yyval.ntag) = static_new_ntags(); }
    break;

  case 30:
#line 269 "sieve.y"
    { if ((yyval.ntag)->options != NULL) { 
					libsieve_sieveerror(context, "duplicate :options"); YYERROR; }
				     else { (yyval.ntag)->options = (yyvsp[(3) - (3)].sl); } }
    break;

  case 31:
#line 272 "sieve.y"
    { if ((yyval.ntag)->importance != 0) {  /* FIXME: "NUMBER" not NUMBER :\ */
					libsieve_sieveerror(context, "duplicate :importance"); YYERROR; }
				   else { (yyval.ntag)->importance = (yyvsp[(3) - (3)].nval); } }
    break;

  case 32:
#line 275 "sieve.y"
    { if ((yyval.ntag)->message != NULL) { 
					libsieve_sieveerror(context, "duplicate :message"); YYERROR; }
				   else { (yyval.ntag)->message = (yyvsp[(3) - (3)].sval); } }
    break;

  case 33:
#line 278 "sieve.y"
    { if ((yyval.ntag)->method != NULL) {
					libsieve_sieveerror(context, "duplicate method"); YYERROR; }
				   else { (yyval.ntag)->method = (yyvsp[(3) - (3)].sval); } }
    break;

  case 34:
#line 281 "sieve.y"
    { if ((yyval.ntag)->method != NULL) { 
					libsieve_sieveerror(context, "duplicate method"); YYERROR; }
				   else { (yyval.ntag)->method = (yyvsp[(2) - (2)].sval); } }
    break;

  case 35:
#line 286 "sieve.y"
    { (yyval.hftag) = static_new_hftags(); }
    break;

  case 36:
#line 287 "sieve.y"
    { (yyval.hftag)->comptag = (yyvsp[(2) - (2)].nval); }
    break;

  case 37:
#line 288 "sieve.y"
    { if ((yyval.hftag)->comparator != NULL) { 
				   libsieve_sieveerror(context, "duplicate comparator tag"); YYERROR; }
				   else { (yyval.hftag)->comparator = (yyvsp[(3) - (3)].sval); } }
    break;

  case 38:
#line 293 "sieve.y"
    { (yyval.vtag) = static_new_vtags(); }
    break;

  case 39:
#line 294 "sieve.y"
    { if ((yyval.vtag)->days != -1) { 
					libsieve_sieveerror(context, "duplicate :days");
					YYERROR; }
				   else { (yyval.vtag)->days = (yyvsp[(3) - (3)].nval); } }
    break;

  case 40:
#line 298 "sieve.y"
    { if ((yyval.vtag)->addresses != NULL) { 
					libsieve_sieveerror(context, "duplicate :addresses"); 
					YYERROR;
				       } else if (!static_verify_stringlist(context, (yyvsp[(3) - (3)].sl),
							static_verify_address)) {
					  YYERROR;
				       } else {
					 (yyval.vtag)->addresses = (yyvsp[(3) - (3)].sl); } }
    break;

  case 41:
#line 306 "sieve.y"
    { if ((yyval.vtag)->subject != NULL) { 
					libsieve_sieveerror(context, "duplicate :subject"); 
					YYERROR;
				   } else if (!static_ok_header(context, (yyvsp[(3) - (3)].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->subject = (yyvsp[(3) - (3)].sval); } }
    break;

  case 42:
#line 312 "sieve.y"
    { if ((yyval.vtag)->handle != NULL) { 
					libsieve_sieveerror(context, "duplicate :handle"); 
					YYERROR;
				   } else if (!static_ok_header(context, (yyvsp[(3) - (3)].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->handle = (yyvsp[(3) - (3)].sval); } }
    break;

  case 43:
#line 318 "sieve.y"
    { if ((yyval.vtag)->from != NULL) { 
					libsieve_sieveerror(context, "duplicate :from"); 
					YYERROR;
				   } else if (!static_ok_header(context, (yyvsp[(3) - (3)].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->from = (yyvsp[(3) - (3)].sval); } }
    break;

  case 44:
#line 324 "sieve.y"
    { if ((yyval.vtag)->mime != -1) { 
					libsieve_sieveerror(context, "duplicate :mime"); 
					YYERROR; }
				   else { (yyval.vtag)->mime = MIME; } }
    break;

  case 45:
#line 330 "sieve.y"
    { (yyval.sl) = (yyvsp[(2) - (3)].sl); }
    break;

  case 46:
#line 331 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[(1) - (1)].sval), NULL); }
    break;

  case 47:
#line 334 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[(1) - (1)].sval), NULL); }
    break;

  case 48:
#line 335 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sl)); }
    break;

  case 49:
#line 338 "sieve.y"
    { (yyval.cl) = (yyvsp[(2) - (3)].cl); }
    break;

  case 50:
#line 339 "sieve.y"
    { (yyval.cl) = NULL; }
    break;

  case 51:
#line 342 "sieve.y"
    { (yyval.test) = libsieve_new_test(ANYOF); (yyval.test)->u.tl = (yyvsp[(2) - (2)].testl); }
    break;

  case 52:
#line 343 "sieve.y"
    { (yyval.test) = libsieve_new_test(ALLOF); (yyval.test)->u.tl = (yyvsp[(2) - (2)].testl); }
    break;

  case 53:
#line 344 "sieve.y"
    { (yyval.test) = libsieve_new_test(EXISTS); (yyval.test)->u.sl = (yyvsp[(2) - (2)].sl); }
    break;

  case 54:
#line 345 "sieve.y"
    { (yyval.test) = libsieve_new_test(SFALSE); }
    break;

  case 55:
#line 346 "sieve.y"
    { (yyval.test) = libsieve_new_test(STRUE); }
    break;

  case 56:
#line 347 "sieve.y"
    { if (!libsieve_parse_context->require.imap4flags) {
                                       libsieve_sieveerror(context, "imap4flags not required");
                                       YYERROR;
                                    }
                                    if (!static_verify_stringlist(context, (yyvsp[(3) - (3)].sl), static_verify_flag)) {
                                       YYERROR; /* vf should call sieveerror() */
				    }
                                    (yyval.test) = libsieve_new_test(HASFLAG);
				    if ((yyvsp[(2) - (3)].hftag)->comptag != -1) { 
				       (yyval.test)->u.hf.comp = libsieve_comparator_lookup((yyvsp[(2) - (3)].hftag)->comparator, (yyvsp[(2) - (3)].hftag)->comptag);
				       (yyval.test)->u.hf.comptag = (yyvsp[(2) - (3)].hftag)->comptag;
				    }
				    if ((yyvsp[(2) - (3)].hftag)) {
				       libsieve_free((yyvsp[(2) - (3)].hftag));
				    }
                                    (yyval.test)->u.hf.sl = (yyvsp[(3) - (3)].sl); }
    break;

  case 57:
#line 364 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist(context, (yyvsp[(3) - (4)].sl), static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   (yyvsp[(2) - (4)].htag) = static_canon_htags((yyvsp[(2) - (4)].htag));
				   if ((yyvsp[(2) - (4)].htag)->comptag == REGEX) {
				     pl = static_verify_regexs(context, (yyvsp[(4) - (4)].sl), (yyvsp[(2) - (4)].htag)->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
				     pl = (patternlist_t *) (yyvsp[(4) - (4)].sl);
				       
				   (yyval.test) = static_build_header(context, HEADER, (yyvsp[(2) - (4)].htag), (yyvsp[(3) - (4)].sl), pl);
				   if ((yyval.test) == NULL) { YYERROR; } }
    break;

  case 58:
#line 380 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist(context, (yyvsp[(3) - (4)].sl), static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   (yyvsp[(2) - (4)].aetag) = static_canon_aetags((yyvsp[(2) - (4)].aetag));
				   if ((yyvsp[(2) - (4)].aetag)->comptag == REGEX) {
				     pl = static_verify_regexs(context, (yyvsp[(4) - (4)].sl), (yyvsp[(2) - (4)].aetag)->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
				     pl = (patternlist_t *) (yyvsp[(4) - (4)].sl);
				       
				   (yyval.test) = static_build_address(context, (yyvsp[(1) - (4)].nval), (yyvsp[(2) - (4)].aetag), (yyvsp[(3) - (4)].sl), pl);
				   if ((yyval.test) == NULL) { YYERROR; } }
    break;

  case 59:
#line 395 "sieve.y"
    { (yyval.test) = libsieve_new_test(NOT); (yyval.test)->u.t = (yyvsp[(2) - (2)].test); }
    break;

  case 60:
#line 396 "sieve.y"
    { (yyval.test) = libsieve_new_test(SIZE); (yyval.test)->u.sz.t = (yyvsp[(2) - (3)].nval);
		                   (yyval.test)->u.sz.n = (yyvsp[(3) - (3)].nval); }
    break;

  case 61:
#line 398 "sieve.y"
    { (yyval.test) = NULL; }
    break;

  case 62:
#line 401 "sieve.y"
    { (yyval.nval) = ADDRESS; }
    break;

  case 63:
#line 402 "sieve.y"
    { (yyval.nval) = ENVELOPE; }
    break;

  case 64:
#line 405 "sieve.y"
    { (yyval.aetag) = static_new_aetags(); }
    break;

  case 65:
#line 406 "sieve.y"
    { (yyval.aetag) = (yyvsp[(1) - (2)].aetag);
				   if ((yyval.aetag)->addrtag != -1) { 
			libsieve_sieveerror(context, "duplicate or conflicting address part tag");
			YYERROR; }
				   else { (yyval.aetag)->addrtag = (yyvsp[(2) - (2)].nval); } }
    break;

  case 66:
#line 411 "sieve.y"
    { (yyval.aetag) = (yyvsp[(1) - (2)].aetag);
				   if ((yyval.aetag)->comptag != -1) { 
			libsieve_sieveerror(context, "duplicate comparator type tag"); YYERROR; }
				   else { (yyval.aetag)->comptag = (yyvsp[(2) - (2)].nval); } }
    break;

  case 67:
#line 415 "sieve.y"
    { (yyval.aetag) = (yyvsp[(1) - (3)].aetag);
				   if ((yyval.aetag)->comparator != NULL) { 
			libsieve_sieveerror(context, "duplicate comparator tag"); YYERROR; }
				   else { (yyval.aetag)->comparator = (yyvsp[(3) - (3)].sval); } }
    break;

  case 68:
#line 421 "sieve.y"
    { (yyval.htag) = static_new_htags(); }
    break;

  case 69:
#line 422 "sieve.y"
    { (yyval.htag) = (yyvsp[(1) - (2)].htag);
				   if ((yyval.htag)->comptag != -1) { 
			libsieve_sieveerror(context, "duplicate comparator type tag"); YYERROR; }
				   else { (yyval.htag)->comptag = (yyvsp[(2) - (2)].nval); } }
    break;

  case 70:
#line 426 "sieve.y"
    { (yyval.htag) = (yyvsp[(1) - (3)].htag);
				   if ((yyval.htag)->comparator != NULL) { 
			libsieve_sieveerror(context, "duplicate comparator tag");
					YYERROR; }
				   else { (yyval.htag)->comparator = (yyvsp[(3) - (3)].sval); } }
    break;

  case 71:
#line 433 "sieve.y"
    { (yyval.nval) = ALL; }
    break;

  case 72:
#line 434 "sieve.y"
    { (yyval.nval) = LOCALPART; }
    break;

  case 73:
#line 435 "sieve.y"
    { (yyval.nval) = DOMAIN; }
    break;

  case 74:
#line 436 "sieve.y"
    { if (!context->require.subaddress) {
				     libsieve_sieveerror(context, "subaddress not required");
				     YYERROR;
				   }
				   (yyval.nval) = USER; }
    break;

  case 75:
#line 441 "sieve.y"
    { if (!context->require.subaddress) {
				     libsieve_sieveerror(context, "subaddress not required");
				     YYERROR;
				   }
				   (yyval.nval) = DETAIL; }
    break;

  case 76:
#line 448 "sieve.y"
    { (yyval.nval) = IS; }
    break;

  case 77:
#line 449 "sieve.y"
    { (yyval.nval) = VALUE | libsieve_relational_lookup((yyvsp[(2) - (2)].sval)); libsieve_free((yyvsp[(2) - (2)].sval)); /* HACK: bits above 10 carry the relational. And we don't need this string anymore, either. */ }
    break;

  case 78:
#line 450 "sieve.y"
    { (yyval.nval) = COUNT | libsieve_relational_lookup((yyvsp[(2) - (2)].sval)); libsieve_free((yyvsp[(2) - (2)].sval)); /* HACK: bits above 10 carry the relational. And we don't need this string anymore, either. */ }
    break;

  case 79:
#line 451 "sieve.y"
    { (yyval.nval) = CONTAINS; }
    break;

  case 80:
#line 452 "sieve.y"
    { (yyval.nval) = MATCHES; }
    break;

  case 81:
#line 453 "sieve.y"
    { if (!context->require.regex) {
				     libsieve_sieveerror(context, "regex not required");
				     YYERROR;
				     }
				   (yyval.nval) = REGEX; }
    break;

  case 82:
#line 460 "sieve.y"
    { (yyval.nval) = OVER; }
    break;

  case 83:
#line 461 "sieve.y"
    { (yyval.nval) = UNDER; }
    break;

  case 84:
#line 464 "sieve.y"
    { (yyval.testl) = (yyvsp[(2) - (3)].testl); }
    break;

  case 85:
#line 467 "sieve.y"
    { (yyval.testl) = libsieve_new_testlist((yyvsp[(1) - (1)].test), NULL); }
    break;

  case 86:
#line 468 "sieve.y"
    { (yyval.testl) = libsieve_new_testlist((yyvsp[(1) - (3)].test), (yyvsp[(3) - (3)].testl)); }
    break;


/* Line 1267 of yacc.c.  */
#line 2317 "sieve.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (context, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (context, yymsg);
	  }
	else
	  {
	    yyerror (context, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, context);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, context);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 471 "sieve.y"


const char *libsieve_sieveptr;         /* pointer to sieve string for address lexer */
char *libsieve_sieveerr;         /* buffer for sieve parser error messages */

void libsieve_sieve_parse_buffer(struct sieve2_context *context)
{
    extern int libsieve_sievelineno;

    libsieve_parse_context = context;

    libsieve_sieveptr = context->script.script;
    libsieve_sieveerr = NULL;
    libsieve_sievelineno = 1;

    libsieve_sievelexrestart();

    if (libsieve_sieveparse(context))
        throw(SIEVE2_ERROR_PARSE);
}

/* This gets called by the address parser,
 * which does not have access to the context. */
int libsieve_sieveerror_exec(char *msg)
{
    libsieve_parse_context->exec_errors++;

    libsieve_do_error_exec(libsieve_parse_context, msg);

    return 0;
}

int libsieve_sieveerror(struct sieve2_context *context, char *msg)
{
    extern int libsieve_sievelineno;

    context->parse_errors++;

    libsieve_do_error_parse(context, libsieve_sievelineno, msg);

    return 0;
}

static test_t *static_build_address(
	struct sieve2_context *context,
	int t, struct aetags *ae,
	stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be either ADDRESS or ENVELOPE */

    libsieve_assert((t == ADDRESS) || (t == ENVELOPE));

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

static test_t *static_build_header(
	struct sieve2_context *context,
	int t, struct htags *h,
	stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = libsieve_new_test(t);	/* can be HEADER */

    libsieve_assert(t == HEADER);

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

static commandlist_t *static_build_vacation(
	struct sieve2_context *context,
	int t, struct vtags *v, char *reason)
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

static commandlist_t *static_build_notify(
	struct sieve2_context *context,
	int t, struct ntags *n)
{
    commandlist_t *ret = libsieve_new_command(t);

    libsieve_assert(t == NOTIFY);

    if (ret) {
	ret->u.n.method = n->method; n->method = NULL;
	ret->u.n.options = n->options; n->options = NULL;
	ret->u.n.from = n->from; n->from= NULL;
	ret->u.n.importance = n->importance; n->importance = 0;
	ret->u.n.message = n->message; n->message = NULL;
	static_free_ntags(n);
    }
    return ret;
}

// FIXME: I think we just test and return true or false... check around.
static commandlist_t *static_build_validnotif(
	struct sieve2_context *context,
	int t, stringlist_t *sl)
{
    commandlist_t *ret = libsieve_new_command(t);

    libsieve_assert(t == VALIDNOTIF);

/*
    if (ret) {
	ret->u.d.comptag = d->comptag;
	ret->u.d.comp = libsieve_comparator_lookup("i;ascii-casemap", d->comptag);
	ret->u.d.pattern = d->pattern; d->pattern = NULL;
	ret->u.d.importance = d->importance;
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
    r->from = NULL;
    r->options = NULL;
    r->importance = 0;
    r->message = NULL;

    return r;
}

static struct ntags *static_canon_ntags(struct ntags *n)
{
    char *from = "$from$: $subject$";
    if (n->message == NULL) { n->message = libsieve_strdup(from); }

    return n;
}

static void static_free_ntags(struct ntags *n)
{
    libsieve_free(n->method);
    libsieve_free(n->from);
    if (n->options) libsieve_free_sl(n->options);
    libsieve_free(n->message);
    libsieve_free(n);
}

static int static_verify_stringlist(struct sieve2_context *context, stringlist_t *sl,
	int (*verify)(struct sieve2_context *, const char *))
{
    for (; sl != NULL && verify(context, sl->s); sl = sl->next) ;
    return (sl == NULL);
}

static int static_verify_flag(struct sieve2_context *context, const char *s)
{
    /* xxx if not a flag, call sieveerror */
    return 1;
}

extern char *libsieve_addrptr;		/* pointer to sieve string for address lexer */
extern char *libsieve_addrerr;		/* buffer for sieve parser error messages */

static int static_verify_address(struct sieve2_context *context, const char *s)
{
    char *aerr = NULL;
    char *serr = NULL;
    struct address *addr = NULL;

    addr = libsieve_addr_parse_buffer(context, &addr, &s, &aerr);
    if (addr == NULL) {
        serr = libsieve_strconcat("address '", s, "': ", aerr, NULL);
        libsieve_sieveerror(context, serr);
        libsieve_free(serr);
        libsieve_free(aerr);
        return 0;
    }
    libsieve_addrstructfree(addr, CHARSALSO);
    return 1;
}

static int static_verify_mailbox(struct sieve2_context *context, const char *s UNUSED)
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
	    libsieve_sieveerror(context, err);
	    libsieve_free(err);
	    return 0;
	}
	h++;
    }
    return 1;
}
 
static regex_t *static_verify_regex(struct sieve2_context *context, const char *s, int cflags)
{
    int ret;
    char errbuf[100];
    regex_t *reg = (regex_t *) libsieve_malloc(sizeof(regex_t));

    if ((ret = libsieve_regcomp(reg, s, cflags)) != 0) {
	(void) libsieve_regerror(ret, reg, errbuf, sizeof(errbuf));
	libsieve_sieveerror(context, errbuf);
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
static int static_ok_header(struct sieve2_context *context UNUSED, char *s UNUSED)
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
    } else if (!strcmp("enotify",req)) {
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


