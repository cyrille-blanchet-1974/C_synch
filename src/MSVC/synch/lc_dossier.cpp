#include <string.h>
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "string.h"
#include "global.h"

#ifdef  _MSC_VER
#define strcasecmp strcmp
#endif

/***********************************************
*class constructor
*recoit le nom du dossier et la liste de ces fichiers
************************************************/
c_lc_dossier::c_lc_dossier(char* ap_nom)
{
    p_suivant=NULL;
    p_precedent=NULL;
    p_nom=NULL;
    p_lst_fichier=NULL;
    p_nom=c_string::copy_alloc(ap_nom);
    #ifdef DEBUG
    printf("c_lc_dossier constructeur(%s)\n",ap_nom);
    #endif
}                

/***********************************************
* destructeur libère la mémoire
************************************************/		
c_lc_dossier::~c_lc_dossier()
{
    if(p_suivant!=NULL) delete p_suivant;
    p_suivant=NULL;
    p_precedent=NULL;
    if(p_nom!=NULL)delete [] p_nom;	
    p_nom=NULL;
    if(p_lst_fichier!=NULL)delete p_lst_fichier;
    p_lst_fichier=NULL;
}

/***********************************************
* ajouter un maillon
*recoit le nom du dossier et la liste de ces fichiers
************************************************/
class c_lc_dossier* c_lc_dossier::ajouter(char* ap_nom)
{   
class c_lc_dossier *p_return    ;
    //printf("\\");
    if (p_suivant == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
        p_suivant = new c_lc_dossier(ap_nom);
        p_suivant->p_precedent = this;
        p_return= p_suivant;
    }
    else
    {p_return= p_suivant->ajouter(ap_nom);}
    return p_return;
}

/***********************************************
* cherche un dossier
* recoit son nom
*retourne un pointeur sur l'élément trouvé
************************************************/
class c_lc_dossier* c_lc_dossier::chercher(char *ap_nom)
{
    //if(strcmp(p_nom,ap_nom)==0)
    if(strcasecmp(p_nom,ap_nom)==0)
    {return this;} // !!!attention aux dossiers vides!!!
    else
    {
        if (p_suivant == NULL)
        {return NULL;}
        else
        {return p_suivant->chercher(ap_nom);}
    }
}

/***********************************************
* affiche le dossier et ses fichiers
* et apple l'affichage du suivant (si dispo)
************************************************/
void c_lc_dossier::afficher()
{
    printf("Dossier %s\n",p_nom);
    if(p_lst_fichier==NULL)
    {printf("pas de fichiers\n");}
    else
    {p_lst_fichier->afficher();}
    if(p_suivant!=NULL)p_suivant->afficher();
}

/***********************************************
* récupère un pointeur su le dossier suivant
************************************************/
c_lc_dossier* c_lc_dossier::get_next()
{
     return p_suivant;
}              

/***********************************************
* récupère un pointeur su le dossier précédant
************************************************/
c_lc_dossier* c_lc_dossier::get_prev()
{
     return p_precedent;
}              

/***********************************************
* récupère le nom du dossier courant
************************************************/
char* c_lc_dossier::get_nom()
{
      return p_nom;
}      

/***********************************************
* récupère la liste de fichier du dossier courant
************************************************/
c_lc_fichier* c_lc_dossier::get_liste_fichier()
{
     return p_lst_fichier;      
}

/***********************************************
* assigner la liste de fichier
************************************************/
void c_lc_dossier::set_liste_fichier(c_lc_fichier* ap_lst_fichier)
{
     printf("set_liste_fichier\n");
//     p_lst_fichier=ap_lst_fichier;
}     

/***********************************************
* ajouter un fichier
*recoit le fichier
************************************************/
class c_lc_fichier* c_lc_dossier::ajouter(c_fichier* ap_fichier)
{   
    //printf("c_lc_dossier(%s) ajout de (%s)\n",p_nom,ap_fichier->get_name());
    if (p_lst_fichier == NULL)
    {
        //on créé le nouveau maillon et on l'ajoute à la liste
        p_lst_fichier = new c_lc_fichier(ap_fichier);
		return p_lst_fichier;
    }
    else
    {
		return p_lst_fichier->ajouter(ap_fichier);
	}
}

