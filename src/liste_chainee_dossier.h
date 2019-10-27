#ifndef LISTE_CHAINEE_DOSSIER_H
#define LISTE_CHAINEE_DOSSIER_H

#include "liste_chainee_fichier.h"
#include "maillon_dossier.h"
#include "global.h"



class c_liste_chainee_dossier
{
    private:
        //variables
        c_maillon_dossier *p_tete;
        c_maillon_dossier *p_queue;
        c_maillon_dossier *p_courant;
    
	public:
		// class constructor
		c_liste_chainee_dossier();
		// class destructor
		~c_liste_chainee_dossier();
		//ajout d'un maillon -> renvoie un pointeur sur la liste de fichier.
		c_liste_chainee_fichier* ajouter(char*   anom);
		//on cherche un fichier si il existe on renvoit data
		c_liste_chainee_fichier* chercher(char *anom);
		//Pour parcourir la liste 
		c_maillon_dossier* get_next(bool restart);
		//Pour afficher
		void afficher();
};

#endif // LISTE_CHAINEE_DOSSIER_H

