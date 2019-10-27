#include <string.h>
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "string.h"
#include "global.h"

// class constructor
c_lc_dossier::c_lc_dossier(char* anom,c_lc_fichier* alst_fichier)
{
    p_suivant=NULL;
    p_precedent=NULL;
    nom=c_string::strcpy_alloc(nom,anom);
    lst_fichier = alst_fichier;    
}                

		
// class destructor
c_lc_dossier::~c_lc_dossier()
{
    if(p_suivant!=NULL) delete p_suivant;
    delete nom;	
    delete lst_fichier;
}



class c_lc_fichier* c_lc_dossier::ajouter(char* anom,c_lc_fichier* alst_fichier)
{   
    if (p_suivant == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
        p_suivant = new c_lc_dossier(anom,alst_fichier);
        p_suivant->p_precedent = this;
    }
    else
    {return p_suivant->ajouter(anom,alst_fichier);}
    return NULL;
}

c_lc_fichier* c_lc_dossier::chercher(char *anom)
{
    if(strcmp(nom,anom)==0)
    {return lst_fichier;} 
    else
    {
        if (p_suivant == NULL)
        {return NULL;}
        else
        {return p_suivant->chercher(anom);}
    }
}

void c_lc_dossier::afficher()
{
    printf("Dossier %s\n",nom);
    if(lst_fichier==NULL)
    {printf("pas de fichiers\n");}
    else
    {lst_fichier->afficher();}
    if(p_suivant!=NULL)p_suivant->afficher();
}

//récupèrer un pointeur vers le chainon suivant
c_lc_dossier* c_lc_dossier::get_next()
{
     return p_suivant;
}              

//récupèrer un pointeur vers le chainon suivant
c_lc_dossier* c_lc_dossier::get_prev()
{
     return p_precedent;
}              

char* c_lc_dossier::get_nom()
{
      return nom;
}      

c_lc_fichier* c_lc_dossier::get_liste_fichier()
{
     return lst_fichier;      
}
