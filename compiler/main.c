#include <stdio.h>
#include "decls.h"

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
    compile(compiler, fp);
    
    // free_compiler(compile);
    return 0;
}