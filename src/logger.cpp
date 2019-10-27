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
//0 au d�but
// +1 a chaque classe qui le 'cr��'
//-1 lors du destructor
//si 0 alors on d�truit le mutex
long c_logger::sl_mutex_add_used=0;

/***********************************************
* constructeur
*recoit le nom du fichier de sortie
************************************************/
c_logger::c_logger(char *ap_nom,bool lb_ecrase)
{
    pFile=NULL;    
	if(lb_ecrase==true)
	{
		#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
			 fopen_s (&pFile,ap_nom,"w");
		#else
			pFile = fopen (ap_nom,"w");
		#endif
	}
	else
	{
		#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
			 fopen_s (&pFile,ap_nom,"a");
		#else
			pFile = fopen (ap_nom,"a");
		#endif
	}
    //une utilisation de plus du mutex
    c_logger::sl_mutex_add_used++;
    //cr�ation/r�cup�ration du mutex
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
    //s'il n'est plus utilis�, on lib�re le mutex
    if(c_logger::sl_mutex_add_used == 0) CloseHandle(hmutex_add);
}

/***********************************************
* ajoute une cha�ne au fichier
* la transforme en caract�re DOS
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
* ajoute une cha�ne au fichier
* la transforme en caract�re DOS
************************************************/
void c_logger::add(c_strings & ap_chaine)
{    
   add(ap_chaine.get());
}

/***********************************************
* ajoute une cha�ne au fichier
* la transforme en caract�re DOS
************************************************/
void c_logger::add(long al_data)
{
char tmp[1024];
	# if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
		sprintf_s(tmp,"%li",al_data);
	#else
		sprintf(tmp,"%li",al_data);
	#endif
  add(tmp);
}
