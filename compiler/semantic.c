#include "decls.h"
#include <string.h>

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
            expr->type = create_typespecifier(expr->binary_expr.left->type->basic_type);
        }
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
        expr->type = create_typespecifier(expr->unary_operand->type->basic_type);
        break;
    case COMMA_EXPRESSION:
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
    case FUNC_CALL_EXPRESSION:
    case IDENTIFIER_EXPRESSION:
    case CAST_EXPRESSION:
    case BOOLEAN_LITERAL_EXPRESSION:  
    case INT_LITERAL_EXPRESSION:
    case DOUBLE_LITERAL_EXPRESSION:
    case STRING_LITERAL_EXPRESSION:
    default:
        break;
    }
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
    Block *pos;

    comp = get_current_compiler();
    for(stat = comp->declaration_stat_list->phead; stat; stat = stat->next) {
        if(strcmp(stat->u.declaration_stat.ident->name, name) == 0)
            return stat;
    }
    if(comp->current_block != NULL) {
        for(pos = comp->current_block->outer_block; pos; pos = pos->outer_block) {
            for(stat = pos->stat_list->phead; stat; stat = stat->next) {
                if(strcmp(stat->u.declaration_stat.ident->name, name) == 0)
                    return stat;
            }
        }
    }

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
        walk_expression(expr->function_call_expr.callee);
        if(expr->function_call_expr.callee->kind != IDENTIFIER_EXPRESSION) {
            printf("walk_expression:FUNC_CALL_EXPRESSION, not identifier\n");
            exit(1);
        }
        /* check arguments type */
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
    case CAST_EXPRESSION:
    case COMMA_EXPRESSION:
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
    case BOOLEAN_LITERAL_EXPRESSION:
    case INT_LITERAL_EXPRESSION:
    case DOUBLE_LITERAL_EXPRESSION:
    case STRING_LITERAL_EXPRESSION:
    default:
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

void walk_declaration_statement(Statement *stat) {
    Compiler *comp;

    comp = get_current_compiler();
    if(comp->current_block != NULL) {
        comp->current_block->declaration_stat_list = chain_statement_list(comp->current_block->declaration_stat_list, stat);
    } else {
        comp->declaration_stat_list = chain_statement_list(comp->declaration_stat_list, stat);
    }
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
            break;
        case WHILE_STATEMENT:
            break;
        case FOREACH_STATEMENT:
            break;
        case IF_STATEMENT:
            break;
        case BREAK_STATEMENT:
            break;
        case CONTINUE_STATEMENT:
            break;
        case DECLARATION_STATEMENT:
            walk_declaration_statement(stat);
            break;
        case RETURN_STATEMENT:
        case TRY_STATEMENT:
        case THROW_STATEMENT:    
        default:
            break;
        }
    }
}

void walk_ast_for_semantic_analysis(Compiler *comp) {
    walk_statement_list(comp->statement_list);
}