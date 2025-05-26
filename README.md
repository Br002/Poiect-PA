# Poiect Proiectarea Algoritmilor
### Calinoiu Vlad

## Ce este?
Acesta este un proiect din cadrul cursului de proiectare a algoritmilor.
Toate cerințele și restricțiile pot fi găsite [aici](https://site-pa.netlify.app/proiecte/director_fisiere/#figura1).

Scopul acestui proiect este simularea a unor functii des utilizate in terminal.

Exemplu:

	ls --all
	ls -a
 	ls -la mydir
  	ls -la --human-readable -T 10 mydir

## Dependente
Codul a fost testat exclusiv in mediu `Linux`. A fost rulat si verificat cu afutorul unui checker furnizat de profesoara si asistentii de la curs, acesta necesita `cppcheck` si `valgrind` pentru a putea rula, analiza 
si verifica codul permitand afisarea posibilelor greseli de sintaxa si memory leaks.

A fost necesara si utilizarea `Git`/`GitHub` pentru a salva multiple variante ale proiectului.


 ## Structura
 Proiectul are ca si cerinte principale 4 taskuri , fiecare avand nevoie de o noua apropiere cat si de debugging intens pentru ca lucrurile nu merg niciodata asa cum vrei.

 


# Prezentare sumativa

## Task 1
Structuri si functii
```c
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
void find_flag_opt(ARG **cap, char* s, FILE* f);
void free_list(ARG *cap);

```

Sunt folosite liste pentru memorarea argumentelor, flagurilor si a optiunilor impreuna cu valorile atribuite acestora pentru ca apoi sa fie accesate in partea de scriere in fisierul de output.

## Task 2
Structuri si functii
```c

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

```
 Sunt folosite liste si stive pentru retinerea optiunilor apelului si pentru a realiza structura de fisiere care va fi afisata in fisierul de output.

 ## Task 3
 Structuri si functii
 ```c
struct Element {
    char *dir_name;
    struct Element** next;
    int child_no;
};
typedef struct Element Node3;


typedef struct stack {
    char ** elems;
    int top;
    int cap;
} STACK;

typedef struct node_stack {
    Node3 ** elems;
    int top;
    int cap;
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
STACK* dfs_stack(Node3 *root, const char *target_fullpath);
void createroot(Node3** root, char* d);
void adoptchild(Node3* root, char* d);
void free_tree(Node3* root);
```
Sunt simulati arbori pentru a compara path-urile a doua fisiere si a gasi ultimul director comun.

## Apeluri de testare
```
#!/bin/sh
echo 1
./tema task1 Ana -m -n=100 --file=teste/dir2/in1.txt --out=ref/data1.out
echo 2
./tema task1 Ana are mere --file=teste/dir1/dir4/in2.txt --out=ref/data2.out
echo 3
./tema task1 argument1 argument2 -ab --file=teste/dir1/in3.txt  --out=ref/data3.out
echo 4
./tema task1 argument2 -bc -d --file=teste/dir1/dir4/in4.txt --out=ref/data4.out
echo 5
./tema task1 argument --arg -b 100 --file=teste/in5.txt --out=ref/data5.out 
echo 6
./tema task2 teste --out=ref/data6.out
echo 7
./tema task2 teste -r --out=ref/data7.out
echo 8
./tema task2 teste -h --out=ref/data8.out
echo 9
./tema task2 teste -rh --out=ref/data9.out
echo 10
./tema task2 teste/dir1/ --out=ref/data10.out
echo 11
./tema task3 ./teste/dir1/dir4/dir6 ./teste/dir2 --out=ref/data11.out
echo 12
./tema task3 ./teste/dir1/dir4/dir7 ./teste/dir1/dir4/dir8 --out=ref/data12.out
echo 13
./tema task3 ./teste/dir3/dir9 ./teste/dir3 --out=ref/data13.out
echo 14
./tema task3 ./teste/dir1 ./teste/dir1/dir4/dir6 --out=ref/data14.out
echo 15
./tema task3 ./teste/dir1/dir4 ./teste/dir3/dir9 --out=ref/data15.out
echo 16
./tema task4 ./teste/dir1/dir8/data16_file1.in ./teste/dir1/dir8/data16_file2.in  --out ref/data16.out
echo 17
./tema task4 ./teste/dir1/dir8/dir10/data17_file1.in ./teste/dir1/dir8/dir10/data17_file2.in  --out ref/data17.out
echo 18
./tema task4 ./teste/dir1/dir4/dir6/dir11/data18_file1.in ./teste/dir1/dir4/dir6/dir11/data18_file2.in --out ref/data18.out
echo 19
./tema task4 ./teste/dir3/data19_file1.in ./teste/dir3/data19_file2.in --out ref/data19.out
echo 20
./tema task4 ./teste/dir3/dir9/data20_file1.in ./teste/dir3/dir9/data20_file2.in --out ref/data20.out

```

#### Atentie
Initial toate taskurile au fost scrise separat fiecare avand un fiser `main.c` `functii.c` si `functii.h` propriu.

Am incercat sa le lipesc pe toate astfel incat sa aiba un fisier `main.c` comun si singurul criteriu a fost posibilitatea de compilare. Nu garantez ca pot functiona impreuna. Recomand restructurarea inainte de rulare. 
