#include <string.h>
#include <stdio.h>
#include <stdarg.h>//pour winuser.h
#include <windef.h>//pour winuser.h
#include <wingdi.h>//pour winuser.h
#include <winuser.h> //pour CharToOem
#include "lib.h"
#define MAX_CHAINE 8192


char * strcpy_alloc(char*dst,char *src)
{
  long taille;   
    taille=strlen(src)+1;
    dst=new char[taille];
    return strcpy(dst,src);
}

char * strcat_alloc(char*dst,char *src)
{
  long taille;                                   
  char* tmp;

    taille=strlen(src)+strlen(dst)+1;
    tmp=new char[taille];
    strcpy(tmp,dst);
    strcat(tmp,src);
    delete dst;
    dst=tmp;
    return tmp;
}

void print_oem(char * as_chaine,FILE * pFile)
{
char ls_oem[MAX_CHAINE];     
   CharToOem(as_chaine,ls_oem);
   fprintf(pFile,"%s",ls_oem);
   fflush(pFile);
}

