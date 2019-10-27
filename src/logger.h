/*******************************************************************************
*
*                   Classe de d'écriture de chaîne dans un fichier
*
*******************************************************************************/
#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <windows.h> //mutex
#include "logger.h"
#include "global.h"
#include "strings.h"

class c_logger
{
    private:
    	FILE *pFile;	
        HANDLE hmutex_add;	
        static long sl_mutex_add_used;//nombre d'instance de la classe qui utilise le mutex 

	public:  
    	// class constructor ouvre le fichier
		c_logger(char *ap_nom,bool lb_ecrase);
		// class destructor ferme le fichier
		~c_logger();
		// ajoute des donnnées au fichier
        void add(char * ap_chaine);
		// ajoute des donnnées au fichier
        void add(c_strings & ap_chaine);
		// ajoute des donnnées au fichier
        void add(long al_data);
};

#endif // LOGGER_H




