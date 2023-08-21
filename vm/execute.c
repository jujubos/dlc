#include "decls.h"
#include "../include/MEM.h"

extern OpcodeInfo opcode_info[];

VirtualMachine vm;

/*
state:
    Byte *codes;
    int  pc;
    int  top;
    int  base;
*/
void Execute() {
    Byte  *codes;
    int   code_size;
    int   pc;
    int   top;
    int   base;

    expand_stack(vm.exe->stk_sz_needed);
    codes = vm.exe->top_codes;
    pc = 0;
    top = 0;
    base = 0;
    while(pc < code_size) {
        
    }
}

void load_static_data(Executable *exe) {
    Variable *var;
    Value    *v;
    
    vm.static_data.size = exe->data_seg->size;
    vm.static_data.arr = (Value*)MEM_malloc(sizeof(Value) * vm.static_data.size);
    for(int i = 0; i < exe->data_seg->size; i ++) {
        var = &exe->data_seg->arr[i];
        v = &vm.static_data.arr[i];
        switch (var->type->basic_type)
        {
        case BOOLEAN_TYPE:
        case INT_TYPE:
            v->int_v = 0;
            break;
        case DOUBLE_TYPE:
            v->double_v = 0.0; 
            break;   
        case STRING_TYPE:
            v->object = MEM_malloc(sizeof(Object));
            v->object->string = "";
            break;
        case UNDETERMIEND:
        default:
            break;
        }
    }
}

void fix_local_var_index(Byte *codes, int code_size, int para_cnt) {
    int pc;
    Byte opcode;
    int idx;
    OpcodeInfo opinfo;

    pc = 0;
    while(pc < code_size) {
        opcode = codes[pc ++];
        if(opcode == PUSH_STACK_INT || opcode == PUSH_STACK_DOUBLE || opcode == PUSH_STACK_STRING ||
            opcode == POP_STACK_INT || opcode == POP_STACK_DOUBLE || opcode == POP_STACK_STRING) 
        {
            idx = ((codes[pc] >> 8) & 0xff) + (codes[pc + 1] & 0xff);
            if(idx >= para_cnt) {
                int q = sizeof(CallerInfo);
                q = sizeof(Value);
                idx += (sizeof(CallerInfo) - 1) / sizeof(Value) + 1;
                codes[pc] = (idx >> 8) & 0xff;
                codes[pc + 1] = idx & 0xff;
            }
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
        default:
            break;
        }
    }
    
}

void load_code(Executable *exe) {
    Function *f;

    for(int i = 0; i < exe->code_seg->size; i ++) {
        f = &exe->code_seg->arr[i];
        fix_local_var_index(f->codes, f->code_size, f->para_cnt);
    }
}

void load_executable_file(Executable *exe) {
    load_static_data(exe);
    load_code(exe);
    vm.exe = exe;
}

void init_virtual_machine() {
    vm.heap.phead = NULL;
    vm.heap.len = 0;
    vm.stack.arr = NULL;
    vm.stack.size = 0;
    vm.stack.top = 0;
    vm.stack.flags = NULL;
    vm.static_data.arr = NULL;
    vm.static_data.size = 0;
    vm.pc = 0;
    vm.exe = NULL;
}

VirtualMachine* get_virtual_machine() {
    return &vm;
}


