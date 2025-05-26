#include <stdio.h>

struct info_dir {
    char *name;//calea până la subdirector + nume
    int depth;//diferenta nivel directoare
};
typedef struct info_dir Data2;

typedef struct info_files {
    char *name;//calea până la fișier + numele său
    long int dimension;//dimensiunea în bytes a fișierului
    struct info_files* next;
}info_files;

struct El {
    Data2 info;
    info_files *content;
    struct El* next;
    int child_no;
    char dir_name;
};
typedef struct El nod;


void push(nod** top, const char* s);
Data2 pop(nod** top);
Data2 top(nod *top);
int isempty(const nod* top);
void sortdirs(nod **stack);
void printStack(const nod* top, FILE* f, int hr);
void freestack(nod* top);
nod* findir(nod* stack, char* path);

void addbegin(info_files **cap, const char* s, long int size);
void sortfiles(info_files **cap);
void printlist2(const info_files *cap, FILE* f, int hr);
void freelist(info_files *cap);

