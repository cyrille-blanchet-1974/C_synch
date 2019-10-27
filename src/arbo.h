/*******************************************************************************
*
*                   Classe de construiction et comparaison d'arboresences
*
*******************************************************************************/
#ifndef ARBO_H
#define ARBO_H
#include <stdio.h>
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "logger.h"
#include "global.h"
#include "strings.h"

class c_arbo
{
    private:
        //c_liste_chainee_dossier liste_dossiers;
        c_lc_dossier* p_liste_dossier;
        c_logger *p_logger;
        //char* p_racine;
        c_strings  p_racine;
		//int parcourir(char *chemin);
		int parcourir(c_strings & chemin);
		//char G_SEPARATOR[2];
		c_strings  G_SEPARATOR;
		//char G_WILDCHAR[4];
		c_strings  G_WILDCHAR;

    
	public:
		// class constructor
		c_arbo( char *ap_nom);
		// class destructor
		~c_arbo();
		//recherche les fichiers manquant en destination
	    void fic_en_moins(c_arbo *ap_DST);
	    //recherche les fichiers en trop en destination
		void fic_en_trop(c_arbo *ap_SRC);
		//indiquer la classe décriture ans le fichier
		void set_logger(c_logger *ap_logger);
};

#endif // ARBO_H
