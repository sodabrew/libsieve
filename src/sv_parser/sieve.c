/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 59 "sieve.y"
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
/* Line 191 of yacc.c.  */
#line 264 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 276 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  24
/* YYNRULES -- Number of rules. */
#define YYNRULES  84
/* YYNRULES -- Number of states. */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      62,    63,     2,     2,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    56,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      55
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
     110,   112,   113,   117,   121,   125,   128,   132,   134,   136,
     140,   144,   147,   150,   153,   156,   158,   160,   165,   170,
     173,   177,   179,   181,   183,   184,   187,   190,   194,   195,
     198,   202,   204,   206,   208,   210,   212,   214,   216,   218,
     220,   222,   224,   228,   230
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      65,     0,    -1,    -1,    66,    68,    -1,    -1,    67,    66,
      -1,    15,    76,    56,    -1,    69,    -1,    69,    68,    -1,
      71,    56,    -1,     5,    79,    78,    70,    -1,     1,    56,
      -1,    -1,     6,    79,    78,    70,    -1,     7,    78,    -1,
       8,     4,    -1,     9,     4,    -1,    10,     4,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    75,     4,    -1,    16,
      76,    -1,    17,    76,    -1,    18,    76,    -1,    19,    -1,
      20,    -1,    21,    72,    -1,    22,    73,    -1,    -1,    72,
      50,     4,    -1,    72,    49,     4,    -1,    72,    51,    76,
      -1,    72,    74,    -1,    72,    55,     4,    -1,    -1,    73,
      74,    -1,    73,    84,     4,    -1,    52,    -1,    53,    -1,
      54,    -1,    -1,    75,    45,     3,    -1,    75,    46,    76,
      -1,    75,    47,     4,    -1,    75,    48,    -1,    57,    77,
      58,    -1,     4,    -1,     4,    -1,     4,    59,    77,    -1,
      60,    68,    61,    -1,    60,    61,    -1,    23,    86,    -1,
      24,    86,    -1,    25,    76,    -1,    26,    -1,    27,    -1,
      28,    82,    76,    76,    -1,    80,    81,    76,    76,    -1,
      29,    79,    -1,    30,    85,     3,    -1,     1,    -1,    31,
      -1,    32,    -1,    -1,    81,    83,    -1,    81,    84,    -1,
      81,    33,     4,    -1,    -1,    82,    84,    -1,    82,    33,
       4,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    62,    87,    63,    -1,    79,    -1,
      79,    59,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    99,    99,   100,   103,   104,   107,   143,   144,   147,
     148,   149,   152,   153,   154,   157,   162,   171,   176,   177,
     178,   179,   187,   196,   205,   214,   219,   225,   233,   242,
     243,   246,   249,   252,   255,   260,   261,   264,   282,   283,
     284,   287,   288,   291,   299,   305,   311,   312,   315,   316,
     319,   320,   323,   324,   325,   326,   327,   328,   346,   364,
     365,   367,   370,   371,   374,   375,   380,   384,   390,   391,
     395,   402,   403,   404,   405,   410,   417,   418,   419,   420,
     427,   428,   431,   434,   435
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IF", "ELSIF", "ELSE", 
  "REJCT", "FILEINTO", "REDIRECT", "KEEP", "STOP", "DISCARD", "VACATION", 
  "REQUIRE", "SETFLAG", "ADDFLAG", "REMOVEFLAG", "MARK", "UNMARK", 
  "NOTIFY", "DENOTIFY", "ANYOF", "ALLOF", "EXISTS", "SFALSE", "STRUE", 
  "HEADER", "NOT", "SIZE", "ADDRESS", "ENVELOPE", "COMPARATOR", "IS", 
  "CONTAINS", "MATCHES", "REGEX", "OVER", "UNDER", "ALL", "LOCALPART", 
  "DOMAIN", "USER", "DETAIL", "DAYS", "ADDRESSES", "SUBJECT", "MIME", 
  "METHOD", "ID", "OPTIONS", "LOW", "NORMAL", "HIGH", "MESSAGE", "';'", 
  "'['", "']'", "','", "'{'", "'}'", "'('", "')'", "$accept", "start", 
  "reqs", "require", "commands", "command", "elsif", "action", "ntags", 
  "dtags", "priority", "vtags", "stringlist", "strings", "block", "test", 
  "addrorenv", "aetags", "htags", "addrparttag", "comptag", "sizetag", 
  "testlist", "tests", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,    59,    91,    93,    44,
     123,   125,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    64,    65,    65,    66,    66,    67,    68,    68,    69,
      69,    69,    70,    70,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    72,    72,    72,    73,    73,    73,    74,    74,
      74,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      82,    83,    83,    83,    83,    83,    84,    84,    84,    84,
      85,    85,    86,    87,    87
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     0,     2,     3,     1,     2,     2,
       4,     2,     0,     4,     2,     2,     2,     2,     1,     1,
       1,     3,     2,     2,     2,     1,     1,     2,     2,     0,
       3,     3,     3,     2,     3,     0,     2,     3,     1,     1,
       1,     0,     3,     3,     3,     2,     3,     1,     1,     3,
       3,     2,     2,     2,     2,     1,     1,     4,     4,     2,
       3,     1,     1,     1,     0,     2,     2,     3,     0,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,     0,     0,     4,    47,     0,     0,     1,     0,
       0,     0,     0,     0,    18,    19,    20,    41,     0,     0,
       0,    25,    26,    29,    35,     3,     0,     0,     5,    48,
       0,     6,    11,    61,     0,     0,     0,    55,    56,    68,
       0,     0,    62,    63,     0,    64,    15,    16,    17,     0,
      22,    23,    24,    27,    28,     8,     9,     0,    46,     0,
      52,    53,    54,     0,    59,    80,    81,     0,     0,    12,
       0,    21,     0,     0,     0,    45,     0,     0,     0,    38,
      39,    40,     0,    33,    76,    77,    78,    79,    36,     0,
      49,    83,     0,     0,     0,    69,    60,    51,     0,     0,
       0,    10,     0,    71,    72,    73,    74,    75,     0,    65,
      66,    42,    43,    44,    31,    30,    32,    34,    37,     0,
      82,    70,    57,    50,     0,    14,    67,    58,    84,    12,
      13
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,     3,     4,    25,    26,   101,    27,    53,    54,
      83,    49,     7,    30,    69,    91,    45,    70,    63,   109,
      89,    67,    60,    92
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const short yypact[] =
{
       6,     0,     8,   133,    -3,   -84,    16,   -43,   -84,   -34,
     101,    20,    21,    38,   -84,   -84,   -84,   -84,     0,     0,
       0,   -84,   -84,   -84,   -84,   -84,    53,   -13,   -84,   -15,
      -8,   -84,   -84,   -84,    15,    15,     0,   -84,   -84,   -84,
     101,   -28,   -84,   -84,    -1,   -84,   -84,   -84,   -84,     1,
     -84,   -84,   -84,   107,    59,   -84,   -84,    16,   -84,   101,
     -84,   -84,   -84,    52,   -84,   -84,   -84,    75,    18,     9,
      64,   -84,    77,     0,    78,   -84,    79,    80,     0,   -84,
     -84,   -84,    87,   -84,   -84,   -84,   -84,   -84,   -84,    99,
     -84,    22,    47,   111,     0,   -84,   -84,   -84,    55,   101,
      -1,   -84,   113,   -84,   -84,   -84,   -84,   -84,     0,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   101,
     -84,   -84,   -84,   -84,    -1,   -84,   -84,   -84,   -84,     9,
     -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -84,   -84,   114,   -84,   -17,   -84,   -10,   -84,   -84,   -84,
      66,   -84,   -18,    65,   -83,    -7,   -84,   -84,   -84,   -84,
     -56,   -84,    88,    17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -8
static const short yytable[] =
{
      50,    51,    52,    44,     5,    71,    -2,    95,     8,    55,
      65,    66,     1,    31,   110,    99,   100,   125,    62,     9,
      29,     1,    32,    10,    46,    47,    11,    12,    13,    14,
      15,    16,    17,    64,    18,    19,    20,    21,    22,    23,
      24,   129,    48,    56,    57,    94,    72,    73,    74,    75,
      58,    98,   108,    -7,     9,   112,     5,     6,    10,    68,
     116,    11,    12,    13,    14,    15,    16,    17,     5,    18,
      19,    20,    21,    22,    23,    24,   122,    59,    96,    97,
     111,   119,   113,   114,   115,    93,    84,    85,    86,    87,
     127,   117,   124,    84,    85,    86,    87,   102,    84,    85,
      86,    87,    33,   118,   103,   104,   105,   106,   107,     6,
     120,    79,    80,    81,    -7,   121,   123,   126,    28,   130,
      88,     6,    90,    61,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     9,     0,   128,     0,    10,     0,
       0,    11,    12,    13,    14,    15,    16,    17,     0,    18,
      19,    20,    21,    22,    23,    24,    76,    77,    78,    79,
      80,    81,    82
};

static const short yycheck[] =
{
      18,    19,    20,    10,     4,     4,     0,    63,     0,    26,
      38,    39,    15,    56,    70,     6,     7,   100,    36,     1,
       4,    15,    56,     5,     4,     4,     8,     9,    10,    11,
      12,    13,    14,    40,    16,    17,    18,    19,    20,    21,
      22,   124,     4,    56,    59,    63,    45,    46,    47,    48,
      58,    68,    70,     0,     1,    73,     4,    57,     5,    60,
      78,     8,     9,    10,    11,    12,    13,    14,     4,    16,
      17,    18,    19,    20,    21,    22,    94,    62,     3,    61,
       3,    59,     4,     4,     4,    33,    34,    35,    36,    37,
     108,     4,    99,    34,    35,    36,    37,    33,    34,    35,
      36,    37,     1,     4,    40,    41,    42,    43,    44,    57,
      63,    52,    53,    54,    61,     4,    61,     4,     4,   129,
      54,    57,    57,    35,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    -1,   119,    -1,     5,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    22,    49,    50,    51,    52,
      53,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    15,    65,    66,    67,     4,    57,    76,     0,     1,
       5,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      18,    19,    20,    21,    22,    68,    69,    71,    66,     4,
      77,    56,    56,     1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    79,    80,     4,     4,     4,    75,
      76,    76,    76,    72,    73,    68,    56,    59,    58,    62,
      86,    86,    76,    82,    79,    38,    39,    85,    60,    78,
      81,     4,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    74,    34,    35,    36,    37,    74,    84,
      77,    79,    87,    33,    76,    84,     3,    61,    68,     6,
       7,    70,    33,    40,    41,    42,    43,    44,    76,    83,
      84,     3,    76,     4,     4,     4,    76,     4,     4,    59,
      63,     4,    76,    61,    79,    78,     4,    76,    87,    78,
      70
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


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
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
  register const char *yys = yystr;

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
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



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
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
#line 99 "sieve.y"
    { ret = NULL; }
    break;

  case 3:
#line 100 "sieve.y"
    { ret = yyvsp[0].cl; }
    break;

  case 6:
#line 107 "sieve.y"
    {
                                    int i = 1;
                                    char *msg;
                                    char *freemsg;
                                    stringlist_t *s;
                                    stringlist_t *sl = yyvsp[-1].sl;

                                    msg = libsieve_strconcat("unsupported feature:", NULL);

                                    while (sl != NULL) {
                                        s = sl;
                                        sl = sl->next;

                                        i &= static_check_reqs(parse_script, s->s);
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
#line 143 "sieve.y"
    { yyval.cl = yyvsp[0].cl; }
    break;

  case 8:
#line 144 "sieve.y"
    { yyvsp[-1].cl->next = yyvsp[0].cl; yyval.cl = yyvsp[-1].cl; }
    break;

  case 9:
#line 147 "sieve.y"
    { yyval.cl = yyvsp[-1].cl; }
    break;

  case 10:
#line 148 "sieve.y"
    { yyval.cl = libsieve_new_if(yyvsp[-2].test, yyvsp[-1].cl, yyvsp[0].cl); }
    break;

  case 11:
#line 149 "sieve.y"
    { yyval.cl = libsieve_new_command(STOP); }
    break;

  case 12:
#line 152 "sieve.y"
    { yyval.cl = NULL; }
    break;

  case 13:
#line 153 "sieve.y"
    { yyval.cl = libsieve_new_if(yyvsp[-2].test, yyvsp[-1].cl, yyvsp[0].cl); }
    break;

  case 14:
#line 154 "sieve.y"
    { yyval.cl = yyvsp[0].cl; }
    break;

  case 15:
#line 157 "sieve.y"
    { if (!parse_script->support.reject) {
				     libsieve_sieveerror("reject not required");
				     YYERROR;
				   }
				   yyval.cl = libsieve_new_command(REJCT); yyval.cl->u.str = yyvsp[0].sval; }
    break;

  case 16:
#line 162 "sieve.y"
    { if (!parse_script->support.fileinto) {
				     libsieve_sieveerror("fileinto not required");
	                             YYERROR;
                                   }
				   if (!static_verify_mailbox(yyvsp[0].sval)) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           yyval.cl = libsieve_new_command(FILEINTO);
				   yyval.cl->u.str = yyvsp[0].sval; }
    break;

  case 17:
#line 171 "sieve.y"
    { yyval.cl = libsieve_new_command(REDIRECT);
				   if (!static_verify_address(yyvsp[0].sval)) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   yyval.cl->u.str = yyvsp[0].sval; }
    break;

  case 18:
#line 176 "sieve.y"
    { yyval.cl = libsieve_new_command(KEEP); }
    break;

  case 19:
#line 177 "sieve.y"
    { yyval.cl = libsieve_new_command(STOP); }
    break;

  case 20:
#line 178 "sieve.y"
    { yyval.cl = libsieve_new_command(DISCARD); }
    break;

  case 21:
#line 179 "sieve.y"
    { if (!parse_script->support.vacation) {
				     libsieve_sieveerror("vacation not required");
				     yyval.cl = libsieve_new_command(VACATION);
				     YYERROR;
				   } else {
  				     yyval.cl = static_build_vacation(VACATION,
					    static_canon_vtags(yyvsp[-1].vtag), yyvsp[0].sval);
				   } }
    break;

  case 22:
#line 187 "sieve.y"
    { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                   }
                                  if (!static_verify_stringlist(yyvsp[0].sl, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = libsieve_new_command(SETFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;

  case 23:
#line 196 "sieve.y"
    { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist(yyvsp[0].sl, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = libsieve_new_command(ADDFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;

  case 24:
#line 205 "sieve.y"
    { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!static_verify_stringlist(yyvsp[0].sl, static_verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = libsieve_new_command(REMOVEFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;

  case 25:
#line 214 "sieve.y"
    { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  yyval.cl = libsieve_new_command(MARK); }
    break;

  case 26:
#line 219 "sieve.y"
    { if (!parse_script->support.imapflags) {
                                    libsieve_sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  yyval.cl = libsieve_new_command(UNMARK); }
    break;

  case 27:
#line 225 "sieve.y"
    { if (!parse_script->support.notify) {
				       libsieve_sieveerror("notify not required");
				       yyval.cl = libsieve_new_command(NOTIFY); 
				       YYERROR;
	 			    } else {
				      yyval.cl = static_build_notify(NOTIFY,
				             static_canon_ntags(yyvsp[0].ntag));
				    } }
    break;

  case 28:
#line 233 "sieve.y"
    { if (!parse_script->support.notify) {
                                       libsieve_sieveerror("notify not required");
				       yyval.cl = libsieve_new_command(DENOTIFY);
				       YYERROR;
				    } else {
					yyval.cl = static_build_denotify(DENOTIFY, yyvsp[0].dtag);
				    } }
    break;

  case 29:
#line 242 "sieve.y"
    { yyval.ntag = static_new_ntags(); }
    break;

  case 30:
#line 243 "sieve.y"
    { if (yyval.ntag->id != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { yyval.ntag->id = yyvsp[0].sval; } }
    break;

  case 31:
#line 246 "sieve.y"
    { if (yyval.ntag->method != NULL) { 
					libsieve_sieveerror("duplicate :method"); YYERROR; }
				   else { yyval.ntag->method = yyvsp[0].sval; } }
    break;

  case 32:
#line 249 "sieve.y"
    { if (yyval.ntag->options != NULL) { 
					libsieve_sieveerror("duplicate :options"); YYERROR; }
				     else { yyval.ntag->options = yyvsp[0].sl; } }
    break;

  case 33:
#line 252 "sieve.y"
    { if (yyval.ntag->priority != NULL) { 
					libsieve_sieveerror("duplicate :priority"); YYERROR; }
				   else { yyval.ntag->priority = yyvsp[0].sval; } }
    break;

  case 34:
#line 255 "sieve.y"
    { if (yyval.ntag->message != NULL) { 
					libsieve_sieveerror("duplicate :message"); YYERROR; }
				   else { yyval.ntag->message = yyvsp[0].sval; } }
    break;

  case 35:
#line 260 "sieve.y"
    { yyval.dtag = static_new_dtags(); }
    break;

  case 36:
#line 261 "sieve.y"
    { if (yyval.dtag->priority != NULL) { 
				libsieve_sieveerror("duplicate priority level"); YYERROR; }
				   else { yyval.dtag->priority = yyvsp[0].sval; } }
    break;

  case 37:
#line 264 "sieve.y"
    { if (yyval.dtag->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR;
				   } else {
				       yyval.dtag->comptag = yyvsp[-1].nval;
#ifdef ENABLE_REGEX
				       if (yyval.dtag->comptag == REGEX) {
					   int cflags = REG_EXTENDED |
					       REG_NOSUB | REG_ICASE;
					   yyval.dtag->pattern =
					       (void*) static_verify_regex(yyvsp[0].sval, cflags);
					   if (!yyval.dtag->pattern) { YYERROR; }
				       }
				       else
#endif
					   yyval.dtag->pattern = yyvsp[0].sval;
				   } }
    break;

  case 38:
#line 282 "sieve.y"
    { yyval.sval = "low"; }
    break;

  case 39:
#line 283 "sieve.y"
    { yyval.sval = "normal"; }
    break;

  case 40:
#line 284 "sieve.y"
    { yyval.sval = "high"; }
    break;

  case 41:
#line 287 "sieve.y"
    { yyval.vtag = static_new_vtags(); }
    break;

  case 42:
#line 288 "sieve.y"
    { if (yyval.vtag->days != -1) { 
					libsieve_sieveerror("duplicate :days"); YYERROR; }
				   else { yyval.vtag->days = yyvsp[0].nval; } }
    break;

  case 43:
#line 291 "sieve.y"
    { if (yyval.vtag->addresses != NULL) { 
					libsieve_sieveerror("duplicate :addresses"); 
					YYERROR;
				       } else if (!static_verify_stringlist(yyvsp[0].sl,
							static_verify_address)) {
					  YYERROR;
				       } else {
					 yyval.vtag->addresses = yyvsp[0].sl; } }
    break;

  case 44:
#line 299 "sieve.y"
    { if (yyval.vtag->subject != NULL) { 
					libsieve_sieveerror("duplicate :subject"); 
					YYERROR;
				   } else if (!static_ok_header(yyvsp[0].sval)) {
					YYERROR;
				   } else { yyval.vtag->subject = yyvsp[0].sval; } }
    break;

  case 45:
#line 305 "sieve.y"
    { if (yyval.vtag->mime != -1) { 
					libsieve_sieveerror("duplicate :mime"); 
					YYERROR; }
				   else { yyval.vtag->mime = MIME; } }
    break;

  case 46:
#line 311 "sieve.y"
    { yyval.sl = yyvsp[-1].sl; }
    break;

  case 47:
#line 312 "sieve.y"
    { yyval.sl = libsieve_new_sl(yyvsp[0].sval, NULL); }
    break;

  case 48:
#line 315 "sieve.y"
    { yyval.sl = libsieve_new_sl(yyvsp[0].sval, NULL); }
    break;

  case 49:
#line 316 "sieve.y"
    { yyval.sl = libsieve_new_sl(yyvsp[-2].sval, yyvsp[0].sl); }
    break;

  case 50:
#line 319 "sieve.y"
    { yyval.cl = yyvsp[-1].cl; }
    break;

  case 51:
#line 320 "sieve.y"
    { yyval.cl = NULL; }
    break;

  case 52:
#line 323 "sieve.y"
    { yyval.test = libsieve_new_test(ANYOF); yyval.test->u.tl = yyvsp[0].testl; }
    break;

  case 53:
#line 324 "sieve.y"
    { yyval.test = libsieve_new_test(ALLOF); yyval.test->u.tl = yyvsp[0].testl; }
    break;

  case 54:
#line 325 "sieve.y"
    { yyval.test = libsieve_new_test(EXISTS); yyval.test->u.sl = yyvsp[0].sl; }
    break;

  case 55:
#line 326 "sieve.y"
    { yyval.test = libsieve_new_test(SFALSE); }
    break;

  case 56:
#line 327 "sieve.y"
    { yyval.test = libsieve_new_test(STRUE); }
    break;

  case 57:
#line 329 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist(yyvsp[-1].sl, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   yyvsp[-2].htag = static_canon_htags(yyvsp[-2].htag);
#ifdef ENABLE_REGEX
				   if (yyvsp[-2].htag->comptag == REGEX) {
				     pl = static_verify_regexs(yyvsp[0].sl, yyvsp[-2].htag->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) yyvsp[0].sl;
				       
				   yyval.test = static_build_header(HEADER, yyvsp[-2].htag, yyvsp[-1].sl, pl);
				   if (yyval.test == NULL) { YYERROR; } }
    break;

  case 58:
#line 347 "sieve.y"
    { patternlist_t *pl;
                                   if (!static_verify_stringlist(yyvsp[-1].sl, static_verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   yyvsp[-2].aetag = static_canon_aetags(yyvsp[-2].aetag);
#ifdef ENABLE_REGEX
				   if (yyvsp[-2].aetag->comptag == REGEX) {
				     pl = static_verify_regexs(yyvsp[0].sl, yyvsp[-2].aetag->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) yyvsp[0].sl;
				       
				   yyval.test = static_build_address(yyvsp[-3].nval, yyvsp[-2].aetag, yyvsp[-1].sl, pl);
				   if (yyval.test == NULL) { YYERROR; } }
    break;

  case 59:
#line 364 "sieve.y"
    { yyval.test = libsieve_new_test(NOT); yyval.test->u.t = yyvsp[0].test; }
    break;

  case 60:
#line 365 "sieve.y"
    { yyval.test = libsieve_new_test(SIZE); yyval.test->u.sz.t = yyvsp[-1].nval;
		                   yyval.test->u.sz.n = yyvsp[0].nval; }
    break;

  case 61:
#line 367 "sieve.y"
    { yyval.test = NULL; }
    break;

  case 62:
#line 370 "sieve.y"
    { yyval.nval = ADDRESS; }
    break;

  case 63:
#line 371 "sieve.y"
    { yyval.nval = ENVELOPE; }
    break;

  case 64:
#line 374 "sieve.y"
    { yyval.aetag = static_new_aetags(); }
    break;

  case 65:
#line 375 "sieve.y"
    { yyval.aetag = yyvsp[-1].aetag;
				   if (yyval.aetag->addrtag != -1) { 
			libsieve_sieveerror("duplicate or conflicting address part tag");
			YYERROR; }
				   else { yyval.aetag->addrtag = yyvsp[0].nval; } }
    break;

  case 66:
#line 380 "sieve.y"
    { yyval.aetag = yyvsp[-1].aetag;
				   if (yyval.aetag->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { yyval.aetag->comptag = yyvsp[0].nval; } }
    break;

  case 67:
#line 384 "sieve.y"
    { yyval.aetag = yyvsp[-2].aetag;
				   if (yyval.aetag->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag"); YYERROR; }
				   else { yyval.aetag->comparator = yyvsp[0].sval; } }
    break;

  case 68:
#line 390 "sieve.y"
    { yyval.htag = static_new_htags(); }
    break;

  case 69:
#line 391 "sieve.y"
    { yyval.htag = yyvsp[-1].htag;
				   if (yyval.htag->comptag != -1) { 
			libsieve_sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { yyval.htag->comptag = yyvsp[0].nval; } }
    break;

  case 70:
#line 395 "sieve.y"
    { yyval.htag = yyvsp[-2].htag;
				   if (yyval.htag->comparator != NULL) { 
			libsieve_sieveerror("duplicate comparator tag");
					YYERROR; }
				   else { yyval.htag->comparator = yyvsp[0].sval; } }
    break;

  case 71:
#line 402 "sieve.y"
    { yyval.nval = ALL; }
    break;

  case 72:
#line 403 "sieve.y"
    { yyval.nval = LOCALPART; }
    break;

  case 73:
#line 404 "sieve.y"
    { yyval.nval = DOMAIN; }
    break;

  case 74:
#line 405 "sieve.y"
    { if (!parse_script->support.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   yyval.nval = USER; }
    break;

  case 75:
#line 410 "sieve.y"
    { if (!parse_script->support.subaddress) {
				     libsieve_sieveerror("subaddress not required");
				     YYERROR;
				   }
				   yyval.nval = DETAIL; }
    break;

  case 76:
#line 417 "sieve.y"
    { yyval.nval = IS; }
    break;

  case 77:
#line 418 "sieve.y"
    { yyval.nval = CONTAINS; }
    break;

  case 78:
#line 419 "sieve.y"
    { yyval.nval = MATCHES; }
    break;

  case 79:
#line 420 "sieve.y"
    { if (!parse_script->support.regex) {
				     libsieve_sieveerror("regex not required");
				     YYERROR;
				   }
				   yyval.nval = REGEX; }
    break;

  case 80:
#line 427 "sieve.y"
    { yyval.nval = OVER; }
    break;

  case 81:
#line 428 "sieve.y"
    { yyval.nval = UNDER; }
    break;

  case 82:
#line 431 "sieve.y"
    { yyval.testl = yyvsp[-1].testl; }
    break;

  case 83:
#line 434 "sieve.y"
    { yyval.testl = libsieve_new_testlist(yyvsp[0].test, NULL); }
    break;

  case 84:
#line 435 "sieve.y"
    { yyval.testl = libsieve_new_testlist(yyvsp[-2].test, yyvsp[0].testl); }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1902 "y.tab.c"

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
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 438 "sieve.y"


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
        err = libsieve_strconcat("address '", s, "': ", libsieve_addrerr, NULL);
        sieveerror(err);
        libsieve_free(libsieve_addrerr);
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
static int static_ok_header(char *s __attribute__((unused)))
{
    return 1;
}

/* Sieve 2 update: allow support to be filled directly
 * without requiring interp to contain anything valid
 *
 * Checks if interpreter supports specified action
 * */
static int static_check_reqs(sieve_script_t *s, char *req)
{
    if (0 == strcmp("fileinto", req)) {
        if (s->interp.fileinto)
	    s->support.fileinto = 1;
        return s->support.fileinto;
    } else if (0 == strcmp("reject", req)) {
        if (s->interp.reject)
	    s->support.reject = 1;
        return s->support.reject;
    } else if (!strcmp("envelope", req)) {
	if (s->interp.getenvelope)
	    s->support.envelope = 1;
        return s->support.reject;
    } else if (!strcmp("vacation", req)) {
	if (s->interp.vacation)
	    s->support.vacation = 1;
        return s->support.vacation;
    } else if (!strcmp("imapflags", req)) {
	if (s->interp.markflags->flag)
	    s->support.imapflags = 1;
        return s->support.imapflags;
    } else if (!strcmp("notify",req)) {
	if (s->interp.notify)
	    s->support.notify = 1;
        return s->support.notify;
#ifdef ENABLE_REGEX
    /* If regex is enabled then it is supported! */
    } else if (!strcmp("regex", req)) {
	s->support.regex = 1;
	return 1;
#endif
    /* Subaddress support is built into the parser! */
    } else if (!strcmp("subaddress", req)) {
	s->support.subaddress = 1;
	return 1;
    } else if (!strcmp("comparator-i;octet", req)) {
	return 1;
    } else if (!strcmp("comparator-i;ascii-casemap", req)) {
	return 1;
    }
    /* If we don't recognize it, then we don't support it! */
    return 0;
}


