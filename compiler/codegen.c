#include <stdarg.h>
#include <string.h>
#include "decls.h"
#include "../include/exe.h"


#define CODEBUF_ALLOC_SIZE (256)
#define LINENUM_BUF_ALLOC_SIZE (256)

extern OpcodeInfo opcode_info[];

static void walk_statement_list(StatementList *stat_list, Executable *exe);
static void gen_code_of_expression(Expression *expr, Executable *exe);

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

/*
    start_i is the start index of backpacked codes.
    jump_i is the destination pc of 'start_i' codes.

    We regulate the operand size to fixed 2 byte for 'jump' family opcode.
*/
void backpack(int start_i, int jump_i) {
    codebuf.codes[start_i + 1] = (jump_i >> 8) & 0xff;
    codebuf.codes[start_i + 2] = jump_i & 0xff;
}

int get_pc() {
    return codebuf.size;
}

static
int emit(OpCodeTag opcode, ...) {
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
    case 'd':    
    case 's':
    case 'p':
        operand_sz = 2;
        break;
    case 'a':
        operand_sz = 3;
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
        case 'd':   /* Fallthrough */ 
        case 's':   /* Fallthrough */
        case 'p':
            codebuf.codes[codebuf.size ++] = (Byte)(operand >> 8 & 0xff);
            codebuf.codes[codebuf.size ++] = (Byte)(operand & 0xff);
            break;
        case 'a':
            codebuf.codes[codebuf.size ++] = (Byte)(operand & 0xff);
            operand = va_arg(args, int); /* 'a' means two operands. */
            codebuf.codes[codebuf.size ++] = (Byte)(operand >> 8 & 0xff);
            codebuf.codes[codebuf.size ++] = (Byte)(operand & 0xff);
            break;
        default:
            break;
        }
    }
    
    // if(linenum_buf.arr == NULL ||
    //     linenum_buf.arr[linenum_buf.size - 1].num != linenum) 
    // {
    //     if(linenum_buf.size >= linenum_buf.cap) {
    //         linenum_buf.cap += LINENUM_BUF_ALLOC_SIZE;
    //         linenum_buf.arr = (LineNumber*)MEM_realloc(linenum_buf.arr, linenum_buf.cap * sizeof(LineNumber));
    //     }
    //     LineNumber *newl = &linenum_buf.arr[linenum_buf.size ++];
    //     newl->num = linenum;
    //     newl->start_pc = start_pc;
    //     newl->last_pc = codebuf.size - 1;
    // } else {
    //     LineNumber *curl = &linenum_buf.arr[linenum_buf.size - 1];
    //     curl->last_pc = codebuf.size - 1;
    // }

    va_end(args);

    return start_pc;
}

static
int add_constant_to_pool(Constant *cons, Executable *exe) {
    exe->constant_seg->size ++;
    exe->constant_seg->arr = (Constant*)MEM_realloc(exe->constant_seg->arr, exe->constant_seg->size * sizeof(Constant));
    exe->constant_seg->arr[exe->constant_seg->size - 1] = *cons;

    return exe->constant_seg->size - 1;
}

static
int basictype_offset(ValueType basic_type) {

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
    case NULL_TYPE:
    case UNDETERMIEND:
    default:
        break;
    }

    return 0;
}

/* For code convenience. */
static 
int type_offset(TypeSpecifier *ts)
{
    if(ts->derive_list_header_p != NULL) {
        return 2;
    }

    switch (ts->basic_type) {
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
    case NULL_TYPE:
    case UNDETERMIEND:
    default:
        break;
    }

    return 0;
}

static 
void pop_to_identifier(Identifier *ident) {
    int is_local;
    TypeSpecifier *type;
    int index;
    is_local = ident->decl->u.declaration_stat.is_local;
    type = ident->decl->u.declaration_stat.type;
    index = ident->decl->u.declaration_stat.index;
    if(is_local) {
        emit(POP_STACK_INT + type_offset(type), index);
    } else {
        emit(POP_STATIC_INT + type_offset(type), index);
    }
}

static
void pop_to_index_expression(Expression *expr) {
    emit(POP_ARRAY_INT + type_offset(expr->type));
}

static 
void pop_to_lvalue(Expression *lvalue) {
    if(lvalue->kind == IDENTIFIER_EXPRESSION) {
        pop_to_identifier(lvalue->ident);
    } else if(lvalue->kind == INDEX_EXPRESSION) {
        pop_to_index_expression(lvalue);
    } else {
        printf("pop_to_lvalue:not lvalue\n");
        exit(1);
    }
}

void gen_code_of_identifier_expression(Expression *expr) {

    if(expr->ident->is_func) {
        emit(PUSH_FUNCTION, expr->ident->func_def->index);
        return;
    }

    Statement *stat = expr->ident->decl;
    if(stat->u.declaration_stat.is_local) {
        emit(PUSH_STACK_INT + type_offset(expr->type), stat->u.declaration_stat.index);
    } else {
        emit(PUSH_STATIC_INT + type_offset(expr->type), stat->u.declaration_stat.index);
    }
}

void gen_code_of_cast_expression(Expression *expr, Executable *exe) {
    gen_code_of_expression(expr->cast_expr.casted_expr, exe);
    switch (expr->cast_expr.type)
    {
    case INT_TO_DOUBLE:
        emit(CAST_INT_TO_DOUBLE_OP);
        break;
    case DOUBLE_TO_INT:
        emit(CAST_DOUBLE_TO_INT_OP);
        break;
    case BOOLEAN_TO_STRING:
        emit(CAST_BOOLEAN_TO_STRING_OP);
        break;
    case INT_TO_STRING:
        emit(CAST_INT_TO_STRING_OP);
        break;
    case DOUBLE_TO_STRING:
        emit(CAST_DOUBLE_TO_STRING_OP);
        break;
    case BOOLEAN_TO_INT:
    case BOOLEAN_TO_DOUBLE:
    case INT_TO_BOOLEAN:
    case DOUBLE_TO_BOOLEAN:
    case STRING_TO_BOOLEAN:
    case STRING_TO_INT:
    case STRING_TO_DOUBLE:
    case UNKNOWN: 
    default:
        break;
    }
}

static
void gen_code_of_expression(Expression *expr, Executable *exe) {
    int backpack_i; /* the start index of codes which need to backpack. */
    Argument *arg;

    switch (expr->kind)
    {
    case NORMAL_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;
    case ADD_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(ADD_INT + type_offset(expr->type));
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;
    case SUB_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(SUB_INT + type_offset(expr->type));
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;
    case MUL_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(MUL_INT + type_offset(expr->type));
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;
    case DIV_ASSIGN_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(DIV_INT + type_offset(expr->type));
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;
    case MOD_ASSIGN_EXPRESSION: 
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(MOD_INT + type_offset(expr->type));
        emit(DUPLICATE);
        if(expr->binary_expr.left->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->binary_expr.left->index_expr.array, exe);
            gen_code_of_expression(expr->binary_expr.left->index_expr.index, exe);
        }
        pop_to_lvalue(expr->binary_expr.left);
        break;        
    case ARITH_ADDITIVE_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(ADD_INT + type_offset(expr->type));
        break;
    case ARITH_SUBSTRACTION_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(SUB_INT + type_offset(expr->type));
        break;
    case ARITH_MULTIPLICATION_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(MUL_INT + type_offset(expr->type));
        break;
    case ARITH_DIVISION_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(DIV_INT + type_offset(expr->type));
        break;
    case ARITH_MODULO_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(MOD_INT + type_offset(expr->type));
        break;    
    case RELATION_EQ_EXPRESSION: 
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(EQ_INT + type_offset(expr->type));
        break;        
    case RELATION_NE_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(NE_INT + type_offset(expr->type));
        break;
    case RELATION_GT_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(GT_INT + type_offset(expr->type));
        break;
    case RELATION_LT_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(LT_INT + type_offset(expr->type));
        break;
    case RELATION_GE_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(GE_INT + type_offset(expr->type));
        break;
    case RELATION_LE_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(LE_INT + type_offset(expr->type));
        break;
    case LOGICAL_AND_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        emit(DUPLICATE);
        backpack_i = emit(JUMP_IF_FALSE, 0);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(LOGICAL_AND_OP);
        backpack(backpack_i, codebuf.size);
        break;
    case LOGICAL_OR_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        emit(DUPLICATE);
        backpack_i = emit(JUMP_IF_TRUE, 0);
        gen_code_of_expression(expr->binary_expr.right, exe);
        emit(LOGICAL_OR_OP);
        backpack(backpack_i, get_pc());
        break;
    case LOGICAL_NOT_EXPRESSION:
        gen_code_of_expression(expr->unary_operand, exe);
        emit(LOGICAL_NOT_OP);
        break;
    case MINUS_EXPRESSION:
        gen_code_of_expression(expr->unary_operand, exe);
        emit(MINUS_INT  + type_offset(expr->type));
        break;
    case FUNC_CALL_EXPRESSION:
        if(expr->function_call_expr.arg_list != NULL) {
            for(arg = expr->function_call_expr.arg_list->phead; arg; arg=arg->next) {
                gen_code_of_expression(arg->expr, exe);
            }
        }
        gen_code_of_expression(expr->function_call_expr.callee, exe);
        emit(INVOKE);
        break;
    case IDENTIFIER_EXPRESSION:
        gen_code_of_identifier_expression(expr);
        break;
    case ARRAY_LITERAL_EXPRESSION:
    {
        ExpressionListNode *enode;
        int i = 0;
        for(enode=expr->array_literal_expr; enode; enode=enode->next) {
            gen_code_of_expression(enode->expr, exe);
            i ++;
        }
        if(expr->type->derive_list_header_p->next != NULL) {
            emit(NEW_ARRAY_LITERAL_OBJECT, i);
        } else {
            emit(NEW_ARRAY_LITERAL_INT + basictype_offset(expr->type->basic_type), i);
        }
        break;
    }
    case ARRAY_CREATION_EXPRESSION:
    {
        ExpressionListNode *enode;
        int typ_idx = expr->array_creation_expr.basic_type;
        int dim_cnt = 0;
        for(enode=expr->array_creation_expr.dimension_list_header_p; enode; enode=enode->next) {
            gen_code_of_expression(enode->expr, exe);
            dim_cnt ++;
        }
        emit(NEW_ARRAY_OP, dim_cnt, typ_idx);
        break;
    }
    case INDEX_EXPRESSION:
    {
        gen_code_of_expression(expr->index_expr.array, exe);
        gen_code_of_expression(expr->index_expr.index, exe);
        if(expr->index_expr.array->type->derive_list_header_p->next == NULL) {
            emit(PUSH_ARRAY_INT + basictype_offset(expr->index_expr.array->type->basic_type));
        } else {
            emit(PUSH_ARRAY_OBJECT);
        }
        break;
    }
    case COMMA_EXPRESSION:
        gen_code_of_expression(expr->binary_expr.left, exe);
        emit(POP_OP);
        gen_code_of_expression(expr->binary_expr.right, exe);
        break;
    case POST_INCREMENT_EXPRESSION:
        gen_code_of_expression(expr->unary_operand, exe);
        emit(DUPLICATE);
        emit(PUSH_INT_1BYTE, 1);
        emit(ADD_INT);
        if(expr->unary_operand->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->unary_operand, exe);
        }
        pop_to_lvalue(expr->unary_operand);
        break;
    case POST_DECREMENT_EXPRESSION:
        gen_code_of_expression(expr->unary_operand, exe);
        emit(DUPLICATE);
        emit(PUSH_INT_1BYTE, 1);
        emit(SUB_INT);
        if(expr->unary_operand->kind == INDEX_EXPRESSION) {
            gen_code_of_expression(expr->unary_operand, exe);
        }
        pop_to_lvalue(expr->unary_operand);
        break;
    case CAST_EXPRESSION:
        gen_code_of_cast_expression(expr, exe);
        break;
    case BOOLEAN_LITERAL_EXPRESSION:
        if(expr->boolean_v == 1) {
            emit(PUSH_INT_1BYTE, 1);
        } else {
            emit(PUSH_INT_1BYTE, 0);
        }
        break;
    case INT_LITERAL_EXPRESSION:
        if(expr->int_v >= 0 && expr->int_v <= 255) {
            emit(PUSH_INT_1BYTE, expr->int_v);
        } else if(expr->int_v >= 256 && expr->int_v <= 65535) {
            emit(PUSH_INT_2BYTE, expr->int_v);
        } else {
            Constant *cons = (Constant*)MEM_malloc(sizeof(Constant));
            cons->tag = INT_CONSTANT;
            cons->int_constant = expr->int_v;
            int idx = add_constant_to_pool(cons, exe);
            emit(PUSH_INT, idx);
            MEM_free(cons);
        }
        break;
    case DOUBLE_LITERAL_EXPRESSION:
        if(expr->double_v == 0) {
            emit(PUSH_DOUBLE_0);
        } else if(expr->double_v == 1) {
            emit(PUSH_DOUBLE_1);
        } else {
            Constant *cons = (Constant*)MEM_malloc(sizeof(Constant));
            cons->tag = DOUBLE_CONSTANT;
            cons->double_constant = expr->double_v;
            int idx = add_constant_to_pool(cons, exe);
            emit(PUSH_DOUBLE, idx);
            MEM_free(cons);
        }
        break;
    case STRING_LITERAL_EXPRESSION:
        {
            Constant *cons = (Constant*)MEM_malloc(sizeof(Constant));
            cons->tag = STRING_CONSTANT;
            cons->string_constant = expr->string_v;
            int idx = add_constant_to_pool(cons, exe);
            emit(PUSH_STRING, idx);
            MEM_free(cons);
            break;
        }
    default:
        break;
    }
}

static 
void walk_block(Block *block, Executable *exe) {
    /* enter a block */
    block->outer_block = get_current_compiler()->current_block;
    get_current_compiler()->current_block = block;

    walk_statement_list(block->declaration_stat_list, exe);
    walk_statement_list(block->stat_list, exe);

    /* leaver the block */
    get_current_compiler()->current_block = get_current_compiler()->current_block->outer_block;
}

static
void walk_statement_list(StatementList *stat_list, Executable *exe) {
    Statement *stat;
    int backpack_i; /* the start index of codes which need to backpack. */

    for(stat=stat_list->phead; stat; stat = stat->next) {
        switch (stat->kind)
        {
        case EXPRESSION_STATEMENT:
            gen_code_of_expression(stat->u.expr, exe);
            emit(POP_OP);
            break;
        case FOR_STATEMENT:
        {
            BackPackPoint *bp;

            /* init */
            gen_code_of_expression(stat->u.for_stat.init_expr, exe);
            emit(POP_OP);
            /* cond */
            stat->u.for_stat.continue_pc = get_pc();
            gen_code_of_expression(stat->u.for_stat.cond_expr, exe);
            backpack_i = emit(JUMP_IF_FALSE, 0);
            /* block */
            walk_block(stat->u.for_stat.block, exe);
            /* post */
            gen_code_of_expression(stat->u.for_stat.post_expr, exe);
            emit(JUMP, stat->u.for_stat.continue_pc);

            backpack(backpack_i, get_pc());
            for(bp = stat->u.for_stat.backpack_points; bp; bp=bp->next) {
                backpack(bp->address, get_pc());
            }
            break;
        }
        case WHILE_STATEMENT:
        {
            BackPackPoint *bp;

            stat->u.while_stat.continue_pc = get_pc();
            gen_code_of_expression(stat->u.while_stat.cond_expr, exe);
            backpack_i = emit(JUMP_IF_FALSE, 0);
            walk_block(stat->u.while_stat.block, exe);
            emit(JUMP, stat->u.while_stat.continue_pc);

            backpack(backpack_i, get_pc());
            for(bp = stat->u.while_stat.backpack_points; bp; bp=bp->next) {
                backpack(bp->address, get_pc());
            }
            break;
        }
        case FOREACH_STATEMENT:
            break;
        case IF_STATEMENT:
        {
            gen_code_of_expression(stat->u.if_stat.cond, exe);
            backpack_i = emit(JUMP_IF_FALSE, 0);
            walk_block(stat->u.if_stat.then_block, exe);
            backpack(backpack_i, get_pc());
            if(stat->u.if_stat.elif_list != NULL) {
                Elif *e = stat->u.if_stat.elif_list;
                while(e != NULL) {
                    gen_code_of_expression(e->cond, exe);
                    backpack_i = emit(JUMP_IF_FALSE, 0);
                    walk_block(e->block, exe);
                    backpack(backpack_i, get_pc());
                    e = e->next;
                }
            }
            if(stat->u.if_stat.else_block != NULL) {
               walk_block(stat->u.if_stat.else_block, exe);
            }
            break;
        }
        case RETURN_STATEMENT:
        {
            if(stat->u.return_stat.ret_expr != NULL) {
                gen_code_of_expression(stat->u.return_stat.ret_expr, exe);
            }
            emit(RETURN);
            break;
        }
        case TRY_STATEMENT:
            break;
        case THROW_STATEMENT:
            break;
        case BREAK_STATEMENT:
        {
            Block *b = get_current_compiler()->current_block;
            if(stat->u.break_stat.label == NULL) {
                while(b) {
                    BackPackPoint *bp;
                    if(b->type == WHILE_STATEMENT_BLOCK) {
                        backpack_i = emit(JUMP, 0);
                        bp = (BackPackPoint*)MEM_malloc(sizeof(BackPackPoint));
                        bp->address = backpack_i;
                        bp->next = b->stat->u.while_stat.backpack_points;
                        b->stat->u.while_stat.backpack_points = bp;
                        break;
                    } else if(b->type == FOR_STATEMENT_BLOCK) {
                        backpack_i = emit(JUMP, 0);
                        bp = (BackPackPoint*)MEM_malloc(sizeof(BackPackPoint));
                        bp->address = backpack_i;
                        bp->next = b->stat->u.for_stat.backpack_points;
                        b->stat->u.for_stat.backpack_points = bp;
                        break;
                    }
                    b = b->outer_block;
                }
            } else {
                while(b) {
                    BackPackPoint *bp;
                    if(b->type == WHILE_STATEMENT_BLOCK && b->stat->u.while_stat.label != NULL) {
                        if(strcmp(b->stat->u.while_stat.label->name, stat->u.break_stat.label->name) == 0) {
                            backpack_i = emit(JUMP, 0);
                            bp = (BackPackPoint*)MEM_malloc(sizeof(BackPackPoint));
                            bp->address = backpack_i;
                            bp->next = stat->u.while_stat.backpack_points;
                            stat->u.while_stat.backpack_points = bp;
                            break;
                        }
                    } else if(b->type == FOR_STATEMENT_BLOCK && b->stat->u.for_stat.label != NULL) {
                        if(strcmp(b->stat->u.for_stat.label->name, stat->u.break_stat.label->name) == 0) {
                            backpack_i = emit(JUMP, 0);
                            bp = (BackPackPoint*)MEM_malloc(sizeof(BackPackPoint));
                            bp->address = backpack_i;
                            bp->next = stat->u.for_stat.backpack_points;
                            stat->u.for_stat.backpack_points = bp;
                            break;
                        }
                    }
                    b = b->outer_block;
                }
            }
            break;
        }
        case CONTINUE_STATEMENT:
        {
            Block *b = get_current_compiler()->current_block;
            if(stat->u.continue_stat.label == NULL) {
                while(b) {
                    if(b->type == WHILE_STATEMENT_BLOCK) {
                        backpack_i = emit(JUMP, b->stat->u.while_stat.continue_pc);
                        break;
                    } else if(b->type == FOR_STATEMENT_BLOCK) {
                        backpack_i = emit(JUMP, b->stat->u.for_stat.continue_pc);
                        break;
                    }
                    b = b->outer_block;
                }
            } else {
                while(b) {
                    if(b->type == WHILE_STATEMENT_BLOCK && b->stat->u.while_stat.label != NULL) {
                        if(strcmp(b->stat->u.while_stat.label->name, stat->u.break_stat.label->name) == 0) {
                            backpack_i = emit(JUMP, b->stat->u.while_stat.continue_pc);
                            break;
                        }
                    } else if(b->type == FOR_STATEMENT_BLOCK && b->stat->u.for_stat.label != NULL) {
                        if(strcmp(b->stat->u.for_stat.label->name, stat->u.break_stat.label->name) == 0) {
                            backpack_i = emit(JUMP, b->stat->u.for_stat.continue_pc);
                            break;
                        }
                    }
                    b = b->outer_block;
                }
            }
            break;
        }
        case DECLARATION_STATEMENT:
            if(stat->u.declaration_stat.initializer != NULL) {
                gen_code_of_expression(stat->u.declaration_stat.initializer, exe);
                pop_to_identifier(stat->u.declaration_stat.ident);
            }
            break;    
        default:
            break;
        }
    }
}

static 
void copy_function_definition(FunctionDefinition *fd, Function *f) {
    Statement *stat;
    Parameter *para;

    f->type = fd->type;
    f->name = fd->ident->name;

    /* copy parameters */
    if(fd->param_list->len > 0) {
        f->para_cnt = fd->param_list->len;
        f->paras = MEM_malloc(sizeof(Variable) * f->para_cnt);
        int i = 0;
        for(para=fd->param_list->phead; para; para=para->next, i++) {
            f->paras[i].name = para->ident->name;
            f->paras[i].type = para->type;
        }
    } else {
        f->para_cnt = 0;
        f->paras = NULL;
    }

    /* copy local variables info */
    f->local_var_cnt = fd->local_variable_cnt;
    f->local_vars = MEM_malloc(sizeof(Variable) * f->local_var_cnt);
    for(int i = 0; i < fd->local_variable_cnt; i ++) {
        stat = fd->local_variables[i];
        f->local_vars[i].name = stat->u.declaration_stat.ident->name;
        f->local_vars[i].type = stat->u.declaration_stat.type;
    }
}

int calc_stk_size_needed(Byte *codes, int code_size) {
    int pc;
    OpcodeInfo *opinfo;
    Byte opcode;
    int s;

    s = 0;
    pc = 0;
    while(pc < code_size) {
        opcode = codes[pc ++];
        opinfo = &opcode_info[opcode];
        if(opinfo->stk_sz_needed > 0) {
            s += opinfo->stk_sz_needed;
        }
        switch (opinfo->para[0])
        {
        case 'b':
            pc += 1;
            break;
        case 'd':
        case 's':
        case 'p':
            pc += 2;
            break;
        default:
            break;
        }
    }

    return s;
}

static
void gen_code_segment(Executable *exe) {
    Compiler *comp = get_current_compiler();
    FunctionDefinition *fd_p;
    int i = 0;

    exe->code_seg->size = comp->function_list->len;
    exe->code_seg->arr = (Function*)MEM_malloc(exe->code_seg->size * sizeof(Function));

    for(fd_p=comp->function_list->phead; fd_p; fd_p=fd_p->next) {
        Function *f = &exe->code_seg->arr[i ++];

        copy_function_definition(fd_p, f);
        
        if(fd_p->block != NULL) {
            reset_code_buf();
            reset_linenum_buf();
            walk_block(fd_p->block, exe);

            f->codes = (Byte*)MEM_malloc(sizeof(Byte) * codebuf.size);
            memcpy(f->codes, codebuf.codes, codebuf.size);
            f->code_size = codebuf.size;
            f->stk_sz_needed = calc_stk_size_needed(f->codes, f->code_size);
            f->is_implemented = 1;
            // f->line_numbers = linenum_buf.arr;
            // f->line_number_size = linenum_buf.size;
        } else {
            f->is_implemented = 0;
        }
    }
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

    exe->top_code_size = 0;
    exe->top_codes = NULL;

    exe->line_numbers = NULL;
    exe->line_number_size = 0;

    exe->stk_sz_needed = 0;

    return exe;
}

static
void gen_data_segment(Executable *exe) {
    Compiler *comp;
    Statement *stat;
    Variable *var;
    int i;

    comp = get_current_compiler();
    exe->data_seg->size = comp->declaration_stat_list->len;
    exe->data_seg->arr = (Variable*)MEM_malloc(sizeof(Variable) * exe->data_seg->size);
    i = 0;
    for(stat=comp->declaration_stat_list->phead; stat; stat=stat->next) {
        var = &exe->data_seg->arr[i ++];
        var->type = stat->u.declaration_stat.type;
        var->name = stat->u.declaration_stat.ident->name;
    }
}

static
void gen_top_codes(Executable *exe) {
    Compiler *comp;

    comp = get_current_compiler();
    reset_code_buf();
    reset_linenum_buf();
    walk_statement_list(comp->declaration_stat_list, exe);
    walk_statement_list(comp->statement_list, exe);
    exe->top_code_size = codebuf.size;
    exe->top_codes = (Byte*)MEM_malloc(sizeof(Byte) * exe->top_code_size);
    memcpy(exe->top_codes, codebuf.codes, codebuf.size);
    exe->stk_sz_needed = calc_stk_size_needed(exe->top_codes, exe->top_code_size);
}

/*
    After semantic analysis, all statement'semantic is right, and information in symbol table is completed.
    So in code generation step, just utilizing symbol table, walk ast to generate code.
*/
Executable* walk_ast_for_gen_exe() {
    Executable *exe;

    exe = alloc_excutable();
    /*
        Do not need this, generate constant segment during walk ast.
        Specifically, each time walking literal expression, alloc a constant to constant pool.
    */
    // gen_constant_segment(exe); 
    gen_data_segment(exe);
    gen_top_codes(exe);
    gen_code_segment(exe);
    
    return exe;
}

/*  The core idea is [walk_statement_list()] and [gen_code_of_expression()]. 
    We stand at the statement level[walk_statement_list()]. 
    We just consider how generate code for each kind of statement(EXPRESSION_STATEMENT, IF_STATEMENT ...)[gen_code_of_expression()].
    So we walk each statement[walk_statement_list()], and generate correct code for the statement we walk to.
    For example, if we walk to expression statement, we just need to generate code for it's(the statement) expression[gen_code_of_expression()].
*/