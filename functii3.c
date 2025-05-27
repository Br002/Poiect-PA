#include "functii3.h"
#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void createroot(Node3 **root, char *d) {
        *root = (Node3 *)malloc(sizeof(Node3));
        (*root)->next = NULL;
        (*root)->dir_name = strdup(d);
        (*root)->child_no = 0;
    }

    void addchild(Node3* root, char* d) {
        root->child_no++;
        root->next = (Node3**)realloc(root->next, root->child_no * sizeof(Node3*));
        createroot(&root->next[root->child_no - 1], d);
    }

    STACK* stack_create(int cap) {
    STACK *s = malloc(sizeof *s);
    s->elems = malloc(cap * sizeof *s->elems);
    s->top   = -1;
    s->cap   = cap;
    return s;
}
void stack_push(STACK *s, const char *name) {
    if (s->top + 1 == s->cap) {
        s->cap *= 2;
        s->elems = realloc(s->elems, s->cap * sizeof *s->elems);
    }
    s->elems[++s->top] = strdup(name);
}
char* stack_pop(STACK *s) {
    if (s->top < 0) return NULL;
    char *r = s->elems[s->top--];
    return r;
}
int stack_is_empty(STACK *s) {
        return s->top < 0;
    }

void stack_delete(STACK *s) {
    free(s->elems);
    free(s);
}
NSTACK* nstack_create(int cap) {
    NSTACK *s = malloc(sizeof *s);
    s->elems = malloc(cap * sizeof *s->elems);
    s->top   = -1;
    s->cap   = cap;
    return s;
}
void nstack_push(NSTACK *s, Node3 *n) {
    if (s->top + 1 == s->cap) {
        s->cap *= 2;
        s->elems = realloc(s->elems, s->cap * sizeof *s->elems);
    }
    s->elems[++s->top] = n;
}
Node3* nstack_pop(NSTACK *s) {
    if (s->top < 0) return NULL;
    return s->elems[s->top--];
}
int nstack_is_empty(NSTACK *s) { return s->top < 0; }
void nstack_delete(NSTACK *s) {
    free(s->elems);
    free(s);
}

typedef struct {
    Node3 *nod;
    int   child_idx;
} Frame;

STACK* dfs_stack(Node3 *root, const char *target) {
    if (!root) return NULL;

    NSTACK *dfs    = nstack_create(16);
    STACK  *path   = stack_create(16);

    Frame *frames  = malloc(16 * sizeof *frames);
    int    frame_cap = 16, frame_top = -1;
    int    found     = 0;

    frames[++frame_top] = (Frame){ .nod = root, .child_idx = 0 };
    nstack_push(dfs, root);

    while (!nstack_is_empty(dfs) && !found) {
        Frame *fr  = &frames[frame_top];
        Node3  *cur = fr->nod;

        if (fr->child_idx == 0 && strcmp(cur->dir_name, target) == 0) {
            for (int i = frame_top; i >= 0; --i) {
                Node3 *n = frames[i].nod;
                char *base = strrchr(n->dir_name, '/');
                base = base ? base + 1 : n->dir_name;
                stack_push(path, base);
            }
            found = 1;
            break;
        }

        if (fr->child_idx < cur->child_no) {
            Node3 *child = cur->next[fr->child_idx++];
            if (frame_top + 1 == frame_cap) {
                frame_cap *= 2;
                frames = realloc(frames, frame_cap * sizeof *frames);
            }
            frames[++frame_top] = (Frame){ .nod = child, .child_idx = 0 };
            nstack_push(dfs, child);
        } else {
            nstack_pop(dfs);
            --frame_top;
        }
    }

    nstack_delete(dfs);
    free(frames);

    if (!found) {
        stack_delete(path);
        return NULL;
    }
    return path;
}

    void free_tree(Node3 *root) {
        if (!root) return;
        for (int i = 0; i < root->child_no; i++) {
            free_tree(root->next[i]);
        }
        free(root->next);
        free(root->dir_name);
        free(root);
    }
