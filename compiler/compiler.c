#include <stdio.h>
#include "decls.h"

extern int yyparse(void);
extern FILE *yyin;

void walk_ast_for_semantic_analysis(Compiler *comp) {
    
}

Executable* compile(Compiler *compiler, FILE *fp) {
    Executable *exe;
    
    yyin = fp;
    set_current_compiler(compiler);
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
    walk_ast_for_semantic_analysis(compiler);
    exe = walk_ast_for_gen_code(compiler);
    
    return exe;
}