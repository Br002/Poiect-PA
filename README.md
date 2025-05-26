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
 
