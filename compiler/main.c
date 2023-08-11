#include <stdio.h>
#include "decls.h"

int main(int argc, char **argv) {
    Compiler * compiler;
    FILE *fp;

    compiler = create_compiler();
    compile(compiler, fp);
    
    free_compiler(compile);
    return 0;
}