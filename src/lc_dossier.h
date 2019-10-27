/*******************************************************************************
*
*                   Classe de liste linéaire doublement chaînée des dossiers
*
*******************************************************************************/
#ifndef LC_DOSSIER_H
#define LC_DOSSIER_H
#include "lc_fichier.h"
#include "global.h"
#include "strings.h"

class c_lc_dossier
{
    private:
        //chaînon précédent
        c_lc_dossier *p_suivant;
        //chaînon suivant
        c_lc_dossier *p_precedent;
        //nom du dossier
        //char *p_nom; 
        c_strings p_nom;
        
        //liste des fichiers du dossier
        c_lc_fichier  *p_lst_fichier;
    
	public:
		// class constructor reçoit le nom du dossier et la liste de fichier
		c_lc_dossier(char *ap_nom);
		// class destructor
		~c_lc_dossier();	
        //assigner la liste de fichier
        void set_liste_fichier(c_lc_fichier* ap_lst_fichier);
		//ajout d'un maillon reçoit le nom du dossier 
		class c_lc_dossier* ajouter(char *ap_nom);
		//ajout d'un fichier
		class c_lc_fichier* ajouter(c_fichier* ap_fichier);
		//on cherche un fichier si il existe on renvoit la liste des fichiers
		class c_lc_dossier* chercher(char *ap_nom);
		//dossier suivant
		c_lc_dossier* get_next();
		//dossier précédent
		c_lc_dossier* get_prev();
		//nom du dossier courant
		char* get_nom();
		//liste des fichiers du dossier courant
    	c_lc_fichier* get_liste_fichier();
		//afficher la liste
		void afficher();
		
};

#endif // LC_DOSSIER_H
