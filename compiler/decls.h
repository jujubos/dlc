#ifndef __DECLS_H__
#define __DECLS_H__

#include "../include/DBG.h"
#include "../include/MEM.h"

/* enum_begin */
typedef enum {
    TRUE,
    FALSE
} Boolean;

typedef enum {
  UNDEFINED_BLOCK = 1,
  FUNCTION_BLOCK,
  WHILE_STATEMENT_BLOCK,
  FOR_STATEMENT_BLOCK
} BlockType;

typedef enum {
    ForStatement,
    WhileStatement,
    IfStatement,
    ReturnStatement,
    BreakStatement,
    ContinueStatement,
} StatementKind;

typedef enum {
    FUNCTION_REDEFINITION,
} CompileError;

typedef enum {
    BOOLEAN,
    INT,
    DOUBLE,
    STRING
} ValueType;

typedef enum {
    ARITH_ADDITIVE,
    ARITH_SUBSTRACTION,
    ARITH_MULTIPLICATION,
    ARITH_DIVISION,
    ARITH_MODULO,
    RELATION_GT,
    RELATION_LT,
    RELATION_GE,
    RELATION_LE,
    RELATION_EQ,
    RELATION_NE,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_NOT,
    MINUS,
    FUNC_CALL,
    COMMA,
    IDENTIFIER_EXPRESSION,
    NORMAL_ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,
    POST_INCREMENT,
    POST_DECREMENT,
} ExpressionKind;
/* enum_end */

/* typedef_begin */
typedef struct Expression Expression;
typedef struct CommaExpression CommaExpression;
typedef struct BinaryExpression BinaryExpression;
typedef struct IdentifierExpression IdentifierExpression;
typedef struct FunctionCallExpression FunctionCallExpression;
typedef struct Parameter Parameter;
typedef struct ParameterList ParameterList;
typedef struct Block Block;
typedef struct FunctionDefinition FunctionDefinition;
typedef struct WhileStatement WhileStatement;
typedef struct ForStatement ForStatement;
typedef struct IfStatement IfStatement;
typedef struct ReturnStatement ReturnStatement;
typedef struct BreakStatement BreakStatement;
typedef struct ContinueStatement ContinueStatement;
typedef struct DeclarationStatement DeclarationStatement;
typedef struct Statement Statement;
typedef struct Identifier Identifier;
typedef struct TypeSpecifier TypeSpecifier;
typedef struct Elif Elif;
typedef struct Argument Argument;
typedef struct ArgumentList ArgumentList;
typedef struct Compiler Compiler;
typedef struct Executable Executable;
typedef struct StatementList StatementList;
typedef struct FunctionList FunctionList;
/* typedef_end */
struct TypeSpecifier {
    ValueType basic_type;
};

struct CommaExpression {
    Expression *left;
    Expression *right;
};

struct BinaryExpression {
    Expression *left;
    Expression *right;
};

struct IdentifierExpression {
    Identifier *ident;
};

struct Argument {
    Expression *expr; 
    Argument   *next;   
};

struct ArgumentList {
    Argument *phead;
};

struct FunctionCallExpression {
    Identifier      *ident;
    ArgumentList    *args;
};

struct Expression {
    ValueType        type;
    ExpressionKind   kind;
    int              linenum;
    union { 
        Boolean      boolean_expr;
        int          int_expr;
        double       double_expr;
        char         *string_expr;
        Expression   *left;
        Expression   *right;
        Expression   *minus_expr;
        Expression   *not_expr;
        Identifier   *ident; 
        ArgumentList *arg_list;
    };
};

struct Parameter {
  TypeSpecifier     *type;
  Identifier        *ident;
  Parameter         *next;
};

struct ParameterList {
    Parameter *phead;
};

struct Block {
    BlockType               type;
    StatementList           stat_list;
    Block                   *outer_block;
    DeclarationStatement    *declaration_list;
};

struct FunctionDefinition {
    TypeSpecifier         *type;
    Identifier            *ident;
    ParameterList         *param_list;
    Block                 *block;
    DeclarationStatement  *local_varaible;
    int                   local_variable_cnt;
    int                   index;
    FunctionDefinition    *next;
};

struct Elif {
    Expression  *cond;
    Block       *block;
    Elif        *next;
};

struct IfStatement {
    Expression  *cond;
    Block       *then_block;
    Elif        *elif_list;
    Block       *else_block;
};

struct ForStatement {
    Expression *init_expr;
    Expression *cond_expr;
    Expression *post_expr;
    Block      *block;
};

struct WhileStatement {
    Expression *cond_expr;
    Block      *block;
};

struct ReturnStatement {
    Expression *ret_expr;
};

struct BreakStatement {

};

struct ContinueStatement {

};

struct Identifier {
    char *name;
};

struct DeclarationStatement {
    TypeSpecifier   type;
    Identifier      *ident;
    Expression      *initializer;
};

struct Statement {
    StatementKind kind;
    union {
        IfStatement if_stat;
        ForStatement for_stat;
        WhileStatement while_stat;
        ReturnStatement return_stat;
        BreakStatement break_stat;
        ContinueStatement continue_stat;
        DeclarationStatement declaration_stat;
        Expression expression_stat;
    } u;
    Statement *next;
};

struct StatementList {
    Statement *phead;
};

struct FunctionList {
    FunctionDefinition *phead;
};

/* 
    A source code file is compiled as <defifition_list, statement_list>. 
    Now, definition_list is just consist of function_definition.
    statement_list include:
       - expression_statement
       - if_statement
       - while_statement
       - for_statement
       - foreach_statement
       - return_statement
       - break_statement
       - continue_statement
       - try_statement
       - throw_statement
       - declaration_statement
*/
struct Compiler {
    FunctionList            function_list;
    int                     function_count;
    StatementList           statement_list;
    DeclarationStatement    *declaration_list;
    int                     current_line_number;
    Block                   *current_block;
    MEM_Storage             compile_storage;
};

struct Executable {
    
};

/* function_begin */

/* create.c */
FunctionDefinition* 
create_function_definition (
    ValueType type, Identifier *ident, ParameterList *param_list, Block *block);
void define_function(ValueType type, Identifier *ident, ParameterList *para_list, Block *block);
ParameterList* create_parameter_list(ValueType type, Identifier *ident);
ParameterList* create_and_chain_parameter(ParameterList *param_list, ValueType type, Identifier *ident);
ArgumentList create_argument_list(Expression *expr);
ArgumentList chain_argument_list(ArgumentList arg_list, Expression *expr);
Expression* create_comma_expression(Expression *left, Expression *right);
StatementList create_statement_list(Statement *stat);
StatementList chain_statement_list(StatementList stat_list, Statement *stat);
Expression* create_binary_expression(ExpressionKind kind, Expression *left, Expression *right);
Expression* create_minus_expression(Expression *right);
Expression* create_function_call_expression(Identifier *ident, ArgumentList *arg_list);
Expression* create_incdec_expression(ExpressionKind kind, Expression *expr);
Expression* create_identifier_expression(Identifier *ident);


/* common.c */
void set_current_compiler(Compiler *comp);
Compiler* get_current_compiler();

void* Malloc(size_t size);
TypeSpecifier* alloc_type_specifier(ValueType type);
void error_message(int linenum, CompileError err);

/* function_end */

#endif
