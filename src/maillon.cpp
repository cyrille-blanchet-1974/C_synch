#include "maillon.h"
#include "fichier.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>




// class constructor
c_maillon::c_maillon(c_fichier *fichier)
{
  long taille;                                   
  char *tmp;
    p_precedent=NULL;
    p_suivant=NULL;
    //data = new c_fichier(fichier);
    data=fichier;
    tmp=fichier->get_cle();
    taille=strlen(tmp)+1;
    cle=new char[taille];
    strcpy(cle,tmp);
}                

		
// class destructor
c_maillon::~c_maillon()
{
    delete cle;	
    delete data;
}
