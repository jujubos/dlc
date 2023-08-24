#include <stdlib.h>
#include "../include/exe.h"

/* typedef_begin */
typedef struct VirtualMachine  VirtualMachine;
typedef struct Object          Object;
typedef struct Heap            Heap;
typedef struct Stack           Stack;
typedef struct StaticStorage   StaticStorage;
typedef struct CallerInfo      CallerInfo;
typedef struct Value           Value;
typedef struct VM_Function     VM_Function;
typedef struct Array           Array;
typedef Value  NativeFunction(int arg_count, Value *args);
/*typedef_end*/

/* enum_begin */
typedef enum {
    STRING_OBJECT = 1,
    ARRAY_OBJECT,
} ObjectType;

typedef enum {
    INT_ARRAY,
    DOUBLE_ARRAY,
    OBJECT_ARRAY,
} ArrayType;

typedef enum {
    UNKNOWN_VALUE,
    INT_VALUE,
    DOUBLE_VALUE,
    OBJECT_VALUE,
    CALLER_INFO_VALUE,
} ValueKind;

typedef enum {
    USER_FUNCTION,
    NATIVE_FUNCTION,
} FunctionKind;
/* enum_end */

struct Value {
    ValueKind        kind;
    union {
        int         int_v;
        double      double_v;
        Object      *object;
        CallerInfo  *caller_info;
    };
};

struct CallerInfo {
    int         pc;
    int         stk_base;
    Function    *func;
    Byte        *codes;
    int         code_size;
};

struct Array {
    ArrayType tag;
    int size;
    int cap;
    union {
        int     *int_arr;
        double  *double_arr;
        Object  **obj_arr;
    };
};

struct Object {
    ObjectType type;
    unsigned int marked:1;
    union {
        char  *string;
        Array  array;
    };
    Object *next;
    Object *prev;
};

struct Stack {
    Value   *arr;
    int     top;
    int     size;
};

struct Heap {
    int     len;
    Object  *phead; /* why Object* instead of Value* ? */
};

struct StaticStorage {
    int     size;
    Value   *arr;
};

struct VM_Function {
    FunctionKind kind;
    char         *name;
    union {
        Function       *user_function;
        NativeFunction *native_function;
    };
};

struct VirtualMachine {
    Stack           stack;
    Heap            heap;
    StaticStorage   static_data;
    int             pc;
    Executable      *exe;
    VM_Function     *functions;
    int             function_count;
};

/* function_begin */
void init_virtual_machine();
void load_executable_file(Executable *exe);
/* function_end */