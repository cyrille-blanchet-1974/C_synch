#ifndef MAILLON_DOSSIER_H
#define MAILLON_DOSSIER_H

#include "maillon_fichier.h"
#include "liste_chainee_fichier.h"
#include "global.h"

class c_maillon_dossier
{
    public:
        //variables
        c_maillon_dossier *p_suivant;
        c_maillon_dossier *p_precedent;
        char *nom; 
        c_liste_chainee_fichier  liste_fichiers;
    
	public:
		// class constructor
		c_maillon_dossier(char *anom );
		// class destructor
		~c_maillon_dossier();	
        c_liste_chainee_fichier* get_liste_fichier();			
};

#endif // MAILLON_DOSSIER_H
