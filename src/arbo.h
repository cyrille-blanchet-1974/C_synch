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
//#include "strings.h"

class c_arbo
{
    private:
        c_lc_dossier* p_liste_dossier;
        c_logger *p_logger;
        c_strings  p_racine;
		int parcourir(c_strings & chemin);
		c_strings  G_SEPARATOR;
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
		//indiquer la classe d�criture ans le fichier
		void set_logger(c_logger *ap_logger);
};

#endif // ARBO_H
