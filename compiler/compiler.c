#include <stdio.h>
#include "decls.h"

extern int yyparse(void);
extern FILE *yyin;

Executable* walk_ast_for_semantic_analysis(Compiler *comp) {
    return NULL;
}

Executable* walk_ast_for_gen_code(Compiler *comp) {
    return NULL;
}

Executable* compile(Compiler *compiler, FILE *fp) {
    Executable *exe;
    
    yyin = fp;
    set_current_compiler(compiler);
    if (yyparse()) {
        printf("compile()\n");
        exit(1);
    }
    walk_ast_for_semantic_analysis(compiler);
    exe = walk_ast_for_gen_code(compiler);
    
    return exe;
}

FunctionList* alloc_function_list() {
    FunctionList *func_list;

    func_list = (FunctionList*)Malloc(sizeof(FunctionList));
    func_list->phead = NULL;
    
    return func_list;
}

StatementList* alloc_statement_list() {
    StatementList *stat_list;

    stat_list = (StatementList*)Malloc(sizeof(StatementList));
    stat_list->phead = NULL;
    
    return stat_list;
}

DeclarationStatementList* alloc_declaration_stat_list() {
    DeclarationStatementList *decl_stat_list;

    decl_stat_list = (DeclarationStatementList*)Malloc(sizeof(DeclarationStatementList));
    decl_stat_list->phead = NULL;
    
    return decl_stat_list;
}

Compiler* create_compiler() {
    MEM_Storage  storage;
    Compiler     *comp;

    storage = MEM_open_storage(0);
    comp = MEM_storage_malloc(storage, sizeof(Compiler));
    set_current_compiler(comp);

    comp->compile_storage = storage;
    comp->current_block = NULL;
    comp->current_line_number = 1;
    comp->function_count = 0;
    comp->function_list = alloc_function_list();
    comp->statement_list = alloc_statement_list();
    comp->declaration_stat_list = alloc_declaration_stat_list();

    return comp;
}