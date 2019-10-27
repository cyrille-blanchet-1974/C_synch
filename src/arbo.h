#ifndef ARBO_H
#define ARBO_H
#include <stdio.h>
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "logger.h"
#include "global.h"

class c_arbo
{
    private:
        //c_liste_chainee_dossier liste_dossiers;
        c_lc_dossier* liste_dossier;
        c_logger *p_logger;
        char* racine;
		int parcourir(char *chemin);
    
	public:
		// class constructor
		c_arbo( char *nom);
		// class destructor
		~c_arbo();
	    void fic_en_moins(c_arbo *DST);
		void fic_en_trop(c_arbo *SRC);
		void set_logger(c_logger *ap_logger);
};

#endif // ARBO_H
