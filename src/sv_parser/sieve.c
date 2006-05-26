/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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
     FROM = 304,
     HANDLE = 305,
     METHOD = 306,
     ID = 307,
     OPTIONS = 308,
     LOW = 309,
     NORMAL = 310,
     HIGH = 311,
     MESSAGE = 312
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
#define FROM 304
#define HANDLE 305
#define METHOD 306
#define ID 307
#define OPTIONS 308
#define LOW 309
#define NORMAL 310
#define HIGH 311
#define MESSAGE 312




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
#include <assert.h>
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

extern int libsieve_sieveerror(char *msg);
extern int libsieve_sievelex(void);

#define YYERROR_VERBOSE /* i want better error messages! */


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
/* Line 196 of yacc.c.  */
#line 280 "sieve.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 292 "sieve.c"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
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
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  24
/* YYNRULES -- Number of rules. */
#define YYNRULES  86
/* YYNRULES -- Number of states. */
#define YYNSTATES  135

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      64,    65,     2,     2,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    58,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,    63,     2,     2,     2,     2,
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
      55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    11,    15,    17,    20,
      23,    28,    31,    32,    37,    40,    43,    46,    49,    51,
      53,    55,    59,    62,    65,    68,    70,    72,    75,    78,
      79,    83,    87,    91,    94,    98,    99,   102,   106,   108,
     110,   112,   113,   117,   121,   125,   129,   133,   136,   140,
     142,   144,   148,   152,   155,   158,   161,   164,   166,   168,
     173,   178,   181,   185,   187,   189,   191,   192,   195,   198,
     202,   203,   206,   210,   212,   214,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   236,   238
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      67,     0,    -1,    -1,    68,    70,    -1,    -1,    69,    68,
      -1,    15,    78,    58,    -1,    71,    -1,    71,    70,    -1,
      73,    58,    -1,     5,    81,    80,    72,    -1,     1,    58,
      -1,    -1,     6,    81,    80,    72,    -1,     7,    80,    -1,
       8,     4,    -1,     9,     4,    -1,    10,     4,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    77,     4,    -1,    16,
      78,    -1,    17,    78,    -1,    18,    78,    -1,    19,    -1,
      20,    -1,    21,    74,    -1,    22,    75,    -1,    -1,    74,
      52,     4,    -1,    74,    51,     4,    -1,    74,    53,    78,
      -1,    74,    76,    -1,    74,    57,     4,    -1,    -1,    75,
      76,    -1,    75,    86,     4,    -1,    54,    -1,    55,    -1,
      56,    -1,    -1,    77,    45,     3,    -1,    77,    46,    78,
      -1,    77,    47,     4,    -1,    77,    50,     4,    -1,    77,
      49,     4,    -1,    77,    48,    -1,    59,    79,    60,    -1,
       4,    -1,     4,    -1,     4,    61,    79,    -1,    62,    70,
      63,    -1,    62,    63,    -1,    23,    88,    -1,    24,    88,
      -1,    25,    78,    -1,    26,    -1,    27,    -1,    28,    84,
      78,    78,    -1,    82,    83,    78,    78,    -1,    29,    81,
      -1,    30,    87,     3,    -1,     1,    -1,    31,    -1,    32,
      -1,    -1,    83,    85,    -1,    83,    86,    -1,    83,    33,
       4,    -1,    -1,    84,    86,    -1,    84,    33,     4,    -1,
      40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    64,    89,    65,    -1,    81,    -1,    81,    61,
      89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   102,   102,   103,   106,   107,   110,   146,   147,   150,
     151,   152,   155,   156,   157,   160,   165,   174,   179,   180,
     181,   182,   190,   200,   210,   220,   226,   233,   241,   250,
     251,   254,   257,   260,   263,   268,   269,   272,   290,   291,
     292,   295,   296,   300,   308,   314,   320,   326,   332,   333,
     336,   337,   340,   341,   344,   345,   346,   347,   348,   349,
     367,   385,   386,   388,   391,   392,   395,   396,   401,   405,
     411,   412,   416,   423,   424,   425,   426,   431,   438,   439,
     440,   441,   448,   449,   452,   455,   456
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IF", "ELSIF",
  "ELSE", "REJCT", "FILEINTO", "REDIRECT", "KEEP", "STOP", "DISCARD",
  "VACATION", "REQUIRE", "SETFLAG", "ADDFLAG", "REMOVEFLAG", "MARK",
  "UNMARK", "NOTIFY", "DENOTIFY", "ANYOF", "ALLOF", "EXISTS", "SFALSE",
  "STRUE", "HEADER", "NOT", "SIZE", "ADDRESS", "ENVELOPE", "COMPARATOR",
  "IS", "CONTAINS", "MATCHES", "REGEX", "OVER", "UNDER", "ALL",
  "LOCALPART", "DOMAIN", "USER", "DETAIL", "DAYS", "ADDRESSES", "SUBJECT",
  "MIME", "FROM", "HANDLE", "METHOD", "ID", "OPTIONS", "LOW", "NORMAL",
  "HIGH", "MESSAGE", "';'", "'['", "']'", "','", "'{'", "'}'", "'('",
  "')'", "$accept", "start", "reqs", "require", "commands", "command",
  "elsif", "action", "ntags", "dtags", "priority", "vtags", "stringlist",
  "strings", "block", "test", "addrorenv", "aetags", "htags",
  "addrparttag", "comptag", "sizetag", "testlist", "tests", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,    59,    91,
      93,    44,   123,   125,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    66,    67,    67,    68,    68,    69,    70,    70,    71,
      71,    71,    72,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    75,    75,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    82,    83,    83,    83,    83,
      84,    84,    84,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    87,    87,    88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     0,     2,     3,     1,     2,     2,
       4,     2,     0,     4,     2,     2,     2,     2,     1,     1,
       1,     3,     2,     2,     2,     1,     1,     2,     2,     0,
       3,     3,     3,     2,     3,     0,     2,     3,     1,     1,
       1,     0,     3,     3,     3,     3,     3,     2,     3,     1,
       1,     3,     3,     2,     2,     2,     2,     1,     1,     4,
       4,     2,     3,     1,     1,     1,     0,     2,     2,     3,
       0,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,     0,     0,     4,    49,     0,     0,     1,     0,
       0,     0,     0,     0,    18,    19,    20,    41,     0,     0,
       0,    25,    26,    29,    35,     3,     0,     0,     5,    50,
       0,     6,    11,    63,     0,     0,     0,    57,    58,    70,
       0,     0,    64,    65,     0,    66,    15,    16,    17,     0,
      22,    23,    24,    27,    28,     8,     9,     0,    48,     0,
      54,    55,    56,     0,    61,    82,    83,     0,     0,    12,
       0,    21,     0,     0,     0,    47,     0,     0,     0,     0,
       0,    38,    39,    40,     0,    33,    78,    79,    80,    81,
      36,     0,    51,    85,     0,     0,     0,    71,    62,    53,
       0,     0,     0,    10,     0,    73,    74,    75,    76,    77,
       0,    67,    68,    42,    43,    44,    46,    45,    31,    30,
      32,    34,    37,     0,    84,    72,    59,    52,     0,    14,
      69,    60,    86,    12,    13
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     3,     4,    25,    26,   103,    27,    53,    54,
      85,    49,     7,    30,    69,    93,    45,    70,    63,   111,
      91,    67,    60,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const short int yypact[] =
{
      29,     2,     7,   119,    11,   -76,    24,   -26,   -76,    -2,
      85,    65,    66,    83,   -76,   -76,   -76,   -76,     2,     2,
       2,   -76,   -76,   -76,   -76,   -76,    63,     9,   -76,    27,
      -1,   -76,   -76,   -76,    25,    25,     2,   -76,   -76,   -76,
      85,    -8,   -76,   -76,    28,   -76,   -76,   -76,   -76,    50,
     -76,   -76,   -76,    91,    67,   -76,   -76,    24,   -76,    85,
     -76,   -76,   -76,     1,   -76,   -76,   -76,    88,     3,    51,
       6,   -76,    90,     2,   101,   -76,   102,   103,   115,   130,
       2,   -76,   -76,   -76,   145,   -76,   -76,   -76,   -76,   -76,
     -76,   146,   -76,    92,    86,   148,     2,   -76,   -76,   -76,
      93,    85,    28,   -76,   150,   -76,   -76,   -76,   -76,   -76,
       2,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,    85,   -76,   -76,   -76,   -76,    28,   -76,
     -76,   -76,   -76,    51,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -76,   -76,   151,   -76,   -17,   -76,    26,   -76,   -76,   -76,
     104,   -76,   -18,   100,   -75,    -7,   -76,   -76,   -76,   -76,
      55,   -76,   125,    38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -8
static const short int yytable[] =
{
      50,    51,    52,    44,     9,     5,     5,     8,    10,    55,
       5,    11,    12,    13,    14,    15,    16,    17,    62,    18,
      19,    20,    21,    22,    23,    24,     1,   129,    29,    -2,
      65,    66,    31,    64,    95,    86,    87,    88,    89,   104,
      86,    87,    88,    89,     1,    96,   105,   106,   107,   108,
     109,   100,   110,   133,    71,   114,    32,   101,   102,    58,
       6,     6,   120,    -7,     9,     6,    99,    56,    10,    46,
      47,    11,    12,    13,    14,    15,    16,    17,   126,    18,
      19,    20,    21,    22,    23,    24,    33,    48,    57,    59,
      68,    98,   131,   113,   128,    72,    73,    74,    75,    76,
      77,    86,    87,    88,    89,   115,   116,   117,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    97,   118,
       9,    81,    82,    83,    10,   112,    -7,    11,    12,    13,
      14,    15,    16,    17,   119,    18,    19,    20,    21,    22,
      23,    24,    78,    79,    80,    81,    82,    83,    84,   121,
     122,   124,   125,   123,   130,    28,   127,    92,    90,   134,
      61,   132
};

static const unsigned char yycheck[] =
{
      18,    19,    20,    10,     1,     4,     4,     0,     5,    26,
       4,     8,     9,    10,    11,    12,    13,    14,    36,    16,
      17,    18,    19,    20,    21,    22,    15,   102,     4,     0,
      38,    39,    58,    40,    33,    34,    35,    36,    37,    33,
      34,    35,    36,    37,    15,    63,    40,    41,    42,    43,
      44,    68,    70,   128,     4,    73,    58,     6,     7,    60,
      59,    59,    80,     0,     1,    59,    63,    58,     5,     4,
       4,     8,     9,    10,    11,    12,    13,    14,    96,    16,
      17,    18,    19,    20,    21,    22,     1,     4,    61,    64,
      62,     3,   110,     3,   101,    45,    46,    47,    48,    49,
      50,    34,    35,    36,    37,     4,     4,     4,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    63,     4,
       1,    54,    55,    56,     5,    70,    63,     8,     9,    10,
      11,    12,    13,    14,     4,    16,    17,    18,    19,    20,
      21,    22,    51,    52,    53,    54,    55,    56,    57,     4,
       4,    65,     4,    61,     4,     4,    63,    57,    54,   133,
      35,   123
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    15,    67,    68,    69,     4,    59,    78,     0,     1,
       5,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      18,    19,    20,    21,    22,    70,    71,    73,    68,     4,
      79,    58,    58,     1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    81,    82,     4,     4,     4,    77,
      78,    78,    78,    74,    75,    70,    58,    61,    60,    64,
      88,    88,    78,    84,    81,    38,    39,    87,    62,    80,
      83,     4,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    76,    34,    35,    36,    37,
      76,    86,    79,    81,    89,    33,    78,    86,     3,    63,
      70,     6,     7,    72,    33,    40,    41,    42,    43,    44,
      78,    85,    86,     3,    78,     4,     4,     4,     4,     4,
      78,     4,     4,    61,    65,     4,    78,    63,    81,    80,
       4,    78,    89,    80,    72
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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
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

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 102 "sieve.y"
    { ret = NULL; }
    break;

  case 3:
#line 103 "sieve.y"
    { ret = (yyvsp[0].cl); }
    break;

  case 6:
#line 110 "sieve.y"
    {
                                    int i = 1;
                                    char *msg;
                                    char *freemsg;
                                    stringlist_t *s;
                                    stringlist_t *sl = (yyvsp[-1].sl);

                                    msg = libsieve_strconcat("unsupported feature:", NULL);

                                    while (sl != NULL) {
                                        s = sl;
                                        sl = sl->next;

                                        i &= static_check_reqs(parse_context, s->s);
                                        if (!i) {
                                            freemsg = msg;
                                            msg = libsieve_strconcat(freemsg, " ", s->s, NULL);
                                            libsieve_free(freemsg);
                                        }

                                        libsieve_free(s->s);
                                        libsieve_free(s);
                                    }

                                    if (!i) {
                                        libsieve_sieveerror(msg);
                                        libsieve_free(msg);
                                        YYERROR; 
                                    }

                                    /* This needs to be free'd regardless of error */
                                    libsieve_free(msg);

                                }
    break;

  case 7:
#line 146 "sieve.y"
    { (yyval.cl) = (yyvsp[0].cl); }
    break;

  case 8:
#line 147 "sieve.y"
    { (yyvsp[-1].cl)->next = (yyvsp[0].cl); (yyval.cl) = (yyvsp[-1].cl); }
    break;

  case 9:
#line 150 "sieve.y"
    { (yyval.cl) = (yyvsp[-1].cl); }
    break;

  case 10:
#line 151 "sieve.y"
    { (yyval.cl) = libsieve_new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl)); }
    break;

  case 11:
#line 152 "sieve.y"
    { (yyval.cl) = libsieve_new_command(STOP); }
    break;

  case 12:
#line 155 "sieve.y"
    { (yyval.cl) = NULL; }
    break;

  case 13:
#line 156 "sieve.y"
    { (yyval.cl) = libsieve_new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl)); }
    break;

  case 14:
#line 157 "sieve.y"
    { (yyval.cl) = (yyvsp[0].cl); }
    break;

  case 15:
#line 160 "sieve.y"
    { if (!parse_context->require.reject) {
				     libsieve_sieveerror("reject not required");
				     YYERROR;
				   }
				   (yyval.cl) = libsieve_new_command(REJCT); (yyval.cl)->u.str = (yyvsp[0].sval); }
    break;

  case 16:
#line 165 "sieve.y"
    { if (!parse_context->require.fileinto) {
				     libsieve_sieveerror("fileinto not required");
	                             YYERROR;
                                   }
				   if (!static_verify_mailbox((yyvsp[0].sval))) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           (yyval.cl) = libsieve_new_command(FILEINTO);
				   (yyval.cl)->u.str = (yyvsp[0].sval); }
    break;

  case 17:
#line 174 "sieve.y"
    { (yyval.cl) = libsieve_new_command(REDIRECT);
				   if (!static_verify_address((yyvsp[0].sval))) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   (yyval.cl)->u.str = (yyvsp[0].sval); }
    break;

  case 18:
#line 179 "sieve.y"
    { (yyval.cl) = libsieve_new_command(KEEP); }
    break;

  case 19:
#line 180 "sieve.y"
    { (yyval.cl) = libsieve_new_command(STOP); }
    break;

  case 20:
#line 181 "sieve.y"
    { (yyval.cl) = libsieve_new_command(DISCARD); }
    break;

  case 21:
#line 182 "sieve.y"
    { if (!parse_context->require.vacation) {
				     libsieve_sieveerror("vacation not required");
				     (yyval.cl) = libsieve_new_command(VACATION);
				     YYERROR;
				   } else {
  				     (yyval.cl) = static_build_vacation(VACATION,
					    static_canon_vtags((yyvsp[-1].vtag)), (yyvsp[0].sval));
				   } }
    break;

  case 22:
#line 190 "sieve.y"
    { if (!parse_context->require.imapflags) {
	// TODO: imap4flags.
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                   }
                                  if (!static_verify_stringlist((yyvsp[0].sl), static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  (yyval.cl) = libsieve_new_command(SETFLAG);
                                  (yyval.cl)->u.sl = (yyvsp[0].sl); }
    break;

  case 23:
#line 200 "sieve.y"
    { if (!parse_context->require.imapflags) {
	 // TODO: imap4flags
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist((yyvsp[0].sl), static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  (yyval.cl) = libsieve_new_command(ADDFLAG);
                                  (yyval.cl)->u.sl = (yyvsp[0].sl); }
    break;

  case 24:
#line 210 "sieve.y"
    { if (!parse_context->require.imapflags) {
	 // TODO: imap4flags
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist((yyvsp[0].sl), static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  (yyval.cl) = libsieve_new_command(REMOVEFLAG);
                                  (yyval.cl)->u.sl = (yyvsp[0].sl); }
    break;

  case 25:
#line 220 "sieve.y"
    { if (!parse_context->require.imapflags) {
	 // TODO: this isn't in imap4flags
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  (yyval.cl) = libsieve_new_command(MARK); }
    break;

  case 26:
#line 226 "sieve.y"
    { if (!parse_context->require.imapflags) {
	 // TODO: this isn't in imap4flags
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  (yyval.cl) = libsieve_new_command(UNMARK); }
    break;

  case 27:
#line 233 "sieve.y"
    { if (!parse_context->require.notify) {
				       libsieve_sieveerror("notify not required");
				       (yyval.cl) = libsieve_new_command(NOTIFY); 
				       YYERROR;
	 			    } else {
				      (yyval.cl) = static_build_notify(NOTIFY,
				             static_canon_ntags((yyvsp[0].ntag)));
				    } }
    break;

  case 28:
#line 241 "sieve.y"
    { if (!parse_context->require.notify) {
                                       libsieve_sieveerror("notify not required");
				       (yyval.cl) = libsieve_new_command(DENOTIFY);
				       YYERROR;
				    } else {
					(yyval.cl) = static_build_denotify(DENOTIFY, (yyvsp[0].dtag));
				    } }
    break;

  case 29:
#line 250 "sieve.y"
    { (yyval.ntag) = static_new_ntags(); }
    break;

  case 30:
#line 251 "sieve.y"
    { if ((yyval.ntag)->id != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { (yyval.ntag)->id = (yyvsp[0].sval); } }
    break;

  case 31:
#line 254 "sieve.y"
    { if ((yyval.ntag)->method != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { (yyval.ntag)->method = (yyvsp[0].sval); } }
    break;

  case 32:
#line 257 "sieve.y"
    { if ((yyval.ntag)->options != NULL) { 
					libsieve_sieveerror("duplicate :options"); YYERROR; }
				     else { (yyval.ntag)->options = (yyvsp[0].sl); } }
    break;

  case 33:
#line 260 "sieve.y"
    { if ((yyval.ntag)->priority != NULL) { 
					libsieve_sieveerror("duplicate :priority"); YYERROR; }
				   else { (yyval.ntag)->priority = (yyvsp[0].sval); } }
    break;

  case 34:
#line 263 "sieve.y"
    { if ((yyval.ntag)->message != NULL) { 
					libsieve_sieveerror("duplicate :message"); YYERROR; }
				   else { (yyval.ntag)->message = (yyvsp[0].sval); } }
    break;

  case 35:
#line 268 "sieve.y"
    { (yyval.dtag) = static_new_dtags(); }
    break;

  case 36:
#line 269 "sieve.y"
    { if ((yyval.dtag)->priority != NULL) { 
				libsieve_sieveerror("duplicate priority level"); YYERROR; }
				   else { (yyval.dtag)->priority = (yyvsp[0].sval); } }
    break;

  case 37:
#line 272 "sieve.y"
    { if ((yyval.dtag)->comptag != -1) { 
				libsieve_sieveerror("duplicate comparator type tag"); YYERROR;
				   } else {
				       (yyval.dtag)->comptag = (yyvsp[-1].nval);
#ifdef ENABLE_REGEX
				       if ((yyval.dtag)->comptag == REGEX) {
					   int cflags = REG_EXTENDED |
					       REG_NOSUB | REG_ICASE;
					   (yyval.dtag)->pattern =
					       (void*) static_verify_regex((yyvsp[0].sval), cflags);
					   if (!(yyval.dtag)->pattern) { YYERROR; }
				       }
				       else
#endif
					   (yyval.dtag)->pattern = (yyvsp[0].sval);
				   } }
    break;

  case 38:
#line 290 "sieve.y"
    { (yyval.sval) = "low"; }
    break;

  case 39:
#line 291 "sieve.y"
    { (yyval.sval) = "normal"; }
    break;

  case 40:
#line 292 "sieve.y"
    { (yyval.sval) = "high"; }
    break;

  case 41:
#line 295 "sieve.y"
    { (yyval.vtag) = static_new_vtags(); }
    break;

  case 42:
#line 296 "sieve.y"
    { if ((yyval.vtag)->days != -1) { 
					libsieve_sieveerror("duplicate :days");
					YYERROR; }
				   else { (yyval.vtag)->days = (yyvsp[0].nval); } }
    break;

  case 43:
#line 300 "sieve.y"
    { if ((yyval.vtag)->addresses != NULL) { 
					libsieve_sieveerror("duplicate :addresses"); 
					YYERROR;
				       } else if (!static_verify_stringlist((yyvsp[0].sl),
							static_verify_address)) {
					  YYERROR;
				       } else {
					 (yyval.vtag)->addresses = (yyvsp[0].sl); } }
    break;

  case 44:
#line 308 "sieve.y"
    { if ((yyval.vtag)->subject != NULL) { 
					libsieve_sieveerror("duplicate :subject"); 
					YYERROR;
				   } else if (!static_ok_header((yyvsp[0].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->subject = (yyvsp[0].sval); } }
    break;

  case 45:
#line 314 "sieve.y"
    { if ((yyval.vtag)->handle != NULL) { 
					libsieve_sieveerror("duplicate :handle"); 
					YYERROR;
				   } else if (!static_ok_header((yyvsp[0].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->handle = (yyvsp[0].sval); } }
    break;

  case 46:
#line 320 "sieve.y"
    { if ((yyval.vtag)->from != NULL) { 
					libsieve_sieveerror("duplicate :from"); 
					YYERROR;
				   } else if (!static_ok_header((yyvsp[0].sval))) {
					YYERROR;
				   } else { (yyval.vtag)->from = (yyvsp[0].sval); } }
    break;

  case 47:
#line 326 "sieve.y"
    { if ((yyval.vtag)->mime != -1) { 
					libsieve_sieveerror("duplicate :mime"); 
					YYERROR; }
				   else { (yyval.vtag)->mime = MIME; } }
    break;

  case 48:
#line 332 "sieve.y"
    { (yyval.sl) = (yyvsp[-1].sl); }
    break;

  case 49:
#line 333 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[0].sval), NULL); }
    break;

  case 50:
#line 336 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[0].sval), NULL); }
    break;

  case 51:
#line 337 "sieve.y"
    { (yyval.sl) = libsieve_new_sl((yyvsp[-2].sval), (yyvsp[0].sl)); }
    break;

  case 52:
#line 340 "sieve.y"
    { (yyval.cl) = (yyvsp[-1].cl); }
    break;

  case 53:
#line 341 "sieve.y"
    { (yyval.cl) = NULL; }
    break;

  case 54:
#line 344 "sieve.y"
    { (yyval.test) = libsieve_new_test(ANYOF); (yyval.test)->u.tl = (yyvsp[0].testl); }
    break;

  case 55:
#line 345 "sieve.y"
    { (yyval.test) = libsieve_new_test(ALLOF); (yyval.test)->u.tl = (yyvsp[0].testl); }
    break;

  case 56:
#line 346 "sieve.y"
    { (yyval.test) = libsieve_new_test(EXISTS); (yyval.test)->u.sl = (yyvsp[0].sl); }
    break;

  case 57:
#line 347 "sieve.y"
    { (yyval.test) = libsieve_new_test(SFALSE); }
    break;

  case 58:
#line 348 "sieve.y"
    { (yyval.test) = libsieve_new_test(STRUE); }
    break;

  case 59:
#line 350 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist((yyvsp[-1].sl), static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   (yyvsp[-2].htag) = static_canon_htags((yyvsp[-2].htag));
#ifdef ENABLE_REGEX
				   if ((yyvsp[-2].htag)->comptag == REGEX) {
				     pl = static_verify_regexs((yyvsp[0].sl), (yyvsp[-2].htag)->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) (yyvsp[0].sl);
				       
				   (yyval.test) = static_build_header(HEADER, (yyvsp[-2].htag), (yyvsp[-1].sl), pl);
				   if ((yyval.test) == NULL) { YYERROR; } }
    break;

  case 60:
#line 368 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist((yyvsp[-1].sl), static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   (yyvsp[-2].aetag) = static_canon_aetags((yyvsp[-2].aetag));
#ifdef ENABLE_REGEX
				   if ((yyvsp[-2].aetag)->comptag == REGEX) {
				     pl = static_verify_regexs((yyvsp[0].sl), (yyvsp[-2].aetag)->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) (yyvsp[0].sl);
				       
				   (yyval.test) = static_build_address((yyvsp[-3].nval), (yyvsp[-2].aetag), (yyvsp[-1].sl), pl);
				   if ((yyval.test) == NULL) { YYERROR; } }
    break;

  case 61:
#line 385 "sieve.y"
    { (yyval.test) = libsieve_new_test(NOT); (yyval.test)->u.t = (yyvsp[0].test); }
    break;

  case 62:
#line 386 "sieve.y"
    { (yyval.test) = libsieve_new_test(SIZE); (yyval.test)->u.sz.t = (yyvsp[-1].nval);
		                   (yyval.test)->u.sz.n = (yyvsp[0].nval); }
    break;

  case 63:
#line 388 "sieve.y"
    { (yyval.test) = NULL; }
    break;

  case 64:
#line 391 "sieve.y"
    { (yyval.nval) = ADDRESS; }
    break;

  case 65:
#line 392 "sieve.y"
    { (yyval.nval) = ENVELOPE; }
    break;

  case 66:
#line 395 "sieve.y"
    { (yyval.aetag) = static_new_aetags(); }
    break;

  case 67:
#line 396 "sieve.y"
    { (yyval.aetag) = (yyvsp[-1].aetag);
				   if ((yyval.aetag)->addrtag != -1) { 
			libsieve_sieveerror("duplicate or conflicting address part tag");
			YYERROR; }
				   else { (yyval.aetag)->addrtag = (yyvsp[0].nval); } }
    break;

  case 68:
#line 401 "sieve.y"
    { (yyval.aetag) = (yyvsp[-1].aetag);
				   if ((yyval.aetag)->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { (yyval.aetag)->comptag = (yyvsp[0].nval); } }
    break;

  case 69:
#line 405 "sieve.y"
    { (yyval.aetag) = (yyvsp[-2].aetag);
				   if ((yyval.aetag)->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag"); YYERROR; }
				   else { (yyval.aetag)->comparator = (yyvsp[0].sval); } }
    break;

  case 70:
#line 411 "sieve.y"
    { (yyval.htag) = static_new_htags(); }
    break;

  case 71:
#line 412 "sieve.y"
    { (yyval.htag) = (yyvsp[-1].htag);
				   if ((yyval.htag)->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { (yyval.htag)->comptag = (yyvsp[0].nval); } }
    break;

  case 72:
#line 416 "sieve.y"
    { (yyval.htag) = (yyvsp[-2].htag);
				   if ((yyval.htag)->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag");
					YYERROR; }
				   else { (yyval.htag)->comparator = (yyvsp[0].sval); } }
    break;

  case 73:
#line 423 "sieve.y"
    { (yyval.nval) = ALL; }
    break;

  case 74:
#line 424 "sieve.y"
    { (yyval.nval) = LOCALPART; }
    break;

  case 75:
#line 425 "sieve.y"
    { (yyval.nval) = DOMAIN; }
    break;

  case 76:
#line 426 "sieve.y"
    { if (!parse_context->require.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   (yyval.nval) = USER; }
    break;

  case 77:
#line 431 "sieve.y"
    { if (!parse_context->require.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   (yyval.nval) = DETAIL; }
    break;

  case 78:
#line 438 "sieve.y"
    { (yyval.nval) = IS; }
    break;

  case 79:
#line 439 "sieve.y"
    { (yyval.nval) = CONTAINS; }
    break;

  case 80:
#line 440 "sieve.y"
    { (yyval.nval) = MATCHES; }
    break;

  case 81:
#line 441 "sieve.y"
    { if (!parse_context->require.regex) {
				     libsieve_sieveerror("regex not required");
				     YYERROR;
				   }
				   (yyval.nval) = REGEX; }
    break;

  case 82:
#line 448 "sieve.y"
    { (yyval.nval) = OVER; }
    break;

  case 83:
#line 449 "sieve.y"
    { (yyval.nval) = UNDER; }
    break;

  case 84:
#line 452 "sieve.y"
    { (yyval.testl) = (yyvsp[-1].testl); }
    break;

  case 85:
#line 455 "sieve.y"
    { (yyval.testl) = libsieve_new_testlist((yyvsp[0].test), NULL); }
    break;

  case 86:
#line 456 "sieve.y"
    { (yyval.testl) = libsieve_new_testlist((yyvsp[-2].test), (yyvsp[0].testl)); }
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2057 "sieve.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
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
	  int yychecklim = YYLAST - yyn;
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
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
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
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
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
	  yydestruct ("Error: discarding", yytoken, &yylval);
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
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 459 "sieve.y"


char *libsieve_sieveptr;         /* pointer to sieve string for address lexer */
char *libsieve_sieveerr;         /* buffer for sieve parser error messages */

commandlist_t *libsieve_sieve_parse_buffer(struct sieve2_context *context)
{
    commandlist_t *t;
    extern commandlist_t *ret;

    parse_context = context;

    libsieve_sieveptr = context->script.script;
    libsieve_sieveerr = NULL;

    libsieve_sievelexrestart();

    if (libsieve_sieveparse()) {
	return NULL;
    } else {
        t = ret;
	ret = NULL;
	return t;
    }
}

/* This gets called by the address parser,
 * which does not have access to the context. */
int libsieve_sieveerror_exec(char *msg)
{
    parse_context->exec_errors++;

    libsieve_do_error_exec(parse_context, msg);

    return 0;
}

int libsieve_sieveerror(char *msg)
{
    extern int libsieve_sievelineno;

    parse_context->parse_errors++;

    libsieve_do_error_parse(parse_context, libsieve_sievelineno, msg);

    return 0;
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
    r->handle = NULL;
    r->from = NULL;
    r->mime = -1;

    return r;
}

static struct vtags *static_canon_vtags(struct vtags *v)
{
/* TODO: Rewrite this. The deal here is that the client app
 * might want to specify min_response and max_response days.
 * libSieve should respect the client app's requests. For
 * right now, we're going to just leave these along and let
 * the script do whatever it wants. Eventually we need a 
 * context registration for this, though. */
//    assert(parse_script->interp.vacation != NULL);

    if (v->days == -1) { v->days = 7; }
    /*
    if (v->days < parse_script->interp.vacation->min_response) 
       { v->days = parse_script->interp.vacation->min_response; }
    if (v->days > parse_script->interp.vacation->max_response)
       { v->days = parse_script->interp.vacation->max_response; }
    */
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

char *libsieve_addrptr;		/* pointer to sieve string for address lexer */
char *libsieve_addrerr;		/* buffer for sieve parser error messages */

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

static int static_verify_mailbox(const char *s UNUSED)
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

    if ((ret = libsieve_regcomp(reg, s, cflags)) != 0) {
	(void) libsieve_regerror(ret, reg, errbuf, sizeof(errbuf));
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
	if ((reg = static_verify_regex(sl2->s, cflags)) == NULL) {
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
    } else if (!strcmp("imapflags", req)) {
        return c->require.imapflags = c->support.imapflags;
    } else if (!strcmp("notify",req)) {
        return c->require.notify = c->support.notify;
#ifdef ENABLE_REGEX
    /* If regex is enabled then it is supported. */
    } else if (!strcmp("regex", req)) {
	return c->require.regex = 1;
#endif
    /* TODO: Perhaps add a callback to let the client
     * perform its own subaddress calculations? Useful
     * for systems that use something other than the
     * Cyrus style username+mailbox@domain format.*/
    } else if (!strcmp("subaddress", req)) {
	return c->require.subaddress = 1;
    /* These comparators are built into the parser. */
    } else if (!strcmp("comparator-i;octet", req)) {
	return 1;
    } else if (!strcmp("comparator-i;ascii-casemap", req)) {
	return 1;
    }
    /* If we don't recognize it, then we don't support it! */
    return 0;
}


