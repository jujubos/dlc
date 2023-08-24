#include <stdio.h>
#include "decls.h"
#include "../include/VM.h"
#include <table.h>

int main(int argc, char **argv) {
    Compiler * compiler;
    FILE *fp;

    if(argc != 2) {
        puts("input file missed or not 2!");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("unabled to open %s\n", argv[1]);
        return 1;
    }

    compiler = create_compiler();
    Executable *exe =  compile(compiler, fp);
    init_virtual_machine();
    load_executable_file(exe);
    // VirtualMachine* vm = get_virtual_machine();
    // disassemble_exe(exe);
    Execute();

    // disassemble_ast(compiler);
    // free_compiler(compile);

    return 0;
}