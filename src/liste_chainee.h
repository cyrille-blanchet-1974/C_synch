#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "maillon.h"
#include "fichier.h"

class c_cache
{
 public:
  char*         cle;
  c_maillon*    maillon;
    // class constructor
    c_cache();
    // class destructor
    ~c_cache();
};


class c_liste_chainee
{
    private:
        //variables
        c_maillon *p_tete;
        c_maillon *p_queue;
        c_maillon *p_courant;
        //pour les recherches
        c_cache *cache;
        long count;
        long nb_strcmp;
    
	public:
		// class constructor
		c_liste_chainee();
		// class destructor
		~c_liste_chainee();
		//ajout d'un maillon
		int ajouter(c_fichier *fichier);
		//on cherche une cle si elle existe on renvoit data
		c_fichier* chercher(char *cle);
		//Pour parcourir la liste 
		char* get_next(bool restart);
		void creer_cache();
		c_fichier* chercher_cache(char *cle);
};

#endif // LISTE_CHAINEE_H

