/* A Bison parser, made from sieve.y
   by GNU bison 1.32.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse sieveparse
#define yylex sievelex
#define yyerror sieveerror
#define yylval sievelval
#define yychar sievechar
#define yydebug sievedebug
#define yynerrs sievenerrs
# define	NUMBER	257
# define	STRING	258
# define	IF	259
# define	ELSIF	260
# define	ELSE	261
# define	REJCT	262
# define	FILEINTO	263
# define	REDIRECT	264
# define	KEEP	265
# define	STOP	266
# define	DISCARD	267
# define	VACATION	268
# define	REQUIRE	269
# define	SETFLAG	270
# define	ADDFLAG	271
# define	REMOVEFLAG	272
# define	MARK	273
# define	UNMARK	274
# define	NOTIFY	275
# define	DENOTIFY	276
# define	ANYOF	277
# define	ALLOF	278
# define	EXISTS	279
# define	SFALSE	280
# define	STRUE	281
# define	HEADER	282
# define	NOT	283
# define	SIZE	284
# define	ADDRESS	285
# define	ENVELOPE	286
# define	COMPARATOR	287
# define	IS	288
# define	CONTAINS	289
# define	MATCHES	290
# define	REGEX	291
# define	OVER	292
# define	UNDER	293
# define	ALL	294
# define	LOCALPART	295
# define	DOMAIN	296
# define	USER	297
# define	DETAIL	298
# define	DAYS	299
# define	ADDRESSES	300
# define	SUBJECT	301
# define	MIME	302
# define	METHOD	303
# define	ID	304
# define	OPTIONS	305
# define	LOW	306
# define	NORMAL	307
# define	HIGH	308
# define	MESSAGE	309

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

extern int sieveerror(char *msg);
extern int sievelex(void);

#define YYERROR_VERBOSE /* i want better error messages! */

#line 57 "sieve.y"
#ifndef YYSTYPE
typedef union {
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
} yystype;
# define YYSTYPE yystype
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		131
#define	YYFLAG		-32768
#define	YYNTBASE	64

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 309 ? yytranslate[x] : 87)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     5,     8,    12,    14,    17,    20,
      25,    28,    29,    34,    37,    40,    43,    46,    48,    50,
      52,    56,    59,    62,    65,    67,    69,    72,    75,    76,
      80,    84,    88,    91,    95,    96,    99,   103,   105,   107,
     109,   110,   114,   118,   122,   125,   129,   131,   133,   137,
     141,   144,   147,   150,   153,   155,   157,   162,   167,   170,
     174,   176,   178,   180,   181,   184,   187,   191,   192,   195,
     199,   201,   203,   205,   207,   209,   211,   213,   215,   217,
     219,   221,   225,   227
};
static const short yyrhs[] =
{
      -1,    65,    67,     0,     0,    66,    65,     0,    15,    75,
      56,     0,    68,     0,    68,    67,     0,    70,    56,     0,
       5,    78,    77,    69,     0,     1,    56,     0,     0,     6,
      78,    77,    69,     0,     7,    77,     0,     8,     4,     0,
       9,     4,     0,    10,     4,     0,    11,     0,    12,     0,
      13,     0,    14,    74,     4,     0,    16,    75,     0,    17,
      75,     0,    18,    75,     0,    19,     0,    20,     0,    21,
      71,     0,    22,    72,     0,     0,    71,    50,     4,     0,
      71,    49,     4,     0,    71,    51,    75,     0,    71,    73,
       0,    71,    55,     4,     0,     0,    72,    73,     0,    72,
      83,     4,     0,    52,     0,    53,     0,    54,     0,     0,
      74,    45,     3,     0,    74,    46,    75,     0,    74,    47,
       4,     0,    74,    48,     0,    57,    76,    58,     0,     4,
       0,     4,     0,     4,    59,    76,     0,    60,    67,    61,
       0,    60,    61,     0,    23,    85,     0,    24,    85,     0,
      25,    75,     0,    26,     0,    27,     0,    28,    81,    75,
      75,     0,    79,    80,    75,    75,     0,    29,    78,     0,
      30,    84,     3,     0,     1,     0,    31,     0,    32,     0,
       0,    80,    82,     0,    80,    83,     0,    80,    33,     4,
       0,     0,    81,    83,     0,    81,    33,     4,     0,    40,
       0,    41,     0,    42,     0,    43,     0,    44,     0,    34,
       0,    35,     0,    36,     0,    37,     0,    38,     0,    39,
       0,    62,    86,    63,     0,    78,     0,    78,    59,    86,
       0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    97,    98,   101,   102,   105,   111,   112,   115,   116,
     117,   120,   121,   122,   125,   130,   139,   144,   145,   146,
     147,   155,   164,   173,   182,   187,   193,   201,   210,   211,
     214,   217,   220,   223,   228,   229,   232,   250,   251,   252,
     255,   256,   259,   267,   273,   279,   280,   283,   284,   287,
     288,   291,   292,   293,   294,   295,   296,   314,   332,   333,
     335,   338,   339,   342,   343,   348,   352,   358,   359,   363,
     370,   371,   372,   373,   378,   385,   386,   387,   388,   395,
     396,   399,   402,   403
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUMBER", "STRING", "IF", "ELSIF", "ELSE", 
  "REJCT", "FILEINTO", "REDIRECT", "KEEP", "STOP", "DISCARD", "VACATION", 
  "REQUIRE", "SETFLAG", "ADDFLAG", "REMOVEFLAG", "MARK", "UNMARK", 
  "NOTIFY", "DENOTIFY", "ANYOF", "ALLOF", "EXISTS", "SFALSE", "STRUE", 
  "HEADER", "NOT", "SIZE", "ADDRESS", "ENVELOPE", "COMPARATOR", "IS", 
  "CONTAINS", "MATCHES", "REGEX", "OVER", "UNDER", "ALL", "LOCALPART", 
  "DOMAIN", "USER", "DETAIL", "DAYS", "ADDRESSES", "SUBJECT", "MIME", 
  "METHOD", "ID", "OPTIONS", "LOW", "NORMAL", "HIGH", "MESSAGE", "';'", 
  "'['", "']'", "','", "'{'", "'}'", "'('", "')'", "start", "reqs", 
  "require", "commands", "command", "elsif", "action", "ntags", "dtags", 
  "priority", "vtags", "stringlist", "strings", "block", "test", 
  "addrorenv", "aetags", "htags", "addrparttag", "comptag", "sizetag", 
  "testlist", "tests", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      68,    69,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    72,    72,    72,    73,    73,    73,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    80,    80,    81,    81,    81,
      82,    82,    82,    82,    82,    83,    83,    83,    83,    84,
      84,    85,    86,    86
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     0,     2,     3,     1,     2,     2,     4,
       2,     0,     4,     2,     2,     2,     2,     1,     1,     1,
       3,     2,     2,     2,     1,     1,     2,     2,     0,     3,
       3,     3,     2,     3,     0,     2,     3,     1,     1,     1,
       0,     3,     3,     3,     2,     3,     1,     1,     3,     3,
       2,     2,     2,     2,     1,     1,     4,     4,     2,     3,
       1,     1,     1,     0,     2,     2,     3,     0,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       3,     0,     0,     3,    46,     0,     0,     0,     0,     0,
       0,     0,    17,    18,    19,    40,     0,     0,     0,    24,
      25,    28,    34,     2,     0,     0,     4,    47,     0,     5,
      10,    60,     0,     0,     0,    54,    55,    67,     0,     0,
      61,    62,     0,    63,    14,    15,    16,     0,    21,    22,
      23,    26,    27,     7,     8,     0,    45,     0,    51,    52,
      53,     0,    58,    79,    80,     0,     0,    11,     0,    20,
       0,     0,     0,    44,     0,     0,     0,    37,    38,    39,
       0,    32,    75,    76,    77,    78,    35,     0,    48,    82,
       0,     0,     0,    68,    59,    50,     0,     0,     0,     9,
       0,    70,    71,    72,    73,    74,     0,    64,    65,    41,
      42,    43,    30,    29,    31,    33,    36,     0,    81,    69,
      56,    49,     0,    13,    66,    57,    83,    11,    12,     0,
       0,     0
};

static const short yydefgoto[] =
{
     129,     2,     3,    23,    24,    99,    25,    51,    52,    81,
      47,     6,    28,    67,    89,    43,    68,    61,   107,    87,
      65,    58,    90
};

static const short yypact[] =
{
       6,     0,   133,    -7,-32768,     8,   -43,   -36,   101,    20,
      21,    38,-32768,-32768,-32768,-32768,     0,     0,     0,-32768,
  -32768,-32768,-32768,-32768,    53,   -34,-32768,    -9,   -14,-32768,
  -32768,-32768,   -19,   -19,     0,-32768,-32768,-32768,   101,   -28,
  -32768,-32768,    -1,-32768,-32768,-32768,-32768,     1,-32768,-32768,
  -32768,   107,    59,-32768,-32768,     8,-32768,   101,-32768,-32768,
  -32768,    52,-32768,-32768,-32768,    74,    18,     9,    64,-32768,
      75,     0,    76,-32768,    77,    78,     0,-32768,-32768,-32768,
      79,-32768,-32768,-32768,-32768,-32768,-32768,    80,-32768,    32,
      40,   106,     0,-32768,-32768,-32768,    54,   101,    -1,-32768,
     112,-32768,-32768,-32768,-32768,-32768,     0,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   101,-32768,-32768,
  -32768,-32768,    -1,-32768,-32768,-32768,-32768,     9,-32768,   117,
     118,-32768
};

static const short yypgoto[] =
{
  -32768,   116,-32768,   -15,-32768,    -4,-32768,-32768,-32768,    68,
  -32768,   -16,    67,   -81,    -5,-32768,-32768,-32768,-32768,   -54,
  -32768,   102,    19
};


#define	YYLAST		162


static const short yytable[] =
{
      48,    49,    50,    42,     4,    69,    -1,    93,     1,    53,
      63,    64,    27,    29,   108,    97,    98,   123,    60,     7,
      30,     1,    54,     8,    44,    45,     9,    10,    11,    12,
      13,    14,    15,    62,    16,    17,    18,    19,    20,    21,
      22,   127,    46,    57,    56,    92,    70,    71,    72,    73,
      55,    96,   106,    -6,     7,   110,     4,     5,     8,    66,
     114,     9,    10,    11,    12,    13,    14,    15,     4,    16,
      17,    18,    19,    20,    21,    22,   120,    94,   109,    95,
     111,   112,   113,   115,   116,    91,    82,    83,    84,    85,
     125,   117,   122,    82,    83,    84,    85,   100,    82,    83,
      84,    85,    31,   118,   101,   102,   103,   104,   105,     5,
     119,    77,    78,    79,    -6,   121,   124,   130,   131,    26,
      86,     5,    88,   128,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,     7,    59,   126,     0,     8,     0,
       0,     9,    10,    11,    12,    13,    14,    15,     0,    16,
      17,    18,    19,    20,    21,    22,    74,    75,    76,    77,
      78,    79,    80
};

static const short yycheck[] =
{
      16,    17,    18,     8,     4,     4,     0,    61,    15,    24,
      38,    39,     4,    56,    68,     6,     7,    98,    34,     1,
      56,    15,    56,     5,     4,     4,     8,     9,    10,    11,
      12,    13,    14,    38,    16,    17,    18,    19,    20,    21,
      22,   122,     4,    62,    58,    61,    45,    46,    47,    48,
      59,    66,    68,     0,     1,    71,     4,    57,     5,    60,
      76,     8,     9,    10,    11,    12,    13,    14,     4,    16,
      17,    18,    19,    20,    21,    22,    92,     3,     3,    61,
       4,     4,     4,     4,     4,    33,    34,    35,    36,    37,
     106,    59,    97,    34,    35,    36,    37,    33,    34,    35,
      36,    37,     1,    63,    40,    41,    42,    43,    44,    57,
       4,    52,    53,    54,    61,    61,     4,     0,     0,     3,
      52,    57,    55,   127,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    33,   117,    -1,     5,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    22,    49,    50,    51,    52,
      53,    54,    55
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
#  define YYSIZE_T YYSTD (size_t)
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#    define YYSIZE_T YYSTD (size_t)
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
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

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
#endif

#line 341 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

  if (yyssp >= yyss + yystacksize - 1)
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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 97 "sieve.y"
{ ret = NULL; }
    break;
case 2:
#line 98 "sieve.y"
{ ret = yyvsp[0].cl; }
    break;
case 5:
#line 105 "sieve.y"
{ if (!check_reqs(yyvsp[-1].sl)) {
                                    sieveerror("unsupported feature");
				    YYERROR; 
                                  } }
    break;
case 6:
#line 111 "sieve.y"
{ yyval.cl = yyvsp[0].cl; }
    break;
case 7:
#line 112 "sieve.y"
{ yyvsp[-1].cl->next = yyvsp[0].cl; yyval.cl = yyvsp[-1].cl; }
    break;
case 8:
#line 115 "sieve.y"
{ yyval.cl = yyvsp[-1].cl; }
    break;
case 9:
#line 116 "sieve.y"
{ yyval.cl = new_if(yyvsp[-2].test, yyvsp[-1].cl, yyvsp[0].cl); }
    break;
case 10:
#line 117 "sieve.y"
{ yyval.cl = new_command(STOP); }
    break;
case 11:
#line 120 "sieve.y"
{ yyval.cl = NULL; }
    break;
case 12:
#line 121 "sieve.y"
{ yyval.cl = new_if(yyvsp[-2].test, yyvsp[-1].cl, yyvsp[0].cl); }
    break;
case 13:
#line 122 "sieve.y"
{ yyval.cl = yyvsp[0].cl; }
    break;
case 14:
#line 125 "sieve.y"
{ if (!parse_script->support.reject) {
				     sieveerror("reject not required");
				     YYERROR;
				   }
				   yyval.cl = new_command(REJCT); yyval.cl->u.str = yyvsp[0].sval; }
    break;
case 15:
#line 130 "sieve.y"
{ if (!parse_script->support.fileinto) {
				     sieveerror("fileinto not required");
	                             YYERROR;
                                   }
				   if (!verify_mailbox(yyvsp[0].sval)) {
				     YYERROR; /* vm should call sieveerror() */
				   }
	                           yyval.cl = new_command(FILEINTO);
				   yyval.cl->u.str = yyvsp[0].sval; }
    break;
case 16:
#line 139 "sieve.y"
{ yyval.cl = new_command(REDIRECT);
				   if (!verify_address(yyvsp[0].sval)) {
				     YYERROR; /* va should call sieveerror() */
				   }
				   yyval.cl->u.str = yyvsp[0].sval; }
    break;
case 17:
#line 144 "sieve.y"
{ yyval.cl = new_command(KEEP); }
    break;
case 18:
#line 145 "sieve.y"
{ yyval.cl = new_command(STOP); }
    break;
case 19:
#line 146 "sieve.y"
{ yyval.cl = new_command(DISCARD); }
    break;
case 20:
#line 147 "sieve.y"
{ if (!parse_script->support.vacation) {
				     sieveerror("vacation not required");
				     yyval.cl = new_command(VACATION);
				     YYERROR;
				   } else {
  				     yyval.cl = build_vacation(VACATION,
					    canon_vtags(yyvsp[-1].vtag), yyvsp[0].sval);
				   } }
    break;
case 21:
#line 155 "sieve.y"
{ if (!parse_script->support.imapflags) {
                                    sieveerror("imapflags not required");
                                    YYERROR;
                                   }
                                  if (!verify_stringlist(yyvsp[0].sl, verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = new_command(SETFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;
case 22:
#line 164 "sieve.y"
{ if (!parse_script->support.imapflags) {
                                    sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!verify_stringlist(yyvsp[0].sl, verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = new_command(ADDFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;
case 23:
#line 173 "sieve.y"
{ if (!parse_script->support.imapflags) {
                                    sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  if (!verify_stringlist(yyvsp[0].sl, verify_flag)) {
                                    YYERROR; /* vf should call sieveerror() */
                                  }
                                  yyval.cl = new_command(REMOVEFLAG);
                                  yyval.cl->u.sl = yyvsp[0].sl; }
    break;
case 24:
#line 182 "sieve.y"
{ if (!parse_script->support.imapflags) {
                                    sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  yyval.cl = new_command(MARK); }
    break;
case 25:
#line 187 "sieve.y"
{ if (!parse_script->support.imapflags) {
                                    sieveerror("imapflags not required");
                                    YYERROR;
                                    }
                                  yyval.cl = new_command(UNMARK); }
    break;
case 26:
#line 193 "sieve.y"
{ if (!parse_script->support.notify) {
				       sieveerror("notify not required");
				       yyval.cl = new_command(NOTIFY); 
				       YYERROR;
	 			    } else {
				      yyval.cl = build_notify(NOTIFY,
				             canon_ntags(yyvsp[0].ntag));
				    } }
    break;
case 27:
#line 201 "sieve.y"
{ if (!parse_script->support.notify) {
                                       sieveerror("notify not required");
				       yyval.cl = new_command(DENOTIFY);
				       YYERROR;
				    } else {
					yyval.cl = build_denotify(DENOTIFY, yyvsp[0].dtag);
				    } }
    break;
case 28:
#line 210 "sieve.y"
{ yyval.ntag = new_ntags(); }
    break;
case 29:
#line 211 "sieve.y"
{ if (yyval.ntag->id != NULL) { 
					sieveerror("duplicate :method"); YYERROR; }
				   else { yyval.ntag->id = yyvsp[0].sval; } }
    break;
case 30:
#line 214 "sieve.y"
{ if (yyval.ntag->method != NULL) { 
					sieveerror("duplicate :method"); YYERROR; }
				   else { yyval.ntag->method = yyvsp[0].sval; } }
    break;
case 31:
#line 217 "sieve.y"
{ if (yyval.ntag->options != NULL) { 
					sieveerror("duplicate :options"); YYERROR; }
				     else { yyval.ntag->options = yyvsp[0].sl; } }
    break;
case 32:
#line 220 "sieve.y"
{ if (yyval.ntag->priority != NULL) { 
					sieveerror("duplicate :priority"); YYERROR; }
				   else { yyval.ntag->priority = yyvsp[0].sval; } }
    break;
case 33:
#line 223 "sieve.y"
{ if (yyval.ntag->message != NULL) { 
					sieveerror("duplicate :message"); YYERROR; }
				   else { yyval.ntag->message = yyvsp[0].sval; } }
    break;
case 34:
#line 228 "sieve.y"
{ yyval.dtag = new_dtags(); }
    break;
case 35:
#line 229 "sieve.y"
{ if (yyval.dtag->priority != NULL) { 
				sieveerror("duplicate priority level"); YYERROR; }
				   else { yyval.dtag->priority = yyvsp[0].sval; } }
    break;
case 36:
#line 232 "sieve.y"
{ if (yyval.dtag->comptag != -1) { 
			sieveerror("duplicate comparator type tag"); YYERROR;
				   } else {
				       yyval.dtag->comptag = yyvsp[-1].nval;
#ifdef ENABLE_REGEX
				       if (yyval.dtag->comptag == REGEX) {
					   int cflags = REG_EXTENDED |
					       REG_NOSUB | REG_ICASE;
					   yyval.dtag->pattern =
					       (void*) verify_regex(yyvsp[0].sval, cflags);
					   if (!yyval.dtag->pattern) { YYERROR; }
				       }
				       else
#endif
					   yyval.dtag->pattern = yyvsp[0].sval;
				   } }
    break;
case 37:
#line 250 "sieve.y"
{ yyval.sval = "low"; }
    break;
case 38:
#line 251 "sieve.y"
{ yyval.sval = "normal"; }
    break;
case 39:
#line 252 "sieve.y"
{ yyval.sval = "high"; }
    break;
case 40:
#line 255 "sieve.y"
{ yyval.vtag = new_vtags(); }
    break;
case 41:
#line 256 "sieve.y"
{ if (yyval.vtag->days != -1) { 
					sieveerror("duplicate :days"); YYERROR; }
				   else { yyval.vtag->days = yyvsp[0].nval; } }
    break;
case 42:
#line 259 "sieve.y"
{ if (yyval.vtag->addresses != NULL) { 
					sieveerror("duplicate :addresses"); 
					YYERROR;
				       } else if (!verify_stringlist(yyvsp[0].sl,
							verify_address)) {
					  YYERROR;
				       } else {
					 yyval.vtag->addresses = yyvsp[0].sl; } }
    break;
case 43:
#line 267 "sieve.y"
{ if (yyval.vtag->subject != NULL) { 
					sieveerror("duplicate :subject"); 
					YYERROR;
				   } else if (!ok_header(yyvsp[0].sval)) {
					YYERROR;
				   } else { yyval.vtag->subject = yyvsp[0].sval; } }
    break;
case 44:
#line 273 "sieve.y"
{ if (yyval.vtag->mime != -1) { 
					sieveerror("duplicate :mime"); 
					YYERROR; }
				   else { yyval.vtag->mime = MIME; } }
    break;
case 45:
#line 279 "sieve.y"
{ yyval.sl = yyvsp[-1].sl; }
    break;
case 46:
#line 280 "sieve.y"
{ yyval.sl = new_sl(yyvsp[0].sval, NULL); }
    break;
case 47:
#line 283 "sieve.y"
{ yyval.sl = new_sl(yyvsp[0].sval, NULL); }
    break;
case 48:
#line 284 "sieve.y"
{ yyval.sl = new_sl(yyvsp[-2].sval, yyvsp[0].sl); }
    break;
case 49:
#line 287 "sieve.y"
{ yyval.cl = yyvsp[-1].cl; }
    break;
case 50:
#line 288 "sieve.y"
{ yyval.cl = NULL; }
    break;
case 51:
#line 291 "sieve.y"
{ yyval.test = new_test(ANYOF); yyval.test->u.tl = yyvsp[0].testl; }
    break;
case 52:
#line 292 "sieve.y"
{ yyval.test = new_test(ALLOF); yyval.test->u.tl = yyvsp[0].testl; }
    break;
case 53:
#line 293 "sieve.y"
{ yyval.test = new_test(EXISTS); yyval.test->u.sl = yyvsp[0].sl; }
    break;
case 54:
#line 294 "sieve.y"
{ yyval.test = new_test(SFALSE); }
    break;
case 55:
#line 295 "sieve.y"
{ yyval.test = new_test(STRUE); }
    break;
case 56:
#line 297 "sieve.y"
{ patternlist_t *pl;
                                   if (!verify_stringlist(yyvsp[-1].sl, verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   yyvsp[-2].htag = canon_htags(yyvsp[-2].htag);
#ifdef ENABLE_REGEX
				   if (yyvsp[-2].htag->comptag == REGEX) {
				     pl = verify_regexs(yyvsp[0].sl, yyvsp[-2].htag->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) yyvsp[0].sl;
				       
				   yyval.test = build_header(HEADER, yyvsp[-2].htag, yyvsp[-1].sl, pl);
				   if (yyval.test == NULL) { YYERROR; } }
    break;
case 57:
#line 315 "sieve.y"
{ patternlist_t *pl;
                                   if (!verify_stringlist(yyvsp[-1].sl, verify_header)) {
                                     YYERROR; /* vh should call sieveerror() */
                                   }

				   yyvsp[-2].aetag = canon_aetags(yyvsp[-2].aetag);
#ifdef ENABLE_REGEX
				   if (yyvsp[-2].aetag->comptag == REGEX) {
				     pl = verify_regexs(yyvsp[0].sl, yyvsp[-2].aetag->comparator);
				     if (!pl) { YYERROR; }
				   }
				   else
#endif
				     pl = (patternlist_t *) yyvsp[0].sl;
				       
				   yyval.test = build_address(yyvsp[-3].nval, yyvsp[-2].aetag, yyvsp[-1].sl, pl);
				   if (yyval.test == NULL) { YYERROR; } }
    break;
case 58:
#line 332 "sieve.y"
{ yyval.test = new_test(NOT); yyval.test->u.t = yyvsp[0].test; }
    break;
case 59:
#line 333 "sieve.y"
{ yyval.test = new_test(SIZE); yyval.test->u.sz.t = yyvsp[-1].nval;
		                   yyval.test->u.sz.n = yyvsp[0].nval; }
    break;
case 60:
#line 335 "sieve.y"
{ yyval.test = NULL; }
    break;
case 61:
#line 338 "sieve.y"
{ yyval.nval = ADDRESS; }
    break;
case 62:
#line 339 "sieve.y"
{ yyval.nval = ENVELOPE; }
    break;
case 63:
#line 342 "sieve.y"
{ yyval.aetag = new_aetags(); }
    break;
case 64:
#line 343 "sieve.y"
{ yyval.aetag = yyvsp[-1].aetag;
				   if (yyval.aetag->addrtag != -1) { 
			sieveerror("duplicate or conflicting address part tag");
			YYERROR; }
				   else { yyval.aetag->addrtag = yyvsp[0].nval; } }
    break;
case 65:
#line 348 "sieve.y"
{ yyval.aetag = yyvsp[-1].aetag;
				   if (yyval.aetag->comptag != -1) { 
			sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { yyval.aetag->comptag = yyvsp[0].nval; } }
    break;
case 66:
#line 352 "sieve.y"
{ yyval.aetag = yyvsp[-2].aetag;
				   if (yyval.aetag->comparator != NULL) { 
			sieveerror("duplicate comparator tag"); YYERROR; }
				   else { yyval.aetag->comparator = yyvsp[0].sval; } }
    break;
case 67:
#line 358 "sieve.y"
{ yyval.htag = new_htags(); }
    break;
case 68:
#line 359 "sieve.y"
{ yyval.htag = yyvsp[-1].htag;
				   if (yyval.htag->comptag != -1) { 
			sieveerror("duplicate comparator type tag"); YYERROR; }
				   else { yyval.htag->comptag = yyvsp[0].nval; } }
    break;
case 69:
#line 363 "sieve.y"
{ yyval.htag = yyvsp[-2].htag;
				   if (yyval.htag->comparator != NULL) { 
			sieveerror("duplicate comparator tag");
					YYERROR; }
				   else { yyval.htag->comparator = yyvsp[0].sval; } }
    break;
case 70:
#line 370 "sieve.y"
{ yyval.nval = ALL; }
    break;
case 71:
#line 371 "sieve.y"
{ yyval.nval = LOCALPART; }
    break;
case 72:
#line 372 "sieve.y"
{ yyval.nval = DOMAIN; }
    break;
case 73:
#line 373 "sieve.y"
{ if (!parse_script->support.subaddress) {
				     sieveerror("subaddress not required");
				     YYERROR;
				   }
				   yyval.nval = USER; }
    break;
case 74:
#line 378 "sieve.y"
{ if (!parse_script->support.subaddress) {
				     sieveerror("subaddress not required");
				     YYERROR;
				   }
				   yyval.nval = DETAIL; }
    break;
case 75:
#line 385 "sieve.y"
{ yyval.nval = IS; }
    break;
case 76:
#line 386 "sieve.y"
{ yyval.nval = CONTAINS; }
    break;
case 77:
#line 387 "sieve.y"
{ yyval.nval = MATCHES; }
    break;
case 78:
#line 388 "sieve.y"
{ if (!parse_script->support.regex) {
				     sieveerror("regex not required");
				     YYERROR;
				   }
				   yyval.nval = REGEX; }
    break;
case 79:
#line 395 "sieve.y"
{ yyval.nval = OVER; }
    break;
case 80:
#line 396 "sieve.y"
{ yyval.nval = UNDER; }
    break;
case 81:
#line 399 "sieve.y"
{ yyval.testl = yyvsp[-1].testl; }
    break;
case 82:
#line 402 "sieve.y"
{ yyval.testl = new_testlist(yyvsp[0].test, NULL); }
    break;
case 83:
#line 403 "sieve.y"
{ yyval.testl = new_testlist(yyvsp[-2].test, yyvsp[0].testl); }
    break;
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
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
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 406 "sieve.y"


char *sieveptr;         /* pointer to sieve string for address lexer */
char *sieveerr;         /* buffer for sieve parser error messages */

commandlist_t *sieve_parse_buffer(sieve_script_t *script, char *b)
{
    commandlist_t *t;

    parse_script = script;

    sieveptr = b;
    sieveerr = NULL;

    /* These are being moved all the way up to script[2].c */
    // addrlexalloc();
    // sievelexalloc();
    if (sieveparse()) {
    /*
        err = sv_strconcat("address '", s, "': ", addrerr, NULL);
        sieveerror(err);
        sv_free(addrerr);
        sv_free(err);
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

commandlist_t *sieve_parse(sieve_script_t *script, FILE *f)
{
    commandlist_t *t;
    size_t f_pos = 0, f_len = 0;
    char *f_buf;
    char *tmp_buf;

    f_buf = NULL; // If null, realloc() behaves as malloc()
    while(!feof(f)) {
        if( f_pos + 1 >= f_len ) {
            tmp_buf = sv_realloc(f_buf, sizeof(char) * (f_len+=200));
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

   t = sieve_parse_buffer(script, f_buf);
   sv_free(f_buf);

   return t;
}

int sieveerror(char *msg)
{
    extern int sievelineno;
    char *tmperr;
    int ret;

    parse_script->err++;
    /* We're in the Sieve 1 API */
    if (parse_script->interp.err) {
	ret = parse_script->interp.err(sievelineno, msg, 
				       parse_script->interp.interp_context,
				       parse_script->script_context);
    } else {
    /* We're in the Sieve 2 API */
        if( sieveerr )
            tmperr = sv_strconcat(sieveerr, ", ", msg, NULL);
        else
            tmperr = sv_strconcat(msg, NULL);
        if( tmperr )
            sieveerr = sv_strdup(tmperr, strlen(tmperr));
        sv_free(tmperr);
    }

    return 0;
}

static int check_reqs(stringlist_t *sl)
{
    int i = 1;
    stringlist_t *s;
    
    while (sl != NULL) {
	s = sl;
	sl = sl->next;

	i &= script_require(parse_script, s->s);

	sv_free(s->s);
	sv_free(s);
    }
    return i;
}

static test_t *build_address(int t, struct aetags *ae,
			     stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = new_test(t);	/* can be either ADDRESS or ENVELOPE */

    assert((t == ADDRESS) || (t == ENVELOPE));

    if (ret) {
	ret->u.ae.comptag = ae->comptag;
	ret->u.ae.comp = lookup_comp(ae->comparator, ae->comptag);
	ret->u.ae.sl = sl;
	ret->u.ae.pl = pl;
	ret->u.ae.addrpart = ae->addrtag;
	free_aetags(ae);
	if (ret->u.ae.comp == NULL) {
	    free_test(ret);
	    ret = NULL;
	}
    }
    return ret;
}

static test_t *build_header(int t, struct htags *h,
			    stringlist_t *sl, patternlist_t *pl)
{
    test_t *ret = new_test(t);	/* can be HEADER */

    assert(t == HEADER);

    if (ret) {
	ret->u.h.comptag = h->comptag;
	ret->u.h.comp = lookup_comp(h->comparator, h->comptag);
	ret->u.h.sl = sl;
	ret->u.h.pl = pl;
	free_htags(h);
	if (ret->u.h.comp == NULL) {
	    free_test(ret);
	    ret = NULL;
	}
    }
    return ret;
}

static commandlist_t *build_vacation(int t, struct vtags *v, char *reason)
{
    commandlist_t *ret = new_command(t);

    assert(t == VACATION);

    if (ret) {
	ret->u.v.subject = v->subject; v->subject = NULL;
	ret->u.v.days = v->days;
	ret->u.v.mime = v->mime;
	ret->u.v.addresses = v->addresses; v->addresses = NULL;
	free_vtags(v);
	ret->u.v.message = reason;
    }
    return ret;
}

static commandlist_t *build_notify(int t, struct ntags *n)
{
    commandlist_t *ret = new_command(t);

    assert(t == NOTIFY);

    if (ret) {
	ret->u.n.method = n->method; n->method = NULL;
	ret->u.n.id = n->id; n->id = NULL;
	ret->u.n.options = n->options; n->options = NULL;
	ret->u.n.priority = n->priority;
	ret->u.n.message = n->message; n->message = NULL;
	free_ntags(n);
    }
    return ret;
}

static commandlist_t *build_denotify(int t, struct dtags *d)
{
    commandlist_t *ret = new_command(t);

    assert(t == DENOTIFY);

    if (ret) {
	ret->u.d.comptag = d->comptag;
	ret->u.d.comp = lookup_comp("i;ascii-casemap", d->comptag);
	ret->u.d.pattern = d->pattern; d->pattern = NULL;
	ret->u.d.priority = d->priority;
	free_dtags(d);
    }
    return ret;
}

static struct aetags *new_aetags(void)
{
    struct aetags *r = (struct aetags *) sv_malloc(sizeof(struct aetags));

    r->addrtag = r->comptag = -1;
    r->comparator = NULL;

    return r;
}

static struct aetags *canon_aetags(struct aetags *ae)
{
    char *map = "i;ascii-casemap";
    if (ae->addrtag == -1) { ae->addrtag = ALL; }
    if (ae->comparator == NULL) { ae->comparator = sv_strdup(map, strlen(map)); }
    if (ae->comptag == -1) { ae->comptag = IS; }
    return ae;
}

static void free_aetags(struct aetags *ae)
{
    sv_free(ae->comparator);
    sv_free(ae);
}

static struct htags *new_htags(void)
{
    struct htags *r = (struct htags *) sv_malloc(sizeof(struct htags));

    r->comptag = -1;
    r->comparator = NULL;

    return r;
}

static struct htags *canon_htags(struct htags *h)
{
    char *map = "i;ascii-casemap";
    if (h->comparator == NULL) { h->comparator = sv_strdup(map, strlen(map)); }
    if (h->comptag == -1) { h->comptag = IS; }
    return h;
}

static void free_htags(struct htags *h)
{
    sv_free(h->comparator);
    sv_free(h);
}

static struct vtags *new_vtags(void)
{
    struct vtags *r = (struct vtags *) sv_malloc(sizeof(struct vtags));

    r->days = -1;
    r->addresses = NULL;
    r->subject = NULL;
    r->mime = -1;

    return r;
}

static struct vtags *canon_vtags(struct vtags *v)
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

static void free_vtags(struct vtags *v)
{
    if (v->addresses) { free_sl(v->addresses); }
    sv_free(v->subject);
    sv_free(v);
}

static struct ntags *new_ntags(void)
{
    struct ntags *r = (struct ntags *) sv_malloc(sizeof(struct ntags));

    r->method = NULL;
    r->id = NULL;
    r->options = NULL;
    r->priority = NULL;
    r->message = NULL;

    return r;
}

static struct ntags *canon_ntags(struct ntags *n)
{
    char *from = "$from$: $subject$";
    if (n->priority == NULL) { n->priority = "normal"; }
    if (n->message == NULL) { n->message = sv_strdup(from, strlen(from)); }

    return n;
}

static void free_ntags(struct ntags *n)
{
    sv_free(n->method);
    sv_free(n->id);
    if (n->options) free_sl(n->options);
    sv_free(n->message);
    sv_free(n);
}

static struct dtags *new_dtags(void)
{
    struct dtags *r = (struct dtags *) sv_malloc(sizeof(struct dtags));

    r->comptag = -1;
    r->pattern = NULL;
    r->priority = NULL;

    return r;
}

static void free_dtags(struct dtags *d)
{
    sv_free(d->pattern);
    sv_free(d);
}

static int verify_stringlist(stringlist_t *sl, int (*verify)(const char *))
{
    for (; sl != NULL && verify(sl->s); sl = sl->next) ;
    return (sl == NULL);
}

char *addrptr;		/* pointer to sieve string for address lexer */
char *addrerr;		/* buffer for sieve parser error messages */

static int verify_address(const char *s)
{
    char *aerr = NULL;
    char *serr = NULL;
    struct address *addr = NULL;

    addr = addr_parse_buffer(&addr, &s, &aerr);
    if (addr == NULL) {
        serr = sv_strconcat("address '", s, "': ", aerr, NULL);
        sieveerror(serr);
        sv_free(serr);
        sv_free(aerr);
        return 0;
    }
    addrstructfree(addr, CHARSALSO);
    return 1;
}

static int verify_mailbox(const char *s __attribute__((unused)))
{
    /* xxx if not a mailbox, call sieveerror */
    return 1;
}

static int verify_header(const char *hdr)
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
	    err = sv_strconcat("header '", hdr, "': not a valid header", NULL);
	    sieveerror(err);
	    sv_free(err);
	    return 0;
	}
	h++;
    }
    return 1;
}
 
/* Was this supposed to be modifying its argument?! */
static int verify_flag(const char *flag)
{
    int ret;
    char *f, *err;

    /* Make ourselves a local copy to change the case */
    f = sv_strdup(flag, strlen(flag));
 
    if (f[0] == '\\') {
	sv_strtolower(f,strlen(f));
	if (strcmp(f, "\\seen") && strcmp(f, "\\answered") &&
	    strcmp(f, "\\flagged") && strcmp(f, "\\draft") &&
	    strcmp(f, "\\deleted")) {
            err = sv_strconcat("flag '", f, "': not a system flag", NULL);
	    sieveerror(err);
	    sv_free(err);
	    ret = 0;
	}
	ret = 1;
    }
    else if (!sv_strisatom(f,strlen(f))) {
	err = sv_strconcat("flag '", f, "': not a valid keyword", NULL);
	sieveerror(err);
	sv_free(err);
	ret = 0;
    }
    ret = 1;

    sv_free(f);
    return ret;
}
 
#ifdef ENABLE_REGEX
static regex_t *verify_regex(const char *s, int cflags)
{
    int ret;
    char errbuf[100];
    regex_t *reg = (regex_t *) sv_malloc(sizeof(regex_t));

    if ((ret = regcomp(reg, s, cflags)) != 0) {
	(void) regerror(ret, reg, errbuf, sizeof(errbuf));
	sieveerror(errbuf);
	sv_free(reg);
	return NULL;
    }
    return reg;
}

static patternlist_t *verify_regexs(stringlist_t *sl, char *comp)
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
	    free_pl(pl, REGEX);
	    break;
	}
	pl = new_pl(reg, pl);
    }
    if (sl2 == NULL) {
	free_sl(sl);
	return pl;
    }
    return NULL;
}
#endif

/* xxx is it ok to put this in an RFC822 header body? */
static int ok_header(char *s __attribute__((unused)))
{
    return 1;
}
