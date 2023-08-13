#include <string.h>
#include "decls.h"
#include "../include/MEM.h"

#define STRING_ALLOC_SIZE   (256)

static char *strbuf;
static int strbufsz;
static int strbufallocsz;

void open_string_literal() {
    strbufsz = 0;
}

void add_string_literal(int letter) {
    if(strbufsz == strbufallocsz) {
        strbufallocsz += STRING_ALLOC_SIZE;
        strbuf = 
            MEM_realloc (strbuf, 
                strbufallocsz);
    }
    strbuf[strbufsz ++] = letter;
}

char* close_string_literal() {
    char* new_str;
    
    new_str = Malloc(strbufsz + 1);
    memcpy(new_str, strbuf, strbufsz);
    new_str[strbufsz + 1] = '\0';

    return new_str;
}

void reset_string_literal() {
    MEM_free(strbuf);
    strbuf = NULL;
    strbufsz = 0;
    strbufallocsz = 0;
}


