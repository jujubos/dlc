
typedef struct VirtualMachine  VirtualMachine;


/* function_begin */
void init_virtual_machine();
void load_executable_file(Executable *exe);
VirtualMachine* get_virtual_machine();
/* function_end */