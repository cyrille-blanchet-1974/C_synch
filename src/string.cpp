#include <string.h>
#include <stdio.h>
#include <stdarg.h>//pour winuser.h
#include <windef.h>//pour winuser.h
#include <wingdi.h>//pour winuser.h
#include <winuser.h> //pour CharToOem
#include "string.h"


char* c_string::strcpy_alloc(char*dst,char *src)
{
  long taille;              
    taille=strlen(src)+1;
    dst=new char[taille];
    return strcpy(dst,src);
}

char* c_string::strcat_alloc(char*dst,char *src)
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
