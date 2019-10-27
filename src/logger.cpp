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

//nombre d'utilisation du mutex
//0 au début
// +1 a chaque classe qui le 'créé'
//-1 lors du destructor
//si 0 alors on détruit le mutex
long c_logger::sl_mutex_add_used=0;

/***********************************************
* constructeur
*recoit le nom du fiochier de sortie
************************************************/
c_logger::c_logger(char *ap_nom)
{
    pFile=NULL;    
	#ifdef _MSC_VER
		 fopen_s (&pFile,ap_nom,"w");
	#else
		pFile = fopen (ap_nom,"w");
	#endif
    //une utilisation de plus du mutex
    c_logger::sl_mutex_add_used++;
    //création du mutex
    hmutex_add = CreateMutex(NULL,FALSE,"CBL_MUTEX_FOR_C_LOGGER");
}

/***********************************************
*destructeur 
* ferme le fichier
************************************************/
c_logger::~c_logger()
{
    fclose (pFile);
    //une utilisation de moins du mutex
    c_logger::sl_mutex_add_used--;
    //s'il n'est plus utilisé, on libère le mutex
    if(c_logger::sl_mutex_add_used == 0) CloseHandle(hmutex_add);
}

/***********************************************
* ajoute une chaîne au fichier
* la transforme en caractère DOS
************************************************/
void c_logger::add(char * ap_chaine)
{
char ls_oem[MAX_CHAINE];     
   WaitForSingleObject(hmutex_add, INFINITE);
   CharToOem(ap_chaine,ls_oem);
   fprintf(pFile,"%s",ls_oem);
   fflush(pFile);
   ReleaseMutex(hmutex_add);
}

/***********************************************
* ajoute une chaîne au fichier
* la transforme en caractère DOS
************************************************/
void c_logger::add(c_strings ap_chaine)
{    
   add((char *)ap_chaine);
}

/***********************************************
* ajoute une chaîne au fichier
* la transforme en caractère DOS
************************************************/
void c_logger::add(long al_data)
{
char tmp[1024];
	#ifdef  _MSC_VER
		sprintf_s(tmp,"%li",al_data);
	#else
		sprintf(tmp,"%li",al_data);
	#endif
  add(tmp);
}
