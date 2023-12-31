#include "../include/exe.h"

/*
    'b' means imm8
    'd' means imm16
    'p' means pointer to constant, that is, two byte index.
    's' means two byte operand generally.
    "bs" means two operand, the first size is 1 byte, the second size is 2 byte.
*/
OpcodeInfo opcode_info[] = {
    {"dummy", "", 0},
    /*7*/
    {"push_int_1byte", "b", 1},
    {"push_int_2byte", "d", 1},
    {"push_int", "p", 1},
    {"push_double_0", "", 1},
    {"push_double_1", "", 1},
    {"push_double", "p", 1},
    {"push_string", "p", 1},
    /*6*/
    {"push_stack_int", "s", 1},
    {"push_stack_double", "s", 1},
    {"push_stack_object", "s", 1},
    {"pop_stack_int", "s", -1},
    {"pop_stack_double", "s", -1},
    {"pop_stack_object", "s", -1},
    /*6*/
    {"push_static_int", "s", 1},
    {"push_static_double", "s", 1},
    {"push_static_object", "s", 1},
    {"pop_static_int", "s", -1},
    {"pop_static_double", "s", -1},
    {"pop_static_object", "s", -1},
    /*6*/
    {"push_array_int", "", 1},
    {"push_array_double", "", 1},
    {"push_array_object", "", 1},
    {"pop_array_int", "", -1},
    {"pop_array_double", "", -1},
    {"pop_array_object", "", -1},
    /*46*/
    {"add_int", "", -1},
    {"add_double", "", -1},
    {"add_string", "", -1},
    {"sub_int", "", -1},
    {"sub_double", "", -1},
    {"mul_int", "", -1},
    {"mul_double", "", -1},
    {"div_int", "", -1},
    {"div_double", "", -1},
    {"mod_int", "", -1},
    {"mod_double", "", -1},
    {"minus_int", "", 0},
    {"minus_double", "", 0},
    {"increment", "", 0},
    {"decrement", "", 0},
    {"cast_int_to_double", "", 0},
    {"cast_double_to_int", "", 0},
    {"cast_boolean_to_string", "", 0},
    {"cast_int_to_string", "", 0},
    {"cast_double_to_string", "", 0},
    {"eq_int", "", -1},
    {"eq_double", "", -1},
    {"eq_string", "", -1},
    {"gt_int", "", -1},
    {"gt_double", "", -1},
    {"gt_string", "", -1},
    {"ge_int", "", -1},
    {"ge_double", "", -1},
    {"ge_string", "", -1},
    {"lt_int", "", -1},
    {"lt_double", "", -1},
    {"lt_string", "", -1},
    {"le_int", "", -1},
    {"le_double", "", -1},
    {"le_string", "", -1},
    {"ne_int", "", -1},
    {"ne_double", "", -1},
    {"ne_string", "", -1},
    {"logical_and", "", -1},
    {"logical_or", "", -1},
    {"logical_not", "", 0},
    {"pop", "", -1},
    {"duplicate", "", 1},
    {"jump", "s", 0},
    {"jump_if_true", "s", -1},
    {"jump_if_false", "s", -1},
    /*3*/
    {"push_function", "s", 1},
    {"invoke", "", -1},
    {"return", "", -1},
    /*4*/
    {"new_array", "a", 0},
    {"new_array_literal_int", "s", 1},
    {"new_array_literal_double", "s", 1},
    {"new_array_literal_object", "s", 1},
};

