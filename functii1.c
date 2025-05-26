#include "functii1.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* is_long(const char* s) 
{
    return strstr(s, "--");
}

char* is_short(const char* s) 
{
  return strstr(s, "-");
}

void opt( char *s1, const char* s2, ARG **opt){
    if(strstr(s1, "="))
      {
        pushopt(opt, s1, atoi(strstr(s1, "=") + 1));
        return;
      }
    if(atoi(s2))
        pushopt(opt, s1, atoi(s2));
}

void pushopt(ARG **cap, char* nval, int nr){
  ARG *newNode = (ARG *)malloc(sizeof(ARG));
  newNode->data.val = malloc(sizeof(int));
  *(int*)newNode->data.val = nr;//valoare numerica
  if(is_long(nval))
    newNode->data.arg_tip = 'l';
   else if(is_short(nval))
    newNode->data.arg_tip = 's';
  newNode->data.id = nval;
  newNode->data.tip = 'o';
	newNode->next = *cap;
	*cap = newNode;
}

void add_arg(ARG **cap, char* nval){
	ARG *newNode = malloc(sizeof(ARG));
	newNode->data.val = strdup(nval);//valoare argument
  newNode->data.tip = 'a';
	newNode->next = *cap;
	*cap = newNode;
}

void pushflag(ARG **cap, char* dval){
	ARG *newNode = (ARG*)malloc(sizeof(ARG));
    newNode->data.val = malloc(sizeof(int));
    *(int*)newNode->data.val = 1;//toggle
    newNode->data.tip = 'f';
  if(is_long(dval))
    newNode->data.arg_tip = 'l';
  else if(is_short(dval))
    newNode->data.arg_tip = 's';
    newNode->data.id = dval;
    newNode->next = *cap;
    *cap = newNode;
}

void farg(char *s, ARG **cap){
  int len = strlen(s);
  for(int i = 2; i < len; i++){
	char temp[3];
	temp[0] = '-';
	temp[1] = s[i];
	temp[2] = '\0';
    if ((*cap)->data.tip == 'f') 
    {
      pushflag(cap, temp);
    } 
    else if ((*cap)->data.tip == 'o') 
    {
      pushopt(cap, temp, *(int*)(*cap)->data.val);
    }
  }
}

void find_f_otp(ARG **cap, char* s, FILE* f) 
{

  if (*cap == NULL) 
  {
    fprintf(f, "\n");
    return;
  }
  
  char aux[100];
  switch ((*cap)->data.arg_tip) 
  {
    case 's':
      char* token = strtok(s, " ");
	if(token)
		strcpy(aux, token);
	else
		aux[0] = '\0';
      break;
    case 'l':
      char* p = strstr(s, "--");
	if(p){
		char* token = strtok(p, " ");
		if(token)
			strcpy(aux, token);
		else aux[0] = '\0';
}	else aux[0] = '\0';
      break;
    default:
	aux[0] = '\0';
      break;
  }

  ARG *capcopy = *cap;
  if (strcmp(capcopy->data.id, aux) == 0) 
  {
    *cap = (*cap)->next;
    fprintf(f, "%d\n", *(int*)capcopy->data.val);

    free(capcopy->data.val);
    free(capcopy);
    return;
  }

  ARG *prev = *cap;
  capcopy = capcopy->next;
  while (capcopy != NULL) 
  {
    if (strcmp(capcopy->data.id, aux) == 0) 
    {
      prev->next = capcopy->next;
      fprintf(f, "%d\n", *(int*)capcopy->data.val);
      free(capcopy->data.val);
      free(capcopy);
      return;
    }
      prev = capcopy;
      capcopy = capcopy->next;
  }
  fprintf(f, "\n");
}

void find_arg(ARG **cap, FILE* f) 
{
  if (*cap == NULL) 
  {
    fprintf(f, "\n");
    return;
  }

  if ((*cap)->next == NULL) 
  {
    fprintf(f, "%s\n", (char*)(*cap)->data.val);
    free(*cap);
    *cap = NULL;
    return;
  }

  ARG *capcopy = *cap;
  while (capcopy->next->next != NULL)
    capcopy = capcopy->next;

  fprintf(f, "%s\n", (char*)capcopy->next->data.val);
  free(capcopy->next);
  capcopy->next = NULL;
}

void free_list(ARG *cap) 
{
  ARG* temp;

  while (cap != NULL) 
  {
    temp = cap;
    cap = cap->next;
	free(temp->data.val);
    free(temp);
  }
}