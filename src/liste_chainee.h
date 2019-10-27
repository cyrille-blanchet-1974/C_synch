#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "maillon.h"
#include "fichier.h"



class c_liste_chainee
{
    private:
        //variables
        c_maillon *p_tete;
        c_maillon *p_queue;
        c_maillon *p_courant;
        c_maillon *p_dernier_trouve;
        long count;
        long nb_strcmp;
        long nb_strcmp_init;
    
	public:
		// class constructor
		c_liste_chainee();
		// class destructor
		~c_liste_chainee();
		//ajout d'un maillon
		int ajouter(c_fichier *fichier);
		//ajout d'un maillon en triant
		int ajouter_trier(c_fichier *fichier);
		//on cherche une cle si elle existe on renvoit data
		c_fichier* chercher(char *cle);
		//Pour parcourir la liste 
		char* get_next(bool restart);
		void afficher();
		c_fichier* chercher_trie(char *cle);
};

#endif // LISTE_CHAINEE_H

