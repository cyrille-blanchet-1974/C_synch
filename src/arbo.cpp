#include "fichier.h"
#include "arbo.h" 
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>




// class constructor
c_arbo::c_arbo(char * nom)
{
	strcpy(racine.name,nom);
    c_arbo::parcourir(nom,&racine);   
               
}                

int c_arbo::parcourir(char * nom, struct st_repertoire *rep)
{
struct _finddata_t lstr_find;
char ls_chemin[FILENAME_MAX];
char ls_chemin_prochain[FILENAME_MAX];
char ls_nom[FILENAME_MAX];
long ll_handle;
long pos_item = 0;
long pos_item2 = 0;
	sprintf(ls_chemin,"%s\\*.*",nom);
	//printf("%s\n",nom);
    ll_handle =  _findfirst (ls_chemin, &lstr_find);
    do
    {
          rep->items[pos_item].fichier= new c_fichier();
          rep->items[pos_item].fichier->init(lstr_find);
          //si pas spécial
          if(rep->items[pos_item].fichier->is_special()==0)
          {
              if(rep->items[pos_item].fichier->is_dir() == 1)
              {
                   rep->items[pos_item].fichier->get_name(ls_nom);
                   sprintf(ls_chemin_prochain,"%s\\%s",nom,ls_nom);
                   rep->items[pos_item].typ=1;
                   rep->items[pos_item].repertoire = new st_repertoire;
                   strcpy(rep->items[pos_item].repertoire->name,ls_nom);
                   parcourir(ls_chemin_prochain,rep->items[pos_item].repertoire);
              }
              else
              {
              //stocker
                   rep->items[pos_item].typ=0;
                   rep->items[pos_item].repertoire = NULL;
              }
              pos_item++;
              if(pos_item > MAX_ITEMS_PER_REP)
              {
                          printf("Nombre maxi d'objet par répertoire atteint: %i \n",MAX_ITEMS_PER_REP);
                          exit(-1);
              }
          }
          else
          {
              delete rep->items[pos_item].fichier;
          }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    for(pos_item2=pos_item;pos_item2 < MAX_ITEMS_PER_REP;pos_item2++)
    {
      rep->items[pos_item2].typ=-1;
      rep->items[pos_item2].repertoire = NULL;
      rep->items[pos_item2].fichier = NULL;
    }
    
    //delete fic;
    _findclose (ll_handle);
    return 0;
}

void c_arbo::afficher(char * nom, struct st_repertoire *rep)
{
char ls_chemin_prochain[FILENAME_MAX];
char ls_nom[FILENAME_MAX];
long pos_item = 0;            
    printf("%s\n",nom);
    for(pos_item=0;pos_item < MAX_ITEMS_PER_REP;pos_item++)
    {
     switch(rep->items[pos_item].typ)                        
     {
        case 0: 
             //fichier
             rep->items[pos_item].fichier->get_name(ls_nom);
             printf("%s\\%s\n",nom,ls_nom);
             break;
        case 1:
             //répertoire
             //rep.items[pos_item].fichier->get_name(ls_nom);
             sprintf(ls_chemin_prochain,"%s\\%s",nom,rep->items[pos_item].repertoire->name);
             afficher(ls_chemin_prochain,rep->items[pos_item].repertoire);
             break;
       case -1:
             //rien
             break;
     }//switch
    }//for
}

void c_arbo::show()
{
     afficher(racine.name,&racine);
}

// class destructor
c_arbo::~c_arbo()
{
	// insert your code here
}
