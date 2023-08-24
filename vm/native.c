#include "decls.h"
#include <stdio.h>

Value native_print(int arg_count, Value *args) {
    if(arg_count != 1) {
        printf("native_print:arg count != 1\n");
        exit(1);
    }

    switch (args->kind)
    {
    case INT_VALUE:
        printf("%d", args->int_v);
        break;
    case DOUBLE_VALUE:
        printf("%lf", args->double_v);
        break;
    case OBJECT_VALUE:
        printf("%s", args->object->string);
        break;
    case CALLER_INFO_VALUE:
    case UNKNOWN_VALUE:
    default:
        printf("native_print:arg kind is UNKNOWN\n");
        exit(1);
        break;
    }
        
    Value ret_v;
    ret_v.kind = INT_VALUE;
    ret_v.int_v = 0;

    return ret_v;
}

Value size_arr(int arg_count, Value *args) {
    if(arg_count != 1) {
        printf("size_arr():arg_count != 1\n");
        exit(1);
    }
    if(args->kind != OBJECT_VALUE || args->object->type != ARRAY_OBJECT) {
        printf("size_arr():arg is not array object\n");
        exit(1);
    }
    Value ret_v;
    ret_v.kind  = INT_TYPE;
    ret_v.int_v = args->object->array.size;

    return ret_v;
}

int native_func_count = 2;
NativeFunction *native_funcs[] = {
    native_print,
    size_arr,
};
char *native_func_names[] = {
    "print",
    "size_arr",
};
