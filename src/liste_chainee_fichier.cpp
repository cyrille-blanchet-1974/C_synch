#include "fichier.h"
#include "liste_chainee_fichier.h"
#include "maillon_fichier.h"
#include <string.h>
#include <stdio.h>


// class constructor
c_liste_chainee_fichier::c_liste_chainee_fichier()
{
    p_tete = NULL;
    p_queue = NULL;               
    p_courant = NULL;
}                

// class destructor
c_liste_chainee_fichier::~c_liste_chainee_fichier()
{
	//liberer les maillon

    //on efface la tête c'est elle qui effacera ci besoin son suivant      
    if(p_tete!=NULL) delete p_tete;

    //RAZ de tous les pointeurs
    p_tete=NULL;
    p_queue=NULL;	
}

int c_liste_chainee_fichier::ajouter(class c_fichier *fichier)
{
    c_maillon_fichier *p_maillon;
    //on créé le nouveau maillon et on l'ajoute à la liste
    p_maillon = new c_maillon_fichier(fichier);
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

c_fichier* c_liste_chainee_fichier::chercher(char *cle)
{
    c_maillon_fichier *p_maillon;
    c_fichier *sortie;
    
    sortie=NULL;
    p_maillon=p_tete;
	while(p_maillon!=NULL)//on stoppe sur le dernier    
	{
              if(strcmp(cle , p_maillon->nom)==0)
              {
                      sortie=p_maillon->data;
                      return sortie;
              }
              else
              {                      
                  //maillon suivant
                  p_maillon=p_maillon->p_suivant;
              }                     
    };
    return sortie;
}
		

c_fichier* c_liste_chainee_fichier::get_next(bool restart)
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
      return p_courant->data;      
}



void c_liste_chainee_fichier::afficher()
{
    c_maillon_fichier *p_maillon;
    
    p_maillon=p_tete;
    if(p_maillon==NULL)
    {
        printf("Pas de fichiers!!\n");
    }
    else
    {
    	do
    	{
             p_maillon->data->afficher();
            //maillon suivant
            p_maillon=p_maillon->p_suivant;
        }while(p_maillon!=NULL);//on stoppe sur le dernier
    }    
}
