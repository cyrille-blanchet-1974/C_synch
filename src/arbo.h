/*******************************************************************************
*
*                   Classe de construiction et comparaison d'arboresences
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
//#include "strings.h"

class c_arbo
{
    private:
        c_lc_dossier* p_liste_dossier;
        c_logger *p_logger;
        c_strings  cs_racine;
		c_strings  G_SEPARATOR;
		c_strings  G_WILDCHAR;
		long nb_fic;
		long nb_fold;
		int parcourir(c_strings & cs_chemin);
        void copie_dossier(char * cs_source,char * cs_destination);
        void copie_fichier(char * cs_source,char * cs_destination);
        void supprime_fichier(char * cs_fichier);
        void supprime_dossier(char * cs_dossier);		

    
	public:
		// class constructor
		c_arbo( char *ap_nom,c_logger *logger);
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
		//indiquer la classe d'écriture dans le fichier debug
		void set_debugger(c_logger *ap_logger);
};

#endif // ARBO_H
