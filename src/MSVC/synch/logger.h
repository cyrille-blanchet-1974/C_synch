/*******************************************************************************
*
*                   Classe de d'écriture de chaîne dans un fichier
*
*******************************************************************************/
#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include "logger.h"
#include "global.h"

class c_logger
{
    private:
    	FILE *pFile;		

	public:  
    	// class constructor ouvre le fichier
		c_logger(char *ap_nom);
		// class destructor ferme le fichier
		~c_logger();
		// ajoute des donnnées au fichier
        void add(char * ap_chaine);
};

#endif // LOGGER_H




