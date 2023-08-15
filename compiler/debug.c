#include <table.h>
#include "decls.h"

#define IDENTIFIER_MAX_LEN 256

char *stat_kinds[] = {
    "EXPRESSION_STATEMENT",
    "FOR_STATEMENT",
    "FOREACH_STATEMENT",
    "WHILE_STATEMENT",
    "IF_STATEMENT",
    "RETURN_STATEMENT",
    "BREAK_STATEMENT",
    "CONTINUE_STATEMENT",
    "TRY_STATEMENT",
    "THROW_STATEMENT",
    "DECLARATION_STATEMENT",
};

char* exprkinds[] = {
    "ARITH_ADDITIVE_EXPRESSION",
    "ARITH_SUBSTRACTION_EXPRESSION",
    "ARITH_MULTIPLICATION_EXPRESSION",
    "ARITH_DIVISION_EXPRESSION",
    "ARITH_MODULO_EXPRESSION",
    "RELATION_GT_EXPRESSION",
    "RELATION_LT_EXPRESSION",
    "RELATION_GE_EXPRESSION",
    "RELATION_LE_EXPRESSION",
    "RELATION_EQ_EXPRESSION",
    "RELATION_NE_EXPRESSION",
    "LOGICAL_AND_EXPRESSION",
    "LOGICAL_OR_EXPRESSION",
    "LOGICAL_NOT_EXPRESSION",
    "MINUS_EXPRESSION",
    "FUNC_CALL_EXPRESSION",
    "COMMA_EXPRESSION",
    "IDENTIFIER_EXPRESSION",
    "NORMAL_ASSIGN_EXPRESSION",
    "ADD_ASSIGN_EXPRESSION",
    "SUB_ASSIGN_EXPRESSION",
    "MUL_ASSIGN_EXPRESSION",
    "DIV_ASSIGN_EXPRESSION",
    "MOD_ASSIGN_EXPRESSION",
    "POST_INCREMENT_EXPRESSION",
    "POST_DECREMENT_EXPRESSION",
    "BOOLEAN_LITERAL_EXPRESSION",
    "INT_LITERAL_EXPRESSION",
    "DOUBLE_LITERAL_EXPRESSION",
    "STRING_LITERAL_EXPRESSION",
    "CAST_EXPRESSION"
};

char *value_types[] = {
    "UNDETERMIEND",
    "BOOLEAN_TYPE",
    "INT_TYPE",
    "DOUBLE_TYPE",
    "STRING_TYPE",
};
/*
    0       Func1       *           *
    1       type        exprtype    kind
    
    #       LocalVar    *           *
    name    index       *           *
*/
void disass_func(FunctionDefinition *fd) {
    Statement *stat;
    table *tab;
    int id = 0;
    int row;
    
    tab = table_new();
    table_add_column(tab, "", TABLE_INT);
    table_add_column(tab, "", TABLE_STRING);
    table_add_column(tab, "", TABLE_STRING);
    table_add_column(tab, "", TABLE_STRING);
    row = table_add_row(tab);
    table_set_int(tab, row, 0, id ++);
    table_set_string(tab, row, 1, fd->ident->name);
    table_set_string(tab, row, 2, "******");
    table_set_string(tab, row, 3, "******");
    for(stat = fd->block->stat_list->phead; stat; stat = stat->next) {
        row = table_add_row(tab);
        table_set_int(tab, row, 0, id ++);
        table_set_string(tab, row, 1, stat_kinds[stat->kind]);
        if(stat->kind == EXPRESSION_STATEMENT) {
            table_set_string(tab, row, 2, value_types[stat->u.expr->type->basic_type]);
            table_set_string(tab, row, 3, exprkinds[stat->u.expr->kind]);
        }
    }
    row = table_add_row(tab);
    table_set_int(tab, row, 0, id ++);
    table_set_string(tab, row, 1, "LocalVars");
    table_set_string(tab, row, 2, "######");
    table_set_string(tab, row, 3, "######");
    for(int i = 0; i < fd->local_variable_cnt; i ++) {
        Statement *d = fd->local_variables[i];
        int row;
        row = table_add_row(tab);
        table_set_int(tab, row, 0, d->u.declaration_stat.index);
        table_set_string(tab, row, 1, d->u.declaration_stat.ident->name);
    }
    /* print the table */
    int row_num = table_get_row_length(tab);
    int col_num = table_get_column_length(tab);
    for(int row = 0; row < row_num; row ++) {
        for(int col = 0; col < col_num; col ++) {
            char buf[200];
            table_cell_to_buffer(tab, row, col, buf, sizeof(buf));
            printf("%-25s\t", buf);
        }
        printf("\n");
    }
    table_delete(tab);
}



void disassemble() {
    Compiler *comp;
    FunctionDefinition *fd;

    comp = get_current_compiler();
    for(fd=comp->function_list->phead; fd; fd=fd->next) {
        disass_func(fd);
    }
    return;
}