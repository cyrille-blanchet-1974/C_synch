#include <string.h>
#include "lc_fichier.h"
#include "fichier.h"
#include <stdio.h>
#include "global.h"

#ifdef  _MSC_VER
#define strcasecmp _stricmp
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
     
    #ifdef DEBUG
    printf("c_lc_fichier constructeur(%s)\n",ap_fichier->get_name());
    #endif                  
    p_data= new c_fichier(ap_fichier);
    p_nom= p_data->get_pname();
    //on met en majuscule pour pas être emb^té par la casse...
    //nom.upper();    
}        

/***********************************************
* destructeur libère la mémoire
************************************************/		
c_lc_fichier::~c_lc_fichier()
{
    if(p_suivant!=NULL) delete p_suivant;
    p_suivant=NULL;
    p_precedent=NULL;
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
    if (p_suivant == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
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
    if(strcasecmp(p_nom->get(),ap_cle)==0)
    //if(p_nom==ap_cle)
    //(strcasecmp(p_nom,ap_cle)==0) 
    //if(p_nom.compnocase(ap_cle)==0) 
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
    printf(" %s\n",p_nom->get());
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
      return p_nom->get();
}      

/***********************************************
* récupère le fichier courant
************************************************/
c_fichier* c_lc_fichier::get_fichier()
{
     return p_data;      
}
