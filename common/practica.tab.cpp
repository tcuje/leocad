
/* A Bison parser, made from practica.y
   by GNU bison 1.29.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	NUM	257
# define	NAME	258
# define	MATRIX	259
# define	IDENTIFICADOR	260
# define	CONNECTOR	261
# define	PARAMETERS	262
# define	LENGHT	263
# define	ID	264
# define	BROTHER	265
# define	RADIUS	266
# define	TOOTH	267
# define	CONNECTI	268
# define	CONA	269
# define	ASSEMBLING	270
# define	VERIFICATION	271

#line 1 "practica.y"

#include "lexyy.c"
#include "contenido.h"
#include "diccionario.h"
#include "piece.h"
#include "utilidades.h"
#include "globals.h"
#include "pasos.h"
yyerror(char *a){}
//yylex(void);
Contenido c;
typedef struct node * di;
typedef struct node{
	Diccionario d;
	di seg;
} node;
di dic=NULL;
di nou;
//Diccionario dic[50];
bool primero=true;
Pasos *pasando;
int conta=0;
char cona[20];
char conb[20];
char *aux,aux2[50];

#line 22 "practica.y"
/*typedef union{
	char *cadena;
} YYSTYPE;*/
#include <stdio.h>



#define	YYFINAL		139
#define	YYFLAG		-32768
#define	YYNTBASE	21

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 271 ? yytranslate[x] : 37)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      18,     2,    20,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17
};

#if YYDEBUG != 0
static const short yyprhs[] =
{
       0,     0,     4,     8,    13,    15,    23,    32,    41,    50,
      53,    55,    60,    64,    67,    70,    75,    86,    89,   114,
     131,   140,   164
};
static const short yyrhs[] =
{
      18,    31,    32,     0,    18,    25,    30,     0,    36,    18,
      31,    32,     0,    36,     0,    33,    33,    34,    35,    18,
      19,    31,     0,    18,    15,    20,     6,    18,    19,    15,
      20,     0,    18,    16,    20,     6,    18,    19,    16,    20,
       0,    18,    17,    20,     6,    18,    19,    17,    20,     0,
      24,    21,     0,    24,     0,    18,    25,    24,    21,     0,
      18,    25,    24,     0,    14,    20,     0,     7,    20,     0,
      28,    18,    19,    25,     0,    28,    18,    26,    27,    18,
      19,    26,    18,    19,    25,     0,    22,    23,     0,    18,
       9,    20,     3,    18,    19,     9,    20,    18,    10,    20,
       3,    18,    19,    10,    20,    18,    11,    20,     3,    18,
      19,    11,    20,     0,    18,    12,    20,     3,    18,    19,
      12,    20,    18,    13,    20,     3,    18,    19,    13,    20,
       0,    18,     4,    20,     6,    18,    19,     4,    20,     0,
      18,     5,    20,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,    18,
      19,     5,    20,     0,     8,    20,     0
};

#endif

#if YYDEBUG != 0
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    31,    32,    35,    36,    38,    40,    42,    44,    47,
      48,    52,    53,    56,    58,    61,    62,    64,    67,    68,
      71,    74,    77
};
#endif


#if YYDEBUG != 0 || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUM", "NAME", "MATRIX", "IDENTIFICADOR",
  "CONNECTOR", "PARAMETERS", "LENGHT", "ID", "BROTHER", "RADIUS", "TOOTH",
  "CONNECTI", "CONA", "ASSEMBLING", "VERIFICATION", "'<'", "'/'", "'>'",
  "expressio", "nombre", "matriz", "valores", "connec", "para", "partes",
  "nm", "ini", "aux2", "connecti", "aux", "cona", "assem", "veri", "val", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    29,    29,    32,    32,    36,    33,    34,    35,    30,
      30,    21,    21,    31,    25,    24,    24,    28,    27,    27,
      22,    23,    26
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     3,     3,     4,     1,     7,     8,     8,     8,     2,
       1,     4,     3,     2,     2,     4,    10,     2,    24,    16,
       8,    23,     2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     0,     0,     0,     0,     0,    14,    13,     0,     0,
      10,     0,     2,     0,     1,     0,     4,     0,     0,    17,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    22,
      15,     0,     0,     0,     0,     0,     0,     3,     0,     0,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    20,     0,     0,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    16,     7,     0,     0,     0,     0,     8,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,    18,     0,     0,     0
};

static const short yydefgoto[] =
{
      21,     9,    19,    10,     4,    31,    42,    11,   137,    12,
       5,    14,    15,    34,    46,    16
};

static const short yypact[] =
{
     -15,    -3,   -14,   -13,    -9,    -2,-32768,-32768,     8,    -1,
       0,     1,-32768,     5,-32768,    -2,     3,    -5,     9,-32768,
      15,-32768,    -6,     4,     7,    12,    17,    10,    -9,    11,
      15,    14,    21,    13,    16,    -2,    18,    25,     0,-32768,
  -32768,    -4,    19,    20,    23,    22,    26,-32768,    27,    30,
  -32768,    28,    29,    31,    32,    34,    33,    35,    37,    42,
      44,    49,    47,    41,    39,    52,    12,    40,    56,    43,
      45,    46,    48,    50,    53,-32768,-32768,    59,    51,    54,
      55,-32768,    60,    58,    62,    57,    63,    15,    61,    65,
      69,    64,    66,-32768,-32768,    67,    75,    70,    71,-32768,
      76,    73,    72,    77,    74,    78,    87,    88,    89,    90,
      79,    81,    92,    82,    83,    93,    94,    95,    97,    85,
      86,   100,    91,-32768,    96,    24,    98,    99,   102,   107,
     101,   104,-32768,   105,   109,   103,-32768,   111,   112,-32768
};

static const short yypgoto[] =
{
      80,-32768,-32768,   106,   -20,    68,-32768,-32768,-32768,-32768,
     -24,   108,   110,-32768,-32768,-32768
};


#define	YYLAST		143


static const short yytable[] =
{
      28,    35,    29,     1,     2,    51,     6,     7,    52,     8,
      40,     3,    17,    30,    27,    26,    13,    18,    20,    22,
      23,    25,     2,    36,    32,    33,     3,    43,    49,    44,
      37,    39,    41,    59,    45,   127,    48,    53,    54,    56,
      64,    67,    75,    55,    57,    68,    58,    69,    60,    61,
      62,    63,    70,    65,    66,    29,    72,    73,    74,    77,
      76,    78,    84,    79,    80,    90,    91,    93,    81,    82,
      85,    83,    96,    86,    87,    92,    88,    89,   100,   103,
     106,    94,    95,   104,    97,   105,    98,    99,   101,   102,
     109,   110,   111,   112,   107,   115,   118,   113,   108,   114,
     121,   116,   117,   124,   119,   122,   123,   130,   120,   125,
     131,   138,   139,     0,   126,     0,     0,   128,    50,   129,
     135,   132,   133,   136,   134,    24,     0,     0,     0,     0,
      71,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    47
};

static const short yycheck[] =
{
      20,    25,     8,    18,     7,     9,    20,    20,    12,    18,
      30,    14,     4,    19,     5,    20,    18,    18,    18,    18,
      15,    18,     7,     6,    20,    18,    14,     6,     3,    16,
      20,    20,    18,     3,    18,    11,    18,    18,    18,    17,
       6,     4,    66,    20,    18,     3,    19,     3,    20,    20,
      19,    19,     3,    20,    19,     8,    15,    18,     6,     3,
      20,    18,     3,    18,    18,     3,     9,    87,    20,    19,
      19,    18,     3,    19,    19,    12,    16,    19,     3,     3,
       3,    20,    17,    10,    20,    13,    20,    20,    18,    18,
       3,     3,     3,     3,    20,     3,     3,    18,    20,    18,
       3,    19,    19,     3,    10,    20,    20,     5,    13,    18,
       3,     0,     0,    -1,    18,    -1,    -1,    19,    38,    20,
      11,    20,    18,    20,    19,    15,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "s:/djgpp/lib/bison.sim"

/* Skeleton output parser for bison,
   Copyright 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

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

#ifndef YYSTACK_USE_ALLOCA
# ifdef alloca
#  define YYSTACK_USE_ALLOCA 1
# else /* alloca not defined */
#  ifdef __GNUC__
#   define YYSTACK_USE_ALLOCA 1
#   define alloca __builtin_alloca
#  else /* not GNU C.  */
#   if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#    define YYSTACK_USE_ALLOCA 1
#    include <alloca.h>
#   else /* not sparc */
     /* We think this test detects Watcom and Microsoft C.  */
     /* This used to test MSDOS, but that is a bad idea since that
	symbol is in the user namespace.  */
#    if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#     if 0
       /* No need for malloc.h, which pollutes the namespace; instead,
	  just don't use alloca.  */
#      include <malloc.h>
#     endif
#    else /* not MSDOS, or __TURBOC__ */
#     if defined(_AIX)
       /* I don't know what this was needed for, but it pollutes the
	  namespace.  So I turned it off.  rms, 2 May 1997.  */
       /* #include <malloc.h>  */
 #pragma alloca
#      define YYSTACK_USE_ALLOCA 1
#     else /* not MSDOS, or __TURBOC__, or _AIX */
#      if 0
	/* haible@ilog.fr says this works for HPUX 9.05 and up, and on
	   HPUX 10.  Eventually we can turn this on.  */
#       ifdef __hpux
#        define YYSTACK_USE_ALLOCA 1
#        define alloca __builtin_alloca
#	endif /* __hpux */
#      endif
#     endif /* not _AIX */
#    endif /* not MSDOS, or __TURBOC__ */
#   endif /* not sparc */
#  endif /* not GNU C */
# endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#if YYSTACK_USE_ALLOCA
# define YYSTACK_ALLOC alloca
#else
# define YYSTACK_ALLOC malloc
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT	goto yyabortlab
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
    {								\
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
# define YYLLOC_DEFAULT(Current, Rhs, N)	\
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
# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    fprintf Args;				\
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
   if the built-in stack extension method is used).  */
#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
# define __yy_memcpy(To, From, Count)	__builtin_memcpy (To, From, Count)
#else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
# ifndef __cplusplus
__yy_memcpy (to, from, count)
     char *to;
     const char *from;
     unsigned int count;
# else /* __cplusplus */
__yy_memcpy (char *to, const char *from, unsigned int count)
# endif
{
  register const char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif

#line 212 "s:/djgpp/lib/bison.sim"


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

#define _YY_DECL_VARIABLES				\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES				\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES
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
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yysv': related to semantic values,
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

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
# if YYLSP_NEEDED
  YYLTYPE yyloc;
# endif

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
      /* Give user a chance to reallocate the stack. Use copies of
	 these so that the &'s don't force the real ones into memory.
	 */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#if YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of the
	 data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yyls1, size * sizeof (*yylsp),
		  &yystacksize);
# else
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yystacksize);
# endif

      yyss = yyss1; yyvs = yyvs1;
# if YYLSP_NEEDED
      yyls = yyls1;
# endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror ("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
# if YYLSP_NEEDED
	      free (yyls);
# endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
# ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
# endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
# if YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
# endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#if YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %d\n", yystacksize));

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
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  fprintf (stderr, ")\n");
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
  YYDPRINTF ((stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]));

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
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 31 "practica.y"
{//conexiones;
    break;}
case 2:
#line 32 "practica.y"
{//pieza;
    break;}
case 3:
#line 35 "practica.y"
{ //mas conexiones;
    break;}
case 4:
#line 36 "practica.y"
{//unica conexion;
    break;}
case 5:
#line 38 "practica.y"
{pasando->IntroducirConectores(cona,conb); ges->Introducir(*pasando);delete pasando;//valores;
    break;}
case 6:
#line 40 "practica.y"
{if(primero){primero=false;pasando=new Pasos();}else{primero=true;}strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2); (primero)?strcpy(conb,aux):strcpy(cona,aux);//conector;
    break;}
case 7:
#line 42 "practica.y"
{strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2);conta=strlen(aux);while (conta>1){pasando->IntroducirPasos(*aux);conta--;aux++;}pasando->IntroducirPasos(*aux);//assenbling;
    break;}
case 8:
#line 44 "practica.y"
{strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2);conta=strlen(aux);while (conta>1){pasando->IntroducirPasosV(*aux);conta--;aux++;}pasando->IntroducirPasosV(*aux);//verificacion;
    break;}
case 9:
#line 47 "practica.y"
{pieza_asembling->crearConector(yyvsp[-1].cadena,dic->d);nou=dic;dic=dic->seg;delete nou;;
    break;}
case 10:
#line 48 "practica.y"
{pieza_asembling->crearConector(yyvsp[0].cadena,dic->d);nou=dic;dic=dic->seg;delete nou;;
    break;}
case 11:
#line 52 "practica.y"
{ pieza_asembling->crearConector(yyvsp[-1].cadena,dic->d);nou=dic;dic=dic->seg;delete nou;;
    break;}
case 12:
#line 53 "practica.y"
{pieza_asembling->crearConector(yyvsp[0].cadena,dic->d);nou=dic;dic=dic->seg;delete nou;;
    break;}
case 15:
#line 61 "practica.y"
{yyval.cadena=yyvsp[-3].cadena;;
    break;}
case 16:
#line 62 "practica.y"
{yyval.cadena=yyvsp[-9].cadena;;
    break;}
case 17:
#line 64 "practica.y"
{yyval.cadena=yyvsp[-1].cadena;;
    break;}
case 18:
#line 67 "practica.y"
{strcpy(aux2,yyvsp[-20].cadena);aux=buscarfin(aux2);c.introducirContenido(aux);dic->d.Introducir ("<lenght>",c);strcpy(aux2,yyvsp[-12].cadena);aux=buscarfin(aux2);c.introducirContenido(aux);dic->d.Introducir ("<id>",c);strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2);c.introducirContenido(aux);dic->d.Introducir ("<brother>",c);;
    break;}
case 19:
#line 68 "practica.y"
{ strcpy(aux2,yyvsp[-12].cadena);aux=buscarfin(aux2);c.introducirContenido(aux);dic->d.Introducir("<radius>",c); strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2);c.introducirContenido(aux);dic->d.Introducir("<tooth>",c); ;
    break;}
case 20:
#line 71 "practica.y"
{strcpy(aux2,yyvsp[-4].cadena);aux=buscarfin(aux2);yyval.cadena=new char[strlen(aux)+1];strcpy(yyval.cadena,aux);c.introducirContenido(aux);nou=new node;nou->seg=dic;dic=nou;dic->d.Introducir("<name>",c);;
    break;}
case 21:
#line 74 "practica.y"
{ strcpy(aux2,yyvsp[-19].cadena);aux=buscarfin(aux2);c.introducirContenido(aux); dic->d.Introducir("<matrix>",c);;
    break;}
}

#line 606 "s:/djgpp/lib/bison.sim"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
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
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen (yytname[x]) + 15, count++;
	  size += strlen ("parse error, unexpected `") + 1;
	  size += strlen (yytname[YYTRANSLATE (yychar)]);
	  msg = (char *) malloc (size);
	  if (msg != 0)
	    {
	      strcpy (msg, "parse error, unexpected `");
	      strcat (msg, yytname[YYTRANSLATE (yychar)]);
	      strcat (msg, "'");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat (msg, count == 0 ? ", expecting `" : " or `");
			strcat (msg, yytname[x]);
			strcat (msg, "'");
			count++;
		      }
		}
	      yyerror (msg);
	      free (msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
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
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
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
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 80 "practica.y"

int parser(char * path)
{
	FILE *prova;
	prova=fopen(path,"r");
	if(prova!=NULL)
	{
		extern FILE *yyin;
		yyin=prova;
		return yyparse();
		yyin=NULL;
		fclose(prova);
	}
	else
	{
		return -1;
	}
}

