#include <string.h>
#include "decls.h"
#include "../include/MEM.h"

#define PUSH_INT(v) (vm.stack.arr[vm.stack.top].int_v = v, vm.stack.arr[vm.stack.top].kind = INT_VALUE, vm.stack.top ++)
#define PUSH_DOUBLE(v) (vm.stack.arr[vm.stack.top].double_v = v, vm.stack.arr[vm.stack.top].kind = DOUBLE_VALUE, vm.stack.top ++)
#define PUSH_OBJECT(obj) (vm.stack.arr[vm.stack.top].object = obj, vm.stack.arr[vm.stack.top].kind = OBJECT_VALUE, vm.stack.top ++)
#define PUSH_CALLER_INFO(caller_info) (vm.stack.arr[vm.stack.top].caller_info = caller_info, vm.stack.arr[vm.stack.top].kind = CALLER_INFO_VALUE, vm.stack.top ++)
#define PUSH_VALUE(val) (vm.stack.arr[vm.stack.top ++] = val)

#define POP_INT()    (vm.stack.top --, vm.stack.arr[vm.stack.top].int_v)
#define POP_DOUBLE() (vm.stack.top --, vm.stack.arr[vm.stack.top].double_v)
#define POP_OBJECT() (vm.stack.top --, vm.stack.arr[vm.stack.top].object)

#define GET_1_BYTE(codes, pc) (codes[pc ++] & 0xff)
#define GET_2_BYTE(codes, pc) (((codes[pc ++] >> 8) & 0xff) + (codes[pc ++] & 0xff))

extern OpcodeInfo opcode_info[];

extern int native_func_count;
extern NativeFunction *native_funcs[];
extern char *native_func_names[];

VirtualMachine vm;

static Object null_string_object = {
    .type = STRING_OBJECT,
    .marked = 0,
    .string = "",
    .next = NULL,
    .prev = NULL,
};

void print_array_object(Object *arr) {
    for(int i = 0; i < arr->array.size; i ++) {
        if(arr->array.tag == INT_ARRAY) {
            printf("%d,", arr->array.int_arr[i]);
        } else if(arr->array.tag == DOUBLE_ARRAY) {
            printf("%lf,", arr->array.double_arr[i]);
        } else if(arr->array.tag == OBJECT_ARRAY) {
            printf("%s,", arr->array.obj_arr[i]->string);
        }
    }
    puts("");
}

void print_string_object(Object *str) {
    char *s = str->string;
    for(int i = 0; s[i]; i ++) {
        if(s[i] == '\n') printf("\\n");
        else if(s[i] == '\t') printf("\\t");
        else if(s[i] == ' ') printf("<BLANKSPACE>");
        else printf("%c", s[i]);
    }
    puts("");
}

void print_stack(char *mnemonic) {
    int t = vm.stack.top;
    puts("^^^^^^^^^");
    printf("%s:\n", mnemonic);
    while(t --) {
        Value *v = &vm.stack.arr[t];
        switch (v->kind)
        {
        case UNKNOWN_VALUE:
            break;
        case INT_VALUE:
        {
            printf("%d\n", v->int_v);
            break;
        }
        case DOUBLE_VALUE:
        {
            printf("%lf\n", v->double_v);
            break;
        }
        case OBJECT_VALUE:
        {
            if(v->object->type == STRING_OBJECT)
                print_string_object(v->object);
            else if(v->object->type == ARRAY_OBJECT)
                print_array_object(v->object);
            break;
        }
        case CALLER_INFO_VALUE:
        {
            printf("pc:%d, bp:%d, caller_name:%s\n", 
                v->caller_info->pc, 
                v->caller_info->stk_base, 
                v->caller_info->func != NULL ? v->caller_info->func->name : "top-level"
            );
            break;
        }        
        default:
            break;
        }
    }
}

void expand_stack(int grow_size) {
    vm.stack.size = vm.stack.size + grow_size;
    vm.stack.arr = (Value*)MEM_realloc(vm.stack.arr, sizeof(Value) * vm.stack.size);
    
}

Object* alloc_string_object(char *str) {
    Object *str_obj;

    str_obj = (Object*)MEM_malloc(sizeof(Object));
    str_obj->type = STRING_OBJECT;
    str_obj->string = str;
    str_obj->next = NULL;
    str_obj->prev = NULL;
    str_obj->marked = 0;

    return str_obj;
}

/*
state:
    Byte        *codes;
    int         code_size;
    int         pc;
    int         top;
    int         base;
    Function    *cur_func;
    
*/
void Execute() {
    Byte        *codes;
    int         code_size;
    int         pc;
    int         base;
    Function    *cur_func;
    OpcodeInfo  opinfo;

    int operand;

    expand_stack(vm.exe->stk_sz_needed);
    codes = vm.exe->top_codes;
    code_size = vm.exe->top_code_size;
    pc = 0;
    base = 0;
    cur_func = NULL;
    while(pc < code_size) {
        Byte opcode = codes[pc ++];
        opinfo = opcode_info[opcode];
        switch (opcode)
        {
        case PUSH_INT_1BYTE: /* ok */
        {
            operand = GET_1_BYTE(codes, pc);
            PUSH_INT(operand);
            break;
        }
        case PUSH_INT_2BYTE: /* ok */
        {
            operand = GET_2_BYTE(codes, pc);
            PUSH_INT(operand);
            break;
        }
        case PUSH_INT: /* ok */                         
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_INT(vm.exe->constant_seg->arr[idx].int_constant);
            break;
        }
        case PUSH_DOUBLE_0: /* ok */
        {
            PUSH_DOUBLE(0.0);                
            break;
        }
        case PUSH_DOUBLE_1: /* ok */
        {
            PUSH_DOUBLE(1.0);
            break;
        }
        case PUSH_DOUBLE: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_DOUBLE(vm.exe->constant_seg->arr[idx].double_constant);
            break;
        }
        case PUSH_STRING: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            Object *str_obj = alloc_string_object(vm.exe->constant_seg->arr[idx].string_constant);
            PUSH_OBJECT(str_obj);
            break;
        }
        case PUSH_STACK_INT: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_INT(vm.stack.arr[base + idx].int_v);
            break;
        }
        case PUSH_STACK_DOUBLE: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_DOUBLE(vm.stack.arr[base + idx].double_v);
            break;
        }
        case PUSH_STACK_OBJECT: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_OBJECT(vm.stack.arr[base + idx].object);
            break;
        }
        case POP_STACK_INT: /* ok */
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.stack.arr[base + idx].int_v = POP_INT();
            break;
        }
        case POP_STACK_DOUBLE:
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.stack.arr[base + idx].double_v = POP_DOUBLE();
            break;
        }
        case POP_STACK_OBJECT:
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.stack.arr[base + idx].object = POP_OBJECT();
            break;
        }
        case PUSH_STATIC_INT:
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_INT(vm.static_data.arr[idx].int_v);
            break;
        }
        case PUSH_STATIC_DOUBLE:
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_DOUBLE(vm.static_data.arr[idx].double_v);
            break;
        }
        case PUSH_STATIC_OBJECT:
        {
            int idx = GET_2_BYTE(codes, pc);
            PUSH_OBJECT(vm.static_data.arr[idx].object);
            break;
        }
        case POP_STATIC_INT:
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.static_data.arr[idx].int_v = POP_INT();
            break;
        }
        case POP_STATIC_DOUBLE:
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.static_data.arr[idx].double_v = POP_DOUBLE();
            break;
        }
        case POP_STATIC_OBJECT:
        {
            int idx = GET_2_BYTE(codes, pc);
            vm.static_data.arr[idx].object = POP_OBJECT();
            break;
        }
        case ADD_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l + r);
            break;
        }
        case ADD_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l + r);
            break;
        }
        case ADD_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            int llen = strlen(l->string);
            int rlen = strlen(r->string);
            Object *new_s = alloc_string_object(NULL);
            new_s->type = STRING_OBJECT;
            new_s->string = (char*)MEM_realloc(l->string, llen + rlen + 1);
            strncat(new_s->string, r->string, rlen + 1);
            PUSH_OBJECT(new_s);
            break;
        }
        case SUB_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l - r);
            break;
        }
        case SUB_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l - r);
            break;
        }
        case MUL_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l * r);
            break;
        }
        case MUL_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l * r);
            break;
        }
        case DIV_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l / r);
            break;
        }
        case DIV_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l / r);
            break;
        }
        case MOD_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l % r);
            break;
        }
        case MOD_DOUBLE:
        {
            break;
        }
        case MINUS_INT:
        {
            int v = POP_INT();
            PUSH_INT(-v);
            break;
        }
        case MINUS_DOUBLE:
        {
            double v = POP_DOUBLE();
            PUSH_DOUBLE(-v);
            break;
        }
        case INCREMENT_OP:
        {
            break;
        }
        case DECREMENT_OP:
        {
            break;
        }
        case CAST_INT_TO_DOUBLE_OP:
        {
            int v = POP_INT();
            PUSH_DOUBLE(v);
            break;
        }
        case CAST_DOUBLE_TO_INT_OP:
        {
            double v = POP_DOUBLE();
            PUSH_INT((int)v);
            break;
        }
        case CAST_BOOLEAN_TO_STRING_OP:
        {
            int b = POP_INT();
            Object *str_obj = alloc_string_object(NULL);
            if(b == 0) {
                str_obj->string = "false";
            } else {
                str_obj->string = "true";
            }
            PUSH_OBJECT(str_obj);
            break;
        }
        case CAST_INT_TO_STRING_OP:
        {
            
            int v = POP_INT();
            Object *str_obj = alloc_string_object(NULL);
            str_obj->string = MEM_malloc(11);
            sprintf(str_obj->string, "%d", v);
            PUSH_OBJECT(str_obj);
            break;
        }
        case CAST_DOUBLE_TO_STRING_OP:
        {
            double v = POP_DOUBLE();
            Object *str_obj = alloc_string_object(NULL);
            str_obj->string = MEM_malloc(50);
            sprintf(str_obj->string, "%lf", v);
            PUSH_OBJECT(str_obj);
            break;
        }
        case EQ_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l == r);
            break;
        }
        case EQ_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l == r);
            break;
        }
        case EQ_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) == 0 ? 1 : 0);
            break;
        }
        case GT_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l > r);
            break;
        }
        case GT_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l > r);
            break;
        }
        case GT_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) > 0 ? 1 : 0);
            break;
        }
        case GE_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l >= r);
            break;
        }
        case GE_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l >= r);
            break;
        }
        case GE_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) >= 0 ? 1 : 0);
            break;
        }
        case LT_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l < r);
            break;
        }
        case LT_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l < r);
            break;
        }
        case LT_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) < 0 ? 1 : 0);
            break;
        }
        case LE_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l <= r);
            break;
        }
        case LE_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l <= r);
            break;
        }
        case LE_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) <= 0 ? 1 : 0);
            break;
        }
        case NE_INT:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l != r);
            break;
        }
        case NE_DOUBLE:
        {
            double r = POP_DOUBLE();
            double l = POP_DOUBLE();
            PUSH_DOUBLE(l != r);
            break;
        }
        case NE_STRING:
        {
            Object *r = POP_OBJECT();
            Object *l = POP_OBJECT();
            PUSH_INT(strcmp(l->string, r->string) != 0 ? 1 : 0);
            break;
        }
        case LOGICAL_AND_OP:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l && r);
            break;
        }
        case LOGICAL_OR_OP:
        {
            int r = POP_INT();
            int l = POP_INT();
            PUSH_INT(l || r);
            break;
        }
        case LOGICAL_NOT_OP:
        {
            int v = POP_INT();
            PUSH_INT(!v);
            break;
        }
        case POP_OP:
        {
            vm.stack.top --;
            break;
        }
        case DUPLICATE:
        {
            Value *v = (Value*)MEM_malloc(sizeof(Value));
            Value *src = &vm.stack.arr[vm.stack.top - 1];
            v->kind = src->kind;
            v->int_v = src->int_v;
            v->double_v = src->double_v;
            v->object = src->object;
            PUSH_VALUE(*v);
            break;
        }
        case JUMP:
        {
            int target_pc = GET_2_BYTE(codes, pc);
            pc = target_pc;
            break;
        }
        case JUMP_IF_TRUE:
        {
            int target_pc = GET_2_BYTE(codes, pc);
            int v = POP_INT();
            if(v != 0) {
                pc = target_pc;
            }
            break;
        }
        case JUMP_IF_FALSE:
        {
            int target_pc = GET_2_BYTE(codes, pc);
            int v = POP_INT();
            if(v == 0) {
                pc = target_pc;
            }
            break;
        }
        case PUSH_FUNCTION:
        {
            int func_idx = GET_2_BYTE(codes, pc);
            PUSH_INT(func_idx);
            break;
        }
        case INVOKE:
        {
            int func_idx = POP_INT();
            Variable *local_var;
            Value    *val;
            
            VM_Function *vm_func = &vm.functions[func_idx];
            if(vm_func->kind == NATIVE_FUNCTION) {
                NativeFunction *native_func    = vm_func->native_function;
                vm.stack.arr[vm.stack.top - 1] = native_func(1, &vm.stack.arr[vm.stack.top - 1]);
            } else {
                Function *func = vm_func->user_function;
                expand_stack(func->local_var_cnt + 1 + func->stk_sz_needed);
                /* push return information */
                CallerInfo *caller_info = (CallerInfo*)MEM_malloc(sizeof(CallerInfo));
                caller_info->pc = pc;
                caller_info->stk_base = base;
                caller_info->func = cur_func;
                caller_info->codes = codes;
                caller_info->code_size = code_size;
                PUSH_CALLER_INFO(caller_info);
                /* change base: point to the first argument */
                base = vm.stack.top - func->para_cnt - 1;
                /* change sp: point to the last local variable + 1 */
                vm.stack.top += (func->local_var_cnt - func->para_cnt);
                /* initialize local vairables */
                for(int i = func->para_cnt; i < func->local_var_cnt; i ++) {
                    local_var = &func->local_vars[i];
                    val = &vm.stack.arr[vm.stack.top - 1 - i + func->para_cnt];
                    switch (local_var->type->basic_type)
                    {
                    case BOOLEAN_TYPE:
                    case INT_TYPE:
                        val->kind = INT_VALUE;
                        val->int_v = 0;
                        break;
                    case DOUBLE_TYPE:
                        val->kind = DOUBLE_VALUE;
                        val->double_v = 0.0;
                        break;
                    case STRING_TYPE:
                        val->kind = OBJECT_VALUE;
                        val->object->string = "";
                        break;
                    case NULL_TYPE:     /* todo */
                    case UNDETERMIEND:
                    default:
                        break;
                    }
                }
                /* switch codes to function codes */
                codes = func->codes;
                code_size = func->code_size;
                pc = 0;
                cur_func = func;
            }
            break;
        }
        case RETURN:
        {
            Value *ret_v = &vm.stack.arr[vm.stack.top - 1];
            CallerInfo *caller = vm.stack.arr[base + cur_func->para_cnt].caller_info;
            //ret_v, sp, bp, codes, code_size, pc, cur_func
            vm.stack.arr[base] = *ret_v;
            vm.stack.top = base + 1;
            base = caller->stk_base;
            codes = caller->func == NULL ? caller->codes : caller->func->codes;
            code_size = caller->func == NULL ? caller->code_size : caller->func->code_size;
            pc = caller->pc;
            cur_func = caller->func;
            break;
        }
        case NEW_ARRAY_OP:
        {
            Object *arr_obj = (Object*)MEM_malloc(sizeof(Object));
            arr_obj->type = ARRAY_OBJECT;
            /* read operands */
            int dim_cnt = GET_1_BYTE(codes, pc);
            int typ_dix = GET_2_BYTE(codes, pc);
            /* calculate array size and capacity */
            int sum = 1;
            while(dim_cnt --) {
                int d = POP_INT();
                sum *= d;
            }
            arr_obj->array.size = sum;
            arr_obj->array.cap = sum;
            /* determine basic type */
            switch ((ValueType)typ_dix)
            {
            case BOOLEAN_TYPE:  /* Fallthrough */
            case INT_TYPE:
            {
                arr_obj->array.tag = INT_ARRAY;
                arr_obj->array.int_arr = (int*)MEM_malloc(sizeof(int) * sum);
                for(int i = 0; i < sum; i ++) {
                    arr_obj->array.int_arr[i] = 0;
                }
                break;
            }
            case DOUBLE_TYPE:
            {
                arr_obj->array.tag = DOUBLE_ARRAY;
                arr_obj->array.double_arr = (double*)MEM_malloc(sizeof(double) * sum);
                for(int i = 0; i < sum; i ++) {
                    arr_obj->array.double_arr[i] = 0.0;
                }
                break;
            }
            case STRING_TYPE:
            {
                arr_obj->array.tag = OBJECT_ARRAY;
                arr_obj->array.obj_arr = (Object**)MEM_malloc(sizeof(Object*) * sum);
                for(int i = 0; i < sum; i ++) {
                    arr_obj->array.obj_arr[i] = &null_string_object;
                }
                break;
            }
            case NULL_TYPE:
                break;
            case UNDETERMIEND:
                break;
            default:
                break;
            }
            PUSH_OBJECT(arr_obj);
            break;
        }
        case NEW_ARRAY_LITERAL_INT:
        {
            int elem_num = GET_2_BYTE(codes, pc);
            Object *arr_obj = (Object*)MEM_malloc(sizeof(Object));
            arr_obj->type = ARRAY_OBJECT;
            arr_obj->array.int_arr = (int*)MEM_malloc(sizeof(int) * elem_num);
            arr_obj->array.tag = INT_ARRAY;
            arr_obj->array.size = elem_num;
            arr_obj->array.cap = elem_num;
            for(int i = elem_num - 1; i >= 0; i --) {
                arr_obj->array.int_arr[i] = POP_INT();
            }
            PUSH_OBJECT(arr_obj);
            break;
        }
        case NEW_ARRAY_LITERAL_DOUBLE:
        {
            int elem_num = GET_2_BYTE(codes, pc);
            Object *arr_obj = (Object*)MEM_malloc(sizeof(Object));
            arr_obj->type = ARRAY_OBJECT;
            arr_obj->array.double_arr = (double*)MEM_malloc(sizeof(double) * elem_num);
            arr_obj->array.tag = DOUBLE_ARRAY;
            arr_obj->array.size = elem_num;
            arr_obj->array.cap = elem_num;
            for(int i = elem_num - 1; i >= 0; i --) {
                arr_obj->array.double_arr[i] = POP_DOUBLE();
            }
            PUSH_OBJECT(arr_obj);
            break;
        }
        case NEW_ARRAY_LITERAL_OBJECT:
        {
            int elem_num = GET_2_BYTE(codes, pc);
            Object *arr_obj = (Object*)MEM_malloc(sizeof(Object));
            arr_obj->type = ARRAY_OBJECT;
            arr_obj->array.obj_arr = (Object**)MEM_malloc(sizeof(Object*) * elem_num);
            arr_obj->array.tag = OBJECT_ARRAY;
            arr_obj->array.size = elem_num;
            arr_obj->array.cap = elem_num;
            for(int i = elem_num - 1; i >= 0; i --) {
                arr_obj->array.obj_arr[i] = POP_OBJECT();
            }
            PUSH_OBJECT(arr_obj);
            break;
        }
        case PUSH_ARRAY_INT:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            PUSH_INT(arr->array.int_arr[idx]);
            break;
        }
        case PUSH_ARRAY_DOUBLE:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            PUSH_DOUBLE(arr->array.double_arr[idx]);
            break;
        }
        case PUSH_ARRAY_OBJECT:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            PUSH_OBJECT(arr->array.obj_arr[idx]);
            break;
        }
        case POP_ARRAY_INT:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            int v = POP_INT();
            arr->array.int_arr[idx] = v;
            break;
        }
        case POP_ARRAY_DOUBLE:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            double v = POP_DOUBLE();
            arr->array.double_arr[idx] = v;
            break;
        }
        case POP_ARRAY_OBJECT:
        {
            int idx = POP_INT();
            Object *arr = POP_OBJECT();
            Object *v = POP_OBJECT();
            arr->array.obj_arr[idx] = v;
            break;
        }
        default:
            break;
        }
        // print_stack(opinfo.mnemonic);
    }
}

int is_derived_type(TypeSpecifier *ts) {
    return ts->derive_list_header_p != NULL;
}

void load_static_data() {
    Variable *var;
    Value    *v;
    Executable *exe = vm.exe;

    vm.static_data.size = exe->data_seg->size;
    vm.static_data.arr = (Value*)MEM_malloc(sizeof(Value) * vm.static_data.size);
    for(int i = 0; i < exe->data_seg->size; i ++) {
        var = &exe->data_seg->arr[i];  /* static variable in executable file */
        v = &vm.static_data.arr[i];    /* static value in virtual machine. */
        if(!is_derived_type(var->type)) {
            switch (var->type->basic_type)
            {
            case BOOLEAN_TYPE:
            case INT_TYPE:
                v->kind = INT_VALUE;
                v->int_v = 0;
                break;
            case DOUBLE_TYPE:
                v->kind = DOUBLE_VALUE;
                v->double_v = 0.0; 
                break;   
            case STRING_TYPE:
                v->kind = OBJECT_VALUE;
                v->object = alloc_string_object("");
                break;
            case NULL_TYPE:     /* todo */
            case UNDETERMIEND:
            default:
                break;
            }
        } else { /* By now(2023-8-24 15:00), only array type is derived type. */
            v->kind = OBJECT_VALUE;
            v->object = NULL;
        }
    }
}

void fix_index(Function *func) {
    int pc;
    Byte opcode;
    int idx;
    OpcodeInfo opinfo;
    Byte *codes = func->codes;
    int code_size = func->code_size;
    int para_cnt = func->para_cnt;
    int idx_in_exe;
    
    pc = 0;
    while(pc < code_size) {
        opcode = codes[pc ++];
        if(opcode == PUSH_STACK_INT || opcode == PUSH_STACK_DOUBLE || opcode == PUSH_STACK_OBJECT ||
            opcode == POP_STACK_INT || opcode == POP_STACK_DOUBLE || opcode == POP_STACK_OBJECT) 
        {
            idx = ((codes[pc] >> 8) & 0xff) + (codes[pc + 1] & 0xff);
            if(idx >= para_cnt) {
                idx += 1;
                codes[pc] = (idx >> 8) & 0xff;
                codes[pc + 1] = idx & 0xff;
            }
        } else if(opcode == PUSH_FUNCTION) {
            idx_in_exe = ((codes[pc] >> 8) & 0xff) + (codes[pc + 1] & 0xff);
            char *callee_func_name = vm.exe->code_seg->arr[idx_in_exe].name;
            int i;
            for(i = 0; i < vm.function_count; i ++) {
                if(strcmp(callee_func_name, vm.functions[i].name) == 0) {
                    break;
                }
            }
            codes[pc] = (i >> 8) & 0xff;
            codes[pc + 1] = i & 0xff;
        }
        opinfo = opcode_info[opcode];
        switch (opinfo.para[0])
        {
        case 'b':
            pc += 1;
            break;
        case 'd':
        case 'p':
        case 's':
            pc += 2;
            break;
        case 'a':
            pc += 3;
            break;
        default:
            break;
        }
    }
    
}

void load_code() {
    Function *f;
    int i;
    Executable *exe = vm.exe;

    vm.function_count = exe->code_seg->size;
    vm.functions = (VM_Function*)MEM_malloc(sizeof(VM_Function) * vm.function_count);
    for(i = 0; i < native_func_count; i ++) {
        vm.functions[i].kind = NATIVE_FUNCTION;
        vm.functions[i].name = native_func_names[i];
        vm.functions[i].native_function = native_funcs[i];
    }
    for(int j = 0; j < exe->code_seg->size; j ++) {
        if(i >= vm.function_count) {
            printf("load_code: j >= vm.function_count\n");
            exit(1);
        }
        f = &exe->code_seg->arr[j];
        if(f->is_implemented) {
            vm.functions[i].kind = USER_FUNCTION;
            vm.functions[i].name = f->name;
            vm.functions[i].user_function = f;
            i ++;
        }
    }

    for(int j = 0; j < exe->code_seg->size; j ++) {
        f = &exe->code_seg->arr[j];
        /* fix local variable index and function index */
        fix_index(f);
    }
}

void load_executable_file(Executable *exe) {
    /* 1. load executable file
       2. load code from executable file loaded in step 1
       3. load static variable from executable file loaded in step 1
     */
    vm.exe = exe;
    load_static_data();
    load_code();
}

void init_virtual_machine() {
    vm.heap.phead = NULL;
    vm.heap.len = 0;
    vm.stack.arr = NULL;
    vm.stack.size = 0;
    vm.stack.top = 0;
    vm.static_data.arr = NULL;
    vm.static_data.size = 0;
    vm.pc = 0;
    vm.exe = NULL;
}

VirtualMachine* get_virtual_machine() {
    return &vm;
}
