#include "functii2.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>

#include <limits.h>

//funcțiile pentru stocarea directoarelor, de prelucrare a stivei
void push(nod** top, const char *s) { //*s este subdirectorul

    nod* newNode = malloc(sizeof(nod));
    if(newNode == NULL) 
    {
        fprintf(stderr, "Memory error\n");
        exit(EXIT_FAILURE);
    }
    newNode->info.name = strdup(s);
    newNode->info.depth = 0;
    newNode->next = *top;
    newNode->content = NULL;
    *top = newNode;

}

Data2 pop(nod** top) 
{

    if (isempty(*top)) 
    {
        Data2 d = {NULL, 0};
        return d;
    }

    nod *temp = *top;
    Data2 aux = temp->info;
    *top = (*top)->next;
    free(temp);

    return aux;
}

Data2 top(nod *top){

    if (isempty(top)) 
    {
        Data2 d = {NULL, 0};
        return d;
    }
    return top->info;
}

void printStack(const nod* top, FILE* f, int hr) 
{

    struct stat dirStat;

    while (top != NULL) 
    {
        if (stat(top->info.name, &dirStat) == 0)
        {
            if(hr)
                fprintf(f ,"%.1fK %s\n", dirStat.st_size / 1024.0, strrchr(top->info.name, '/') + 1);
            else
                fprintf(f, "%ld %s\n", dirStat.st_size, strrchr(top->info.name, '/') + 1);
        }

        if(top->content)
            printlist2(top->content, f, hr);

        top = top->next;
    }
}

int isempty(const nod* top) 
{

    return top == NULL;
}

nod* findir(nod* stack, char* path) 
{
    nod* temp = stack;
    while(temp) 
    {
        if(strcmp(path, temp->info.name) == 0) 
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void sortdirs(nod **stack) 
{

    if (isempty(*stack) || (*stack)->next == NULL)
        return;

    int aux;

    do 
    {

        aux = 0;
        nod **p = stack;
        while (*p && (*p)->next) 
        {

            if (strcmp((*p)->info.name, (*p)->next->info.name) > 0) 
            {

                nod *temp = *p;
                *p = (*p)->next;
                temp->next = (*p)->next;
                (*p)->next = temp;
                aux = 1;
            }

            p = &(*p)->next;
        }
    } while (aux);
}

void freestack(nod* top) 
{

    while (top) 
    {

        nod *temp = top;
        top = top->next;

        free(temp->info.name);
       freelist(temp->content);
        free(temp);
    }
}


//funcțiile pentru stocarea fișierelor, de prelucrare a listei

void addbegin(info_files **cap, const char* s, long int size) 
{

    info_files *newNode = malloc(sizeof(info_files));
    newNode->name = strdup(s);
    newNode->dimension = size;
    newNode->next = *cap;
    *cap = newNode;
}

void sortfiles(info_files **cap) 
{

    if (*cap == NULL) return;

    int aux;
    info_files *p;
    info_files *lp = NULL;

    do 
    {
        aux = 0;
        p = *cap;

        while (p->next != lp) 
        {
            if (strcmp(p->name, p->next->name) > 0) 
            {

                char *temp_name = p->name;
                p->name = p->next->name;
                p->next->name = temp_name;

                long int temp_dim = p->dimension;
                p->dimension = p->next->dimension;
                p->next->dimension = temp_dim;

                aux = 1;
            }
            p = p->next;
        }
        lp = p;
    } while (aux);
}

void printlist2(const info_files *cap, FILE* f, int hr) 
{

    while (cap != NULL) 
    {
            if(hr)
                fprintf(f ,"%.1fK %s\n", cap->dimension / 1024.0, strrchr(cap->name, '/') + 1);
            else
                fprintf(f, "%ld %s\n", cap->dimension, strrchr(cap->name, '/') + 1);
        cap = cap->next;
    }
}

void freelist(info_files *cap) 
{

    while (cap) 
    {
        info_files *next = cap;
        cap = cap->next;
        free(next->name);
        free(next);
    }
}