#include <string.h>
#include "lc_fichier.h"
#include "fichier.h"
#include <stdio.h>
#include "global.h"

#ifdef  _MSC_VER
#define strcasecmp strcmp
#endif


/***********************************************
*class constructor
*recoit le fichier
************************************************/
c_lc_fichier::c_lc_fichier(c_fichier* ap_fichier)
{
    p_suivant=NULL;
    p_precedent=NULL;
    p_data=NULL;
    //p_nom=NULL;
     
    #ifdef DEBUG
    printf("c_lc_fichier constructeur(%s)\n",ap_fichier->get_name());
    #endif                  
    p_data= new c_fichier(ap_fichier);
    //p_nom=c_string::copy_alloc(p_data->get_name());
    p_nom=p_data->get_name();

    #ifdef DEBUG
    //printf("c_lc_fichier constructeuradn(%s,%s,%s)2\n",ap_fichier->get_name(),p_data->get_name(),p_nom);
    #endif                  
}        

/***********************************************
* destructeur libère la mémoire
************************************************/		
c_lc_fichier::~c_lc_fichier()
{
    if(p_suivant!=NULL) delete p_suivant;
    p_suivant=NULL;
    p_precedent=NULL;
    //if(p_nom!=NULL)delete [] p_nom;	
    //p_nom=NULL;
    if(p_data!=NULL)delete p_data;
    p_data=NULL;
}

/***********************************************
* ajouter un maillon
*recoit le fichier
************************************************/
class c_lc_fichier* c_lc_fichier::ajouter(class c_fichier *ap_fichier)
{   
class c_lc_fichier* p_return;    
    //printf(">");
    if (p_suivant == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
        //printf("c_lc_fichier ajouter new (%s)\n",ap_fichier->get_name());
      /*  if(strcmp(ap_fichier->get_name(),"func_033.js")==0)
        {
           printf("Erreur ici\n");
        }
        if(strcmp(ap_fichier->get_name(),"cap-left.gif")==0)
        {
           printf("Erreur ici\n");
        }*/
        p_suivant = new c_lc_fichier(ap_fichier);
        p_suivant->p_precedent = this;
        p_return = p_suivant;
    }
    else
    {p_return = p_suivant->ajouter(ap_fichier);}
    return p_return;
}

/***********************************************
* cherche un fichier
* recoit son nom
*retourne le fichier ou NULL
************************************************/
c_fichier* c_lc_fichier::chercher(char *ap_cle)
{
    //if(strcmp(p_nom,ap_cle)==0)
    if(strcasecmp(p_nom,ap_cle)==0) 
    {return p_data;} 
    else
    {
        if (p_suivant == NULL)
        {return NULL;}
        else
        {return p_suivant->chercher(ap_cle);}
    }
}

/***********************************************
* affiche le fichier 
* et apple l'affichage du suivant (si dispo)
************************************************/
void c_lc_fichier::afficher()
{
    printf(" %s\n",(char *)p_nom);
    if(p_suivant!=NULL)p_suivant->afficher();
}
        
/***********************************************
* récupère un pointeur su le fichier suivant
************************************************/
c_lc_fichier* c_lc_fichier::get_next()
{
     return p_suivant;
}

/***********************************************
* récupère un pointeur su le fichier précédant
************************************************/
c_lc_fichier* c_lc_fichier::get_prev()
{
     return p_precedent;
}

/***********************************************
* récupère le nom du fichier courant
************************************************/
char* c_lc_fichier::get_nom()
{
      return p_nom;
}      

/***********************************************
* récupère le fichier courant
************************************************/
c_fichier* c_lc_fichier::get_fichier()
{
     return p_data;      
}
