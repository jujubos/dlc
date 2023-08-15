#include "MEM.h"
#include "decls.h"

#define STACK_ALLOC_SIZE (256)

struct Stack {
    void **arr;
    int top;
    int cap;
};

struct Stack* new_stk(struct Stack *stk) {
    struct Stack *stk;

    stk = (struct Stack*)Malloc(sizeof(struct Stack));
    stk->arr = NULL;
    stk->top = 0;
    stk->cap = 0;

    return stk;
}

void push_stk(struct Stack *stk, void *elem) {
    if(stk == NULL) {
        printf("push stk: push to NULL stack!");
        exit(1);
    }

    if(stk->top >= stk->cap) {
        stk->cap += STACK_ALLOC_SIZE;
        stk->arr = Realloc(stk->arr, stk->cap);
    }

    (stk->arr)[++stk->top] = elem;
}

void* pop_stk(struct Stack *stk) {
    if(stk->top == 0) {
        printf("pop_stk: pop NULL stack!");
        exit(1);
    }
    
    return stk->arr[stk->top--];
}

int stk_size(struct Stack *stk) {
    return stk->top;
}

