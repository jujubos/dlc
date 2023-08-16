#include "decls.h"
#include <string.h>
#include <stdlib.h>

extern char *value_types[];

void walk_statement_list(StatementList *stat_list);

static FunctionDefinition *cur_func = NULL;

CastType cast_A_to_B[5][5] = {
    {0,0,0,0,0},
    {0,0,1,2,3},
    {0,4,0,5,6},
    {0,7,8,0,9},
    {0,10,11,12,0}
};

int is_expr_type(Expression *expr, ValueType typ) {
    return (expr->type->basic_type) == (typ);
}

FunctionDefinition* search_function(char *name) {
    Compiler *comp;
    FunctionDefinition *func_def;

    comp = get_current_compiler();
    for(func_def = comp->function_list->phead; func_def; func_def = func_def->next) {
        if(strcmp(func_def->ident->name, name) == 0) {
            return func_def;
        }
    }
    return NULL;
}

Statement* search_declaration(char *name) {
    Compiler *comp;
    Statement *stat;
    Block *pos_blk;

    comp = get_current_compiler();
    for(stat = comp->declaration_stat_list->phead; stat; stat = stat->next) {
        if(strcmp(stat->u.declaration_stat.ident->name, name) == 0)
            return stat;
    }
    int finded = 0;

    if(comp->current_block != NULL) {
        for(pos_blk = comp->current_block->outer_block; pos_blk; pos_blk = pos_blk->outer_block) {
            for(stat = pos_blk->declaration_stat_list->phead; stat; stat = stat->next) {
                if(strcmp(stat->u.declaration_stat.ident->name, name) == 0) {
                    finded = 1;
                    break;
                }
            }
            if(finded) break;
        }
        for(int i = 0; i < cur_func->local_variable_cnt; i ++) {
            stat = cur_func->local_variables[i];
            if(strcmp(name, stat->u.declaration_stat.ident->name) == 0) {
                if(!finded) {
                    finded = 1;
                    break;
                } else {
                    printf("search_declaration,identifier redefined, parameter and block variable conflict:%s\n", name);
                    exit(1); 
                }
            }
        }
    }

    if(finded) return stat;

    printf("search_declaration,identifier not found:%s\n", name);
    exit(1); 
}

int fill_identifier(Identifier *ident) {
    Statement *decl;
    FunctionDefinition *fd;

    if((decl = search_declaration(ident->name)) != NULL) {
        ident->decl = decl;
        ident->is_func = 0;
        return 1;
    } else if((fd = search_function(ident->name))) {
        ident->func_def = fd;
        ident->is_func = 1;
        return 1;
    }

    return 0;
}

void add_cast_node(Expression *expr) {
    Expression *cast_expr;
    TypeSpecifier *ltype, *rtype;
    
    ltype = expr->binary_expr.left->type;
    rtype = expr->binary_expr.right->type;
    cast_expr = (Expression*)Malloc(sizeof(Expression));
    cast_expr->kind = CAST_EXPRESSION;
    cast_expr->cast_expr.casted_expr = NULL;
    switch (expr->kind)
    {
    case NORMAL_ASSIGN_EXPRESSION:          /* Fallthrough */
    case ADD_ASSIGN_EXPRESSION:             /* Fallthrough */
    case SUB_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MUL_ASSIGN_EXPRESSION:             /* Fallthrough */
    case DIV_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MOD_ASSIGN_EXPRESSION: 
        cast_expr->cast_expr.type = cast_A_to_B[ltype->basic_type][rtype->basic_type];
        cast_expr->cast_expr.casted_expr = expr;
        expr->binary_expr.right = cast_expr;
        expr->type = create_typespecifier(ltype->basic_type);
        break;
    case ARITH_ADDITIVE_EXPRESSION:         /* Fallthrough */
    case ARITH_SUBSTRACTION_EXPRESSION:     /* Fallthrough */
    case ARITH_MULTIPLICATION_EXPRESSION:   /* Fallthrough */
    case ARITH_DIVISION_EXPRESSION:         /* Fallthrough */
    case ARITH_MODULO_EXPRESSION:           /* Fallthrough */  
    case RELATION_EQ_EXPRESSION:            /* Fallthrough */
    case RELATION_NE_EXPRESSION:            /* Fallthrough */
    case RELATION_GT_EXPRESSION:            /* Fallthrough */ 
    case RELATION_LT_EXPRESSION:            /* Fallthrough */
    case RELATION_GE_EXPRESSION:            /* Fallthrough */
    case RELATION_LE_EXPRESSION:
        if(ltype->basic_type > rtype->basic_type) {
            cast_expr->cast_expr.type = cast_A_to_B[rtype->basic_type][ltype->basic_type];
            cast_expr->cast_expr.casted_expr = expr->binary_expr.right;
            expr->binary_expr.right = cast_expr;
            expr->type = create_typespecifier(ltype->basic_type);
        } else {
            cast_expr->cast_expr.type = cast_A_to_B[ltype->basic_type][rtype->basic_type];
            cast_expr->cast_expr.casted_expr = expr->binary_expr.left;
            expr->binary_expr.left = cast_expr;
            expr->type = create_typespecifier(rtype->basic_type);
        }
        break;
    case LOGICAL_AND_EXPRESSION:
    case LOGICAL_NOT_EXPRESSION:
    case MINUS_EXPRESSION:
    case LOGICAL_OR_EXPRESSION:
    case COMMA_EXPRESSION:
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
    case FUNC_CALL_EXPRESSION:
    case IDENTIFIER_EXPRESSION:
    case BOOLEAN_LITERAL_EXPRESSION:
    case INT_LITERAL_EXPRESSION:
    case DOUBLE_LITERAL_EXPRESSION:
    case STRING_LITERAL_EXPRESSION:
    case CAST_EXPRESSION:
    default:
        break;
    }
}

void type_check_and_cast(Expression *expr) {
    switch (expr->kind)
    {
    case NORMAL_ASSIGN_EXPRESSION:          /* Fallthrough */
    case ADD_ASSIGN_EXPRESSION:             /* Fallthrough */
    case SUB_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MUL_ASSIGN_EXPRESSION:             /* Fallthrough */
    case DIV_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MOD_ASSIGN_EXPRESSION:     
        if(expr->binary_expr.left->type != expr->binary_expr.right->type) {
            if(is_expr_type(expr->binary_expr.left, STRING_TYPE) || 
                is_expr_type(expr->binary_expr.right, STRING_TYPE)) {
                printf("type_check_and_cast:ASSIGN EXPRESSION,STRING_TYPE\n");
                exit(1);
            }
            add_cast_node(expr);
        } else {
            expr->type = expr->binary_expr.left->type;
        }
        break;
    case ARITH_ADDITIVE_EXPRESSION:
        if(expr->binary_expr.left->type != expr->binary_expr.right->type) {
            add_cast_node(expr);
        } else {
            expr->type = create_typespecifier(expr->binary_expr.left->type->basic_type);
        }
        break;
    case ARITH_SUBSTRACTION_EXPRESSION:     /* Fallthrough */
    case ARITH_MULTIPLICATION_EXPRESSION:   /* Fallthrough */
    case ARITH_DIVISION_EXPRESSION:         /* Fallthrough */
    case ARITH_MODULO_EXPRESSION:           /* Fallthrough */  
        if(is_expr_type(expr->binary_expr.left, STRING_TYPE) || 
            is_expr_type(expr->binary_expr.right, STRING_TYPE)) {
            printf("type_check_and_cast:ARITH EXPRESSION EXCEPT FOR ADD,STRING_TYPE\n");
            exit(1);
        }
        if(expr->binary_expr.left->type != expr->binary_expr.right->type) {
            add_cast_node(expr);
        } else {
            expr->type = create_typespecifier(expr->binary_expr.left->type->basic_type);
        }
        break;
    case RELATION_EQ_EXPRESSION:    /* Fallthrough */
    case RELATION_NE_EXPRESSION:    /* Fallthrough */
    case RELATION_GT_EXPRESSION:    /* Fallthrough */ 
    case RELATION_LT_EXPRESSION:    /* Fallthrough */
    case RELATION_GE_EXPRESSION:    /* Fallthrough */
    case RELATION_LE_EXPRESSION:
        if(expr->binary_expr.left->type != expr->binary_expr.right->type) {
            if(is_expr_type(expr->binary_expr.left, STRING_TYPE) || 
                is_expr_type(expr->binary_expr.right, STRING_TYPE)) {
                printf("type_check_and_cast:RELATION EXPRESSION,STRING_TYPE\n");
                exit(1);
            }
            add_cast_node(expr);
        }
        expr->type = create_typespecifier(BOOLEAN_TYPE);
        break;
    case LOGICAL_AND_EXPRESSION:
    case LOGICAL_OR_EXPRESSION:
        if(is_expr_type(expr->binary_expr.left, STRING_TYPE) || 
            is_expr_type(expr->binary_expr.right, STRING_TYPE)) {
            printf("type_check_and_cast:LOGICAL AND and OR EXPRESSION,STRING_TYPE\n");
            exit(1);
        }
        expr->type = create_typespecifier(BOOLEAN_TYPE);
        break;
    case LOGICAL_NOT_EXPRESSION:    /* Fallthrough */
        if(is_expr_type(expr->unary_operand, STRING_TYPE)) {
            printf("type_check_and_cast:LOGICAL_NOT_EXPRESSION,STRING_TYPE\n");
            exit(1);
        }
        expr->type = create_typespecifier(BOOLEAN_TYPE);
        break;
    case MINUS_EXPRESSION:
        if(is_expr_type(expr->unary_operand, STRING_TYPE)) {
            printf("type_check_and_cast:LOGICAL_NOT_EXPRESSION,STRING_TYPE\n");
            exit(1);
        }
        expr->type = expr->unary_operand->type;
        break;
    case COMMA_EXPRESSION:
        expr->type = expr->binary_expr.right->type;
        break;
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
        if(is_expr_type(expr->unary_operand, STRING_TYPE)) {
            printf("type_check_and_cast:POST INCR(DECR)EMENT EXPRESSION,STING_TYPE\n");
            exit(1);
        }
        expr->type = expr->unary_operand->type;
        break;
    case FUNC_CALL_EXPRESSION:
        if(expr->function_call_expr.callee->kind != IDENTIFIER_EXPRESSION) {
            printf("type_check_and_cast:FUNC_CALL_EXPRESSION,callee not identifier\n");
            exit(1);
        }
        FunctionDefinition *fd;
        if((fd = search_function(expr->function_call_expr.callee->ident->name)) == NULL) {
            printf("type_check_and_cast:FUNC_CALL_EXPRESSION,function not found\n");
            exit(1);
        }
        expr->type = fd->type;
        break;
    case IDENTIFIER_EXPRESSION:
        if(!fill_identifier(expr->ident)) {
            printf("identifier not found:%s", expr->ident->name);
            exit(1);
        }
        if(expr->ident->is_func) {
            expr->type = expr->ident->func_def->type;
        } else {
            expr->type = expr->ident->decl->u.declaration_stat.type;
        }
        break;
    case BOOLEAN_LITERAL_EXPRESSION:    /* processed in flex */
    case INT_LITERAL_EXPRESSION:        /* processed in flex */
    case DOUBLE_LITERAL_EXPRESSION:     /* processed in flex */
    case STRING_LITERAL_EXPRESSION:     /* processed in flex */
    case CAST_EXPRESSION:               /* processed in VM */
    default:
        break;
    }
}

/*
    Terninating point: 
        1. Literal expression
        2. Identifier expression
*/
void walk_expression(Expression *expr) {
    switch (expr->kind)
    {
    case NORMAL_ASSIGN_EXPRESSION:          /* Fallthrough */
    case ADD_ASSIGN_EXPRESSION:             /* Fallthrough */
    case SUB_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MUL_ASSIGN_EXPRESSION:             /* Fallthrough */
    case DIV_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MOD_ASSIGN_EXPRESSION:             
        walk_expression(expr->binary_expr.left);
        if(expr->binary_expr.left->kind != IDENTIFIER_EXPRESSION) {
            printf("walk_expression:ASSIGN EXPRESSION, left value err\n");
            exit(1);
        }
        walk_expression(expr->binary_expr.right);
        type_check_and_cast(expr);
        break;
    case ARITH_ADDITIVE_EXPRESSION:         /* Fallthrough */
    case ARITH_SUBSTRACTION_EXPRESSION:     /* Fallthrough */
    case ARITH_MULTIPLICATION_EXPRESSION:   /* Fallthrough */
    case ARITH_DIVISION_EXPRESSION:         /* Fallthrough */
    case ARITH_MODULO_EXPRESSION:           /* Fallthrough */    
    case RELATION_EQ_EXPRESSION:            /* Fallthrough */
    case RELATION_NE_EXPRESSION:            /* Fallthrough */
    case RELATION_GT_EXPRESSION:            /* Fallthrough */
    case RELATION_LT_EXPRESSION:            /* Fallthrough */
    case RELATION_GE_EXPRESSION:            /* Fallthrough */
    case RELATION_LE_EXPRESSION:            /* Fallthrough */
    case LOGICAL_AND_EXPRESSION:            /* Fallthrough */
    case LOGICAL_OR_EXPRESSION:
        walk_expression(expr->binary_expr.left);
        walk_expression(expr->binary_expr.right);
        type_check_and_cast(expr);
        break;
    case LOGICAL_NOT_EXPRESSION:
    case MINUS_EXPRESSION:
        walk_expression(expr->unary_operand);
        type_check_and_cast(expr);
        break;
    case FUNC_CALL_EXPRESSION:
        type_check_and_cast(expr);
        break;
    case IDENTIFIER_EXPRESSION:
        type_check_and_cast(expr);
        break;
    case COMMA_EXPRESSION:
        walk_expression(expr->binary_expr.left);
        walk_expression(expr->binary_expr.right);
        type_check_and_cast(expr);
        break;
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
        walk_expression(expr->unary_operand);
        type_check_and_cast(expr);
        break;
    case CAST_EXPRESSION:               
    case BOOLEAN_LITERAL_EXPRESSION:    
    case INT_LITERAL_EXPRESSION:        
    case DOUBLE_LITERAL_EXPRESSION:     
    case STRING_LITERAL_EXPRESSION:
    default:
        type_check_and_cast(expr);
        break;
    }
}

/*
    1. type check and cast
    2. Undefinition check for Identifier
*/
void walk_expression_statement(Statement *stat) {
    walk_expression(stat->u.expr);
}

void walk_block(Block *block) {
    Compiler *comp;

    comp = get_current_compiler();

    comp->current_block = block;
    walk_statement_list(block->stat_list);
    comp->current_block = comp->current_block->outer_block;
}

void walk_for_statement(Statement *stat) {
    walk_expression(stat->u.for_stat.init_expr);
    walk_expression(stat->u.for_stat.cond_expr);
    if(is_expr_type(stat->u.for_stat.cond_expr, UNDETERMIEND) || 
        is_expr_type(stat->u.for_stat.cond_expr, STRING_TYPE)) {
        printf("walk_for_statement:type check,cond not boolean,got %s\n", value_types[stat->u.for_stat.cond_expr->type->basic_type]);
        exit(1);
    }
    walk_block(stat->u.for_stat.block);
    walk_expression(stat->u.for_stat.post_expr);
}

void walk_while_statement(Statement *stat) {
    walk_expression(stat->u.while_stat.cond_expr);
    if(is_expr_type(stat->u.while_stat.cond_expr, UNDETERMIEND) || 
        is_expr_type(stat->u.while_stat.cond_expr, STRING_TYPE)) {
        printf("walk_for_statement:type check,cond not boolean,got %s\n", value_types[stat->u.while_stat.cond_expr->type->basic_type]);
        exit(1);
    }
    walk_block(stat->u.while_stat.block);
}

void walk_foreach_statement(Statement *stat) {
    walk_expression(stat->u.foreach_stat.ident);
    walk_expression(stat->u.foreach_stat.expr);
    walk_block(stat->u.foreach_stat.block);
}

void walk_elif_list(Elif *elif) {
    while(elif) {
        walk_expression(elif->cond);
        walk_block(elif->block);
        elif = elif->next;
    }
}

/* If statement must have then_block, but elif_list and else_block may be NULL. 

    Note that:
        In my opinion, block is null means that in grammer-level, there is no block.
        If there is block in grammer-level, block must not be NULL and block->stat_list must not be null too,
        although block->stat_list.phead may be NULL in this situation, 
        which indicates there is none statement in the block.
*/
void walk_if_statement(Statement *stat) {
    walk_expression(stat->u.if_stat.cond);
    walk_block(stat->u.if_stat.then_block);
    if(stat->u.if_stat.elif_list != NULL) {
        walk_elif_list(stat->u.if_stat.elif_list);
    }
    if(stat->u.if_stat.else_block != NULL) {
        walk_block(stat->u.if_stat.else_block);
    }
}

void walk_return_statement(Statement *stat) {
    walk_expression(stat->u.return_stat.ret_expr);
    /* Todo after walk statement list of block */
    if(cur_func != NULL) {
        if(stat->u.return_stat.ret_expr->type->basic_type != cur_func->type->basic_type) {
            printf("walk_return_statement:return type not matched, need %s, got %s\n", 
                value_types[cur_func->type->basic_type],
                value_types[stat->u.return_stat.ret_expr->type->basic_type]
            );
            exit(1);
        }
    }
}

void walk_break_statement(Statement *stat) {
    Compiler *comp;
    Block *blk;

    comp = get_current_compiler();
    for(blk = comp->current_block; blk; blk=blk->outer_block) {
        if(blk->type == FOR_STATEMENT_BLOCK ||
            blk->type == WHILE_STATEMENT_BLOCK ) 
        { 
            return;
        }
    }
    
    printf("walk_break_statement:break not in loop block\n");
    exit(1);
}

void walk_continue_statement(Statement *stat) {
    Compiler *comp;
    Block *blk;

    comp = get_current_compiler();
    for(blk = comp->current_block; blk; blk=blk->outer_block) {
        if(blk->type == FOR_STATEMENT_BLOCK ||
            blk->type == WHILE_STATEMENT_BLOCK ) 
        { 
            return;
        }
    }

    printf("walk_continue_statement:continue not in loop block\n");
    exit(1);
}

void walk_statement_list(StatementList *stat_list) {
    Statement *stat;

    for(stat=stat_list->phead; stat; stat = stat->next) {
        switch (stat->kind)
        {
        case EXPRESSION_STATEMENT:
            walk_expression_statement(stat);
            break;
        case FOR_STATEMENT:
            walk_for_statement(stat);
            break;
        case WHILE_STATEMENT:
            walk_while_statement(stat);
            break;
        case FOREACH_STATEMENT:
            walk_foreach_statement(stat);
            break;
        case IF_STATEMENT:
            walk_if_statement(stat);
            break;
        case RETURN_STATEMENT:
            walk_return_statement(stat);
            break;
        case TRY_STATEMENT:
            break;
        case THROW_STATEMENT:
            break;
        case BREAK_STATEMENT:
            walk_break_statement(stat);
            break;
        case CONTINUE_STATEMENT:
            walk_continue_statement(stat);
            break;
        case DECLARATION_STATEMENT:
            break;    
        default:
            break;
        }
    }
}

void assemble_local_variable(FunctionDefinition *fd) {
    int sz;
    Parameter *param_p;
    Statement *stat;

    sz = fd->param_list->len + fd->block->declaration_stat_list->len;

    fd->local_variables = (Statement**)Malloc(sizeof(Statement*) * sz);
    for(param_p=fd->param_list->phead; param_p; param_p=param_p->next) {
        Statement *d = (Statement*)Malloc(sizeof(Statement));
        d->u.declaration_stat.type = param_p->type;
        d->u.declaration_stat.ident = param_p->ident;
        d->u.declaration_stat.index = fd->local_variable_cnt;
        d->u.declaration_stat.is_local = 1;
        fd->local_variables[fd->local_variable_cnt ++] = d;
    }
    for(stat=fd->block->declaration_stat_list->phead; stat; stat=stat->next) {
        /* todo: I think the design is not good.
            Maybe define a local variable struct instead of reuse DeclarationStatement is better.
            But now, I've decided not to change it.
            //Now, I decide to change it to Statement instead of DeclarationStatement.
         */
        stat->u.declaration_stat.index = fd->local_variable_cnt;
        stat->u.declaration_stat.is_local = 1;
        fd->local_variables[fd->local_variable_cnt ++] = stat;
    }
}

void add_return_statement(FunctionDefinition *fd) {
    Statement *stat, *pos;

    stat = NULL;
    stat = (Statement*)Malloc(sizeof(Statement));
    // stat = (Statement*)malloc(sizeof(Statement));
    stat->kind = RETURN_STATEMENT;
    stat->u.return_stat.ret_expr = NULL; /* Is NULL fine here??? */
    stat->next = NULL;
    if(fd->block->stat_list->phead == NULL) {
        fd->block->stat_list->phead = stat;
    } else {
        for(pos = fd->block->stat_list->phead; pos->next; pos = pos->next)
            ;
        if(pos->kind != RETURN_STATEMENT)
            pos->next = stat;
    }
    
    return;
}

void walk_ast_for_semantic_analysis(Compiler *comp) {
    /* walk top-level statement list */
    walk_statement_list(comp->statement_list);

    /* walk statement list of each function block */
    for(cur_func=comp->function_list->phead; cur_func; cur_func=cur_func->next) {
        /* I do not know the necessity of the procedure. */
        assemble_local_variable(cur_func);

        walk_block(cur_func->block);
        /* add return statement at the end of statement list of cur_func block */
        add_return_statement(cur_func);
    }
}