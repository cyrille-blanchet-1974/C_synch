#include <string.h>
#include <stdio.h>
//#include <stdarg.h>//pour winuser.h
//#include <windef.h>//pour winuser.h
//#include <wingdi.h>//pour winuser.h
//#include <winuser.h> //pour CharToOem
#include "string.h"


/***********************************************
* copy une chaine dans une autre
* alloue la m�moire
************************************************/
char* c_string::copy_alloc(char *ap_chaine)
{
  long taille,i;              
  char* p_tmp=NULL;
    //d�terminer la taille de la chaine a copier
    taille = 0;
    while(*ap_chaine)
    {
       ap_chaine++;
       taille++;
    }
    //on remet notre pointeur � z�ro
    ap_chaine -= taille; 
    //allouer la m�moire
    p_tmp=new char[taille+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la cha�ne src vers p_tmp
    for (i=0; i < taille ; i++)
        p_tmp[i] = ap_chaine[i];
    //on place le caract�re de fin (null)
    p_tmp[taille] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

/***********************************************
* concataine deux cha�nes
************************************************/
char* c_string::concat_alloc(char *ap_chaine1,char *ap_chaine2)
{
  long taille1,taille2,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    //taille2=strlen(ap_chaine2);
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

/***********************************************
* concataine trois cha�nes
************************************************/
char* c_string::concat_alloc(char *ap_chaine1,char *ap_chaine2,char * ap_chaine3)
{
  long taille1,taille2,taille3,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    taille3 = 0;
    while(*ap_chaine3)
    {
       ap_chaine3++;
       taille3++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine3 -= taille3;         
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+taille3+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la seconde cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on copie la troisi�me cha�ne src vers p_tmp
    for (i=0; i < taille3 ; i++,j++)
        p_tmp[j] = ap_chaine3[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2+taille3] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

char* c_string::concat_alloc(char *ap_chaine1,char *ap_chaine2,char * ap_chaine3,char * ap_chaine4)
{
  long taille1,taille2,taille3,taille4,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    taille3 = 0;
    while(*ap_chaine3)
    {
       ap_chaine3++;
       taille3++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine3 -= taille3;         
    taille4 = 0;
    while(*ap_chaine4)
    {
       ap_chaine4++;
       taille4++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine4 -= taille4;         
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+taille3+taille4+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la seconde cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on copie la troisi�me cha�ne src vers p_tmp
    for (i=0; i < taille3 ; i++,j++)
        p_tmp[j] = ap_chaine3[i];
    //on copie la quitri�me cha�ne src vers p_tmp
    for (i=0; i < taille4 ; i++,j++)
        p_tmp[j] = ap_chaine4[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2+taille3+taille4] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

