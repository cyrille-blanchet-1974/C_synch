/*******************************************************************************
*
*                   Classe de liste lin�aire doublement cha�n�e des fichiers
*
*******************************************************************************/
#ifndef LC_FICHIER_H
#define LC_FICHIER_H
#include "fichier.h"
#include "global.h"

class c_lc_fichier
{
    private:
        //cha�non pr�c�dent
        c_lc_fichier *p_suivant;
        //cha�non suivant
        c_lc_fichier *p_precedent;
        //nom du fichier
        c_strings    *p_nom;

        //objet fichier 
        c_fichier    *p_data;
    
	public:
		// class constructor
		c_lc_fichier(c_fichier *ap_fichier);
		//c_lc_fichier(struct _finddata_t infos);
		// class destructor
		~c_lc_fichier();		
		//ajout d'un maillon
		class c_lc_fichier* ajouter(c_fichier *ap_fichier);
		//on cherche un fichier si il existe on renvoit le fichier
		c_fichier* chercher(char *ap_cle);
		//nom du fichier courant
		char* get_nom();		
		//objet fichier courant
		c_fichier* get_fichier();
		//r�cup�rer un pointeur vers le chainon suivant
		c_lc_fichier* get_next();
		//r�cup�rer un pointeur vers le chainon pr�c�dent
		c_lc_fichier* get_prev();
		//afficher la liste
		void afficher();
		
};

#endif // LC_FICHIER_H
