#include "../include/exe.h"

typedef struct VirtualMachine  VirtualMachine;
typedef struct Object          Object;
typedef struct Heap            Heap;
typedef struct Stack           Stack;
typedef struct StaticStorage   StaticStorage;
typedef struct CallerInfo      CallerInfo;
/* enum_begin */
typedef enum {
    STRING_OBJECT = 1,
} ObjectType;
/* enum_end */

typedef union {
    int     int_v;
    double  double_v;
    Object  *object;
} Value;

struct CallerInfo {
    int         pc;
    int         stk_base;
    Function    *caller; /* replace with codes? */
};

struct Object {
    ObjectType type;
    unsigned int marked:1;
    union {
        char *string;
    };
    Object *next;
    Object *prev;
};

struct Stack {
    Value   *arr;
    int     top;
    int     size;
    int     *flags;
};

struct Heap {
    int     len;
    Object  *phead; /* why Object* instead of Value* ? */
};

struct StaticStorage {
    int     size;
    Value   *arr;
};

struct VirtualMachine {
    Stack           stack;
    Heap            heap;
    StaticStorage   static_data;
    int             pc;
    Executable      *exe;
};

/* function_begin */
void init_virtual_machine();
void load_executable_file(Executable *exe);
/* function_end */