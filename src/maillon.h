#ifndef MAILLON_H
#define MAILLON_H

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "fichier.h"

class c_maillon
{
    public:
        //variables
        c_maillon *p_precedent;
        c_maillon *p_suivant;
        char *cle; 
        c_fichier  *data;
    
	public:
		// class constructor
		c_maillon(char *acle, struct _finddata_t adata,char *chemin );
		// class destructor
		~c_maillon();		
		
};

#endif // MAILLON_H
