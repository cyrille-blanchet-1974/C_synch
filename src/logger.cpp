#ifndef  _MSC_VER
#include <stdarg.h>//pour winuser.h
#include <windef.h>//pour winuser.h
#include <wingdi.h>//pour winuser.h
#else
#include <WTYPES.H>
#endif 

#include <winuser.h> //pour CharToOem
#include <string.h>
#include <stdio.h>
#include "logger.h"
#include "global.h"


/***********************************************
* constructeur
*recoit le nom du fiochier de sortie
************************************************/
c_logger::c_logger(char *ap_nom)
{
    pFile=NULL;                    
    pFile = fopen (ap_nom,"w");
}

/***********************************************
*destructeur 
* ferme le fichier
************************************************/
c_logger::~c_logger()
{
    fclose (pFile);
}

/***********************************************
* ajoute une chaîne au fichier
* la transforme en caractère DOS
************************************************/
void c_logger::add(char * ap_chaine)
{
char ls_oem[MAX_CHAINE];     
   CharToOem(ap_chaine,ls_oem);
   fprintf(pFile,"%s",ls_oem);
   fflush(pFile);
}
