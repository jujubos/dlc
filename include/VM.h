
typedef struct VirtualMachine  VirtualMachine;


/* function_begin */
void init_virtual_machine();
VirtualMachine* get_virtual_machine();
void load_executable_file(Executable *exe);
void Execute();
/* function_end */