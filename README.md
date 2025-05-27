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

 


# Prezentare functii utilizate

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
### Detectare Argumente
- `is_long` - Verifică opțiuni lungi (`--`).
- `is_short` - Verifică opțiuni scurte (`-`).

### Gestionare Listă
- `pushopt` - Adaugă o opțiune cu valoare.
- `add_arg` - Adaugă un argument obișnuit.
- `pushflag` - Adaugă un flag.
- `opt` - Procesează opțiuni și valori.
- `farg` - Descompune opțiuni grupate.

### Căutare și Ieșire
- `find_flag_opt` - Caută și afișează flag-uri/opțiuni.
- `find_arg` - Returnează ultimul argument.

### Memorie
- `free_list` - Eliberează lista.


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
## Funcții pentru directoare (stiva)

-`void push(nod** top, const char *s)`-
Adaugă un nod nou în vârful stivei (`top`), reprezentând un nou director. Alocă memorie, copiază numele directorului și setează `depth = 0`.



-`Data2 pop(nod** top)`-
Scoate și returnează nodul din vârful stivei. Dacă stiva este goală, returnează un `Data2` gol. Eliberează memoria asociată nodului.



-`Data2 top(nod *top)`-
Returnează informația din vârful stivei fără a elimina nodul. Dacă stiva este goală, returnează un `Data2` gol.



-`void printStack(const nod* top, FILE* f, int hr)`-
Parcurge stiva și afișează informații despre directoare (dimensiunea în bytes sau KB, în funcție de `hr`). Dacă un nod conține o listă de fișiere (`content`), apelează `printlist2`.



-`int isempty(const nod* top)`-
Verifică dacă stiva este goală (`top == NULL`).



 -`nod* findir(nod* stack, char* path)`-
Caută un nod cu `name == path` în stivă. Returnează pointerul la nod dacă este găsit, altfel `NULL`.



 -`void sortdirs(nod **stack)`-Sortează stiva alfabetic după numele directoarelor folosind Bubble Sort. Reordonează legăturile între noduri.




-`void freestack(nod* top)`-
Eliberează toată memoria asociată stivei, inclusiv lista de fișiere (`freelist`).


## Funcții pentru fișiere (lista)

-`void addbegin(info_files **cap, const char* s, long int size)`-
Adaugă un fișier la începutul listei `cap`. Alocă memorie pentru un nod nou, copiază numele și setează dimensiunea.



-`void sortfiles(info_files **cap)`-
Sortează lista alfabetic după numele fișierelor folosind Bubble Sort. Se face prin permutarea câmpurilor din noduri (nu a legăturilor).


-`void printlist2(const info_files *cap, FILE* f, int hr)`-
Afișează fișierele din listă, inclusiv dimensiunea și numele fișierului. Formatul este în bytes sau KB, în funcție de `hr`.



-`void freelist(info_files *cap)`-
Eliberează memoria pentru întreaga listă de fișiere.

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
void addchild(Node3* root, char* d);
void free_tree(Node3* root);
```
### Funcții pentru gestionarea structurii arborescente (Node3):

-`createroot(Node3 **root, char *d)`-
Creează un nod rădăcină pentru arbore.

Alocă memorie pentru nod și inițializează campurile: next (lista de copii) este setată la NULL, dir_name este copiat din d folosind strdup, iar child_no (numărul de copii) este setat la 0.

-`adochild(Node3* root, char* d)`-
Adaugă un nou copil la nodul root.

Mărește numărul de copii (child_no), realocă memoria pentru lista de copii (next) și apelează createroot pentru a crea noul copil.

-`free_tree(Node3 *root)`-
Eliberează recursiv memoria alocată pentru întregul arbore, inclusiv pentru numele directorului (dir_name) și pentru lista de copii (next).

### Funcții pentru gestionarea stivelor (STACK și NSTACK):

-`stack_create(int cap)`-
Creează o stivă (`STACK`) cu capacitatea cap.

Alocă memorie pentru stivă și pentru elementele sale, inițializând top la -1 (stivă goală).

-`stack_push(STACK *s, const char *name)`
Adaugă un element (`name`) în stivă.

Dacă stiva este plină, dublează capacitatea folosind realloc.

Copiază name în stivă folosind strdup.

-`stack_pop(STACK *s)`-
Extrage și returnează elementul din vârful stivei.
Returnează NULL dacă stiva este goală.

-`stack_is_empty(STACK *s)`-
Verifică dacă stiva este goală (returnează 1 dacă top este -1, altfel 0).

-`stack_delete(STACK *s)`-
Eliberează memoria alocată pentru stivă și elementele sale.

-`nstack_create(int cap)`-
Similar cu stack_create, dar creează o stivă (`NSTACK`) care stochează pointeri la noduri (`Node3*`).

-`nstack_push(NSTACK *s, Node3 *n)`-
Adaugă un nod (`n`) în stiva `NSTACK`.

-`nstack_pop(NSTACK *s)`-
Extrage și returnează un nod din vârful stivei NSTACK.

-`nstack_is_empty(NSTACK *s)`-
Verifică dacă stiva NSTACK este goală.

-`nstack_delete(NSTACK *s)`-
Eliberează memoria alocată pentru stiva NSTACK și elementele sale.

### Funcție pentru parcurgerea arborelui:

-`dfs_stack(Node3 *root, const char *target)`-
Implementează o parcurgere în adâncime (`DFS`) a arborelui pentru a găsi un nod cu dir_name egal cu target.

Utilizează o stivă (NSTACK) pentru noduri și o altă stivă (`STACK`) pentru a construi calea către nodul găsit.

Returnează o stivă cu numele nodurilor de-a lungul căii de la rădăcină la nodul țintă, sau `NULL` dacă nodul nu este găsit.

Folosește o structură auxiliară (`Frame`) pentru a ține evidența poziției curente în parcurgere.


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
