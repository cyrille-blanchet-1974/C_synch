#include "fichier.h"
#include "liste_chainee.h"
#include "maillon.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>




// class constructor
c_liste_chainee::c_liste_chainee()
{
    p_tete = NULL;
    p_queue = NULL;               
    p_courant = NULL;
}                

int c_liste_chainee::ajouter(char *cle, struct _finddata_t data, char *chemin)
{
    c_maillon *p_maillon;
    //on créé le nouveau maillon et on l'ajoute à la liste
    p_maillon = new c_maillon(cle,data,chemin);
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
    return 0;
}


c_fichier* c_liste_chainee::chercher(char *cle)
{
    c_maillon *p_maillon;
    c_fichier *sortie;
    bool trouvee=false;
    
    sortie=NULL;
    p_maillon=p_tete;
	do
	{
              if(strcmp(cle , p_maillon->cle)==0)
              {
                      trouvee = true;
                      sortie=p_maillon->data;
              }
              else
              {                      
                  //maillon suivant
                  p_maillon=p_maillon->p_suivant;
                  }                     
    }while(	!trouvee && p_maillon!=NULL);//on stoppe sur le dernier
    return sortie;
      
}
		
// class destructor
c_liste_chainee::~c_liste_chainee()
{
	//liberer les maillon
	c_maillon *p_maillon;
	do
	{
              //sauve la suite de la tete 
              p_maillon=p_tete->p_suivant;
              //efface la tete
              delete p_tete;
              //nouvelle tete= suivant
              p_tete=p_maillon;
                     
    }while(	p_maillon != NULL);//on stoppe sur le dernier
    //RAZ de tous les pointeurs
    p_maillon=NULL;
    p_tete=NULL;
    p_queue=NULL;	
}

char* c_liste_chainee::get_next(bool restart)
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
      return p_courant->cle;      
}
