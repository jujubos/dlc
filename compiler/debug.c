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

char *value_types[] = {
    "UNDETERMIEND",
    "BOOLEAN_TYPE",
    "INT_TYPE",
    "DOUBLE_TYPE",
    "STRING_TYPE",
};


void disassemble(Compiler *comp) {
    Statement *stat;
    table *tab;
    int col_id, col_stat_kind, col_expr_stat_type;
    int id = 0;

    tab = table_new();
    col_id= table_add_column(tab, "id", TABLE_INT);
    col_stat_kind = table_add_column(tab, "stat_type", TABLE_STRING);
    col_expr_stat_type = table_add_column(tab, "expr_stat.type", TABLE_STRING);
    for(stat = comp->statement_list->phead; stat; stat = stat->next) {
        int row;
        row = table_add_row(tab);
        table_set_int(tab, row, col_id, id ++);
        table_set_string(tab, row, col_stat_kind, stat_kinds[stat->kind]);
        if(stat->kind == EXPRESSION_STATEMENT) {
            table_set_string(tab, row, col_expr_stat_type, value_types[stat->u.expr->type->basic_type]);
        } else if(stat->kind == DECLARATION_STATEMENT) {
            char ident_name[IDENTIFIER_MAX_LEN + 3];
            sprintf(ident_name, "<%s>", stat->u.declaration_stat.ident->name);
            table_set_string(tab, row, col_expr_stat_type, ident_name);
        }
    }

    /* print the table */
    int row_num = table_get_row_length(tab);
    int col_num = table_get_column_length(tab);
    for(int row = 0; row < row_num; row ++) {
        for(int col = 0; col < col_num; col ++) {
            char buf[200];
            table_cell_to_buffer(tab, row, col, buf, sizeof(buf));
            printf("%-4s\t", buf);
        }
        printf("\n");
    }
    table_delete(tab);

    return;
}