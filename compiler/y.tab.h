/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 190 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
