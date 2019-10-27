#ifndef LC_DOSSIER_H
#define LC_DOSSIER_H
#include "lc_fichier.h"
#include "global.h"

class c_lc_dossier
{
    private:
        //variables
        c_lc_dossier *p_suivant;
        c_lc_dossier *p_precedent;
        char *nom; 
        c_lc_fichier  *lst_fichier;
    
	public:
		// class constructor
		c_lc_dossier(char *anom,c_lc_fichier* alst_fichier);
		// class destructor
		~c_lc_dossier();		
		//ajout d'un maillon
		class c_lc_fichier* ajouter(char *anom,c_lc_fichier* alst_fichier);
		//on cherche un fichier si il existe on renvoit data
		c_lc_fichier* chercher(char *anom);
		c_lc_dossier* get_next();
		c_lc_dossier* get_prev();
		char* get_nom();
    	c_lc_fichier* get_liste_fichier();

		//afficher la liste
		void afficher();
		
};

#endif // LC_DOSSIER_H
