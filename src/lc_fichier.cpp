#include <string.h>
#include "lc_fichier.h"
#include "fichier.h"
#include "string.h"
#include "global.h"



// class constructor
c_lc_fichier::c_lc_fichier(c_fichier* fichier)
{
    p_suivant=NULL;
    p_precedent=NULL;
   
    data= new c_fichier(fichier);
    nom=c_string::strcpy_alloc(nom,fichier->get_name());
}                

		
// class destructor
c_lc_fichier::~c_lc_fichier()
{
    if(p_suivant!=NULL) delete p_suivant;
    delete nom;	
    delete data;
}



class c_fichier * c_lc_fichier::ajouter(class c_fichier *fichier)
{   
    if (p_suivant == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
        p_suivant = new c_lc_fichier(fichier);
        p_suivant->p_precedent = this;
    }
    else
    {return p_suivant->ajouter(fichier);}
    return 0;
}

c_fichier* c_lc_fichier::chercher(char *cle)
{
    if(strcmp(nom,cle)==0)
    {return data;} 
    else
    {
        if (p_suivant == NULL)
        {return NULL;}
        else
        {return p_suivant->chercher(cle);}
    }
}

void c_lc_fichier::afficher()
{
    printf(" %s\n",nom);
    if(p_suivant!=NULL)p_suivant->afficher();
}
        

//récupèrer un pointeur vers le chainon suivant
c_lc_fichier* c_lc_fichier::get_next()
{
     return p_suivant;
}

//récupèrer un pointeur vers le chainon précédent
c_lc_fichier* c_lc_fichier::get_prev()
{
     return p_precedent;
}

char* c_lc_fichier::get_nom()
{
      return nom;
}      

c_fichier* c_lc_fichier::get_fichier()
{
     return data;      
}
