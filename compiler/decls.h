#ifndef __DECLS_H__
#define __DECLS_H__

#include "../include/DBG.h"
#include "../include/MEM.h"

#define LINE_BUF_SIZE (1024)
#define smaller(a, b) ((a) < (b) ? (a) : (b))
#define larger(a, b) ((a) > (b) ? (a) : (b))

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
    EXPRESSION_STATEMENT, 
    FOR_STATEMENT,
    FOREACH_STATEMENT,
    WHILE_STATEMENT,
    IF_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,
    TRY_STATEMENT,
    THROW_STATEMENT,
    DECLARATION_STATEMENT
} StatementKind;

typedef enum {
    FUNCTION_REDEFINITION,
} CompileError;

typedef enum {
    UNDETERMIEND,
    BOOLEAN_TYPE,
    INT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE
} ValueType;

typedef enum {
    ARITH_ADDITIVE_EXPRESSION,
    ARITH_SUBSTRACTION_EXPRESSION,
    ARITH_MULTIPLICATION_EXPRESSION,
    ARITH_DIVISION_EXPRESSION,
    ARITH_MODULO_EXPRESSION,
    RELATION_GT_EXPRESSION,
    RELATION_LT_EXPRESSION,
    RELATION_GE_EXPRESSION,
    RELATION_LE_EXPRESSION,
    RELATION_EQ_EXPRESSION,
    RELATION_NE_EXPRESSION,
    LOGICAL_AND_EXPRESSION,
    LOGICAL_OR_EXPRESSION,
    LOGICAL_NOT_EXPRESSION,
    MINUS_EXPRESSION,
    FUNC_CALL_EXPRESSION,
    COMMA_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    NORMAL_ASSIGN_EXPRESSION,
    ADD_ASSIGN_EXPRESSION,
    SUB_ASSIGN_EXPRESSION,
    MUL_ASSIGN_EXPRESSION,
    DIV_ASSIGN_EXPRESSION,
    MOD_ASSIGN_EXPRESSION,
    POST_INCREMENT_EXPRESSION,
    POST_DECREMENT_EXPRESSION,
    BOOLEAN_LITERAL_EXPRESSION,
    INT_LITERAL_EXPRESSION,
    DOUBLE_LITERAL_EXPRESSION,
    STRING_LITERAL_EXPRESSION,
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
typedef struct TryStatement TryStatement;
typedef struct ThrowStatement ThrowStatement;
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
typedef struct ForeachStatement ForeachStatement;
typedef struct DeclarationStatementList DeclarationStatementList;
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

struct Expression {
    ValueType        type;
    ExpressionKind   kind;
    int              linenum;
    union {
        Boolean      boolean_v;
        int          int_v;
        double       double_v;
        char         *string_v;
        struct {
            Expression   *callee;
            ArgumentList *arg_list;
        }  function_call_expr;
        struct {
            Expression   *left;
            Expression   *right;
        }  binary_expr;
        Expression  *unary_operand;
        Identifier  *ident;
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
    StatementList           *stat_list;
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
    Identifier *label;
    Expression *init_expr;
    Expression *cond_expr;
    Expression *post_expr;
    Block      *block;
};

struct ForeachStatement {
    Identifier  *label;
    Identifier  *ident;
    Expression  *expr;
    Block       *block;
};

struct WhileStatement {
    Identifier *label;
    Expression *cond_expr;
    Block      *block;
};

struct ReturnStatement {
    Expression *ret_expr;
};

struct BreakStatement {
    Identifier *label;
};

struct ContinueStatement {
    Identifier *label;
};

struct Identifier {
    char *name;
};

struct TryStatement {
    Block       *try_block;
    Identifier  *catch_obj;
    Block       *catch_block;
    Block       *final_block;
};

struct ThrowStatement {
    Expression *exception;
};

struct DeclarationStatement {
    TypeSpecifier   *type;
    Identifier      *ident;
    Expression      *initializer;
};

struct Statement {
    StatementKind kind;
    union {
        IfStatement             if_stat;
        ForStatement            for_stat;
        ForeachStatement        foreach_stat;
        WhileStatement          while_stat;
        ReturnStatement         return_stat;
        BreakStatement          break_stat;
        ContinueStatement       continue_stat;
        TryStatement            try_stat;
        ThrowStatement          throw_stat;
        DeclarationStatement    declaration_stat;
        Expression              *expr; /* Semantic: An expression statement points to a expression. */
    } u;
    Statement *next;
};

struct StatementList {
    Statement *phead;
};

struct FunctionList {
    FunctionDefinition *phead;
};

struct DeclarationStatementList {
    DeclarationStatement *phead;
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
    FunctionList                *function_list;
    int                         function_count;
    StatementList               *statement_list;
    DeclarationStatementList    *declaration_stat_list;
    int                         current_line_number;
    Block                       *current_block;
    MEM_Storage                 compile_storage;
};

struct Executable {
    char dummy;
};

/* function_begin */

/* create.c */
Identifier* create_identifier(char *name);
Expression* alloc_expression(ExpressionKind kind);
FunctionDefinition* 
create_function_definition (
    TypeSpecifier *ts, Identifier *ident, ParameterList *param_list, Block *block);
void define_function(TypeSpecifier *ts, Identifier *ident, ParameterList *para_list, Block *block);
ParameterList* create_parameter_list(TypeSpecifier *ts, Identifier *ident);
ParameterList* create_and_chain_parameter(ParameterList *param_list, TypeSpecifier *ts, Identifier *ident);
ArgumentList* create_argument_list(Expression *expr);
ArgumentList* chain_argument_list(ArgumentList *arg_list, Expression *expr);
Expression* create_comma_expression(Expression *left, Expression *right);
StatementList* create_statement_list(Statement *stat);
StatementList* chain_statement_list(StatementList* stat_list, Statement *stat);
Expression* create_binary_expression(ExpressionKind kind, Expression *left, Expression *right);
Expression* create_minus_expression(Expression *right);
Expression* create_logical_not_expression(Expression *right);
Expression* create_function_call_expression(Expression *callee, ArgumentList *arg_list);
Expression* create_incdec_expression(ExpressionKind kind, Expression *expr);
Expression* create_identifier_expression(Identifier *ident);
Expression* create_boolean_expression(Boolean v);
Statement* create_expression_statement(Expression *expr);
Statement* create_if_statement(Expression *cond, Block *then_block, Elif *elif_list, Block *else_block);
Elif* create_elif(Expression *cond, Block *block);
Elif* chain_elif_list(Elif *elif_list, Elif *elif);
Statement* create_while_statement(Identifier *label, Expression *cond, Block *block);
Statement* create_for_statement(Identifier *label, 
    Expression *init, Expression *cond, Expression *post, Block *block);
Statement* create_foreach_statement(Identifier *label, 
    Identifier *ident, Expression *expr, Block *block);
Statement* create_return_statement(Expression *expr);
Statement* create_break_statement(Identifier *label);
Statement* create_continue_statement(Identifier *label);
Statement* create_try_statement(
    Block *try_block, Identifier *catch_obj, Block *catch_block, Block *final_block);
Statement* create_throw_statement(Expression *except);
Statement* create_declaration_statement(TypeSpecifier *ts, Identifier *ident, Expression *initializer);
Block* open_block();
Block* close_block(Block *block, StatementList *stat_list);
TypeSpecifier* create_typespecifer(ValueType typ);

/* common.c */
void set_current_compiler(Compiler *comp);
Compiler* get_current_compiler();
void* Malloc(size_t size);
void error_message(int linenum, CompileError err);

/* compiler.c */
Compiler* create_compiler();
Executable* compile(Compiler *compiler, FILE *fp);
Executable* walk_ast_for_semantic_analysis(Compiler *comp);
Executable* walk_ast_for_gen_code(Compiler *comp);

/* string.c */
void open_string_literal();
void add_string_literal(int letter);
char* close_string_literal();
void reset_string_literal();

/* function_end */

#endif
