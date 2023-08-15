%{
#include <stdio.h>
#include "decls.h"
#define YYDEBUG 1
%}
%union {
    Identifier          *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    Statement           *statement;
    Block               *block;
    Elif                *elif;
    TypeSpecifier       *type_specifier;
}
%token <expression>     INT_LITERAL
%token <expression>     DOUBLE_LITERAL
%token <expression>     STRING_LITERAL
%token <expression>     REGEXP_LITERAL
%token <identifier>     IDENTIFIER
%token IF ELSE ELSIF WHILE FOR FOREACH RETURN_T BREAK CONTINUE
        LP RP LC RC SEMICOLON COLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T EXCLAMATION DOT
        ADD_ASSIGN_T SUB_ASSIGN_T MUL_ASSIGN_T DIV_ASSIGN_T MOD_ASSIGN_T
        INCREMENT DECREMENT TRY CATCH FINALLY THROW
        BOOLEAN_T INT_T DOUBLE_T STRING_T
%type   <parameter_list> parameter_list
%type   <argument_list> argument_list
%type   <expression> expression expression_opt
        assignment_expression logical_and_expression logical_or_expression
        equality_expression relational_expression
        additive_expression multiplicative_expression
        unary_expression postfix_expression primary_expression
%type   <statement> statement
        if_statement while_statement for_statement foreach_statement
        return_statement break_statement continue_statement try_statement
        throw_statement declaration_statement
%type   <block> block
%type   <elif> elif elif_list
%type   <identifier> identifier_opt label_opt
%type   <type_specifier> type_specifier
%%
translation_unit
        : definition_or_statement
        | translation_unit definition_or_statement
        ;
definition_or_statement
        : function_definition
        | statement
        { 
            chain_top_level_statement($1);
        }
        ;
type_specifier
        : BOOLEAN_T
        {
            $$ = create_typespecifier(BOOLEAN_TYPE);
        }
        | INT_T
        {
            $$ = create_typespecifier(INT_TYPE);
        }
        | DOUBLE_T
        {
            $$ = create_typespecifier(DOUBLE_TYPE);
        }
        | STRING_T
        {
            $$ = create_typespecifier(STRING_TYPE);
        }
        ;
function_definition
        : type_specifier IDENTIFIER LP parameter_list RP block
        {
            define_function($1, $2, $4, $6);
        }
        | type_specifier IDENTIFIER LP RP block
        {
            ParameterList *para_list = (ParameterList*)Malloc(sizeof(ParameterList));
            para_list->len = 0;
            para_list->phead = NULL;
            define_function($1, $2, para_list, $5);
        }
        | type_specifier IDENTIFIER LP parameter_list RP SEMICOLON
        {
            define_function($1, $2, $4, NULL);
        }
        | type_specifier IDENTIFIER LP RP SEMICOLON
        {
            ParameterList *para_list = (ParameterList*)Malloc(sizeof(ParameterList));
            para_list->len = 0;
            para_list->phead = NULL;
            define_function($1, $2, para_list, NULL);
        }
        ;
parameter_list
        : type_specifier IDENTIFIER
        {
            $$ = create_parameter_list($1, $2);
        }
        | parameter_list COMMA type_specifier IDENTIFIER
        {
            $$ = create_and_chain_parameter($1, $3, $4);
        }
        ;
argument_list
        : assignment_expression
        {
            $$ = create_argument_list($1);
        }
        | argument_list COMMA assignment_expression
        {
            $$ = chain_argument_list($1, $3);
        }
        ;
statement_list
        : statement
        {   chain_block_statement($1); }
        | statement_list statement
        {   chain_block_statement($2); }
        ;
expression
        : assignment_expression
        | expression COMMA assignment_expression
        {
            $$ = create_comma_expression($1, $3);
        }
        ;
assignment_expression
        : logical_or_expression
        | postfix_expression ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(NORMAL_ASSIGN_EXPRESSION, $1, $3);
        }
        | postfix_expression ADD_ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(ADD_ASSIGN_EXPRESSION, $1, $3);
        }
        | postfix_expression SUB_ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(SUB_ASSIGN_EXPRESSION, $1, $3);
        }
        | postfix_expression MUL_ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(MUL_ASSIGN_EXPRESSION, $1, $3);
        }
        | postfix_expression DIV_ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(DIV_ASSIGN_EXPRESSION, $1, $3);
        }
        | postfix_expression MOD_ASSIGN_T assignment_expression
        {
            $$ = create_binary_expression(MOD_ASSIGN_EXPRESSION, $1, $3);
        }
        ;
logical_or_expression
        : logical_and_expression
        | logical_or_expression LOGICAL_OR logical_and_expression
        {
            $$ = create_binary_expression(LOGICAL_OR_EXPRESSION, $1, $3);
        }
        ;
logical_and_expression
        : equality_expression
        | logical_and_expression LOGICAL_AND equality_expression
        {
            $$ = create_binary_expression(LOGICAL_AND_EXPRESSION, $1, $3);
        }
        ;
equality_expression
        : relational_expression
        | equality_expression EQ relational_expression
        {
            $$ = create_binary_expression(RELATION_EQ_EXPRESSION, $1, $3);
        }
        | equality_expression NE relational_expression
        {
            $$ = create_binary_expression(RELATION_NE_EXPRESSION, $1, $3);
        }
        ;
relational_expression
        : additive_expression
        | relational_expression GT additive_expression
        {
            $$ = create_binary_expression(RELATION_GT_EXPRESSION, $1, $3);
        }
        | relational_expression GE additive_expression
        {
            $$ = create_binary_expression(RELATION_GE_EXPRESSION, $1, $3);
        }
        | relational_expression LT additive_expression
        {
            $$ = create_binary_expression(RELATION_LT_EXPRESSION, $1, $3);
        }
        | relational_expression LE additive_expression
        {
            $$ = create_binary_expression(RELATION_LE_EXPRESSION, $1, $3);
        }
        ;
additive_expression
        : multiplicative_expression
        | additive_expression ADD multiplicative_expression
        {
            $$ = create_binary_expression(ARITH_ADDITIVE_EXPRESSION, $1, $3);
        }
        | additive_expression SUB multiplicative_expression
        {
            $$ = create_binary_expression(ARITH_SUBSTRACTION_EXPRESSION, $1, $3);
        }
        ;
multiplicative_expression
        : unary_expression
        | multiplicative_expression MUL unary_expression
        {
            $$ = create_binary_expression(ARITH_MULTIPLICATION_EXPRESSION, $1, $3);
        }
        | multiplicative_expression DIV unary_expression
        {
            $$ = create_binary_expression(ARITH_DIVISION_EXPRESSION, $1, $3);
        }
        | multiplicative_expression MOD unary_expression
        {
            $$ = create_binary_expression(ARITH_MODULO_EXPRESSION, $1, $3);
        }
        ;
unary_expression
        : postfix_expression
        | SUB unary_expression
        {
            $$ = create_minus_expression($2);
        }
        | EXCLAMATION unary_expression
        {
            $$ = create_logical_not_expression($2);
        }
        ;
postfix_expression
        : primary_expression
        | postfix_expression LP argument_list RP
        {
            $$ = create_function_call_expression($1, $3);
        }
        | postfix_expression LP RP
        {
            $$ = create_function_call_expression($1, NULL);
        }
        | postfix_expression INCREMENT
        {
            $$ = create_incdec_expression(POST_INCREMENT_EXPRESSION, $1);
        }
        | postfix_expression DECREMENT
        {
            $$ = create_incdec_expression(POST_DECREMENT_EXPRESSION, $1);
        }
        ;
primary_expression
        : LP expression RP
        {
            $$ = $2;
        }
        | IDENTIFIER
        {
            $$ = create_identifier_expression($1);
        }
        | INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | REGEXP_LITERAL
        | TRUE_T
        {
            $$ = create_boolean_expression(TRUE);
        }
        | FALSE_T
        {
            $$ = create_boolean_expression(FALSE);
        }
        ;
statement
        : expression SEMICOLON
        {
          $$ = create_expression_statement($1);
        }
        | if_statement
        | while_statement
        | for_statement
        | foreach_statement
        | return_statement
        | break_statement
        | continue_statement
        | try_statement
        | throw_statement
        | declaration_statement
        ;
if_statement
        : IF LP expression RP block
        {
            $$ = create_if_statement($3, $5, NULL, NULL);
        }
        | IF LP expression RP block ELSE block
        {
            $$ = create_if_statement($3, $5, NULL, $7);
        }
        | IF LP expression RP block elif_list
        {
            $$ = create_if_statement($3, $5, $6, NULL);
        }
        | IF LP expression RP block elif_list ELSE block
        {
            $$ = create_if_statement($3, $5, $6, $8);
        }
        ;
elif_list
        : elif
        | elif_list elif
        {
            $$ = chain_elif_list($1, $2);
        }
        ;
elif
        : ELSIF LP expression RP block
        {
            $$ = create_elif($3, $5);
        }
        ;
label_opt
        : /* empty */
        {
            $$ = NULL;
        }
        | IDENTIFIER COLON
        {
            $$ = $1;
        }
        ;
while_statement
        : label_opt WHILE LP expression RP block
        {
            $$ = create_while_statement($1, $4, $6);
        }
        ;
for_statement
        : label_opt FOR LP expression_opt SEMICOLON expression_opt SEMICOLON
          expression_opt RP block
        {
            $$ = create_for_statement($1, $4, $6, $8, $10);
        }
        ;
foreach_statement
        : label_opt FOREACH LP IDENTIFIER COLON expression RP block
        {
            $$ = create_foreach_statement($1, $4, $6, $8);
        }
        ;
expression_opt
        : /* empty */
        {
            $$ = NULL;
        }
        | expression
        ;
return_statement
        : RETURN_T expression_opt SEMICOLON
        {
            $$ = create_return_statement($2);
        }
        ;
identifier_opt
        : /* empty */
        {
            $$ = NULL;
        }
        | IDENTIFIER
        ;
break_statement 
        : BREAK identifier_opt SEMICOLON
        {
            $$ = create_break_statement($2);
        }
        ;
continue_statement
        : CONTINUE identifier_opt SEMICOLON
        {
            $$ = create_continue_statement($2);
        }
        ;
try_statement
        : TRY block CATCH LP IDENTIFIER RP block FINALLY block
        {
            $$ = create_try_statement($2, $5, $7, $9);
        }
        | TRY block FINALLY block
        {
            $$ = create_try_statement($2, NULL, NULL, $4);
        }
        | TRY block CATCH LP IDENTIFIER RP block
        {
            $$ = create_try_statement($2, $5, $7, NULL);
        }
throw_statement
        : THROW expression SEMICOLON
        {
            $$ = create_throw_statement($2);
        }
declaration_statement
        : type_specifier IDENTIFIER SEMICOLON
        {
            $$ = create_declaration_statement($1, $2, NULL);
        }
        | type_specifier IDENTIFIER ASSIGN_T expression SEMICOLON
        {
            $$ = create_declaration_statement($1, $2, $4);
        }
        ;
block
        : LC
        {
            $<block>$ = open_block();
        }
          statement_list RC
        {
            $<block>$ = close_block($<block>2);
        }
        | LC RC
        {
            Block *empty_block = open_block();
            $<block>$ = close_block(empty_block);
        }
        ;
%%
