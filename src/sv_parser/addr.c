/* A Bison parser, made from addr.y
   by GNU bison 1.32.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse addrparse
#define yylex addrlex
#define yyerror addrerror
#define yylval addrlval
#define yychar addrchar
#define yydebug addrdebug
#define yynerrs addrnerrs
# define	ATOM	257
# define	QTEXT	258
# define	DTEXT	259
# define	QUOTE	260

#line 1 "addr.y"

/*
 * addr.y -- RFC 822 address parser
 * Ken Murchison
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

#include <stdlib.h>
#include <string.h>

/* This only works in C99 and higher... */
#ifdef DEBUG
#define sv_debugf(...) printf(__VA_ARGS__)
#else
#define sv_debugf(...) 
#endif /* ifdef DEBUG */

/* Better yacc error messages make me happy */
#define YYERROR_VERBOSE
/* Must be defined before addr.h */
#define YYSTYPE char *

/* sv_util */
#include "util.h"
/* sv_parser */
#include "addr.h"
#include "addrinc.h"

/* There are global to this file */
char *addrptr;          /* pointer to sieve string for address lexer */
char *addrerr;          /* buffer for sieve parser error messages */
struct address *addr = NULL;
static struct mlbuf *ml = NULL;
#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		50
#define	YYFLAG		-32768
#define	YYNTBASE	16

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 260 ? yytranslate[x] : 31)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     9,     2,    13,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     7,     8,
      10,     2,    11,     2,    12,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    14,     2,    15,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     8,    13,    15,    19,    21,    23,
      26,    30,    36,    40,    43,    48,    50,    54,    56,    60,
      62,    64,    66,    70,    72,    75,    77,    79
};
static const short yyrhs[] =
{
      18,     0,    17,     0,    28,     7,     8,     0,    28,     7,
      18,     8,     0,    19,     0,    18,     9,    19,     0,    20,
       0,    21,     0,    28,    20,     0,    10,    21,    11,     0,
      10,    22,     7,    21,    11,     0,    23,    12,    24,     0,
      12,    24,     0,    12,    24,     9,    22,     0,    29,     0,
      23,    13,    29,     0,    25,     0,    24,    13,    25,     0,
      26,     0,    27,     0,     3,     0,    14,     5,    15,     0,
      29,     0,    28,    29,     0,     3,     0,    30,     0,     6,
       4,     6,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    62,    63,    65,    66,    68,    74,    81,    83,    84,
      91,    92,    99,   108,   112,   117,   118,   123,   124,   129,
     130,   132,   134,   139,   140,   145,   146,   148
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "ATOM", "QTEXT", "DTEXT", "QUOTE", "':'", 
  "';'", "','", "'<'", "'>'", "'@'", "'.'", "'['", "']'", "address", 
  "group", "mailboxes", "mailbox", "routeaddr", "addrspec", "route", 
  "localpart", "domain", "subdomain", "domainref", "domainlit", "phrase", 
  "word", "qstring", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    16,    16,    17,    17,    18,    18,    19,    19,    19,
      20,    20,    21,    22,    22,    23,    23,    24,    24,    25,
      25,    26,    27,    28,    28,    29,    29,    30
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     3,     4,     1,     3,     1,     1,     2,
       3,     5,     3,     2,     4,     1,     3,     1,     3,     1,
       1,     1,     3,     1,     2,     1,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    25,     0,     0,     2,     1,     5,     7,     8,     0,
       0,    23,    26,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     9,    24,    27,    21,     0,    13,    17,    19,
      20,    10,     0,     6,     0,    12,    16,     3,     0,     0,
       0,     0,     0,     4,    22,    14,    18,    11,     0,     0,
       0
};

static const short yydefgoto[] =
{
      48,     4,     5,     6,     7,     8,    16,     9,    27,    28,
      29,    30,    34,    11,    12
};

static const short yypact[] =
{
      15,-32768,     7,     3,-32768,    -5,-32768,-32768,-32768,    22,
      13,    24,-32768,    16,     0,    29,     6,-32768,    15,     0,
      21,     2,-32768,-32768,-32768,-32768,    28,    19,-32768,-32768,
  -32768,-32768,    21,-32768,    15,    31,-32768,-32768,    30,    26,
      33,     0,    32,-32768,-32768,-32768,-32768,-32768,    42,    46,
  -32768
};

static const short yypgoto[] =
{
  -32768,-32768,    27,    34,    -8,    -2,     9,-32768,    35,    10,
  -32768,-32768,    47,    -3,-32768
};


#define	YYLAST		54


static const short yytable[] =
{
      17,    15,    22,    25,    18,     1,     1,    23,     2,     2,
      37,    13,     3,    32,    26,    14,     1,    36,     1,     2,
      21,     2,    24,     3,     1,     3,    22,     2,    40,    17,
      42,    23,    41,    39,    19,    20,   -15,   -15,    43,    18,
      31,    44,    49,    47,    41,    14,    50,    10,    38,    45,
       0,    46,    33,     0,    35
};

static const short yycheck[] =
{
       3,     3,    10,     3,     9,     3,     3,    10,     6,     6,
       8,     4,    10,     7,    14,    12,     3,    20,     3,     6,
       7,     6,     6,    10,     3,    10,    34,     6,     9,    32,
      32,    34,    13,     5,    12,    13,    12,    13,     8,     9,
      11,    15,     0,    11,    13,    12,     0,     0,    21,    40,
      -1,    41,    18,    -1,    19
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
#line 62 "addr.y"
{ sv_debugf( "address: mailbox: %s\n", yyvsp[0] ); }
    break;
case 2:
#line 63 "addr.y"
{ sv_debugf( "address: group: %s\n", yyvsp[0] ); }
    break;
case 3:
#line 65 "addr.y"
{ sv_debugf( "group: phrase: %s\n", yyvsp[-2] ); }
    break;
case 4:
#line 66 "addr.y"
{ sv_debugf( "group: phrase mailboxes: %s %s\n", yyvsp[-3], yyvsp[-1] ); }
    break;
case 5:
#line 68 "addr.y"
{
	 	/* Each new address is allocated here and back-linked */
		sv_debugf( "mailboxes: mailbox: %s\n", yyvsp[0] );
		sv_debugf( "allocating newaddr %s\n" );
		addrappend(&addr);
		}
    break;
case 6:
#line 74 "addr.y"
{
	 	/* Each new address is allocated here and back-linked */
		sv_debugf( "mailboxes: mailboxes mailbox: %s %s\n", yyvsp[-2], yyvsp[0] );
		sv_debugf( "allocating newaddr %s\n" );
		addrappend(&addr);
		}
    break;
case 7:
#line 82 "addr.y"
{ sv_debugf( "mailbox: routeaddr: %s\n", yyvsp[0] ); }
    break;
case 8:
#line 83 "addr.y"
{ sv_debugf( "mailbox: addrspec: %s\n", yyvsp[0] ); }
    break;
case 9:
#line 84 "addr.y"
{
		sv_debugf( "mailbox: phrase routeaddr: %s %s\n", yyvsp[-1], yyvsp[0] );
		// This is a "top terminal" state...
		sv_debugf( "addr->name: %s\n", yyvsp[-1] );
		addr->name = sv_strdup( yyvsp[-1], strlen(yyvsp[-1]) );
		}
    break;
case 10:
#line 91 "addr.y"
{ sv_debugf( "routeaddr: addrspec: %s\n", yyvsp[-1] ); }
    break;
case 11:
#line 92 "addr.y"
{
		sv_debugf( "routeaddr: route addrspec: %s\n", yyvsp[-3], yyvsp[-1] );
		// This is a "top terminal" state...
		sv_debugf( "addr->route: %s\n", yyvsp[-3] );
		addr->route = sv_strdup( yyvsp[-3], strlen(yyvsp[-3]) );
		}
    break;
case 12:
#line 99 "addr.y"
{
		sv_debugf( "addrspec: localpart domain: %s %s\n", yyvsp[-2], yyvsp[0] );
		// This is a "top terminal" state...
		sv_debugf( "addr->mailbox: %s\n", yyvsp[-2] );
		addr->mailbox = sv_strdup( yyvsp[-2], strlen(yyvsp[-2]) );
		sv_debugf( "addr->domain: %s\n", yyvsp[0] );
		addr->domain = sv_strdup( yyvsp[0], strlen(yyvsp[0]) );
		}
    break;
case 13:
#line 108 "addr.y"
{
		sv_debugf( "route: domain: %s\n", yyvsp[0] );
                yyval = sv_strbuf(ml, sv_strconcat( "@", yyvsp[0], NULL ), strlen(yyvsp[0])+1, FREEME);
		}
    break;
case 14:
#line 112 "addr.y"
{
		sv_debugf( "route: domain route: %s %s\n", yyvsp[-2], yyvsp[0] );
		yyval = sv_strbuf(ml, sv_strconcat( "@", yyvsp[-2], ",", yyvsp[0], NULL ), strlen(yyvsp[-2])+strlen(yyvsp[0])+2, FREEME);
		}
    break;
case 15:
#line 117 "addr.y"
{ sv_debugf( "localpart: word: %s\n", yyvsp[0] ); }
    break;
case 16:
#line 118 "addr.y"
{
		sv_debugf( "localpart: localpart word: %s %s\n", yyvsp[-2], yyvsp[0] );
		yyval = sv_strbuf(ml, sv_strconcat( yyvsp[-2], ".", yyvsp[0], NULL ), strlen(yyvsp[-2])+strlen(yyvsp[0])+1, FREEME);
		}
    break;
case 17:
#line 123 "addr.y"
{ sv_debugf( "domain: subdomain: %s\n", yyvsp[0] ); }
    break;
case 18:
#line 124 "addr.y"
{
		sv_debugf( "domain: domain subdomain: %s %s\n", yyvsp[-2], yyvsp[0] );
		yyval = sv_strbuf(ml, sv_strconcat( yyvsp[-2], ".", yyvsp[0], NULL ), strlen(yyvsp[-2])+strlen(yyvsp[0])+1, FREEME);
		}
    break;
case 19:
#line 129 "addr.y"
{ sv_debugf( "subdomain: domainref: %s\n", yyvsp[0] ); }
    break;
case 20:
#line 130 "addr.y"
{ sv_debugf( "subdomain: domainlit: %s\n", yyvsp[0] ); }
    break;
case 21:
#line 132 "addr.y"
{ sv_debugf( "domainref: ATOM: %s\n", yyvsp[0] ); }
    break;
case 22:
#line 134 "addr.y"
{
	 	sv_debugf( "domainlit: DTEXT: %s\n", yyvsp[-1] );
		yyval = yyvsp[-1];
		}
    break;
case 23:
#line 139 "addr.y"
{ sv_debugf( "phrase: word: %s\n", yyvsp[0] ); }
    break;
case 24:
#line 140 "addr.y"
{
		sv_debugf( "phrase: phrase word: %s %s\n", yyvsp[-1], yyvsp[0] );
		yyval = sv_strbuf(ml, sv_strconcat( yyvsp[-1], " ", yyvsp[0], NULL ), strlen(yyvsp[-1])+strlen(yyvsp[0])+1, FREEME);
		}
    break;
case 25:
#line 145 "addr.y"
{ sv_debugf( "word: ATOM: %s\n", yyvsp[0] ); }
    break;
case 26:
#line 146 "addr.y"
{ sv_debugf( "word: qstring: %s\n", yyvsp[0] ); }
    break;
case 27:
#line 148 "addr.y"
{
		sv_debugf( "qstring: QTEXT: %s\n", yyvsp[-1] );
		yyval = yyvsp[-1];
		}
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
#line 153 "addr.y"


/* copy address error message into buffer provided by sieve parser */
void addrerror(const char *s)
{
    extern char *addrerr;
    addrerr = sv_strdup(s, strlen(s));
}

/* Wrapper for addrparse() which sets up the 
 * required environment and allocates variables
 */
struct address *addr_parse_buffer(struct address **data, const char **ptr, char **err)
{
    struct address *newdata = NULL;
    extern struct mlbuf *ml;
    extern struct address *addr;

    addr = NULL;
    addrappend(&addr);

    sv_strbufalloc(&ml);

    (const char *)addrptr = *ptr;

    /* This is now done higher up the call chain...
     * addrlexalloc();
     */
    if(addrparse()) {
        /*
        *err = sv_strdup(addrerr);
        sv_debugf( "%s\n", err );
        sv_free(err);
        */
        // FIXME: Make sure that this is sufficient cleanup
        addrstructfree(addr, CHARSALSO);
        sv_strbuffree(&ml);
        return NULL;
    }

    /* Get to the tail end... */
    newdata = *data;
    while(newdata != NULL) {
        newdata = newdata->next;
    }

    /* While adding the new results onto the current set,
     * we notice that addrparse() leaves an extra struct
     * at the top, but at least we can hide that here!
     */
    newdata = addrstructcopy(addr->next, STRUCTONLY);
    addrstructfree(addr, STRUCTONLY);
    sv_strbuffree(&ml);
    /* This causes a segfault here...
     * but now it's been put much higher up and works
     * addrlexfree();
     */

    if(*data == NULL)
        *data = newdata;

    return *data;
}

void addrstructfree(struct address *addr, int freeall)
{
    struct address *bddr;

    while(addr != NULL) {
        bddr = addr;
        if(freeall) {
            sv_debugf("I'd like to free this: %s\n", bddr->mailbox);
            sv_free(bddr->mailbox);
            sv_debugf("I'd like to free this: %s\n", bddr->domain);
            sv_free(bddr->domain);
            sv_debugf("I'd like to free this: %s\n", bddr->route);
            sv_free(bddr->route);
            sv_debugf("I'd like to free this: %s\n", bddr->name);
            sv_free(bddr->name);
        }
        addr = bddr->next;
        sv_free(bddr);
    }
}

struct address *addrstructcopy(struct address *addr, int copyall)
{
    struct address *new;
    struct address *tmp = addr;
    struct address *top = sv_malloc(sizeof(struct address));

    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
    top->mailbox = tmp->mailbox;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
    top->domain = tmp->domain;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
    top->route = tmp->route;
    sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
    top->name = tmp->name;
    tmp = tmp->next;
    new = top;
    while(tmp != NULL) {
        new->next = (struct address *)sv_malloc(sizeof(struct address));
        if (new->next == NULL)
            return NULL;   
        else
            new = new->next;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->mailbox, tmp->mailbox);
        new->mailbox = tmp->mailbox;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->domain, tmp->domain);
        new->domain = tmp->domain;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->route, tmp->route);
        new->route = tmp->route;
        sv_debugf("I'd like to copy this pointer: %p: %s\n", tmp->name, tmp->name);
        new->name = tmp->name;
        tmp = tmp->next;
    }
    new->next = NULL; /* Clear the last entry */

    return top;
}

void addrappend(struct address **a)
{
    sv_debugf( "Prepending a new addr struct\n" );
    struct address *new = (struct address *)sv_malloc(sizeof(struct address));
    new->mailbox = NULL;
    new->domain = NULL;
    new->route = NULL;
    new->name = NULL;
    new->next = *a;
    *a = new;
}

