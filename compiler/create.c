#include <stdlib.h>
#include <string.h>
#include "decls.h"

Identifier* create_identifier(char *name) {
    Identifier *ident;
    char *new_str;

    new_str = (char*)Malloc(strlen(name) + 1);
    strcpy(new_str, name);
    ident = (Identifier*)Malloc(sizeof(Identifier));
    ident->name = new_str;
    
    return ident;
}

Expression* alloc_expression(ExpressionKind kind) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = kind;
    expr->type = UNDETERMIEND;
    expr->linenum = get_current_compiler()->current_line_number;
    
    return expr;
}

FunctionDefinition* 
create_function_definition (
    TypeSpecifier *ts, Identifier *ident, ParameterList *param_list, Block *block) 
{
    Compiler *comp;
    FunctionDefinition *func_def;

    comp = get_current_compiler();
    func_def = (FunctionDefinition*)Malloc(sizeof(FunctionDefinition));
    func_def->type = ts;
    func_def->ident = ident;
    func_def->param_list = param_list;
    func_def->block = block;
    func_def->local_variables = NULL;
    func_def->local_variable_cnt = 0;
    func_def->index = comp->function_list->len;
    func_def->next = NULL;

    return func_def;
}

void define_function(TypeSpecifier *ts, Identifier *ident, ParameterList *para_list, Block *block) {
    Compiler *comp;
    FunctionDefinition *func_def, *pos;

    comp = get_current_compiler();
    /* Semantic analysis for "FUNCTION_REDEFINITION" */
    if(comp->function_list->phead) {
        for(pos = comp->function_list->phead; pos; pos = pos->next) {
            if(strcmp(ident->name, pos->ident->name) == 0) {
                error_message(comp->current_line_number, FUNCTION_REDEFINITION);
                return;
            }
        }
    }

    func_def = create_function_definition(ts, ident, para_list, block);
    if(block) {
        block->type = FUNCTION_BLOCK;
        block->func_def = func_def;
    }
    if(!comp->function_list->phead) {
        comp->function_list->phead = func_def;
    } else {
        for(pos = comp->function_list->phead; pos->next; pos = pos->next) 
            ;
        pos->next = func_def;
    }
    comp->function_list->len ++;
}

ParameterList* create_parameter_list(TypeSpecifier *ts, Identifier *ident) {
    ParameterList   *param_list;
    Parameter       *param;

    param = Malloc(sizeof(Parameter));
    param->ident = ident;
    param->type = ts;
    param->next = NULL;
    
    param_list = Malloc(sizeof(ParameterList));
    param_list->phead = param;
    param_list->len = 1;
    
    return param_list;    
}

ParameterList* create_and_chain_parameter(ParameterList *param_list, TypeSpecifier *ts, Identifier *ident) {
    Parameter *param, *pos;

    param = Malloc(sizeof(Parameter));
    param->type = ts;
    param->ident = ident;
    param->next = NULL;
    
    for(pos = param_list->phead; pos->next; pos=pos->next)
        ;
    pos->next = param;
    param_list->len ++;

    return param_list;
}

ArgumentList* create_argument_list(Expression *expr) {
    ArgumentList* arg_list;
    Argument *arg;
    
    arg_list = (ArgumentList*)Malloc(sizeof(ArgumentList));
    arg = (Argument*)Malloc(sizeof(Argument));
    arg->expr = expr;
    arg->next = NULL;
    arg_list->phead = arg;

    return arg_list;
}

ArgumentList* chain_argument_list(ArgumentList* arg_list, Expression *expr) {
    Argument *arg, *pos;

    arg = (Argument*)Malloc(sizeof(Argument));
    arg->expr = expr;
    arg->next = NULL;
    for(pos = arg_list->phead; pos->next; pos = pos->next) 
        ;
    pos->next = arg;
    
    return arg_list;
}

void chain_declaration_statement(Statement* stat) {
    Statement *pos_stat;
    StatementList* stat_list;
 
    stat_list = get_current_compiler()->current_block->declaration_stat_list;
    if(stat_list->phead != NULL) {
        for(pos_stat = stat_list->phead; pos_stat->next; pos_stat=pos_stat->next)
                ;
        pos_stat->next = stat;
    } else {
        stat_list->phead = stat;        
    }
    stat_list->len ++;
}

void chain_nondecl_statement(Statement* stat) {
    Statement *pos_stat;
    StatementList* stat_list;
 
    stat_list = get_current_compiler()->current_block->stat_list;
    if(stat_list->phead != NULL) {
        for(pos_stat = stat_list->phead; pos_stat->next; pos_stat=pos_stat->next)
                ;
        pos_stat->next = stat;
    } else {
        stat_list->phead = stat;        
    }
    stat_list->len ++;
}

void chain_block_statement(Statement *stat) {
    if(stat->kind != DECLARATION_STATEMENT) {
        chain_nondecl_statement(stat);
    } else {
        chain_declaration_statement(stat);
    }
}

void chain_top_level_statement(Statement *stat) {
    Compiler *comp;
    Statement *pos;
    StatementList* stat_list;

    comp = get_current_compiler();
    if(stat->kind != DECLARATION_STATEMENT) {
        stat_list = comp->statement_list;
    } else {
        stat->u.declaration_stat.is_local = 0;
        stat->u.declaration_stat.index = comp->declaration_stat_list->len;
        stat_list = comp->declaration_stat_list;
    }

    if(stat_list->phead != NULL) {
        for(pos = stat_list->phead; pos->next; pos = pos->next)
            ;
        pos->next = stat;
    } else {
        stat_list->phead = stat;
    }
    stat_list->len ++;
}

Expression* create_comma_expression(Expression *left, Expression *right) {
    Expression *expr;

    expr = Malloc(sizeof(Expression));
    expr->kind = COMMA_EXPRESSION;
    expr->type = UNDETERMIEND;
    /* Actually, we can set expr->type here, but the author of the book doesn't do this.
       I don't know why yet. And I decide to do the same as him.
     */
    expr->binary_expr.left = left;
    expr->binary_expr.right = right;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_binary_expression(ExpressionKind kind, Expression *left, Expression *right) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = kind;
    expr->binary_expr.left = left;
    expr->binary_expr.right = right;
    expr->type = UNDETERMIEND;
    expr->linenum = get_current_compiler()->current_line_number;
    
    return expr;
}

Expression* create_minus_expression(Expression *operand) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = MINUS_EXPRESSION;
    expr->unary_operand = operand;
    expr->type = UNDETERMIEND;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_logical_not_expression(Expression *operand) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = LOGICAL_NOT_EXPRESSION;
    expr->unary_operand = operand;
    expr->type = UNDETERMIEND;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_function_call_expression(Expression *callee, ArgumentList *arg_list) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = FUNC_CALL_EXPRESSION;
    expr->type = UNDETERMIEND;
    expr->function_call_expr.callee = callee;
    expr->function_call_expr.arg_list = arg_list;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_incdec_expression(ExpressionKind kind, Expression *operand) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = kind;
    expr->type = UNDETERMIEND;
    expr->unary_operand = operand;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Expression* create_identifier_expression(Identifier *ident) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = IDENTIFIER_EXPRESSION;
    expr->type = UNDETERMIEND;
    expr->ident = ident;
    expr->linenum = get_current_compiler()->current_line_number;    

    return expr;
}

Expression* create_boolean_expression(Boolean v) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = BOOLEAN_LITERAL_EXPRESSION;
    expr->type = create_typespecifier(BOOLEAN_TYPE);
    expr->boolean_v = v;
    expr->linenum = get_current_compiler()->current_line_number;

    return expr;
}

Statement* create_expression_statement(Expression *expr) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = EXPRESSION_STATEMENT;
    stat->u.expr = expr;
    stat->next = NULL;

    return stat;
}

Statement* create_if_statement(Expression *cond, Block *then_block, Elif *elif_list, Block *else_block) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement)); 
    stat->kind = IF_STATEMENT;
    stat->u.if_stat.cond = cond;
    stat->u.if_stat.then_block = then_block;
    stat->u.if_stat.elif_list = elif_list;
    stat->u.if_stat.else_block = else_block;
    stat->next = NULL;
    
    return stat;
}

Elif* create_elif(Expression *cond, Block *block){ 
    Elif *elif;

    elif = (Elif*)Malloc(sizeof(Elif));
    elif->cond = cond;
    elif->block = block;
    elif->next = NULL;

    return elif;
}

Elif* chain_elif_list(Elif *elif_list, Elif *elif) {
    Elif *pos;

    for(pos = elif_list; pos->next; pos = pos->next) 
        ;
    pos->next = elif;

    return elif_list;
}

Statement* create_while_statement(Identifier *label, Expression *cond, Block *block) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = WHILE_STATEMENT;
    stat->u.while_stat.label = label;
    stat->u.while_stat.cond_expr = cond;
    stat->u.while_stat.block = block;
    stat->u.while_stat.backpack_points = NULL;
    stat->next = NULL;
    block->type = WHILE_STATEMENT_BLOCK;
    block->stat = stat;

    return stat;
}

Statement* create_for_statement(Identifier *label, Expression *init, Expression *cond, Expression *post, Block *block) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = FOR_STATEMENT;
    stat->u.for_stat.label = label;
    stat->u.for_stat.init_expr = init;
    stat->u.for_stat.cond_expr = cond;
    stat->u.for_stat.post_expr = post;
    stat->u.for_stat.block = block;
    stat->u.for_stat.backpack_points = NULL;
    stat->next = NULL;
    block->type = FOR_STATEMENT_BLOCK;
    block->stat = stat;

    return stat;
}

Statement* create_foreach_statement(Identifier *label, Identifier *ident, Expression *expr, Block *block) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = FOREACH_STATEMENT;
    stat->u.foreach_stat.label = label;
    stat->u.foreach_stat.ident = ident;
    stat->u.foreach_stat.expr = expr;
    stat->u.foreach_stat.block = block;
    stat->u.foreach_stat.backpack_points = NULL;
    stat->next = NULL;
    block->type = FOR_STATEMENT_BLOCK;

    return stat;
}

Statement* create_return_statement(Expression *expr) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = RETURN_STATEMENT;
    stat->u.return_stat.ret_expr =  expr;
    stat->next = NULL;

    return stat;
}

Statement* create_break_statement(Identifier *label) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = BREAK_STATEMENT;
    stat->u.break_stat.label = label;
    stat->next = NULL;

    return stat;
}

Statement* create_continue_statement(Identifier *label) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = CONTINUE_STATEMENT;
    stat->u.break_stat.label = label;
    stat->next = NULL;

    return stat;
}

Statement* 
create_try_statement(
    Block *try_block, Identifier *catch_obj, Block *catch_block, Block *final_block) 
{
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = TRY_STATEMENT;
    stat->u.try_stat.try_block = try_block;
    stat->u.try_stat.catch_obj = catch_obj;
    stat->u.try_stat.catch_block = catch_block;
    stat->u.try_stat.final_block = final_block;
    stat->next = NULL;

    return stat;      
}

Statement* create_throw_statement(Expression *except) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = THROW_STATEMENT;
    stat->u.throw_stat.exception = except;
    stat->next = NULL;

    return stat;
}

Statement* create_declaration_statement(TypeSpecifier *ts, Identifier *ident, Expression *initializer) {
    Statement *stat;

    stat = (Statement*)Malloc(sizeof(Statement));
    stat->kind = DECLARATION_STATEMENT;
    stat->u.declaration_stat.type = ts;
    stat->u.declaration_stat.ident = ident;
    stat->u.declaration_stat.initializer = initializer;
    stat->next = NULL;
    ident->decl = stat;
    ident->is_func = 0;
    ident->func_def = NULL;

    return stat;
}

Block* open_block() {
    Block *block;
    Compiler *comp;

    comp = get_current_compiler();
    block = (Block*)Malloc(sizeof(Block));
    block->outer_block = comp->current_block;
    block->type = UNDEFINED_BLOCK;
    block->declaration_stat_list = (StatementList*)Malloc(sizeof(StatementList));
    block->declaration_stat_list->phead = NULL;
    block->declaration_stat_list->len = 0;
    block->stat_list = (StatementList*)Malloc(sizeof(StatementList));
    block->stat_list->phead = NULL;
    block->stat_list->len = 0;
    comp->current_block = block;
    
    return block;
}

Block* close_block(Block *block) {
    Compiler *comp;

    comp = get_current_compiler();
    comp->current_block = block->outer_block;

    return block;
}

TypeSpecifier* create_typespecifier(ValueType typ) {
    TypeSpecifier* ts;

    ts = (TypeSpecifier*)Malloc(sizeof(TypeSpecifier));
    ts->basic_type = typ;
    ts->derive_list_header_p = NULL;

    return ts;
}

TypeSpecifier* create_array_typespecifier(TypeSpecifier *ts) {
    TypeDerive *td;
    TypeDerive *pos;

    td = (TypeDerive*)Malloc(sizeof(TypeDerive));
    td->tag = ARRAY_DERIVE;
    td->next = 0;
    if(ts->derive_list_header_p == NULL) {
        ts->derive_list_header_p = td;
    } else {
        for(pos=ts->derive_list_header_p; pos->next; pos=pos->next)
            ;
        pos->next = td;
    }

    return ts;
}

Expression* create_index_expression(Expression *array, Expression *index) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = INDEX_EXPRESSION;
    expr->index_expr.array = array;
    expr->index_expr.index = index;
    
    return expr;
}

Expression* create_array_literal_expression(ExpressionListNode *elist) {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = ARRAY_LITERAL_EXPRESSION;
    expr->array_literal_expr = elist;

    return expr;
}

Expression* create_array_creation_expression(ValueType basic_type, 
    ExpressionListNode *expr_list, ExpressionListNode *empty_expr_list)
{
    Expression *expr;
    ExpressionListNode *pos;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = ARRAY_CREATION_EXPRESSION;
    expr->array_creation_expr.basic_type = basic_type;
    for(pos=expr_list; pos->next; pos=pos->next) 
        ;
    pos->next = empty_expr_list;
    expr->array_creation_expr.dimension_list_header_p = expr_list;

    return expr;
}

ExpressionListNode* create_expression_list(Expression *expr) {
    ExpressionListNode *enode;
    
    enode = (ExpressionListNode*)Malloc(sizeof(ExpressionListNode));
    enode->expr = expr;
    enode->next = NULL;

    return enode;
}

ExpressionListNode* chain_expression_list(Expression *expr, ExpressionListNode *elist) {
    ExpressionListNode *new_enode;
    ExpressionListNode *pos;

    new_enode = (ExpressionListNode*)Malloc(sizeof(ExpressionListNode));
    new_enode->expr = expr;
    new_enode->next = NULL;
    for(pos = elist; pos->next; pos = pos->next)
        ;
    pos->next = new_enode;

    return elist;
}

ExpressionListNode* create_array_dimension(Expression *expr) {
    ExpressionListNode *array_dimension_list;

    array_dimension_list = (ExpressionListNode*)Malloc(sizeof(ExpressionListNode));
    array_dimension_list->expr = expr;
    array_dimension_list->next = NULL;

    return array_dimension_list;
}

ExpressionListNode* chain_array_dimension(Expression *expr, ExpressionListNode *array_dimension_list) {
    ExpressionListNode *new_array_dimension;
    ExpressionListNode *pos;

    new_array_dimension = (ExpressionListNode*)Malloc(sizeof(ExpressionListNode));
    new_array_dimension->expr = expr;
    new_array_dimension->next = NULL;
    for(pos=array_dimension_list; pos->next; pos=pos->next)
        ;
    pos->next = new_array_dimension;

    return array_dimension_list;
}

Expression *create_null_expression() {
    Expression *expr;

    expr = (Expression*)Malloc(sizeof(Expression));
    expr->kind = NULL_EXPRESSION;

    return expr;
}