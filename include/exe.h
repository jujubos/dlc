#ifndef __EXE__
#define __EXE__
#include <stdint.h>

/* enum_begin */
typedef enum {
    UNDETERMIEND,
    BOOLEAN_TYPE,
    INT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE
} ValueType;

typedef enum {
    INT_CONSTANT,
    DOUBLE_CONSTANT,
    STRING_CONSTANT,
} ConstantType;

typedef enum {
    PUSH_INT_1BYTE = 1,
    PUSH_INT_2BYTE,
    PUSH_INT,
    PUSH_DOUBLE_0,
    PUSH_DOUBLE_1,
    PUSH_DOUBLE,
    PUSH_STRING,
    /**********/
    PUSH_STACK_INT,
    PUSH_STACK_DOUBLE,
    PUSH_STACK_STRING,
    POP_STACK_INT,
    POP_STACK_DOUBLE,
    POP_STACK_STRING,
    /**********/
    PUSH_STATIC_INT,
    PUSH_STATIC_DOUBLE,
    PUSH_STATIC_STRING,
    POP_STATIC_INT,
    POP_STATIC_DOUBLE,
    POP_STATIC_STRING,
    /**********/
    ADD_INT,
    ADD_DOUBLE,
    ADD_STRING,
    SUB_INT,
    SUB_DOUBLE,
    MUL_INT,
    MUL_DOUBLE,
    DIV_INT,
    DIV_DOUBLE,
    MOD_INT,
    MOD_DOUBLE,
    MINUS_INT,
    MINUS_DOUBLE,
    INCREMENT_OP,
    DECREMENT_OP,
    CAST_INT_TO_DOUBLE_OP,
    CAST_DOUBLE_TO_INT_OP,
    CAST_BOOLEAN_TO_STRING_OP,
    CAST_INT_TO_STRING_OP,
    CAST_DOUBLE_TO_STRING_OP,
    EQ_INT,
    EQ_DOUBLE,
    EQ_STRING,
    GT_INT,
    GT_DOUBLE,
    GT_STRING,
    GE_INT,
    GE_DOUBLE,
    GE_STRING,
    LT_INT,
    LT_DOUBLE,
    LT_STRING,
    LE_INT,
    LE_DOUBLE,
    LE_STRING,
    NE_INT,
    NE_DOUBLE,
    NE_STRING,
    LOGICAL_AND_OP,
    LOGICAL_OR_OP,
    LOGICAL_NOT_OP,
    POP_OP,
    DUPLICATE,
    JUMP,
    JUMP_IF_TRUE,
    JUMP_IF_FALSE,
    /**/
    PUSH_FUNCTION,
    INVOKE,
    RETURN,
} OpCodeTag;
/* enum_end */

/* typedef_begin */
typedef struct TypeSpecifier    TypeSpecifier;
typedef unsigned char Byte;
typedef struct Executable       Executable;
typedef struct ConstantSegment  ConstantSegment;
typedef struct Constant         Constant;
typedef struct LineNumber       LineNumber;
typedef struct Variable         Variable;
typedef struct DataSegment      DataSegment;
typedef struct CodeSegment      CodeSegment;
typedef struct Function         Function;
typedef struct OpcodeInfo       OpcodeInfo;
/* typedef_end */
struct TypeSpecifier {
    ValueType basic_type;
};

struct OpcodeInfo {
    char    *mnemonic;
    char    *para;
    int     stk_sz_needed;
};

struct Constant {
    ConstantType tag;
    union {
        // Boolean bool;
        int     int_constant;
        double  double_constant;
        char    *string_constant;
    };
};

struct ConstantSegment {
    Constant *arr;
    int      size;
};

struct Variable {
    TypeSpecifier *type;
    char          *name;
};

struct LineNumber {
    int num;
    int start_pc;
    int last_pc;
};

struct DataSegment {
    Variable   *arr;
    int        size;
};

struct Function {
    TypeSpecifier   *type;
    char            *name;
    Variable        *paras;
    int             para_cnt;
    Variable        *local_vars;
    int             local_var_cnt;
    Byte            *codes;
    int             code_size;
    LineNumber      *line_numbers;
    int             line_number_size; 
    int             stk_sz_needed;
    int             is_implemented;
};

struct CodeSegment {
    Function *arr;
    int      size;
};

struct Executable {
    ConstantSegment *constant_seg;
    DataSegment     *data_seg;
    CodeSegment     *code_seg;
    Byte            *top_codes;
    int             top_code_size;
    LineNumber      *line_numbers;
    int             line_number_size;
    int             stk_sz_needed;
};

#endif