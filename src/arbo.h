/*******************************************************************************
*
*                   Classe de construction et comparaison d'arboresences
*
*******************************************************************************/
#ifndef ARBO_H
#define ARBO_H
#include <stdio.h>
#include <windows.h> //mutex
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "logger.h"
#include "global.h"
#include "ignore_list.h"
//#include "strings.h"




class c_arbo
{
    private:
        c_lc_dossier*     p_liste_dossier;
        c_logger*         p_logger;
        c_strings         cs_racine;
		c_ignore_list     lc_ignore_list;
		long              nb_fic;
		long              nb_fold;
		bool              b_verbose;
		int parcourir(char *a_chemin);

    
	public:
		// class constructor
		c_arbo( char *ap_nom,c_logger *logger,bool b_verbose);
		// class destructor
		~c_arbo();
		//lance le parcours de l'arboresence
		void parcourir();
		//recherche les fichiers manquant en destination
	    void fic_en_moins(c_arbo *ap_DST);
	    //recherche les fichiers en trop en destination
		void fic_en_trop(c_arbo *ap_SRC);
		//indiquer l'état (nb fichier et nb dossiers
		void get_status(long *nb_folders,long *nb_files);
		//indiquer l'état (nb fichier et nb dossiers
		void get_status();
};

#endif // ARBO_H
