#include <stdarg.h>
#include "decls.h"
#include "../include/exe.h"


#define CODEBUF_ALLOC_SIZE (256)

extern OpcodeInfo opcode_info[];

static 
struct {
    int             size;
    int             cap;
    Byte            *codes;
} codebuf;

static
struct {
    LineNumber  *arr;
    int         size;
    int         cap;
} linenum_buf;

void reset_code_buf() {
    codebuf.size = 0;
}

void reset_linenum_buf() {
    linenum_buf.size = 0;
}

static
void emit(int linenum, OpCodeTag opcode, ...) {
    char *para;
    OpcodeInfo opinfo;
    int operand_sz;
    int start_pc;

    opinfo = opcode_info[opcode];
    switch (opinfo.para[0])
    {
    case '\0':
        operand_sz = 0;
        break;
    case 'b':
        operand_sz = 1;
        break;
    case 's':
    case 'p':
        operand_sz = 2;
        break;
    default:
        break;
    }
    if(codebuf.size + operand_sz >= codebuf.cap) {
        codebuf.cap += CODEBUF_ALLOC_SIZE;
        codebuf.codes = (Byte*)MEM_realloc(codebuf.codes, sizeof(Byte) * codebuf.cap);
    }
    
    start_pc = codebuf.size;
    codebuf.codes[codebuf.size ++] = (Byte)opcode;
    va_list args;
    va_start(args, opcode);
    for(int i = 0; opinfo.para[i] != '\0'; i ++) {
        unsigned int operand = va_arg(args, int); /* ??? why cast int to unsigned int*/
        switch (opinfo.para[i])
        {
        case 'b':
            codebuf.codes[codebuf.size ++] = (Byte)operand;
            break;
        case 's':   /* Fallthrough */
        case 'p':
            codebuf.codes[codebuf.size ++] = (Byte)(operand >> 8 & 0xff);
            codebuf.codes[codebuf.size ++] = (Byte)(operand & 0xff);
            break;
        default:
            break;
        }
    }
    
    if(linenum_buf.arr == NULL ||
        linenum_buf.arr[linenum_buf.size - 1].num != linenum) 
    {
        linenum_buf.size ++;
        linenum_buf.arr = (LineNumber*)MEM_realloc(linenum_buf.arr, linenum_buf.size * sizeof(LineNumber));
        LineNumber *newl = &linenum_buf.arr[linenum_buf.size - 1];
        newl->num = linenum;
        newl->start_pc = start_pc;
        newl->last_pc = codebuf.size - 1;
    } else {
        LineNumber *curl = &linenum_buf.arr[linenum_buf.size - 1];
        curl->last_pc = codebuf.size - 1;
    }

    va_end(args);
}

static
void gen_constant_segment(Executable *exe) {
    
}

static
void gen_data_segment(Executable *exe) {

}

static int
type_offset(ValueType basic_type)
{
    switch (basic_type) {
    case BOOLEAN_TYPE:
        return 0;
        break;
    case INT_TYPE:
        return 0;
        break;
    case DOUBLE_TYPE:
        return 1;
        break;
    case STRING_TYPE:
        return 2;
        break;
    case UNDETERMIEND:
    default:
        break;
    }

    return 0;
}

static 
void pop_to_identifier(int linenum, Expression *ident_expr) {
    int is_local;
    ValueType basic_type;
    int index;
    is_local = ident_expr->ident->decl->u.declaration_stat.is_local;
    basic_type = ident_expr->type->basic_type;
    index = ident_expr->ident->decl->u.declaration_stat.index;
    if(is_local) {
        emit(linenum, POP_STACK_INT + type_offset(basic_type), index);
    } else {
        emit(linenum, POP_STATIC_INT + type_offset(basic_type), index);
    }
}

static
void gen_code_of_expression(Expression *expr) {
    int linenum = expr->linenum;
    switch (expr->kind)
    {
    case NORMAL_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.right);
        emit(linenum, DUPLICATE);
        pop_to_identifier(linenum, expr->binary_expr.left);
        break;
    case ADD_ASSIGN_EXPRESSION:             /* Fallthrough */
    case SUB_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MUL_ASSIGN_EXPRESSION:             /* Fallthrough */
    case DIV_ASSIGN_EXPRESSION:             /* Fallthrough */
    case MOD_ASSIGN_EXPRESSION:             
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
        break;
    case LOGICAL_NOT_EXPRESSION:
    case MINUS_EXPRESSION:
        break;
    case FUNC_CALL_EXPRESSION:
        break;
    case IDENTIFIER_EXPRESSION:
        break;
    case COMMA_EXPRESSION:
        break;
    case POST_INCREMENT_EXPRESSION:
    case POST_DECREMENT_EXPRESSION:
        break;
    case CAST_EXPRESSION:               
    case BOOLEAN_LITERAL_EXPRESSION:    
    case INT_LITERAL_EXPRESSION:        
    case DOUBLE_LITERAL_EXPRESSION:     
    case STRING_LITERAL_EXPRESSION:
    default:
        break;
    }
}

static
void walk_expression_statement(Statement *stat) {
    gen_code_of_expression(stat->u.expr);
}

static
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
        case RETURN_STATEMENT:
            break;
        case TRY_STATEMENT:
            break;
        case THROW_STATEMENT:
            break;
        case BREAK_STATEMENT:
            break;
        case CONTINUE_STATEMENT:
            break;
        case DECLARATION_STATEMENT:
            break;    
        default:
            break;
        }
    }
}

static 
void walk_block(Block *block) {
    walk_statement_list(block->stat_list);
}

static
void gen_code_segment(Executable *exe) {
    Compiler *comp = get_current_compiler();
    FunctionDefinition *fd_p;
    int i = 0;

    exe->code_seg->arr = (Function*)MEM_malloc(comp->function_list->len * sizeof(Function));
    for(fd_p=comp->function_list->phead; fd_p; fd_p=fd_p->next) {
        // copy_function(fd_p, &exe->code_seg->arr[i]);
        
        Function *f = &exe->code_seg->arr[i];
        if(fd_p->block != NULL) {
            reset_code_buf();
            reset_linenum_buf();
            walk_block(fd_p->block);
            f->codes = codebuf.codes;
            f->code_size = codebuf.size;
            f->line_numbers = linenum_buf.arr;
            f->line_number_size = linenum_buf.size;
        } else {

        }
    }
}

void gen_top_codes(Executable *exe) {

}

Executable* alloc_excutable() {
    Executable *exe;

    exe = (Executable*)MEM_malloc(sizeof(Executable));

    exe->constant_seg = (ConstantSegment*)MEM_malloc(sizeof(ConstantSegment));
    exe->constant_seg->arr = NULL, exe->constant_seg->size = 0;

    exe->data_seg = (DataSegment*)MEM_malloc(sizeof(DataSegment));
    exe->data_seg->arr = NULL, exe->data_seg->size = 0;
    
    exe->code_seg = (CodeSegment*)MEM_malloc(sizeof(CodeSegment));
    exe->code_seg->arr = NULL, exe->code_seg->size = 0;

    exe->line_numbers = NULL;
    exe->line_number_size = 0;

    exe->stk_sz_needed = 0;

    return exe;
}

Executable* walk_ast_for_gen_exe() {
    Compiler *comp;
    Executable *exe;

    comp = get_current_compiler();
    exe = alloc_excutable();
    gen_constant_segment(exe);
    gen_data_segment(exe);
    gen_top_codes(exe);
    gen_code_segment(exe);

    return exe;
}