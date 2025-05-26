

#include <stdio.h>


struct param_arg 
{
    char tip;
    void* val;
    char arg_tip;
    char *id;
};
typedef struct param_arg Data;

struct arg 
{
    Data data;
    struct arg* next;
};
typedef struct arg ARG;

//void printlist(void **cap); // pt verificari
void add_arg(ARG **cap, char* nval);
void pushopt(ARG **cap, char* nval, int nr);
void pushflag(ARG **cap, char* dval);
char* is_long(const char* s);
char* is_short(const char* s);
void opt(char* s1, const char*s2, ARG **opt);
void farg(char *s, ARG **cap);
void find_arg(ARG **cap, FILE* f);
void find_f_otp(ARG **cap, char* s, FILE* f);
void free_list(ARG *cap);


