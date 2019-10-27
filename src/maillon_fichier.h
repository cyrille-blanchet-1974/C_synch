#ifndef MAILLON_FICHIER_H
#define MAILLON_FICHIER_H

#include "fichier.h"
#include "global.h"

class c_maillon_fichier
{
    public:
        //variables
        c_maillon_fichier *p_suivant;
        c_maillon_fichier *p_precedent;
        char *nom; 
        c_fichier  *data;
    
	public:
		// class constructor
		c_maillon_fichier(c_fichier *fichier );
		// class destructor
		~c_maillon_fichier();		
		
};

#endif // MAILLON_FICHIER_H
