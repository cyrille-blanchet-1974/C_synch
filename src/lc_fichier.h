#ifndef LC_FICHIER_H
#define LC_FICHIER_H
#include "fichier.h"
#include "global.h"

class c_lc_fichier
{
    private:
        //variables
        c_lc_fichier *p_suivant;
        c_lc_fichier *p_precedent;
        char *nom; 
        c_fichier  *data;
    
	public:
		// class constructor
		c_lc_fichier(c_fichier *fichier );
		// class destructor
		~c_lc_fichier();		
		//ajout d'un maillon
		class c_fichier* ajouter(c_fichier *fichier);
		//on cherche un fichier si il existe on renvoit data
		c_fichier* chercher(char *anom);
		char* get_nom();
		c_fichier* get_fichier();
		//récupèrer un pointeur vers le chainon suivant
		c_lc_fichier* get_next();
		c_lc_fichier* get_prev();
		//afficher la liste
		void afficher();
		
};

#endif // LC_FICHIER_H
