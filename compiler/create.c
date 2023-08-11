#include "decls.h"

FunctionDefinition* 
create_function_definition (
    ValueType type, Identifier *ident, ParameterList *param_list, Block *block) 
{
    Compiler *comp;
    FunctionDefinition *func_def;

    comp = get_current_compiler();
    func_def = (FunctionDefinition*)Malloc(sizeof(FunctionDefinition));
    func_def->type = alloc_type_specifer(type);
    func_def->ident = ident;
    func_def->param_list = param_list;
    func_def->block = block;
    func_def->local_varaible = NULL;
    func_def->local_variable_cnt = 0;
    func_def->index = comp->function_count ++;
    func_def->next = NULL;

    return func_def;
}

void define_function(ValueType type, Identifier *ident, ParameterList *para_list, Block *block) {
    Compiler *comp;
    FunctionDefinition *func_def, *pos;

    comp = get_current_compiler();
    /* Semantic analysis for "FUNCTION_REDEFINITION" */
    for(pos = comp->function_list.phead; pos; pos = pos->next) {
        if(strcmp(ident->name, pos->ident->name) == 0) {
            error_message(comp->current_line_number, FUNCTION_REDEFINITION);
            return;
        }
    }

    func_def = create_function_definition(type, ident, para_list, block);
    if(block) {
        block->type = FUNCTION_BLOCK;
    }
    if(!comp->function_list.phead) {
        comp->function_list.phead = func_def;
    } else {
        for(pos = comp->function_list.phead; pos->next; pos = pos->next) 
            ;
        pos->next = func_def;
    }
}

ParameterList* create_parameter_list(ValueType type, Identifier *ident) {
    ParameterList   *param_list;
    Parameter       *param;
    TypeSpecifier   *ts;

    ts = Malloc(sizeof(TypeSpecifier));
    ts->basic_type = type;

    param = Malloc(sizeof(Parameter));
    param->ident = ident;
    param->type = ts;
    param->next = NULL;
    
    param_list = Malloc(sizeof(ParameterList));
    param_list->phead = param;
    
    return param_list;    
}

ParameterList* create_and_chain_parameter(ParameterList *param_list, ValueType type, Identifier *ident) {
    Parameter *param, *pos;
    TypeSpecifier *ts;

    ts = Malloc(sizeof(TypeSpecifier));
    ts->basic_type = type;

    param = Malloc(sizeof(Parameter));
    param->type = ts;
    param->ident = ident;
    param->next = NULL;
    
    for(pos = param_list->phead; pos->next; pos=pos->next)
        ;
    pos->next = param;

    return param_list;
}

ArgumentList create_argument_list(Expression *expr) {
    ArgumentList arg_list;
    Argument *arg;
    
    arg = (Argument*)Malloc(sizeof(Argument));
    arg->expr = expr;

    arg_list.phead = arg;
    
    return arg_list;
}

ArgumentList chain_argument_list(ArgumentList arg_list, Expression *expr) {
    Argument *arg, *pos;

    arg = (Argument*)Malloc(sizeof(Argument));
    arg->expr = expr;
    arg->next = NULL;
    for(pos = arg_list.phead; pos->next; pos = pos->next) 
        ;
    pos->next = arg;
    
    return arg_list;
}

StatementList create_statement_list(Statement *stat) {
    StatementList stat_list;

    stat_list.phead = stat;

    return stat_list;
}

StatementList chain_statement_list(StatementList stat_list, Statement *stat) {
    Statement *pos;

    for(pos = stat_list.phead; pos->next; pos = pos->next) 
        ;
    pos->next = stat;

    return stat_list;
}

Expression* create_comma_expression(Expression *left, Expression *right) {
    Expression *expr;

    expr = Malloc(sizeof(Expression));
    expr->kind = COMMA;
    expr->type = NULL;
    /* Actually, we can set expr->type here, but the author of the book doesn't do this.
       I don't know why yet. And I decide to do the same as him.
     */
    expr->left = left;
    expr->right = right;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_binary_expression(ExpressionKind kind, Expression *left, Expression *right) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = kind;
    expr->left = left;
    expr->right = right;
    expr->type = NULL;
    expr->linenum = get_current_compiler()->current_line_number;
    
    return expr;
}

Expression* create_minus_expression(Expression *right) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = MINUS;
    expr->right = right;
    expr->type = NULL;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_logical_not_expression(Expression *right) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = LOGICAL_OR;
    expr->right = right;
    expr->type = NULL;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_function_call_expression(Identifier *ident, ArgumentList *arg_list) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = FUNC_CALL;
    expr->type = NULL;
    expr->ident = ident;
    expr->arg_list = arg_list;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_incdec_expression(ExpressionKind kind, Expression *expr) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = kind;
    expr->type = NULL;
    expr->left = expr;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_identifier_expression(Identifier *ident) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = IDENTIFIER_EXPRESSION;
    expr->type = NULL;
    expr->ident = ident;
    expr->linenum = get_current_compiler()->current_line_number;    

    return expr;
}
