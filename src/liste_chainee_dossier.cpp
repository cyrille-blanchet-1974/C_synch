#include "liste_chainee_dossier.h"
#include "liste_chainee_fichier.h"
#include "maillon_dossier.h"

#include <string.h>
#include <stdio.h>

// class constructor
c_liste_chainee_dossier::c_liste_chainee_dossier()
{
    p_tete = NULL;
    p_queue = NULL;               
    p_courant = NULL;
}                

// class destructor
c_liste_chainee_dossier::~c_liste_chainee_dossier()
{
	//liberer les maillon

    //on efface la tête c'est elle qui effacera ci besoin son suivant 
    if(p_tete!=NULL) delete p_tete;
    //RAZ de tous les pointeurs
    p_tete=NULL;
    p_queue=NULL;	
}

c_liste_chainee_fichier* c_liste_chainee_dossier::ajouter(char* anom)
{
    c_maillon_dossier *p_maillon;
    //on créé le nouveau maillon et on l'ajoute à la liste
    p_maillon = new c_maillon_dossier(anom);
    if(p_tete == NULL)
    {
        //pas encore de maillon?
        p_tete=p_maillon;
    }
    else
    {
        //sinon on ajoute le maillon en fin de chaine
        p_queue->p_suivant=p_maillon;
        p_maillon->p_precedent=p_queue;
    }
    //le maillon ajouté est la nouvelle queue
    p_queue=p_maillon;
    return &p_maillon->liste_fichiers;
}

c_liste_chainee_fichier* c_liste_chainee_dossier::chercher(char *cle)
{
    c_maillon_dossier *p_maillon;
    c_liste_chainee_fichier* sortie;
    bool trouvee=false;
    
    sortie=NULL;
    p_maillon=p_tete;
    
	while(	!trouvee && p_maillon!=NULL)//on stoppe sur le dernier
	{
              if(strcmp(cle , p_maillon->nom)==0)
              {
                      trouvee = true;
                      sortie=&p_maillon->liste_fichiers;
              }
              else
              {                      
                  //maillon suivant
                  p_maillon=p_maillon->p_suivant;
                  }                     
    };
    return sortie;
}
		

c_maillon_dossier* c_liste_chainee_dossier::get_next(bool restart)
{
      if(restart) 
      {
          p_courant=p_tete;
      }
      else
      {
          p_courant=p_courant->p_suivant;
      }
      if(p_courant == NULL) return NULL;
      return p_courant;      
}

void c_liste_chainee_dossier::afficher()
{
    c_maillon_dossier *p_maillon;
    
    p_maillon=p_tete;
	do
	{
        printf("Dossier : %s\n", p_maillon->nom);
        p_maillon->liste_fichiers.afficher();
        //maillon suivant
        p_maillon=p_maillon->p_suivant;
    }while(p_maillon!=NULL);//on stoppe sur le dernier
}
