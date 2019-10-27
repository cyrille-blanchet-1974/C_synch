#include "maillon_dossier.h"
#include "maillon_fichier.h"
#include "string.h"
#include "lib.h"

// class constructor
c_maillon_dossier::c_maillon_dossier(char* anom)
{
    p_suivant=NULL;
    p_precedent=NULL;
    nom=c_string::strcpy_alloc(nom,anom);
}                

		
// class destructor
c_maillon_dossier::~c_maillon_dossier()
{
    if(p_suivant!=NULL) delete p_suivant;
    delete nom;	
}

c_liste_chainee_fichier* c_maillon_dossier::get_liste_fichier()
{
     return &liste_fichiers;
}                         
