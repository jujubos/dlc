#include <stdio.h>
#include "decls.h"
#include "../include/exe.h"


extern int yyparse(void);
extern FILE *yyin;

Executable* compile(Compiler *compiler, FILE *fp) {
    Executable *exe;
    
    yyin = fp;
    set_current_compiler(compiler);
    if (yyparse()) {
        printf("compile()\n");
        exit(1);
    }
    walk_ast_for_semantic_analysis(compiler);
    exe = walk_ast_for_gen_exe(compiler);
    
    return exe;
}

FunctionList* alloc_function_list() {
    FunctionList *func_list;

    func_list = (FunctionList*)Malloc(sizeof(FunctionList));
    func_list->phead = NULL;
    func_list->len = 0;
    
    return func_list;
}

StatementList* alloc_statement_list() {
    StatementList *stat_list;

    stat_list = (StatementList*)Malloc(sizeof(StatementList));
    stat_list->phead = NULL;
    stat_list->len = 0;
    
    return stat_list;
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
    comp->function_list = alloc_function_list();
    comp->statement_list = alloc_statement_list();
    comp->declaration_stat_list = alloc_statement_list();

    return comp;
}