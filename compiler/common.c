#include "decls.h"

Compiler* st_current_compiler;


Compiler* get_current_compiler() {
    return st_current_compiler;
}

void set_current_compiler(Compiler *comp) {
    st_current_compiler = comp;
}

void* Malloc(size_t sz) {
    void *p;
    Compiler *comp;
    
    comp = get_current_compiler();
    p = MEM_storage_malloc(comp->compile_storage, sz);
    
    return p;
}

void error_message(int linenum, CompileError err) {
    switch (err) {
        case FUNCTION_REDEFINITION:
            printf("line %d:%s\n", linenum, "FUNCTION_REDEFINITION");
            break;
    }    
    return;
}

int
yyerror(char const *str)
{
    
    printf("yyerror exit! %s line %d\n", str, get_current_compiler()->current_line_number);
    exit(1);
    // dkc_compile_error(dkc_get_current_compiler()->current_line_number,
    //                   PARSE_ERR,
    //                   STRING_MESSAGE_ARGUMENT, "token", yytext,
    //                   MESSAGE_ARGUMENT_END);
}