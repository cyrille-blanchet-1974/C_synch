#ifndef LISTE_CHAINEE_FICHIER_H
#define LISTE_CHAINEE_FICHIER_H


#include "maillon_fichier.h"
#include "fichier.h"
#include "global.h"


class c_liste_chainee_fichier
{
    private:
        //variables
        c_maillon_fichier *p_tete;
        c_maillon_fichier *p_queue;
        c_maillon_fichier *p_courant;
    
	public:
		// class constructor
		c_liste_chainee_fichier();
		// class destructor
		~c_liste_chainee_fichier();
		//ajout d'un maillon
		int ajouter(c_fichier *fichier);
		//on cherche un fichier si il existe on renvoit data
		c_fichier* chercher(char *anom);
		//Pour parcourir la liste 
		c_fichier* get_next(bool restart);
		void afficher();
};

#endif // LISTE_CHAINEE_FICHIER_H

