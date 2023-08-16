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
#line 1 "diksam.y"

#include <stdio.h>
#include "decls.h"
#define YYDEBUG 1

#line 77 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_LITERAL = 258,             /* INT_LITERAL  */
    DOUBLE_LITERAL = 259,          /* DOUBLE_LITERAL  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    REGEXP_LITERAL = 261,          /* REGEXP_LITERAL  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    ELSIF = 265,                   /* ELSIF  */
    WHILE = 266,                   /* WHILE  */
    FOR = 267,                     /* FOR  */
    FOREACH = 268,                 /* FOREACH  */
    RETURN_T = 269,                /* RETURN_T  */
    BREAK = 270,                   /* BREAK  */
    CONTINUE = 271,                /* CONTINUE  */
    LP = 272,                      /* LP  */
    RP = 273,                      /* RP  */
    LC = 274,                      /* LC  */
    RC = 275,                      /* RC  */
    SEMICOLON = 276,               /* SEMICOLON  */
    COLON = 277,                   /* COLON  */
    COMMA = 278,                   /* COMMA  */
    ASSIGN_T = 279,                /* ASSIGN_T  */
    LOGICAL_AND = 280,             /* LOGICAL_AND  */
    LOGICAL_OR = 281,              /* LOGICAL_OR  */
    EQ = 282,                      /* EQ  */
    NE = 283,                      /* NE  */
    GT = 284,                      /* GT  */
    GE = 285,                      /* GE  */
    LT = 286,                      /* LT  */
    LE = 287,                      /* LE  */
    ADD = 288,                     /* ADD  */
    SUB = 289,                     /* SUB  */
    MUL = 290,                     /* MUL  */
    DIV = 291,                     /* DIV  */
    MOD = 292,                     /* MOD  */
    TRUE_T = 293,                  /* TRUE_T  */
    FALSE_T = 294,                 /* FALSE_T  */
    EXCLAMATION = 295,             /* EXCLAMATION  */
    DOT = 296,                     /* DOT  */
    ADD_ASSIGN_T = 297,            /* ADD_ASSIGN_T  */
    SUB_ASSIGN_T = 298,            /* SUB_ASSIGN_T  */
    MUL_ASSIGN_T = 299,            /* MUL_ASSIGN_T  */
    DIV_ASSIGN_T = 300,            /* DIV_ASSIGN_T  */
    MOD_ASSIGN_T = 301,            /* MOD_ASSIGN_T  */
    INCREMENT = 302,               /* INCREMENT  */
    DECREMENT = 303,               /* DECREMENT  */
    TRY = 304,                     /* TRY  */
    CATCH = 305,                   /* CATCH  */
    FINALLY = 306,                 /* FINALLY  */
    THROW = 307,                   /* THROW  */
    BOOLEAN_T = 308,               /* BOOLEAN_T  */
    INT_T = 309,                   /* INT_T  */
    DOUBLE_T = 310,                /* DOUBLE_T  */
    STRING_T = 311                 /* STRING_T  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT_LITERAL 258
#define DOUBLE_LITERAL 259
#define STRING_LITERAL 260
#define REGEXP_LITERAL 261
#define IDENTIFIER 262
#define IF 263
#define ELSE 264
#define ELSIF 265
#define WHILE 266
#define FOR 267
#define FOREACH 268
#define RETURN_T 269
#define BREAK 270
#define CONTINUE 271
#define LP 272
#define RP 273
#define LC 274
#define RC 275
#define SEMICOLON 276
#define COLON 277
#define COMMA 278
#define ASSIGN_T 279
#define LOGICAL_AND 280
#define LOGICAL_OR 281
#define EQ 282
#define NE 283
#define GT 284
#define GE 285
#define LT 286
#define LE 287
#define ADD 288
#define SUB 289
#define MUL 290
#define DIV 291
#define MOD 292
#define TRUE_T 293
#define FALSE_T 294
#define EXCLAMATION 295
#define DOT 296
#define ADD_ASSIGN_T 297
#define SUB_ASSIGN_T 298
#define MUL_ASSIGN_T 299
#define DIV_ASSIGN_T 300
#define MOD_ASSIGN_T 301
#define INCREMENT 302
#define DECREMENT 303
#define TRY 304
#define CATCH 305
#define FINALLY 306
#define THROW 307
#define BOOLEAN_T 308
#define INT_T 309
#define DOUBLE_T 310
#define STRING_T 311

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 6 "diksam.y"

    Identifier          *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    Statement           *statement;
    Block               *block;
    Elif                *elif;
    TypeSpecifier       *type_specifier;

#line 253 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 4,             /* DOUBLE_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_REGEXP_LITERAL = 6,             /* REGEXP_LITERAL  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_ELSIF = 10,                     /* ELSIF  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_FOREACH = 13,                   /* FOREACH  */
  YYSYMBOL_RETURN_T = 14,                  /* RETURN_T  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_LP = 17,                        /* LP  */
  YYSYMBOL_RP = 18,                        /* RP  */
  YYSYMBOL_LC = 19,                        /* LC  */
  YYSYMBOL_RC = 20,                        /* RC  */
  YYSYMBOL_SEMICOLON = 21,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 22,                     /* COLON  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_ASSIGN_T = 24,                  /* ASSIGN_T  */
  YYSYMBOL_LOGICAL_AND = 25,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 26,                /* LOGICAL_OR  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_NE = 28,                        /* NE  */
  YYSYMBOL_GT = 29,                        /* GT  */
  YYSYMBOL_GE = 30,                        /* GE  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_ADD = 33,                       /* ADD  */
  YYSYMBOL_SUB = 34,                       /* SUB  */
  YYSYMBOL_MUL = 35,                       /* MUL  */
  YYSYMBOL_DIV = 36,                       /* DIV  */
  YYSYMBOL_MOD = 37,                       /* MOD  */
  YYSYMBOL_TRUE_T = 38,                    /* TRUE_T  */
  YYSYMBOL_FALSE_T = 39,                   /* FALSE_T  */
  YYSYMBOL_EXCLAMATION = 40,               /* EXCLAMATION  */
  YYSYMBOL_DOT = 41,                       /* DOT  */
  YYSYMBOL_ADD_ASSIGN_T = 42,              /* ADD_ASSIGN_T  */
  YYSYMBOL_SUB_ASSIGN_T = 43,              /* SUB_ASSIGN_T  */
  YYSYMBOL_MUL_ASSIGN_T = 44,              /* MUL_ASSIGN_T  */
  YYSYMBOL_DIV_ASSIGN_T = 45,              /* DIV_ASSIGN_T  */
  YYSYMBOL_MOD_ASSIGN_T = 46,              /* MOD_ASSIGN_T  */
  YYSYMBOL_INCREMENT = 47,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 48,                 /* DECREMENT  */
  YYSYMBOL_TRY = 49,                       /* TRY  */
  YYSYMBOL_CATCH = 50,                     /* CATCH  */
  YYSYMBOL_FINALLY = 51,                   /* FINALLY  */
  YYSYMBOL_THROW = 52,                     /* THROW  */
  YYSYMBOL_BOOLEAN_T = 53,                 /* BOOLEAN_T  */
  YYSYMBOL_INT_T = 54,                     /* INT_T  */
  YYSYMBOL_DOUBLE_T = 55,                  /* DOUBLE_T  */
  YYSYMBOL_STRING_T = 56,                  /* STRING_T  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_translation_unit = 58,          /* translation_unit  */
  YYSYMBOL_definition_or_statement = 59,   /* definition_or_statement  */
  YYSYMBOL_type_specifier = 60,            /* type_specifier  */
  YYSYMBOL_function_definition = 61,       /* function_definition  */
  YYSYMBOL_parameter_list = 62,            /* parameter_list  */
  YYSYMBOL_argument_list = 63,             /* argument_list  */
  YYSYMBOL_statement_list = 64,            /* statement_list  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_assignment_expression = 66,     /* assignment_expression  */
  YYSYMBOL_logical_or_expression = 67,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 68,    /* logical_and_expression  */
  YYSYMBOL_equality_expression = 69,       /* equality_expression  */
  YYSYMBOL_relational_expression = 70,     /* relational_expression  */
  YYSYMBOL_additive_expression = 71,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 72, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 73,          /* unary_expression  */
  YYSYMBOL_postfix_expression = 74,        /* postfix_expression  */
  YYSYMBOL_primary_expression = 75,        /* primary_expression  */
  YYSYMBOL_statement = 76,                 /* statement  */
  YYSYMBOL_if_statement = 77,              /* if_statement  */
  YYSYMBOL_elif_list = 78,                 /* elif_list  */
  YYSYMBOL_elif = 79,                      /* elif  */
  YYSYMBOL_label_opt = 80,                 /* label_opt  */
  YYSYMBOL_while_statement = 81,           /* while_statement  */
  YYSYMBOL_for_statement = 82,             /* for_statement  */
  YYSYMBOL_foreach_statement = 83,         /* foreach_statement  */
  YYSYMBOL_expression_opt = 84,            /* expression_opt  */
  YYSYMBOL_return_statement = 85,          /* return_statement  */
  YYSYMBOL_identifier_opt = 86,            /* identifier_opt  */
  YYSYMBOL_break_statement = 87,           /* break_statement  */
  YYSYMBOL_continue_statement = 88,        /* continue_statement  */
  YYSYMBOL_try_statement = 89,             /* try_statement  */
  YYSYMBOL_throw_statement = 90,           /* throw_statement  */
  YYSYMBOL_declaration_statement = 91,     /* declaration_statement  */
  YYSYMBOL_block = 92,                     /* block  */
  YYSYMBOL_93_1 = 93                       /* @1  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   309

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   311


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    44,    44,    45,    48,    49,    55,    59,    63,    67,
      73,    77,    84,    88,    97,   101,   107,   111,   117,   119,
     123,   124,   130,   131,   135,   139,   143,   147,   151,   157,
     158,   164,   165,   171,   172,   176,   182,   183,   187,   191,
     195,   201,   202,   206,   212,   213,   217,   221,   227,   228,
     232,   238,   239,   243,   247,   251,   257,   261,   265,   266,
     267,   268,   269,   273,   279,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   295,   299,   303,   307,   313,
     314,   320,   327,   330,   336,   342,   349,   356,   359,   362,
     369,   372,   375,   381,   387,   391,   395,   400,   405,   409,
     416,   415,   423
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "DOUBLE_LITERAL", "STRING_LITERAL", "REGEXP_LITERAL", "IDENTIFIER", "IF",
  "ELSE", "ELSIF", "WHILE", "FOR", "FOREACH", "RETURN_T", "BREAK",
  "CONTINUE", "LP", "RP", "LC", "RC", "SEMICOLON", "COLON", "COMMA",
  "ASSIGN_T", "LOGICAL_AND", "LOGICAL_OR", "EQ", "NE", "GT", "GE", "LT",
  "LE", "ADD", "SUB", "MUL", "DIV", "MOD", "TRUE_T", "FALSE_T",
  "EXCLAMATION", "DOT", "ADD_ASSIGN_T", "SUB_ASSIGN_T", "MUL_ASSIGN_T",
  "DIV_ASSIGN_T", "MOD_ASSIGN_T", "INCREMENT", "DECREMENT", "TRY", "CATCH",
  "FINALLY", "THROW", "BOOLEAN_T", "INT_T", "DOUBLE_T", "STRING_T",
  "$accept", "translation_unit", "definition_or_statement",
  "type_specifier", "function_definition", "parameter_list",
  "argument_list", "statement_list", "expression", "assignment_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "statement", "if_statement", "elif_list", "elif",
  "label_opt", "while_statement", "for_statement", "foreach_statement",
  "expression_opt", "return_statement", "identifier_opt",
  "break_statement", "continue_statement", "try_statement",
  "throw_statement", "declaration_statement", "block", "@1", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     229,  -127,  -127,  -127,  -127,   -15,    -2,   269,     4,     4,
     269,   269,  -127,  -127,   269,    18,   269,  -127,  -127,  -127,
    -127,   121,  -127,    22,  -127,    56,  -127,    28,    33,   106,
      84,    -9,    95,  -127,    47,  -127,  -127,  -127,   128,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,   269,
    -127,    73,   122,  -127,   124,   131,     8,  -127,    -3,  -127,
     138,    96,    61,  -127,  -127,     6,  -127,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   253,   269,   269,   269,   269,   269,   269,  -127,  -127,
     145,   148,   149,    10,  -127,  -127,  -127,  -127,  -127,   229,
     151,    18,  -127,    -5,  -127,   269,  -127,    33,   106,    84,
      84,    -9,    -9,    -9,    -9,    95,    95,  -127,  -127,  -127,
    -127,    17,  -127,  -127,  -127,  -127,  -127,  -127,  -127,   269,
     269,   162,    18,   164,   175,  -127,   177,  -127,    66,   178,
      34,    76,  -127,   269,    38,   165,   166,   139,    15,  -127,
    -127,   169,  -127,  -127,  -127,   123,    14,  -127,  -127,    18,
     269,   269,    18,   176,   141,  -127,    18,  -127,  -127,   187,
    -127,   179,    42,  -127,   269,    18,  -127,   146,  -127,   269,
      18,    58,  -127,    18,   180,  -127,    18,  -127,    18,  -127,
    -127
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      82,    58,    59,    60,    61,    57,     0,    87,    90,    90,
       0,     0,    62,    63,     0,     0,     0,     6,     7,     8,
       9,    82,     2,     0,     4,     0,    20,    22,    29,    31,
      33,    36,    41,    44,    48,    51,     5,    65,     0,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    83,     0,
      57,    88,     0,    91,     0,     0,     0,    49,    48,    50,
     100,     0,     0,     1,     3,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,    89,    92,    93,    56,   102,    82,
       0,     0,    97,     0,    98,     0,    21,    30,    32,    34,
      35,    37,    38,    39,    40,    42,    43,    45,    46,    47,
      53,     0,    16,    23,    24,    25,    26,    27,    28,     0,
      87,     0,     0,     0,    82,    18,     0,    95,     0,     0,
       0,     0,    52,     0,     0,     0,     0,    75,     0,   101,
      19,     0,    13,    11,    14,     0,     0,    99,    17,     0,
      87,     0,     0,     0,    77,    79,     0,    12,    10,     0,
      84,     0,     0,    76,     0,     0,    80,    96,    15,    87,
       0,     0,    78,     0,     0,    86,     0,    94,     0,    81,
      85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,   181,   -93,  -127,  -127,  -127,  -127,    -7,   -65,
    -127,   133,   127,    86,    45,    87,    -6,    32,  -127,   -87,
    -127,  -127,    35,  -127,  -127,  -127,  -127,  -126,  -127,   194,
    -127,  -127,  -127,  -127,  -127,  -100,  -127
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    21,    22,    23,    24,   140,   121,   134,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   164,   165,    38,    39,    40,    41,    52,    42,    54,
      43,    44,    45,    46,    47,    61,    99
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,   137,   106,    56,   145,    57,   133,    48,    59,    62,
     139,    53,   135,   138,    81,    49,   122,   123,   124,   125,
     126,   127,   128,   103,    76,    77,    97,   104,   132,    65,
     105,    67,   147,    67,   171,   142,   104,    60,   153,   105,
     143,   133,    93,    58,    88,    89,    58,   150,    17,    18,
      19,    20,   155,   184,    68,   168,   159,   156,    69,   170,
     180,    67,   173,   169,    81,    67,   177,    17,    18,    19,
      20,    82,   117,   118,   119,   182,   186,    66,   158,    67,
     185,    67,   102,   187,    67,    60,   189,   152,   190,    83,
      84,    85,    86,    87,    88,    89,    67,   157,   141,    67,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    72,    73,    74,    75,   111,   112,   113,
     114,    63,   144,    51,     1,     2,     3,     4,     5,     6,
      78,    79,    80,    70,    71,     7,     8,     9,    10,    90,
      91,    92,    60,    94,   167,    95,   100,   101,   162,   163,
     175,   163,    96,    51,   172,    11,   109,   110,    98,    12,
      13,    14,   129,   115,   116,   130,   131,   181,   136,   146,
      15,   148,    51,    16,    17,    18,    19,    20,     1,     2,
       3,     4,     5,     6,   151,   154,   160,   166,   161,     7,
       8,     9,    10,   174,   178,   149,   108,   183,   188,   176,
     179,   107,    64,    55,     0,     0,     0,     0,     0,    11,
       0,     0,     0,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,    16,    17,    18,
      19,    20,     1,     2,     3,     4,     5,     6,     0,     0,
       0,     0,     0,     7,     8,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     3,     4,
      50,     0,     0,    11,     0,     0,     0,    12,    13,    14,
      10,   120,     1,     2,     3,     4,    50,     0,    15,     0,
       0,    16,    17,    18,    19,    20,    10,    11,     0,     0,
       0,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     0,     0,    12,    13,    14
};

static const yytype_int16 yycheck[] =
{
       7,   101,    67,    10,   130,    11,    99,    22,    14,    16,
     103,     7,    99,    18,    17,    17,    81,    82,    83,    84,
      85,    86,    87,    17,    33,    34,    18,    21,    18,     7,
      24,    23,   132,    23,   160,    18,    21,    19,   138,    24,
      23,   134,    49,    11,    47,    48,    14,   134,    53,    54,
      55,    56,    18,   179,    26,   155,    18,    23,    25,   159,
      18,    23,   162,   156,    17,    23,   166,    53,    54,    55,
      56,    24,    78,    79,    80,   175,    18,    21,   143,    23,
     180,    23,    21,   183,    23,    19,   186,    21,   188,    42,
      43,    44,    45,    46,    47,    48,    23,    21,   105,    23,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    29,    30,    31,    32,    72,    73,    74,
      75,     0,   129,   130,     3,     4,     5,     6,     7,     8,
      35,    36,    37,    27,    28,    14,    15,    16,    17,    11,
      12,    13,    19,    21,    21,    21,    50,    51,     9,    10,
       9,    10,    21,   160,   161,    34,    70,    71,    20,    38,
      39,    40,    17,    76,    77,    17,    17,   174,    17,     7,
      49,     7,   179,    52,    53,    54,    55,    56,     3,     4,
       5,     6,     7,     8,     7,     7,    21,    18,    22,    14,
      15,    16,    17,    17,     7,    20,    69,    51,    18,   164,
      21,    68,    21,     9,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    52,    53,    54,
      55,    56,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    34,    -1,    -1,    -1,    38,    39,    40,
      17,    18,     3,     4,     5,     6,     7,    -1,    49,    -1,
      -1,    52,    53,    54,    55,    56,    17,    34,    -1,    -1,
      -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    14,    15,    16,
      17,    34,    38,    39,    40,    49,    52,    53,    54,    55,
      56,    58,    59,    60,    61,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    80,    81,
      82,    83,    85,    87,    88,    89,    90,    91,    22,    17,
       7,    65,    84,     7,    86,    86,    65,    73,    74,    73,
      19,    92,    65,     0,    59,     7,    21,    23,    26,    25,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    17,    24,    42,    43,    44,    45,    46,    47,    48,
      11,    12,    13,    65,    21,    21,    21,    18,    20,    93,
      50,    51,    21,    17,    21,    24,    66,    68,    69,    70,
      70,    71,    71,    71,    71,    72,    72,    73,    73,    73,
      18,    63,    66,    66,    66,    66,    66,    66,    66,    17,
      17,    17,    18,    60,    64,    76,    17,    92,    18,    60,
      62,    65,    18,    23,    65,    84,     7,    92,     7,    20,
      76,     7,    21,    92,     7,    18,    23,    21,    66,    18,
      21,    22,     9,    10,    78,    79,    18,    21,    92,    60,
      92,    84,    65,    92,    17,     9,    79,    92,     7,    21,
      18,    65,    92,    51,    84,    92,    18,    92,    18,    92,
      92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    58,    59,    59,    60,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    68,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    71,    71,    71,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    78,
      78,    79,    80,    80,    81,    82,    83,    84,    84,    85,
      86,    86,    87,    88,    89,    89,    89,    90,    91,    91,
      93,    92,    92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       6,     5,     6,     5,     2,     4,     1,     3,     1,     2,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     1,     4,     3,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     7,     6,     8,     1,
       2,     5,     0,     2,     6,    10,     8,     0,     1,     3,
       0,     1,     3,     3,     9,     4,     7,     3,     3,     5,
       0,     4,     2
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
  case 5: /* definition_or_statement: statement  */
#line 50 "diksam.y"
        { 
            chain_top_level_statement((yyvsp[0].statement));
        }
#line 1490 "y.tab.c"
    break;

  case 6: /* type_specifier: BOOLEAN_T  */
#line 56 "diksam.y"
        {
            (yyval.type_specifier) = create_typespecifier(BOOLEAN_TYPE);
        }
#line 1498 "y.tab.c"
    break;

  case 7: /* type_specifier: INT_T  */
#line 60 "diksam.y"
        {
            (yyval.type_specifier) = create_typespecifier(INT_TYPE);
        }
#line 1506 "y.tab.c"
    break;

  case 8: /* type_specifier: DOUBLE_T  */
#line 64 "diksam.y"
        {
            (yyval.type_specifier) = create_typespecifier(DOUBLE_TYPE);
        }
#line 1514 "y.tab.c"
    break;

  case 9: /* type_specifier: STRING_T  */
#line 68 "diksam.y"
        {
            (yyval.type_specifier) = create_typespecifier(STRING_TYPE);
        }
#line 1522 "y.tab.c"
    break;

  case 10: /* function_definition: type_specifier IDENTIFIER LP parameter_list RP block  */
#line 74 "diksam.y"
        {
            define_function((yyvsp[-5].type_specifier), (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].block));
        }
#line 1530 "y.tab.c"
    break;

  case 11: /* function_definition: type_specifier IDENTIFIER LP RP block  */
#line 78 "diksam.y"
        {
            ParameterList *para_list = (ParameterList*)Malloc(sizeof(ParameterList));
            para_list->len = 0;
            para_list->phead = NULL;
            define_function((yyvsp[-4].type_specifier), (yyvsp[-3].identifier), para_list, (yyvsp[0].block));
        }
#line 1541 "y.tab.c"
    break;

  case 12: /* function_definition: type_specifier IDENTIFIER LP parameter_list RP SEMICOLON  */
#line 85 "diksam.y"
        {
            define_function((yyvsp[-5].type_specifier), (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), NULL);
        }
#line 1549 "y.tab.c"
    break;

  case 13: /* function_definition: type_specifier IDENTIFIER LP RP SEMICOLON  */
#line 89 "diksam.y"
        {
            ParameterList *para_list = (ParameterList*)Malloc(sizeof(ParameterList));
            para_list->len = 0;
            para_list->phead = NULL;
            define_function((yyvsp[-4].type_specifier), (yyvsp[-3].identifier), para_list, NULL);
        }
#line 1560 "y.tab.c"
    break;

  case 14: /* parameter_list: type_specifier IDENTIFIER  */
#line 98 "diksam.y"
        {
            (yyval.parameter_list) = create_parameter_list((yyvsp[-1].type_specifier), (yyvsp[0].identifier));
        }
#line 1568 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier IDENTIFIER  */
#line 102 "diksam.y"
        {
            (yyval.parameter_list) = create_and_chain_parameter((yyvsp[-3].parameter_list), (yyvsp[-1].type_specifier), (yyvsp[0].identifier));
        }
#line 1576 "y.tab.c"
    break;

  case 16: /* argument_list: assignment_expression  */
#line 108 "diksam.y"
        {
            (yyval.argument_list) = create_argument_list((yyvsp[0].expression));
        }
#line 1584 "y.tab.c"
    break;

  case 17: /* argument_list: argument_list COMMA assignment_expression  */
#line 112 "diksam.y"
        {
            (yyval.argument_list) = chain_argument_list((yyvsp[-2].argument_list), (yyvsp[0].expression));
        }
#line 1592 "y.tab.c"
    break;

  case 18: /* statement_list: statement  */
#line 118 "diksam.y"
        {   chain_block_statement((yyvsp[0].statement)); }
#line 1598 "y.tab.c"
    break;

  case 19: /* statement_list: statement_list statement  */
#line 120 "diksam.y"
        {   chain_block_statement((yyvsp[0].statement)); }
#line 1604 "y.tab.c"
    break;

  case 21: /* expression: expression COMMA assignment_expression  */
#line 125 "diksam.y"
        {
            (yyval.expression) = create_comma_expression((yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1612 "y.tab.c"
    break;

  case 23: /* assignment_expression: postfix_expression ASSIGN_T assignment_expression  */
#line 132 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(NORMAL_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1620 "y.tab.c"
    break;

  case 24: /* assignment_expression: postfix_expression ADD_ASSIGN_T assignment_expression  */
#line 136 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ADD_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1628 "y.tab.c"
    break;

  case 25: /* assignment_expression: postfix_expression SUB_ASSIGN_T assignment_expression  */
#line 140 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(SUB_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1636 "y.tab.c"
    break;

  case 26: /* assignment_expression: postfix_expression MUL_ASSIGN_T assignment_expression  */
#line 144 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(MUL_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1644 "y.tab.c"
    break;

  case 27: /* assignment_expression: postfix_expression DIV_ASSIGN_T assignment_expression  */
#line 148 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(DIV_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1652 "y.tab.c"
    break;

  case 28: /* assignment_expression: postfix_expression MOD_ASSIGN_T assignment_expression  */
#line 152 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(MOD_ASSIGN_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1660 "y.tab.c"
    break;

  case 30: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 159 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(LOGICAL_OR_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1668 "y.tab.c"
    break;

  case 32: /* logical_and_expression: logical_and_expression LOGICAL_AND equality_expression  */
#line 166 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(LOGICAL_AND_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1676 "y.tab.c"
    break;

  case 34: /* equality_expression: equality_expression EQ relational_expression  */
#line 173 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_EQ_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1684 "y.tab.c"
    break;

  case 35: /* equality_expression: equality_expression NE relational_expression  */
#line 177 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_NE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1692 "y.tab.c"
    break;

  case 37: /* relational_expression: relational_expression GT additive_expression  */
#line 184 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_GT_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1700 "y.tab.c"
    break;

  case 38: /* relational_expression: relational_expression GE additive_expression  */
#line 188 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_GE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1708 "y.tab.c"
    break;

  case 39: /* relational_expression: relational_expression LT additive_expression  */
#line 192 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_LT_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1716 "y.tab.c"
    break;

  case 40: /* relational_expression: relational_expression LE additive_expression  */
#line 196 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(RELATION_LE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1724 "y.tab.c"
    break;

  case 42: /* additive_expression: additive_expression ADD multiplicative_expression  */
#line 203 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ARITH_ADDITIVE_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1732 "y.tab.c"
    break;

  case 43: /* additive_expression: additive_expression SUB multiplicative_expression  */
#line 207 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ARITH_SUBSTRACTION_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1740 "y.tab.c"
    break;

  case 45: /* multiplicative_expression: multiplicative_expression MUL unary_expression  */
#line 214 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ARITH_MULTIPLICATION_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1748 "y.tab.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression DIV unary_expression  */
#line 218 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ARITH_DIVISION_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1756 "y.tab.c"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression MOD unary_expression  */
#line 222 "diksam.y"
        {
            (yyval.expression) = create_binary_expression(ARITH_MODULO_EXPRESSION, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1764 "y.tab.c"
    break;

  case 49: /* unary_expression: SUB unary_expression  */
#line 229 "diksam.y"
        {
            (yyval.expression) = create_minus_expression((yyvsp[0].expression));
        }
#line 1772 "y.tab.c"
    break;

  case 50: /* unary_expression: EXCLAMATION unary_expression  */
#line 233 "diksam.y"
        {
            (yyval.expression) = create_logical_not_expression((yyvsp[0].expression));
        }
#line 1780 "y.tab.c"
    break;

  case 52: /* postfix_expression: postfix_expression LP argument_list RP  */
#line 240 "diksam.y"
        {
            (yyval.expression) = create_function_call_expression((yyvsp[-3].expression), (yyvsp[-1].argument_list));
        }
#line 1788 "y.tab.c"
    break;

  case 53: /* postfix_expression: postfix_expression LP RP  */
#line 244 "diksam.y"
        {
            (yyval.expression) = create_function_call_expression((yyvsp[-2].expression), NULL);
        }
#line 1796 "y.tab.c"
    break;

  case 54: /* postfix_expression: postfix_expression INCREMENT  */
#line 248 "diksam.y"
        {
            (yyval.expression) = create_incdec_expression(POST_INCREMENT_EXPRESSION, (yyvsp[-1].expression));
        }
#line 1804 "y.tab.c"
    break;

  case 55: /* postfix_expression: postfix_expression DECREMENT  */
#line 252 "diksam.y"
        {
            (yyval.expression) = create_incdec_expression(POST_DECREMENT_EXPRESSION, (yyvsp[-1].expression));
        }
#line 1812 "y.tab.c"
    break;

  case 56: /* primary_expression: LP expression RP  */
#line 258 "diksam.y"
        {
            (yyval.expression) = (yyvsp[-1].expression);
        }
#line 1820 "y.tab.c"
    break;

  case 57: /* primary_expression: IDENTIFIER  */
#line 262 "diksam.y"
        {
            (yyval.expression) = create_identifier_expression((yyvsp[0].identifier));
        }
#line 1828 "y.tab.c"
    break;

  case 62: /* primary_expression: TRUE_T  */
#line 270 "diksam.y"
        {
            (yyval.expression) = create_boolean_expression(TRUE);
        }
#line 1836 "y.tab.c"
    break;

  case 63: /* primary_expression: FALSE_T  */
#line 274 "diksam.y"
        {
            (yyval.expression) = create_boolean_expression(FALSE);
        }
#line 1844 "y.tab.c"
    break;

  case 64: /* statement: expression SEMICOLON  */
#line 280 "diksam.y"
        {
          (yyval.statement) = create_expression_statement((yyvsp[-1].expression));
        }
#line 1852 "y.tab.c"
    break;

  case 75: /* if_statement: IF LP expression RP block  */
#line 296 "diksam.y"
        {
            (yyval.statement) = create_if_statement((yyvsp[-2].expression), (yyvsp[0].block), NULL, NULL);
        }
#line 1860 "y.tab.c"
    break;

  case 76: /* if_statement: IF LP expression RP block ELSE block  */
#line 300 "diksam.y"
        {
            (yyval.statement) = create_if_statement((yyvsp[-4].expression), (yyvsp[-2].block), NULL, (yyvsp[0].block));
        }
#line 1868 "y.tab.c"
    break;

  case 77: /* if_statement: IF LP expression RP block elif_list  */
#line 304 "diksam.y"
        {
            (yyval.statement) = create_if_statement((yyvsp[-3].expression), (yyvsp[-1].block), (yyvsp[0].elif), NULL);
        }
#line 1876 "y.tab.c"
    break;

  case 78: /* if_statement: IF LP expression RP block elif_list ELSE block  */
#line 308 "diksam.y"
        {
            (yyval.statement) = create_if_statement((yyvsp[-5].expression), (yyvsp[-3].block), (yyvsp[-2].elif), (yyvsp[0].block));
        }
#line 1884 "y.tab.c"
    break;

  case 80: /* elif_list: elif_list elif  */
#line 315 "diksam.y"
        {
            (yyval.elif) = chain_elif_list((yyvsp[-1].elif), (yyvsp[0].elif));
        }
#line 1892 "y.tab.c"
    break;

  case 81: /* elif: ELSIF LP expression RP block  */
#line 321 "diksam.y"
        {
            (yyval.elif) = create_elif((yyvsp[-2].expression), (yyvsp[0].block));
        }
#line 1900 "y.tab.c"
    break;

  case 82: /* label_opt: %empty  */
#line 327 "diksam.y"
        {
            (yyval.identifier) = NULL;
        }
#line 1908 "y.tab.c"
    break;

  case 83: /* label_opt: IDENTIFIER COLON  */
#line 331 "diksam.y"
        {
            (yyval.identifier) = (yyvsp[-1].identifier);
        }
#line 1916 "y.tab.c"
    break;

  case 84: /* while_statement: label_opt WHILE LP expression RP block  */
#line 337 "diksam.y"
        {
            (yyval.statement) = create_while_statement((yyvsp[-5].identifier), (yyvsp[-2].expression), (yyvsp[0].block));
        }
#line 1924 "y.tab.c"
    break;

  case 85: /* for_statement: label_opt FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP block  */
#line 344 "diksam.y"
        {
            (yyval.statement) = create_for_statement((yyvsp[-9].identifier), (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].block));
        }
#line 1932 "y.tab.c"
    break;

  case 86: /* foreach_statement: label_opt FOREACH LP IDENTIFIER COLON expression RP block  */
#line 350 "diksam.y"
        {
            (yyval.statement) = create_foreach_statement((yyvsp[-7].identifier), (yyvsp[-4].identifier), (yyvsp[-2].expression), (yyvsp[0].block));
        }
#line 1940 "y.tab.c"
    break;

  case 87: /* expression_opt: %empty  */
#line 356 "diksam.y"
        {
            (yyval.expression) = NULL;
        }
#line 1948 "y.tab.c"
    break;

  case 89: /* return_statement: RETURN_T expression_opt SEMICOLON  */
#line 363 "diksam.y"
        {
            (yyval.statement) = create_return_statement((yyvsp[-1].expression));
        }
#line 1956 "y.tab.c"
    break;

  case 90: /* identifier_opt: %empty  */
#line 369 "diksam.y"
        {
            (yyval.identifier) = NULL;
        }
#line 1964 "y.tab.c"
    break;

  case 92: /* break_statement: BREAK identifier_opt SEMICOLON  */
#line 376 "diksam.y"
        {
            (yyval.statement) = create_break_statement((yyvsp[-1].identifier));
        }
#line 1972 "y.tab.c"
    break;

  case 93: /* continue_statement: CONTINUE identifier_opt SEMICOLON  */
#line 382 "diksam.y"
        {
            (yyval.statement) = create_continue_statement((yyvsp[-1].identifier));
        }
#line 1980 "y.tab.c"
    break;

  case 94: /* try_statement: TRY block CATCH LP IDENTIFIER RP block FINALLY block  */
#line 388 "diksam.y"
        {
            (yyval.statement) = create_try_statement((yyvsp[-7].block), (yyvsp[-4].identifier), (yyvsp[-2].block), (yyvsp[0].block));
        }
#line 1988 "y.tab.c"
    break;

  case 95: /* try_statement: TRY block FINALLY block  */
#line 392 "diksam.y"
        {
            (yyval.statement) = create_try_statement((yyvsp[-2].block), NULL, NULL, (yyvsp[0].block));
        }
#line 1996 "y.tab.c"
    break;

  case 96: /* try_statement: TRY block CATCH LP IDENTIFIER RP block  */
#line 396 "diksam.y"
        {
            (yyval.statement) = create_try_statement((yyvsp[-5].block), (yyvsp[-2].identifier), (yyvsp[0].block), NULL);
        }
#line 2004 "y.tab.c"
    break;

  case 97: /* throw_statement: THROW expression SEMICOLON  */
#line 401 "diksam.y"
        {
            (yyval.statement) = create_throw_statement((yyvsp[-1].expression));
        }
#line 2012 "y.tab.c"
    break;

  case 98: /* declaration_statement: type_specifier IDENTIFIER SEMICOLON  */
#line 406 "diksam.y"
        {
            (yyval.statement) = create_declaration_statement((yyvsp[-2].type_specifier), (yyvsp[-1].identifier), NULL);
        }
#line 2020 "y.tab.c"
    break;

  case 99: /* declaration_statement: type_specifier IDENTIFIER ASSIGN_T expression SEMICOLON  */
#line 410 "diksam.y"
        {
            (yyval.statement) = create_declaration_statement((yyvsp[-4].type_specifier), (yyvsp[-3].identifier), (yyvsp[-1].expression));
        }
#line 2028 "y.tab.c"
    break;

  case 100: /* @1: %empty  */
#line 416 "diksam.y"
        {
            (yyval.block) = open_block();
        }
#line 2036 "y.tab.c"
    break;

  case 101: /* block: LC @1 statement_list RC  */
#line 420 "diksam.y"
        {
            (yyval.block) = close_block((yyvsp[-2].block));
        }
#line 2044 "y.tab.c"
    break;

  case 102: /* block: LC RC  */
#line 424 "diksam.y"
        {
            Block *empty_block = open_block();
            (yyval.block) = close_block(empty_block);
        }
#line 2053 "y.tab.c"
    break;


#line 2057 "y.tab.c"

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

#line 429 "diksam.y"

