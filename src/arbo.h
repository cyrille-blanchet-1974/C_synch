#ifndef ARBO_H
#define ARBO_H

#include <stdio.h>
#include "liste_chainee_dossier.h"
#include "liste_chainee_fichier.h"
#include "logger.h"
#include "global.h"

/*
 * No description
 */
class c_arbo
{
    private:
        c_liste_chainee_dossier liste_dossiers;
        c_logger *p_logger;
        char* racine;
		int parcourir(char *chemin,c_liste_chainee_fichier *liste_fic);
    
	public:
		// class constructor
		c_arbo( char *nom);
		// class destructor
		~c_arbo();
	    void fic_en_moins(c_arbo *DST);
		void fic_en_trop(c_arbo *SRC);
		class c_liste_chainee_dossier* get_liste_dossier();
		char* get_racine();
		void set_logger(c_logger *ap_logger);
};

#endif // ARBO_H
