/*******************************************************************************
*
*                   Classe de liste lin�aire doublement cha�n�e des dossiers
*
*******************************************************************************/
#ifndef LC_DOSSIER_H
#define LC_DOSSIER_H
#include "lc_fichier.h"
#include "global.h"
//#include "strings.h"

class c_lc_dossier
{
    private:
        //cha�non pr�c�dent
        class c_lc_dossier *p_suivant;
        //cha�non suivant
        class c_lc_dossier *p_precedent;
        //nom du dossier
        class c_strings p_nom;
        
        //liste des fichiers du dossier
        class c_lc_fichier  *p_lst_fichier;
    
	public:
		// class constructor re�oit le nom du dossier et la liste de fichier
		c_lc_dossier(char *ap_nom);
		// class destructor
		~c_lc_dossier();	
        //assigner la liste de fichier
        void set_liste_fichier(class c_lc_fichier* ap_lst_fichier);
		//ajout d'un maillon re�oit le nom du dossier 
		class c_lc_dossier* ajouter(char *ap_nom);
		//ajout d'un fichier
		class c_lc_fichier* ajouter(class c_fichier* ap_fichier);
		//on cherche un fichier si il existe on renvoit la liste des fichiers
		class c_lc_dossier* chercher(char *ap_nom);
		//dossier suivant
		class c_lc_dossier* get_next();
		//dossier pr�c�dent
		class c_lc_dossier* get_prev();
		//nom du dossier courant
		char* get_nom();		
		//liste des fichiers du dossier courant
    	class c_lc_fichier* get_liste_fichier();
		//afficher la liste
		void afficher();
		
};

#endif // LC_DOSSIER_H
