#include <string.h>
#include "decls.h"

#define IDENTIFIER_MAX_LEN 256

extern OpcodeInfo opcode_info[];

typedef enum {
    TABLE_TYPE_UNSET,
    TABLE_INT,
    TABLE_DOUBLE,
    TABLE_STRING,
} TableColumnType;

typedef struct table  table;
typedef struct Cell   Cell;

struct Cell {
    TableColumnType type;
    union {
        int int_v;
        char *str_v;
        double double_v;
    };
};

struct table {
    Cell     *arr;
    int      col_num;
    int      row_num; /* 0 means no rows. 1 means there is one row. */
};

table* table_new() {
    table *tab;

    tab = MEM_malloc(sizeof(table));
    tab->arr = NULL;
    tab->col_num = 0;
    tab->row_num = 0;

    return tab;
}

void table_add_column(table* tab, const char* name, TableColumnType ctype) {
    tab->col_num ++;
}

int table_add_row(table *tab) {
    tab->row_num ++;
    tab->arr = MEM_realloc(tab->arr, tab->row_num * tab->col_num * sizeof(Cell));
    
    int idx = (tab->row_num - 1) * tab->col_num;
    for(int i = 0; i < tab->col_num; i ++) {
        tab->arr[idx + i].type = TABLE_TYPE_UNSET;
    }

    return tab->row_num;
}

void table_set_int(table *tab, int row, int col, int value) {
    int idx = (row-1) * tab->col_num + (col - 1);
    tab->arr[idx].type = TABLE_INT;
    tab->arr[idx].int_v = value;
}

void table_set_double(table *tab, int row, int col, double value) {
    int idx = (row-1) * tab->col_num + (col - 1);
    tab->arr[idx].type = TABLE_DOUBLE;
    tab->arr[idx].double_v = value;
}

void table_set_string(table *tab, int row, int col, char* value) {
    int idx = (row-1) * tab->col_num + (col - 1);
    tab->arr[idx].type = TABLE_STRING;
    tab->arr[idx].str_v = value;
}

int table_get_row_num(table *tab) {
    return tab->row_num;
}

int table_get_col_num(table *tab) {
    return tab->col_num;
}

void reverse(char *str) {
    if(str == NULL) return;
    char *end = str;
    while(*end) end ++;
    end --;
    while(str < end) {
        char t = *str;
        *str = *end;
        *end = t;
        str ++, end --;
    }
}

void int_to_str(int x, char *buf, int buf_sz) {
    char *str = buf;

    if(x == 0) {
        if(buf_sz > 1) {
            *buf ++ = '0';
            *buf = '\0';
        } else {
            printf("table_cell_to_buffer:buf_size < int 0\n");
            exit(1);
        }
    }

    int s = 0;
    while(x) {
        if(s + 1 >= buf_sz) {
            printf("table_cell_to_buffer:buf_size < int length\n");
            exit(1);
        }
        *buf++ = x % 10 + '0';
        x /= 10;
        s ++;
    }
    *buf = '\0';
    reverse(str);
}

void table_cell_to_buffer(table *tab, int row, int col, char *buf, int buf_size) {
    int idx = (row-1) * tab->col_num + (col - 1);
    Cell* cell = tab->arr + idx;
    switch (cell->type)
    {
    case TABLE_INT:
        int_to_str(cell->int_v, buf, buf_size);
        break;
    case TABLE_DOUBLE:
        sprintf(buf, "%lf", cell->double_v);
        break;
    case TABLE_STRING:
        if(strlen(cell->str_v) >= buf_size) {
            printf("table_cell_to_buffer:strlen(cell->str_v) >= buf_size\n");
            exit(1);
        }
        strcpy(buf, cell->str_v);
        break;
    case TABLE_TYPE_UNSET:
        if(buf_size < 1) {
            printf("table_cell_to_buffer:buf_size < empty string length\n");
            exit(1);
        }
        strcpy(buf, "");
        break;
    default:
        break;
    }
}

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

void print_seperate_line(char *line, int n) {
    for(int i = 0; i < n; i ++) {
        printf("%-20s\t", line);
    }
    printf("\n");
}

void print_line(char *cell1, char *cell2, char *cell3, char *cell4, char *cell5, char *cell6) {
    printf("%-20s\t", cell1);
    printf("%-20s\t", cell2);
    printf("%-20s\t", cell3);
    printf("%-20s\t", cell4);
    printf("%-20s\t", cell5);
    printf("%-20s\t", cell6);
    printf("\n");
    print_seperate_line("-------------", 6);
}

void print_table(table *tab) {
    /* print the table */
    int row_num = table_get_row_num(tab);
    int col_num = table_get_col_num(tab);
    for(int row = 1; row <= row_num; row ++) {
        for(int col = 1; col <= col_num; col ++) {
            char buf[200];
            table_cell_to_buffer(tab, row, col, buf, sizeof(buf));
            printf("%-20s\t", buf);
        }
        printf("\n");
        print_seperate_line("-------------", 6);
    }
}

/*
    0       Func1       *           *
    1       type        exprtype    kind
    
    #       LocalVar    *           *
    name    index       *           *
*/
static
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
    table_set_int(tab, row, 1, id ++);
    table_set_string(tab, row, 2, fd->ident->name);
    table_set_string(tab, row, 3, "******");
    table_set_string(tab, row, 4, "******");
    for(stat = fd->block->stat_list->phead; stat; stat = stat->next) {
        row = table_add_row(tab);
        table_set_int(tab, row, 1, id ++);
        table_set_string(tab, row, 2, stat_kinds[stat->kind]);
        if(stat->kind == EXPRESSION_STATEMENT) {
            table_set_string(tab, row, 3, value_types[stat->u.expr->type->basic_type]);
            table_set_string(tab, row, 4, exprkinds[stat->u.expr->kind]);
        }
    }
    row = table_add_row(tab);
    table_set_int(tab, row, 1, id ++);
    table_set_string(tab, row, 2, "LocalVars");
    table_set_string(tab, row, 3, "######");
    table_set_string(tab, row, 4, "######");
    for(int i = 0; i < fd->local_variable_cnt; i ++) {
        Statement *d = fd->local_variables[i];
        int row;
        row = table_add_row(tab);
        table_set_int(tab, row, 1, d->u.declaration_stat.index);
        table_set_string(tab, row, 2, d->u.declaration_stat.ident->name);
    }
    
    print_table(tab);

}

static
void disass_func_codes(Function *func, Executable *exe) {
    table *tab = NULL;
    int row;
    int pc = 0, imm8, imm16, idx;
    Byte opcode;

    tab = table_new();

    table_add_column(tab, "", TABLE_INT);    
    table_add_column(tab, "", TABLE_STRING); /* OpCode Name */
    table_add_column(tab, "", TABLE_INT);    /* Operand size */
    table_add_column(tab, "", TABLE_INT);    /* Index or Operand */
    table_add_column(tab, "", TABLE_STRING); /* Identifier */
    table_add_column(tab, "", TABLE_INT);    /* label */

    while(pc < func->code_size) {
        row = table_add_row(tab);
        table_set_int(tab, row, 1, pc);
        opcode = func->codes[pc ++];
        table_set_string(tab, row, 2, opcode_info[opcode].mnemonic);
        switch (opcode_info[opcode].para[0])
        {
        case 'b': 
            imm8 = func->codes[pc ++];
            table_set_int(tab, row, 3, 1);
            table_set_int(tab, row, 4, (int)imm8);
            break;
        case 'd':
            imm16 = ((int)func->codes[pc] << 8) + func->codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, imm16);
            pc += 2;
        case 's':
            idx = ((int)func->codes[pc] << 8) + func->codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, idx);
            pc += 2;          
            if(opcode >= 8 && opcode <= 13) {           /* push_stack_int */
                if(idx >= func->para_cnt) idx -= 2;     /* idx -= (sizeof(CallerInfo) - 1) / sizeof(Value) + 1 */
                Variable v = func->local_vars[idx];
                table_set_string(tab, row, 5, v.name);
            } else if(opcode >= 14 && opcode <= 19) {   /* push_static_int */
                Variable v = exe->data_seg->arr[idx];
                table_set_string(tab, row, 5, v.name);
            } else if(opcode >= 63 && opcode <= 65) {   /* jump label */
                table_set_int(tab, row, 6, idx);
            }
            break;
        case 'p':
            idx = ((int)func->codes[pc] << 8) + func->codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, idx);
            pc += 2;
            break;
        case '\0':
        default:
            break;
        }
    }
    /* print table header */
    print_line("START_PC", "OPCODE_NAME", "OPERAND_SIZE", "OPERAND", "IDENTIFIER", "LABEL");
    print_table(tab);

}

void disass_codes(Executable *exe, Byte* codes, int code_size, Function *func) {
    table *tab = NULL;
    int row;
    int pc = 0, imm8, imm16, idx;
    Byte opcode;

    tab = table_new();

    table_add_column(tab, "", TABLE_INT);    
    table_add_column(tab, "", TABLE_STRING); /* OpCode Name */
    table_add_column(tab, "", TABLE_INT);    /* Operand size */
    table_add_column(tab, "", TABLE_INT);    /* Index or Operand */
    table_add_column(tab, "", TABLE_STRING); /* Identifier */
    table_add_column(tab, "", TABLE_INT); /* label */

    while(pc < code_size) {
        row = table_add_row(tab);
        table_set_int(tab, row, 1, pc);
        opcode = codes[pc ++];
        table_set_string(tab, row, 2, opcode_info[opcode].mnemonic);
        switch (opcode_info[opcode].para[0])
        {
        case 'b': 
            imm8 = codes[pc ++];
            table_set_int(tab, row, 3, 1);
            table_set_int(tab, row, 4, (int)imm8);
            break;
        case 'd':
            imm16 = ((int)codes[pc] << 8) + codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, imm16);
            pc += 2;
        case 's':
            idx = ((int)codes[pc] << 8) + codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, idx);
            pc += 2;          
            if(opcode >= 8 && opcode <= 13) {           /* push_stack_int */
                Variable v = func->local_vars[idx];
                table_set_string(tab, row, 5, v.name);
            } else if(opcode >= 14 && opcode <= 19) {   /* push_static_int */
                Variable v = exe->data_seg->arr[idx];
                table_set_string(tab, row, 5, v.name);
            } else if(opcode >= 63 && opcode <= 65) {   /* jump label */
                table_set_int(tab, row, 6, idx);
            }
            break;
        case 'p':
            idx = ((int)codes[pc] << 8) + codes[pc + 1];
            table_set_int(tab, row, 3, 2);
            table_set_int(tab, row, 4, idx);
            pc += 2;
            break;
        case '\0':
        default:
            break;
        }
    }

    /* print table header */
    print_line("START_PC", "OPCODE_NAME", "OPERAND_SIZE", "OPERAND", "IDENTIFIER", "LABEL");
    print_table(tab);
}

void disass_data_seg(Executable *exe) {
    table *tab;
    Variable *var;
    int row;

    tab = table_new();

    table_add_column(tab, "", TABLE_INT);    
    table_add_column(tab, "", TABLE_STRING);    
    table_add_column(tab, "", TABLE_STRING);
    for(int i = 0; i < exe->data_seg->size; i ++) {
        var = &exe->data_seg->arr[i];
        row = table_add_row(tab);
        table_set_int(tab, row, 1, i);
        table_set_string(tab, row, 2, value_types[var->type->basic_type]);
        table_set_string(tab, row, 3, var->name);
    }

    /* print table */
    print_seperate_line("*************", 6);
    print_line("Index", "Type", "Name", "","","");
    print_table(tab);
}

char *cons_tags[3] = {
    "INT CONSTANT",
    "DOUBLE CONSTANT",
    "STRING CONSTANT",
};

void disass_const_seg(Executable *exe) {
    table *tab;
    Constant *cons;
    int row;

    tab = table_new();
    table_add_column(tab, "", TABLE_INT);      /* Index */
    table_add_column(tab, "", TABLE_STRING);   /* Tag*/ 
    table_add_column(tab, "", TABLE_INT);      /* int_v */
    table_add_column(tab, "", TABLE_DOUBLE);   /* double_v */
    table_add_column(tab, "", TABLE_STRING);   /* string_v */
    for(int i = 0; i < exe->constant_seg->size; i ++) {
        cons = &exe->constant_seg->arr[i];
        row = table_add_row(tab);
        table_set_int(tab, row, 1, i);
        table_set_string(tab, row, 2, cons_tags[cons->tag]);
        if(cons->tag == INT_CONSTANT) {
            table_set_int(tab, row, 3, cons->int_constant);
        } else if(cons->tag == DOUBLE_CONSTANT) {
            table_set_double(tab, row, 4, cons->double_constant);
        } else if(cons->tag == STRING_CONSTANT) {
            table_set_string(tab, row, 5, cons->string_constant);
        }
    }

    /* print table */
    print_seperate_line("#############", 6);
    print_line("Index", "Constant Type", "Int", "Double", "String", "");
    print_table(tab);
}

void disassemble_exe(Executable *exe) {
    Function f;

    for(int i = 0; i < exe->code_seg->size; i ++) {
        f = exe->code_seg->arr[i];
        print_line("<FUNCTION>", f.name, "", "", "", "");
        disass_func_codes(&f, exe);
    }

    disass_codes(exe, exe->top_codes, exe->top_code_size, NULL);

    disass_data_seg(exe);
    disass_const_seg(exe);

}

void disassemble_ast() {
    Compiler *comp;
    FunctionDefinition *fd;

    comp = get_current_compiler();
    for(fd=comp->function_list->phead; fd; fd=fd->next) {
        disass_func(fd);
    }

    return;
}