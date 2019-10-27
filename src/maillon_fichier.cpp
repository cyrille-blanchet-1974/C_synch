#include "maillon_fichier.h"
#include "fichier.h"
#include "string.h"
#include "lib.h"


// class constructor
c_maillon_fichier::c_maillon_fichier(c_fichier *fichier)
{
    p_suivant=NULL;
    p_precedent=NULL;
    data= new c_fichier(fichier);
    nom=c_string::strcpy_alloc(nom,fichier->get_name());
}                

		
// class destructor
c_maillon_fichier::~c_maillon_fichier()
{
    if(p_suivant!=NULL) delete p_suivant;
    delete nom;	
    delete data;
}
