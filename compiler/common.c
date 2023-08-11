#include "decls.h"

Compiler* st_current_compiler;


Compiler* get_current_compiler() {
    return st_current_compiler;
}

void set_currentC_compiler(Compiler *comp) {
    st_current_compiler = comp;
}

void* Malloc(size_t sz) {
    void *p;
    Compiler *comp;
    
    comp = get_current_compiler();
    p = MEM_storage_malloc(comp->compile_storage, sz);
    
    return p;
}

TypeSpecifier* alloc_type_specifier(ValueType type) {
    TypeSpecifier *typ;
    
    typ = (TypeSpecifier*)Malloc(sizeof(TypeSpecifier));
    typ->basic_type = type;

    return typ;
}

void error_message(int linenum, CompileError err) {
    switch (err) {
        case FUNCTION_REDEFINITION:
            printf("line %d:%s\n", linenum, "FUNCTION_REDEFINITION");
            break;
    }    
    return;
}

