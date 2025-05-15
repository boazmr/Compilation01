/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include "nodes.hpp"
#include "output.hpp"

// bison declarations
extern int yylineno;
extern int yylex();

void yyerror(const char*);

// root of the AST, set by the parser and used by other parts of the compiler
std::shared_ptr<ast::Node> program;

using namespace std;

// TODO: Place any additional declarations here

#line 90 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_BYTE = 5,                       /* BYTE  */
  YYSYMBOL_BOOL = 6,                       /* BOOL  */
  YYSYMBOL_TRUE = 7,                       /* TRUE  */
  YYSYMBOL_FALSE = 8,                      /* FALSE  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_BREAK = 13,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 14,                  /* CONTINUE  */
  YYSYMBOL_SC = 15,                        /* SC  */
  YYSYMBOL_COMMA = 16,                     /* COMMA  */
  YYSYMBOL_LPAREN = 17,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 18,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 19,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 20,                    /* RBRACE  */
  YYSYMBOL_LBRACK = 21,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 22,                    /* RBRACK  */
  YYSYMBOL_ASSIGN = 23,                    /* ASSIGN  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_NUM = 25,                       /* NUM  */
  YYSYMBOL_NUM_B = 26,                     /* NUM_B  */
  YYSYMBOL_STRING = 27,                    /* STRING  */
  YYSYMBOL_BINOP_ADD = 28,                 /* BINOP_ADD  */
  YYSYMBOL_BINOP_SUB = 29,                 /* BINOP_SUB  */
  YYSYMBOL_BINOP_DIV = 30,                 /* BINOP_DIV  */
  YYSYMBOL_BINOP_MUL = 31,                 /* BINOP_MUL  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_OR = 34,                        /* OR  */
  YYSYMBOL_RelOp_EQ = 35,                  /* RelOp_EQ  */
  YYSYMBOL_RelOp_NE = 36,                  /* RelOp_NE  */
  YYSYMBOL_RelOp_LT = 37,                  /* RelOp_LT  */
  YYSYMBOL_RelOp_GT = 38,                  /* RelOp_GT  */
  YYSYMBOL_RelOp_LE = 39,                  /* RelOp_LE  */
  YYSYMBOL_RelOp_GE = 40,                  /* RelOp_GE  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_Program = 42,                   /* Program  */
  YYSYMBOL_Funcs = 43,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 44,                  /* FuncDecl  */
  YYSYMBOL_RetType = 45,                   /* RetType  */
  YYSYMBOL_Formals = 46,                   /* Formals  */
  YYSYMBOL_FormalsList = 47,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 48,                /* FormalDecl  */
  YYSYMBOL_Statements = 49,                /* Statements  */
  YYSYMBOL_Statement = 50,                 /* Statement  */
  YYSYMBOL_Call = 51,                      /* Call  */
  YYSYMBOL_ExpList = 52,                   /* ExpList  */
  YYSYMBOL_Type = 53,                      /* Type  */
  YYSYMBOL_Exp = 54                        /* Exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   419

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    70,    70,    72,    73,    75,    77,    78,    79,    80,
      82,    83,    86,    88,    89,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   107,
     108,   110,   111,   114,   115,   116,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "BYTE",
  "BOOL", "TRUE", "FALSE", "RETURN", "IF", "ELSE", "WHILE", "BREAK",
  "CONTINUE", "SC", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACK", "RBRACK", "ASSIGN", "ID", "NUM", "NUM_B", "STRING",
  "BINOP_ADD", "BINOP_SUB", "BINOP_DIV", "BINOP_MUL", "NOT", "AND", "OR",
  "RelOp_EQ", "RelOp_NE", "RelOp_LT", "RelOp_GT", "RelOp_LE", "RelOp_GE",
  "$accept", "Program", "Funcs", "FuncDecl", "RetType", "Formals",
  "FormalsList", "FormalDecl", "Statements", "Statement", "Call",
  "ExpList", "Type", "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   -35,   -35,   -35,   -35,     8,   -35,    29,    -3,   -35,
     -35,   -35,    -4,    11,     6,   -35,    10,     3,    19,    11,
     -35,   293,   -35,   149,    34,    36,    39,    42,   293,    35,
     259,   -35,    44,    49,   -35,   -35,   -35,    59,   -14,   -35,
     -35,   -35,   175,   -35,    64,   175,   175,   -35,   -35,   276,
     153,   175,   175,   -35,   -35,   -35,   -11,    56,   194,   175,
     372,   -35,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   208,   222,   -35,   -35,    57,   180,
     291,    81,   -35,   175,   175,   175,   -35,   310,   342,   354,
     364,   372,   379,   151,   297,    68,    30,   -34,    37,   -35,
     293,   293,   -35,   175,    55,   -35,   329,    98,   342,   -35,
     -35,   -35,   -35,   175,    65,   -35,   115,   -35,   -35
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     7,    33,    34,    35,     0,     2,     4,     0,     6,
       1,     3,     0,     8,     0,     9,    10,     0,     0,     0,
      12,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,    47,    48,    22,     0,    42,    44,
      45,    46,     0,    43,     0,     0,     0,    27,    28,     0,
       0,     0,     0,     5,    14,    21,     0,     0,     0,     0,
      49,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    30,     0,    31,
       0,     0,    16,     0,     0,     0,    36,     0,    38,    39,
      41,    40,    50,    51,    52,    53,    54,    55,    56,    57,
       0,     0,    29,     0,     0,    18,     0,     0,    58,    37,
      24,    26,    32,     0,     0,    17,     0,    20,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,    80,   -35,   -35,   -35,    69,   -35,    61,   -29,
     -19,    20,    18,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    14,    15,    16,    30,    31,
      43,    78,    33,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    54,    32,    50,    82,    72,    73,    59,    10,    32,
      83,    32,    84,    13,    58,     2,     3,     4,     9,    60,
      54,    12,    74,    75,    18,     9,    19,    20,    80,    81,
      32,    17,     1,     2,     3,     4,    87,    17,    21,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    45,    50,    46,    47,    57,    51,    48,    52,    55,
     106,   107,   108,     2,     3,     4,    34,    35,    71,    72,
      73,   110,   111,    56,    85,   102,    37,    73,   113,    61,
     117,    32,    32,    38,    39,    40,    41,    11,    22,    49,
     116,    42,    62,    63,    64,    65,   105,    66,    67,    68,
      69,    70,    71,    72,    73,    70,    71,    72,    73,    62,
      63,    64,    65,   115,    66,    67,    68,    69,    70,    71,
      72,    73,     0,   112,     0,     0,    62,    63,    64,    65,
     118,    66,    67,    68,    69,    70,    71,    72,    73,     0,
       0,     0,     0,    62,    63,    64,    65,     0,    66,    67,
      68,    69,    70,    71,    72,    73,    34,    35,     0,     0,
      34,    35,     0,     0,    36,     0,    37,     0,     0,     0,
      37,    77,     0,    38,    39,    40,    41,    38,    39,    40,
      41,    42,    34,    35,     0,    42,    68,    69,    70,    71,
      72,    73,    37,     0,     0,     0,   103,     0,     0,    38,
      39,    40,    41,     0,     0,     0,     0,    42,    62,    63,
      64,    65,    86,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    62,    63,    64,    65,   100,    66,    67,    68,
      69,    70,    71,    72,    73,     0,    62,    63,    64,    65,
     101,    66,    67,    68,    69,    70,    71,    72,    73,     0,
      62,    63,    64,    65,     0,    66,    67,    68,    69,    70,
      71,    72,    73,     2,     3,     4,     0,     0,    23,    24,
       0,    25,    26,    27,     0,     0,     0,     0,    28,    53,
       2,     3,     4,    29,     0,    23,    24,     0,    25,    26,
      27,     0,     0,     0,     0,    28,    76,     2,     3,     4,
      29,     0,    23,    24,     0,    25,    26,    27,     0,     0,
       0,     0,    28,   104,     0,     0,     0,    29,     0,    62,
      63,    64,    65,     0,    66,    67,    68,    69,    70,    71,
      72,    73,   109,    69,    70,    71,    72,    73,    62,    63,
      64,    65,     0,    66,    67,    68,    69,    70,    71,    72,
      73,   114,     0,     0,     0,     0,     0,    62,    63,    64,
      65,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      62,    63,    64,    65,     0,    66,    67,    68,    69,    70,
      71,    72,    73,    63,    64,    65,     0,    66,    67,    68,
      69,    70,    71,    72,    73,    65,     0,    66,    67,    68,
      69,    70,    71,    72,    73,    66,    67,    68,    69,    70,
      71,    72,    73,    67,    68,    69,    70,    71,    72,    73
};

static const yytype_int8 yycheck[] =
{
      23,    30,    21,    17,    15,    39,    40,    21,     0,    28,
      21,    30,    23,    17,    37,     4,     5,     6,     0,    42,
      49,    24,    45,    46,    18,     7,    16,    24,    51,    52,
      49,    13,     3,     4,     5,     6,    59,    19,    19,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    17,    17,    17,    15,    37,    21,    15,    23,    15,
      83,    84,    85,     4,     5,     6,     7,     8,    38,    39,
      40,   100,   101,    24,    18,    18,    17,    40,    23,    15,
      15,   100,   101,    24,    25,    26,    27,     7,    19,    28,
     113,    32,    28,    29,    30,    31,    15,    33,    34,    35,
      36,    37,    38,    39,    40,    37,    38,    39,    40,    28,
      29,    30,    31,    15,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,   103,    -1,    -1,    28,    29,    30,    31,
      15,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,     7,     8,    -1,    -1,
       7,     8,    -1,    -1,    15,    -1,    17,    -1,    -1,    -1,
      17,    18,    -1,    24,    25,    26,    27,    24,    25,    26,
      27,    32,     7,     8,    -1,    32,    35,    36,    37,    38,
      39,    40,    17,    -1,    -1,    -1,    16,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    32,    28,    29,
      30,    31,    18,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    28,    29,    30,    31,    18,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    28,    29,    30,    31,
      18,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,     4,     5,     6,    -1,    -1,     9,    10,
      -1,    12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,
       4,     5,     6,    24,    -1,     9,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    20,     4,     5,     6,
      24,    -1,     9,    10,    -1,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    22,    -1,    -1,    -1,    24,    -1,    28,
      29,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    22,    36,    37,    38,    39,    40,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    29,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    33,    34,    35,    36,    37,
      38,    39,    40,    34,    35,    36,    37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    42,    43,    44,    45,    53,
       0,    43,    24,    17,    46,    47,    48,    53,    18,    16,
      24,    19,    47,     9,    10,    12,    13,    14,    19,    24,
      49,    50,    51,    53,     7,     8,    15,    17,    24,    25,
      26,    27,    32,    51,    54,    17,    17,    15,    15,    49,
      17,    21,    23,    20,    50,    15,    24,    53,    54,    21,
      54,    15,    28,    29,    30,    31,    33,    34,    35,    36,
      37,    38,    39,    40,    54,    54,    20,    18,    52,    54,
      54,    54,    15,    21,    23,    18,    18,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      18,    18,    18,    16,    22,    15,    54,    54,    54,    22,
      50,    50,    52,    23,    22,    15,    54,    15,    15
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     8,     1,     1,     0,     1,
       1,     3,     2,     1,     2,     3,     3,     5,     4,     7,
       6,     2,     2,     3,     5,     7,     5,     2,     2,     4,
       3,     1,     3,     1,     1,     1,     3,     4,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Funcs  */
#line 70 "parser.y"
                              { program = yyvsp[0]; }
#line 1260 "parser.tab.c"
    break;

  case 3: /* Funcs: FuncDecl Funcs  */
#line 72 "parser.y"
                              {yyval = yyvsp[0]; yyval->push_front(yyvsp[-1]);}
#line 1266 "parser.tab.c"
    break;

  case 4: /* Funcs: %empty  */
#line 73 "parser.y"
                              {yyval = std::shared_ptr(new ast::Funcs());}
#line 1272 "parser.tab.c"
    break;

  case 5: /* FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE  */
#line 75 "parser.y"
                                                                    {yyval = std::shared_ptr(new FuncDecl(yyvsp[-6], yyvsp[-7], yyvsp[-4], yyvsp[-1]))}
#line 1278 "parser.tab.c"
    break;

  case 6: /* RetType: Type  */
#line 77 "parser.y"
                              {yyval = yyvsp[0]}
#line 1284 "parser.tab.c"
    break;

  case 7: /* RetType: VOID  */
#line 78 "parser.y"
                              {yyval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::VOID));}
#line 1290 "parser.tab.c"
    break;

  case 8: /* Formals: %empty  */
#line 79 "parser.y"
                              {yyval = std::shared_ptr(new ast::Formals())}
#line 1296 "parser.tab.c"
    break;

  case 9: /* Formals: FormalsList  */
#line 80 "parser.y"
                              { }
#line 1302 "parser.tab.c"
    break;

  case 10: /* FormalsList: FormalDecl  */
#line 82 "parser.y"
                              {yyval = std::shared_ptr(new ast::Formals(yyvsp[0]))}
#line 1308 "parser.tab.c"
    break;

  case 11: /* FormalsList: FormalDecl COMMA FormalsList  */
#line 83 "parser.y"
                                          {yyval = yyvsp[0];
                                           yyval->push_front(yyvsp[-2]);}
#line 1315 "parser.tab.c"
    break;

  case 12: /* FormalDecl: Type ID  */
#line 86 "parser.y"
                              {yyval = std::shared_ptr(new ast::Formal(yyvsp[0],yyvsp[-1]))}
#line 1321 "parser.tab.c"
    break;

  case 13: /* Statements: Statement  */
#line 88 "parser.y"
                                 {yyval = std::shared_ptr(new ast::Statements(yyvsp[0]));}
#line 1327 "parser.tab.c"
    break;

  case 14: /* Statements: Statements Statement  */
#line 89 "parser.y"
                                 {yyval = yyvsp[-1];
                                  yyval->push_back(yyvsp[0]);}
#line 1334 "parser.tab.c"
    break;

  case 15: /* Statement: LBRACE Statements RBRACE  */
#line 92 "parser.y"
                                                          {yyval = yyvsp[-2];}
#line 1340 "parser.tab.c"
    break;

  case 16: /* Statement: Type ID SC  */
#line 93 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::VarDecl(yyvsp[-1], yyvsp[-2]));}
#line 1346 "parser.tab.c"
    break;

  case 17: /* Statement: Type ID ASSIGN Exp SC  */
#line 94 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::VarDecl(yyvsp[-3], yyvsp[-4], yyvsp[-1]));}
#line 1352 "parser.tab.c"
    break;

  case 18: /* Statement: ID ASSIGN Exp SC  */
#line 95 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::Assign(yyvsp[-3], yyvsp[-1]));}
#line 1358 "parser.tab.c"
    break;

  case 19: /* Statement: ID LBRACK Exp RBRACK ASSIGN Exp SC  */
#line 96 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::ArrayAssign(yyvsp[-6], yyvsp[-1], yyvsp[-4]));}
#line 1364 "parser.tab.c"
    break;

  case 20: /* Statement: Type ID LBRACK Exp RBRACK SC  */
#line 97 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::ArrayType(yyvsp[-5]->type,yyvsp[-2]));}
#line 1370 "parser.tab.c"
    break;

  case 21: /* Statement: Call SC  */
#line 98 "parser.y"
                                                          {yyval = yyvsp[-1]}
#line 1376 "parser.tab.c"
    break;

  case 22: /* Statement: RETURN SC  */
#line 99 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::Return());}
#line 1382 "parser.tab.c"
    break;

  case 23: /* Statement: RETURN Exp SC  */
#line 100 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::Return(yyvsp[-1]));}
#line 1388 "parser.tab.c"
    break;

  case 24: /* Statement: IF LPAREN Exp RPAREN Statement  */
#line 101 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::If(yyvsp[-2], yyvsp[0]));}
#line 1394 "parser.tab.c"
    break;

  case 25: /* Statement: IF LPAREN Exp RPAREN Statement ELSE Statement  */
#line 102 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::If(yyvsp[-4], yyvsp[-2], yyvsp[0]));}
#line 1400 "parser.tab.c"
    break;

  case 26: /* Statement: WHILE LPAREN Exp RPAREN Statement  */
#line 103 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::While(yyvsp[-2], yyvsp[0]));}
#line 1406 "parser.tab.c"
    break;

  case 27: /* Statement: BREAK SC  */
#line 104 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::Break());}
#line 1412 "parser.tab.c"
    break;

  case 28: /* Statement: CONTINUE SC  */
#line 105 "parser.y"
                                                          {yyval = std::shared_ptr(new ast::Continue());}
#line 1418 "parser.tab.c"
    break;

  case 29: /* Call: ID LPAREN ExpList RPAREN  */
#line 107 "parser.y"
                                  {yyval = std::shared_ptr(new ast::Call(yyvsp[-3], yyvsp[-1]));}
#line 1424 "parser.tab.c"
    break;

  case 30: /* Call: ID LPAREN RPAREN  */
#line 108 "parser.y"
                                  {yyval = std_shared_ptr(new ast::Call(yyvsp[-2]))}
#line 1430 "parser.tab.c"
    break;

  case 31: /* ExpList: Exp  */
#line 110 "parser.y"
                                  {yyval = std::shared_ptr(new ast::ExpList(yyvsp[0]));}
#line 1436 "parser.tab.c"
    break;

  case 32: /* ExpList: Exp COMMA ExpList  */
#line 111 "parser.y"
                                  {yyval = yyvsp[0];
                                   yyval->push_front(yyvsp[-2]);}
#line 1443 "parser.tab.c"
    break;

  case 33: /* Type: INT  */
#line 114 "parser.y"
                                  {yyval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::INT));}
#line 1449 "parser.tab.c"
    break;

  case 34: /* Type: BYTE  */
#line 115 "parser.y"
                                  {yyval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BYTE));}
#line 1455 "parser.tab.c"
    break;

  case 35: /* Type: BOOL  */
#line 116 "parser.y"
                                  {yyval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BOOL));}
#line 1461 "parser.tab.c"
    break;

  case 36: /* Exp: LPAREN Exp RPAREN  */
#line 118 "parser.y"
                                                {yyval = yyvsp[-2];}
#line 1467 "parser.tab.c"
    break;

  case 37: /* Exp: ID LBRACK Exp RBRACK  */
#line 119 "parser.y"
                                                {yyval = std::shared_ptr(new ast::ArrayDereference(yyvsp[-3], yyvsp[-1]));}
#line 1473 "parser.tab.c"
    break;

  case 38: /* Exp: Exp BINOP_ADD Exp  */
#line 120 "parser.y"
                                                {yyval = std::shared_ptr(new ast::BinOp(yyvsp[-2], yyvsp[0], ast::BinOpType::ADD));}
#line 1479 "parser.tab.c"
    break;

  case 39: /* Exp: Exp BINOP_SUB Exp  */
#line 121 "parser.y"
                                                {yyval = std::shared_ptr(new ast::BinOp(yyvsp[-2], yyvsp[0], ast::BinOpType::SUB));}
#line 1485 "parser.tab.c"
    break;

  case 40: /* Exp: Exp BINOP_MUL Exp  */
#line 122 "parser.y"
                                                {yyval = std::shared_ptr(new ast::BinOp(yyvsp[-2], yyvsp[0], ast::BinOpType::MUL));}
#line 1491 "parser.tab.c"
    break;

  case 41: /* Exp: Exp BINOP_DIV Exp  */
#line 123 "parser.y"
                                                {yyval = std::shared_ptr(new ast::BinOp(yyvsp[-2], yyvsp[0], ast::BinOpType::DIV));}
#line 1497 "parser.tab.c"
    break;

  case 42: /* Exp: ID  */
#line 124 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1503 "parser.tab.c"
    break;

  case 43: /* Exp: Call  */
#line 125 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1509 "parser.tab.c"
    break;

  case 44: /* Exp: NUM  */
#line 126 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1515 "parser.tab.c"
    break;

  case 45: /* Exp: NUM_B  */
#line 127 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1521 "parser.tab.c"
    break;

  case 46: /* Exp: STRING  */
#line 128 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1527 "parser.tab.c"
    break;

  case 47: /* Exp: TRUE  */
#line 129 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1533 "parser.tab.c"
    break;

  case 48: /* Exp: FALSE  */
#line 130 "parser.y"
                                                {yyval = yyvsp[0];}
#line 1539 "parser.tab.c"
    break;

  case 49: /* Exp: NOT Exp  */
#line 131 "parser.y"
                                                {yyval = std::shared_ptr(new ast::Not(yyvsp[0]));}
#line 1545 "parser.tab.c"
    break;

  case 50: /* Exp: Exp AND Exp  */
#line 132 "parser.y"
                                                {yyval = std::shared_ptr(new ast::And(yyvsp[-2], yyvsp[0]));}
#line 1551 "parser.tab.c"
    break;

  case 51: /* Exp: Exp OR Exp  */
#line 133 "parser.y"
                                                {yyval = std::shared_ptr(new ast::(yyvsp[-2], yyvsp[0]));}
#line 1557 "parser.tab.c"
    break;

  case 52: /* Exp: Exp RelOp_EQ Exp  */
#line 134 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::EQ));}
#line 1563 "parser.tab.c"
    break;

  case 53: /* Exp: Exp RelOp_NE Exp  */
#line 135 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::NE));}
#line 1569 "parser.tab.c"
    break;

  case 54: /* Exp: Exp RelOp_LT Exp  */
#line 136 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::LT));}
#line 1575 "parser.tab.c"
    break;

  case 55: /* Exp: Exp RelOp_GT Exp  */
#line 137 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::GT));}
#line 1581 "parser.tab.c"
    break;

  case 56: /* Exp: Exp RelOp_LE Exp  */
#line 138 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::LE));}
#line 1587 "parser.tab.c"
    break;

  case 57: /* Exp: Exp RelOp_GE Exp  */
#line 139 "parser.y"
                                                {yyval = std::shared_ptr(new ast::RelOp(yyvsp[-2], yyvsp[0], ast::RelOpType::GE));}
#line 1593 "parser.tab.c"
    break;

  case 58: /* Exp: LPAREN Type RPAREN Exp  */
#line 140 "parser.y"
                                                {yyval = std::shared_ptr(new ast::Cast(yyvsp[0], std::dynamic_pointer_cast<ast::PrimitiveType>(yyvsp[-2])));}
#line 1599 "parser.tab.c"
    break;


#line 1603 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 143 "parser.y"


// TODO: Place any additional code here
