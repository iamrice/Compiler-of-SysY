/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "parse_tree.h"


void yyerror(char *s, ...);
int yylex();
program* ast_root;

#line 79 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST = 258,
    VOID = 259,
    IF = 260,
    WHILE = 261,
    BREAK = 262,
    CONTINUE = 263,
    RETURN = 264,
    ELSE = 265,
    INT = 266,
    IDENT = 267,
    INTCONST = 268,
    GE = 269,
    NE = 270,
    LT = 271,
    GT = 272,
    LE = 273,
    EQ = 274,
    AND = 275,
    OR = 276,
    ASSIGN = 277,
    TIMES = 278,
    MOD = 279,
    OVER = 280,
    PLUS = 281,
    MINUS = 282,
    MARK = 283,
    COMMA = 284,
    SEMICOLON = 285,
    LBRACE = 286,
    RBRACE = 287,
    LPAREN = 288,
    RPAREN = 289,
    LB = 290,
    RB = 291,
    COMA = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "parser.y" /* yacc.c:355  */

	Program program;
	CompUnit compUnit;
	CompUnits compUnits;
	Decl decl;
	VarDef varDef;
	VarDefs varDefs;
	InitVal initVal;
	InitVals initVals;
	FuncDef funcDef;
	FuncFParam funcFParam;
	FuncFParams funcFParams;
	Block block;
	Blocks blocks;
	Stmt stmt;
	PrimaryExp primaryExp;
	UnaryExp unaryExp;
	UnaryOp unaryOp;
	MulExp mulExp;
	AddExp addExp;
	AddExps addExps;
	FuncRParams funcRParams;
	RelExp relExp;
	EqExp eqExp;
	LAndExp lAndExp;
	LOrExp lOrExp;
	Id id;
	char* symbol;

#line 184 "parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);



/* Copy the second part of user declarations.  */

#line 215 "parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    98,    99,   101,   102,   104,   105,   107,
     108,   110,   111,   113,   114,   117,   118,   120,   123,   125,
     129,   130,   132,   135,   137,   141,   142,   145,   147,   150,
     152,   154,   156,   158,   160,   162,   164,   166,   168,   170,
     173,   175,   177,   179,   181,   183,   185,   187,   189,   191,
     196,   198,   200,   203,   205,   207,   209,   212,   214,   216,
     219,   221,   224,   226,   228,   230,   234,   235,   238,   240,
     242,   245,   247,   249,   251,   253,   256,   258,   260,   263,
     265,   268,   270,   273
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "VOID", "IF", "WHILE", "BREAK",
  "CONTINUE", "RETURN", "ELSE", "INT", "IDENT", "INTCONST", "GE", "NE",
  "LT", "GT", "LE", "EQ", "AND", "OR", "ASSIGN", "TIMES", "MOD", "OVER",
  "PLUS", "MINUS", "MARK", "COMMA", "SEMICOLON", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "LB", "RB", "COMA", "$accept", "program",
  "compUnits", "compUnit", "decl", "varDefs", "varDef", "initVal",
  "initVals", "funcDef", "funcFParams", "funcFParam", "blocks", "block",
  "stmt", "stmt1", "primaryExp", "unaryExp", "unaryOp", "funcRParams",
  "mulExp", "addExps", "addExp", "relExp", "eqExp", "lAndExp", "lOrExp",
  "id", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF -157

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-157)))

#define YYTABLE_NINF -50

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,     4,    25,    25,    45,    77,  -157,  -157,  -157,    25,
    -157,    19,    79,  -157,    89,  -157,  -157,   114,    43,    71,
      25,  -157,    71,    16,    82,  -157,    25,    50,  -157,  -157,
      60,  -157,  -157,  -157,  -157,    16,  -157,  -157,    16,   144,
     -17,    97,    38,    58,    71,    84,   102,    85,  -157,    16,
      16,    16,    16,    16,    43,    13,  -157,    38,  -157,   175,
      99,  -157,  -157,  -157,  -157,  -157,  -157,  -157,   144,   144,
    -157,  -157,    62,   175,  -157,    63,    43,   167,   178,    16,
    -157,    38,  -157,  -157,   106,   115,   121,   132,    90,    25,
    -157,  -157,  -157,  -157,  -157,  -157,   123,    97,  -157,   175,
    -157,    16,    16,  -157,  -157,  -157,   131,   209,  -157,   142,
     175,   124,    12,   134,    -1,    14,  -157,  -157,    16,    16,
      16,    16,    16,    16,    16,    16,    16,   249,   258,   133,
     175,   175,   175,   175,   124,   124,    12,   134,   149,   155,
     147,   162,   101,   186,  -157,  -157,   193,   242,    97,  -157,
    -157,    16,    16,   197,   203,   214,   266,   220,   258,   224,
     208,    49,    56,   228,   235,  -157,    16,   249,   249,   268,
     239,  -157,   263,   249,  -157
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     4,     5,     6,     0,
      83,     0,     0,     9,    66,     1,     3,     0,    66,    20,
       0,     8,    20,     0,    11,     7,     0,     0,    22,    10,
       0,    52,    57,    58,    59,     0,    53,    62,     0,    68,
       0,    66,     0,    23,     0,     0,     0,     0,    56,     0,
       0,     0,     0,     0,    66,     0,    51,    15,    12,    13,
       0,    21,    25,    25,    50,    63,    65,    64,    69,    70,
      67,    55,     0,    61,    17,     0,    66,     0,     0,     0,
      54,     0,    14,    24,     0,     0,     0,     0,     0,     0,
      30,    25,    18,    27,    26,    28,     0,    66,    19,    60,
      16,     0,     0,    36,    37,    39,     0,     0,    31,    51,
      71,    76,    79,    81,     0,     0,    38,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    72,    73,    74,    78,    77,    80,    82,     0,     0,
       0,     0,     0,    30,    25,    34,     0,     0,    66,    35,
      29,     0,     0,    36,    37,    39,     0,     0,     0,    31,
      51,     0,     0,    38,    32,    33,     0,     0,     0,     0,
       0,    45,    29,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -157,  -157,  -157,   269,     8,   210,   261,   -51,  -157,  -157,
     256,   243,   -59,  -157,  -105,  -156,  -157,    23,  -157,  -157,
     191,   -38,   -21,   136,   158,   164,   -97,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    93,    12,    13,    58,    75,     8,
      27,    28,    77,    94,    95,   146,    36,    37,    38,    72,
      39,    24,   110,   111,   112,   113,   114,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,    14,    40,    56,    78,   115,    74,    18,     7,    52,
      53,   170,   171,     7,    47,     9,    70,   174,    18,    54,
     126,    59,   145,   149,    43,    10,    31,   123,    10,    31,
     100,   124,   107,   127,    73,   126,    59,    10,    83,    32,
      33,    34,    32,    33,    34,    15,    35,    71,   128,    35,
      10,    31,    19,   165,   161,   162,    96,    96,    99,   109,
      59,    48,   145,   149,    32,    33,    34,   106,   165,    57,
     126,    35,    65,    66,    67,    97,    97,   126,    23,    44,
       1,     2,    26,   167,    45,   157,    96,    18,     3,    44,
     168,    79,    81,    60,    46,    82,    80,   129,   130,   131,
     132,   133,    10,    31,    42,    97,   147,    96,    20,    21,
     160,    52,    53,    10,    31,    62,    32,    33,    34,    64,
     105,   156,    22,    35,    23,   148,    97,    32,    33,    34,
      55,   155,    23,    63,    35,    76,    96,    96,   119,   101,
     120,   121,   122,    20,    25,   169,   147,   147,   102,    52,
      53,   103,   147,   108,   125,    97,    97,    52,    53,    52,
      53,   116,   104,   150,   118,   148,   148,    49,    50,    51,
       1,   148,    84,    85,    86,    87,    88,   153,    89,    10,
      31,     1,   151,    84,    85,    86,    87,    88,   152,    89,
      10,    31,   154,    32,    33,    34,   -41,    90,    91,    92,
      35,    52,    53,   158,    32,    33,    34,   -46,    90,    91,
      98,    35,     1,   -47,    84,    85,    86,    87,    88,    17,
      89,    10,    31,     1,   -49,    84,    85,    86,    87,    88,
     166,    89,    10,    31,   -42,    32,    33,    34,   -48,    90,
      91,   117,    35,    68,    69,   -43,    32,    33,    34,   173,
      90,    91,   164,    35,   138,   139,   140,   141,   142,   134,
     135,    10,    31,    84,    85,    86,    87,    88,    52,    53,
      10,    31,   159,   -40,    16,    32,    33,    34,    30,   143,
     144,    29,    35,   136,    32,    33,    34,    61,    90,    91,
     137,    35,    52,    53,    52,    53,   163,     0,   172
};

static const yytype_int16 yycheck[] =
{
       2,     3,    23,    41,    63,   102,    57,     9,     0,    26,
      27,   167,   168,     5,    35,    11,    54,   173,    20,    36,
      21,    42,   127,   128,    26,    12,    13,    15,    12,    13,
      81,    19,    91,    34,    55,    21,    57,    12,    76,    26,
      27,    28,    26,    27,    28,     0,    33,    34,    34,    33,
      12,    13,    33,   158,   151,   152,    77,    78,    79,    97,
      81,    38,   167,   168,    26,    27,    28,    88,   173,    31,
      21,    33,    49,    50,    51,    77,    78,    21,    35,    29,
       3,     4,    11,    34,    34,   144,   107,    89,    11,    29,
      34,    29,    29,    35,    34,    32,    34,   118,   119,   120,
     121,   122,    12,    13,    22,   107,   127,   128,    29,    30,
     148,    26,    27,    12,    13,    31,    26,    27,    28,    34,
      30,   142,    33,    33,    35,   127,   128,    26,    27,    28,
      33,    30,    35,    31,    33,    36,   157,   158,    14,    33,
      16,    17,    18,    29,    30,   166,   167,   168,    33,    26,
      27,    30,   173,    30,    20,   157,   158,    26,    27,    26,
      27,    30,    30,    30,    22,   167,   168,    23,    24,    25,
       3,   173,     5,     6,     7,     8,     9,    30,    11,    12,
      13,     3,    33,     5,     6,     7,     8,     9,    33,    11,
      12,    13,    30,    26,    27,    28,    10,    30,    31,    32,
      33,    26,    27,    10,    26,    27,    28,    10,    30,    31,
      32,    33,     3,    10,     5,     6,     7,     8,     9,     9,
      11,    12,    13,     3,    10,     5,     6,     7,     8,     9,
      22,    11,    12,    13,    10,    26,    27,    28,    10,    30,
      31,    32,    33,    52,    53,    10,    26,    27,    28,    10,
      30,    31,    32,    33,     5,     6,     7,     8,     9,   123,
     124,    12,    13,     5,     6,     7,     8,     9,    26,    27,
      12,    13,    30,    10,     5,    26,    27,    28,    22,    30,
      31,    20,    33,   125,    26,    27,    28,    44,    30,    31,
     126,    33,    26,    27,    26,    27,    30,    -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    11,    39,    40,    41,    42,    47,    11,
      12,    65,    43,    44,    65,     0,    41,    43,    65,    33,
      29,    30,    33,    35,    59,    30,    11,    48,    49,    44,
      48,    13,    26,    27,    28,    33,    54,    55,    56,    58,
      60,    65,    22,    65,    29,    34,    34,    60,    55,    23,
      24,    25,    26,    27,    36,    33,    59,    31,    45,    60,
      35,    49,    31,    31,    34,    55,    55,    55,    58,    58,
      59,    34,    57,    60,    45,    46,    36,    50,    50,    29,
      34,    29,    32,    59,     5,     6,     7,     8,     9,    11,
      30,    31,    32,    42,    51,    52,    60,    65,    32,    60,
      45,    33,    33,    30,    30,    30,    60,    50,    30,    59,
      60,    61,    62,    63,    64,    64,    30,    32,    22,    14,
      16,    17,    18,    15,    19,    20,    21,    34,    34,    60,
      60,    60,    60,    60,    61,    61,    62,    63,     5,     6,
       7,     8,     9,    30,    31,    52,    53,    60,    65,    52,
      30,    33,    33,    30,    30,    30,    60,    50,    10,    30,
      59,    64,    64,    30,    32,    52,    22,    34,    34,    60,
      53,    53,    30,    10,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    46,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    58,    58,    58,    58,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     4,     3,     1,
       3,     2,     4,     1,     3,     0,     3,     1,     8,     8,
       0,     3,     1,     2,     5,     0,     2,     1,     1,     5,
       1,     2,     3,     7,     5,     5,     2,     2,     3,     2,
       5,     1,     2,     3,     7,     5,     2,     2,     3,     2,
       3,     2,     1,     1,     4,     3,     2,     1,     1,     1,
       3,     1,     1,     3,     3,     3,     0,     4,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 96 "parser.y" /* yacc.c:1646  */
    {(yyloc) = (yylsp[0]); ast_root = new program((yyvsp[0].compUnits));}
#line 1527 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 98 "parser.y" /* yacc.c:1646  */
    { (yyval.compUnits) =new append_node<CompUnit>((yyvsp[-1].compUnits),new single_node<CompUnit>((yyvsp[0].compUnit)));}
#line 1533 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 99 "parser.y" /* yacc.c:1646  */
    {(yyval.compUnits) =new single_node<CompUnit>((yyvsp[0].compUnit));}
#line 1539 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 101 "parser.y" /* yacc.c:1646  */
    {(yyval.compUnit) = new decl_CompUnit((yyvsp[0].decl));}
#line 1545 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval.compUnit) = new funcDef_CompUnit((yyvsp[0].funcDef));}
#line 1551 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 104 "parser.y" /* yacc.c:1646  */
    {(yyval.decl) = new constVarDecl((yyvsp[-1].varDefs));}
#line 1557 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "parser.y" /* yacc.c:1646  */
    {(yyval.decl) = new varDecl((yyvsp[-1].varDefs));}
#line 1563 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "parser.y" /* yacc.c:1646  */
    {(yyval.varDefs) = new single_node<VarDef>((yyvsp[0].varDef));}
#line 1569 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval.varDefs) = new append_node<VarDef>((yyvsp[-2].varDefs),new single_node<VarDef>((yyvsp[0].varDef)));}
#line 1575 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 110 "parser.y" /* yacc.c:1646  */
    {(yyval.varDef) = new uninit_VarDef((yyvsp[-1].id),(yyvsp[0].addExps)); }
#line 1581 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 111 "parser.y" /* yacc.c:1646  */
    {(yyval.varDef) = new init_VarDef((yyvsp[-3].id),(yyvsp[-2].addExps),(yyvsp[0].initVal));}
#line 1587 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 113 "parser.y" /* yacc.c:1646  */
    {(yyval.initVal) = new one_InitVal((yyvsp[0].addExp));}
#line 1593 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 114 "parser.y" /* yacc.c:1646  */
    {(yyval.initVal) = new more_InitVal((yyvsp[-1].initVals));}
#line 1599 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval.initVals) = new nil_node<InitVal>();}
#line 1605 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 119 "parser.y" /* yacc.c:1646  */
    {(yyval.initVals) = new append_node<InitVal>((yyvsp[-2].initVals),new single_node<InitVal>((yyvsp[0].initVal))); }
#line 1611 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 121 "parser.y" /* yacc.c:1646  */
    {(yyval.initVals) = new single_node<InitVal>((yyvsp[0].initVal));}
#line 1617 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 124 "parser.y" /* yacc.c:1646  */
    {(yyval.funcDef) = new void_Func((yyvsp[-6].id),(yyvsp[-4].funcFParams),(yyvsp[-1].blocks));}
#line 1623 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.funcDef) = new int_Func((yyvsp[-6].id),(yyvsp[-4].funcFParams),(yyvsp[-1].blocks));}
#line 1629 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.funcFParams) = new nil_node<FuncFParam>();}
#line 1635 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval.funcFParams) = new append_node<FuncFParam>((yyvsp[-2].funcFParams),new single_node<FuncFParam>((yyvsp[0].funcFParam)));}
#line 1641 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 133 "parser.y" /* yacc.c:1646  */
    {(yyval.funcFParams) = new single_node<FuncFParam>((yyvsp[0].funcFParam));}
#line 1647 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.funcFParam) = new int_Param((yyvsp[0].id));}
#line 1653 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 138 "parser.y" /* yacc.c:1646  */
    {(yyval.funcFParam) = new array_Param((yyvsp[-3].id),(yyvsp[0].addExps));}
#line 1659 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 141 "parser.y" /* yacc.c:1646  */
    {(yyval.blocks) = new nil_node<Block>();}
#line 1665 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval.blocks) = new append_node<Block>((yyvsp[-1].blocks),new single_node<Block>((yyvsp[0].block)));}
#line 1671 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.block) = new decl_block((yyvsp[0].decl));}
#line 1677 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 148 "parser.y" /* yacc.c:1646  */
    {(yyval.block) = new stmt_block((yyvsp[0].stmt));}
#line 1683 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new assign_Stmt((yyvsp[-4].id),(yyvsp[-3].addExps),(yyvsp[-1].addExp));}
#line 1689 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 153 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new empty_Stmt();}
#line 1695 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 155 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new exp_Stmt((yyvsp[-1].addExp));}
#line 1701 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new block_Stmt((yyvsp[-1].blocks));}
#line 1707 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new else_Stmt((yyvsp[-4].lOrExp),(yyvsp[-2].stmt),(yyvsp[0].stmt));}
#line 1713 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 161 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new if_Stmt((yyvsp[-2].lOrExp),(yyvsp[0].stmt));}
#line 1719 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new while_Stmt((yyvsp[-2].lOrExp),(yyvsp[0].stmt));}
#line 1725 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new break_Stmt();}
#line 1731 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new continue_Stmt();}
#line 1737 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new return_exp_Stmt((yyvsp[-1].addExp));}
#line 1743 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 171 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new return_Stmt();}
#line 1749 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 174 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new assign_Stmt((yyvsp[-4].id),(yyvsp[-3].addExps),(yyvsp[-1].addExp));}
#line 1755 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new empty_Stmt();}
#line 1761 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new exp_Stmt((yyvsp[-1].addExp));}
#line 1767 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 180 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new block_Stmt((yyvsp[-1].blocks));}
#line 1773 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new else_Stmt((yyvsp[-4].lOrExp),(yyvsp[-2].stmt),(yyvsp[0].stmt));}
#line 1779 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 184 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new while_Stmt((yyvsp[-2].lOrExp),(yyvsp[0].stmt));}
#line 1785 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new break_Stmt();}
#line 1791 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 188 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new continue_Stmt();;}
#line 1797 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 190 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new return_exp_Stmt((yyvsp[-1].addExp));}
#line 1803 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = new return_Stmt();}
#line 1809 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyval.primaryExp) = new primary_Exp((yyvsp[-1].addExp));}
#line 1815 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 199 "parser.y" /* yacc.c:1646  */
    {(yyval.primaryExp) = new lval((yyvsp[-1].id),(yyvsp[0].addExps));}
#line 1821 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 201 "parser.y" /* yacc.c:1646  */
    {(yyval.primaryExp) = new number((yyvsp[0].symbol)); }
#line 1827 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryExp) = new pri_Una((yyvsp[0].primaryExp));}
#line 1833 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryExp) = new func_Una((yyvsp[-3].id),(yyvsp[-1].funcRParams));}
#line 1839 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryExp) = new func_Una((yyvsp[-2].id),new nil_node<AddExp>());}
#line 1845 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryExp) = new op_Una((yyvsp[-1].unaryOp),(yyvsp[0].unaryExp));}
#line 1851 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 213 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryOp) = new una_Op("+");}
#line 1857 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryOp) = new una_Op("-");}
#line 1863 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.unaryOp) = new una_Op("!");}
#line 1869 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.funcRParams) = new append_node<AddExp>((yyvsp[-2].funcRParams),new single_node<AddExp>((yyvsp[0].addExp)));}
#line 1875 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.funcRParams) = new single_node<AddExp>((yyvsp[0].addExp));}
#line 1881 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 225 "parser.y" /* yacc.c:1646  */
    {(yyval.mulExp) = new una_Mul((yyvsp[0].unaryExp));}
#line 1887 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.mulExp) = new times_Mul((yyvsp[-2].mulExp),(yyvsp[0].unaryExp));}
#line 1893 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.mulExp) = new over_Mul((yyvsp[-2].mulExp),(yyvsp[0].unaryExp));}
#line 1899 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval.mulExp) = new mod_Mul((yyvsp[-2].mulExp),(yyvsp[0].unaryExp));}
#line 1905 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyval.addExps) = new nil_node<AddExp>();}
#line 1911 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.addExps) = new append_node<AddExp>(new single_node<AddExp>((yyvsp[-2].addExp)),(yyvsp[0].addExps));}
#line 1917 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 239 "parser.y" /* yacc.c:1646  */
    {(yyval.addExp) = new mul_AddExp((yyvsp[0].mulExp));}
#line 1923 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 241 "parser.y" /* yacc.c:1646  */
    {(yyval.addExp) = new plus_AddExp((yyvsp[-2].addExp),(yyvsp[0].mulExp));}
#line 1929 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.addExp) = new minus_AddExp((yyvsp[-2].addExp),(yyvsp[0].mulExp));}
#line 1935 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 246 "parser.y" /* yacc.c:1646  */
    {(yyval.relExp) = new add_RelExp((yyvsp[0].addExp));}
#line 1941 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 248 "parser.y" /* yacc.c:1646  */
    {(yyval.relExp) = new lt_RelExp((yyvsp[-2].relExp),(yyvsp[0].addExp));}
#line 1947 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 250 "parser.y" /* yacc.c:1646  */
    {(yyval.relExp) = new gt_RelExp((yyvsp[-2].relExp),(yyvsp[0].addExp));}
#line 1953 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 252 "parser.y" /* yacc.c:1646  */
    {(yyval.relExp) = new le_RelExp((yyvsp[-2].relExp),(yyvsp[0].addExp));}
#line 1959 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 254 "parser.y" /* yacc.c:1646  */
    {(yyval.relExp) = new ge_RelExp((yyvsp[-2].relExp),(yyvsp[0].addExp));}
#line 1965 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval.eqExp) = new rel_EqExp((yyvsp[0].relExp));}
#line 1971 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.eqExp) = new eq_EqExp((yyvsp[-2].eqExp),(yyvsp[0].relExp));}
#line 1977 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyval.eqExp) = new nq_EqExp((yyvsp[-2].eqExp),(yyvsp[0].relExp));}
#line 1983 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval.lAndExp) = new eq_LAndExp((yyvsp[0].eqExp));}
#line 1989 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 266 "parser.y" /* yacc.c:1646  */
    {(yyval.lAndExp) = new and_LAndExp((yyvsp[-2].lAndExp),(yyvsp[0].eqExp));}
#line 1995 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 269 "parser.y" /* yacc.c:1646  */
    {(yyval.lOrExp) = new and_LOrExp((yyvsp[0].lAndExp));}
#line 2001 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 271 "parser.y" /* yacc.c:1646  */
    {(yyval.lOrExp) = new or_LOrExp((yyvsp[-2].lOrExp),(yyvsp[0].lAndExp));}
#line 2007 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 273 "parser.y" /* yacc.c:1646  */
    {(yyval.id) = new id((yyvsp[0].symbol));}
#line 2013 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2017 "parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 274 "parser.y" /* yacc.c:1906  */


#include "irGen.h"
#include "armGen.h"
#include "flowPass.h"
#include "blockGen.h"
int main(int argc, const char *args[])
{
	//yydebug = 1;
	extern FILE *yyin;
	yyin = fopen(args[4], "r");
	extern FILE *yyout;
	yyout = fopen(args[3], "w");

	if (!yyparse()) {
		IrGen* gen = new IrGen();
		Prog* res = gen->run(ast_root->e1);
		
		for (Meth* meth : *(res->meths))
		{
			BlockGen* bg = new BlockGen();
			FlowPass* fp = new FlowPass();
			bg->newGen(meth);
			fp->run(meth);
		}
		
		armGen* arm = new armGen();
		std::list<armStmt*>* tmp = arm->run(res);
		for (armStmt* stmt : *tmp) {
			fprintf(yyout, "%s", stmt->render().c_str());
		}
		fclose(yyin);
		fclose(yyout);
		//exit(-1);
	}

	return 0;
}


void yyerror(char *s, ...)
{
    extern int yylineno;

    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
