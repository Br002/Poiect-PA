#include <stdio.h>



struct Element {
    char *dir_name;
    struct Element** next;
    int child_no;
};
typedef struct Element Node3;


typedef struct stack {
    char ** elems;
    int     top;
    int     cap;
} STACK;

typedef struct node_stack {
    Node3 ** elems;
    int     top;
    int     cap;
} NSTACK;

STACK* stack_create(int initial_cap);
void stack_push(STACK *s, const char *name);
char* stack_pop(STACK *s);
int stack_is_empty(STACK *s);
void stack_delete(STACK *s);

NSTACK* nstack_create(int initial_cap);
void nstack_push(NSTACK *s, Node3 *n);
Node3* nstack_pop(NSTACK *s);
int nstack_is_empty(NSTACK *s);
void nstack_delete(NSTACK *s);

STACK*    dfs_stack(Node3 *root, const char *target_fullpath);


void createroot(Node3** root, char* d);
void addchild(Node3* root, char* d);
void free_tree(Node3* root);
