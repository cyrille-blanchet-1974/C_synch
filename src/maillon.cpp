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
c_maillon::c_maillon(char *acle,struct _finddata_t adata,char *chemin)
{
  long taille;                                   
    p_precedent=NULL;
    p_suivant=NULL;
    taille=strlen(acle)+1;
    cle=new char[taille];
    strcpy(cle,acle);
    data=new c_fichier(adata,chemin);
}                

		
// class destructor
c_maillon::~c_maillon()
{
    delete cle;	
}
