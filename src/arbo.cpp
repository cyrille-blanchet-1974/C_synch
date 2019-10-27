#include "arbo.h" 
#include "liste_chainee_dossier.h"
#include "liste_chainee_fichier.h"
#include "maillon_fichier.h"
#include "maillon_dossier.h"
#include "string.h"
#include "logger.h"
#include "lib.h"

#include <stdio.h> //printf
#include <string.h> //str*



// class constructor
c_arbo::c_arbo(char * nom)
{
    c_liste_chainee_fichier *liste_fic;
    
    racine=c_string::strcpy_alloc(racine,nom);
    
   
	liste_fic = liste_dossiers.ajouter("");
    c_arbo::parcourir(nom,liste_fic);   
    #ifdef DEBUG
    liste_dossiers.afficher();                 
    #endif
}                

// class destructor
c_arbo::~c_arbo()
{                           
	// insert your code here
	delete racine;
	
}

void c_arbo::set_logger(c_logger *ap_logger)
{
     p_logger=ap_logger;
}


int c_arbo::parcourir(char * chemin,c_liste_chainee_fichier *liste_fic)
{
c_liste_chainee_fichier *lliste_fic;
c_fichier fichier;
struct _finddata_t lstr_find;
char* ls_chemin;
char* ls_nom;
char *cle;
long ll_handle;
   #ifdef DEBUG
   printf("Parcours %s \n",chemin);
   #endif
   ls_chemin = c_string::strcpy_alloc(ls_chemin,chemin);
   ls_chemin = c_string::strcat_alloc(ls_chemin,"\\*.*");
   ll_handle =  _findfirst (ls_chemin, &lstr_find);
    do
    {
          //ignorer les fichiers .  ..       et le volume du disque
         if( (strcmp(lstr_find.name,".")!=0) && 
             (strcmp(lstr_find.name,"..")!=0) && 
            !(lstr_find.attrib & _A_VOLID)  && 
             (strcmp(lstr_find.name,"System Volume Information")!=0) && 
             (strcmp(lstr_find.name,"RECYCLER")!=0) )
         {
              ls_nom=c_string::strcpy_alloc(ls_nom,chemin);
              ls_nom=c_string::strcat_alloc(ls_nom,"\\");
              ls_nom=c_string::strcat_alloc(ls_nom,lstr_find.name);
              cle=ls_nom;
              //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
              cle = cle+strlen(racine);
              //si c'est un dossier
             if (lstr_find.attrib & _A_SUBDIR)
             {
                   lliste_fic = liste_dossiers.ajouter(cle);               
                   parcourir(ls_nom,lliste_fic);
             }
             else
             {
                  fichier.init(lstr_find,cle);
                  liste_fic->ajouter(&fichier);
             }
             delete ls_nom;     
         }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    _findclose (ll_handle);
    delete ls_chemin;
    return 0;
}



c_liste_chainee_dossier* c_arbo::get_liste_dossier()
{
   return &liste_dossiers;
}

char* c_arbo::get_racine()
{
      return racine;
}

void c_arbo::fic_en_moins(c_arbo *DST)
{
 //parcourir les dossier sources
c_maillon_dossier *maillon_dossier,*maillon_dossier2;
c_fichier *fic_src,*fic_dst;
c_liste_chainee_fichier *lst_fic_src,*lst_fic_dst;
long li_copy,len;
char ls_commande[MAX_CHAINE];

      maillon_dossier = liste_dossiers.get_next(true);            
      while( maillon_dossier!=NULL)
      {
         //cherche le dossier en destination    
         lst_fic_dst = DST->liste_dossiers.chercher(maillon_dossier->nom);
         if(lst_fic_dst == NULL)
         {
            //non trouvé            
             #ifdef DEBUG
             sprintf(ls_commande,"Echo répertoire %s%s non trouvé !!!\n",DST->racine,maillon_dossier->nom);
             p_logger->add(ls_commande);
             #endif
             sprintf(ls_commande,"xcopy \"%s%s\\*.*\" \"%s%s\\\" /E /I /H /Y /K \n",racine,maillon_dossier->nom,DST->racine,maillon_dossier->nom);
             p_logger->add(ls_commande);
             //comme on copie un dossier entier, on saute tou ces fichiers et sous-dossiers
             strcpy(ls_commande,maillon_dossier->nom);
             strcat(ls_commande,"\\");
             len=strlen(ls_commande);
             maillon_dossier2=maillon_dossier;
             do
             {
                 maillon_dossier2=liste_dossiers.get_next(false);            //on boucle
             }while( (maillon_dossier!=NULL) && (strncmp(ls_commande,maillon_dossier2->nom,len)==0) ); //tant que même début et pas arrivé à la fin
             maillon_dossier=maillon_dossier2;
         }   
         else
         {
             //trouvé -> comparer lmes listes de fichiers
             lst_fic_src =     maillon_dossier->get_liste_fichier();
             if(lst_fic_src != NULL)//normalement impossible car liste_fichiers n'est pas un pointeur mais un attribut en dur
             {
                 //maintenant on boucle sur la liste des fichiers sources
                 fic_src= lst_fic_src->get_next(true);            
                 while( fic_src!=NULL)
                 {
                     fic_dst=lst_fic_dst->chercher(fic_src->get_name());
                     if(fic_dst==NULL)
                     {
                          #ifdef DEBUG
                          sprintf(ls_commande,"echo Fichier %s%s\\%s non trouvé!!!\n",DST->racine,maillon_dossier->nom,fic_src->get_name());
                          p_logger->add(ls_commande);
                          #endif
                          sprintf(ls_commande,"xcopy \"%s%s\\%s\" \"%s%s\"  /H /Y /K \n",racine,maillon_dossier->nom,fic_src->get_name(),DST->racine,maillon_dossier->nom);
                          p_logger->add(ls_commande);
                     }
                     else
                     {
                           li_copy=0;
                           //le copier
                           if (fic_src->get_size()        != fic_dst->get_size())        
                           {
                              #ifdef DEBUG                            
                              sprintf(ls_commande,"Echo Fichier %s%s\\%s taille différente!!!\n",DST->racine,maillon_dossier->nom,fic_src->get_name());
                              p_logger->add(ls_commande);
                              #endif
                              li_copy=1;
                            }
                            if (fic_src->get_time_write()  != fic_dst->get_time_write())  
                            {
                                #ifdef DEBUG                           
                                sprintf(ls_commande,"Echo Fichier %s%s\\%s heure de modification différente!!!\n",DST->racine,maillon_dossier->nom,fic_src->get_name());
                                p_logger->add(ls_commande);
                                #endif
                                li_copy=1;
                            }
                            if (li_copy==1) 
                            {
                              sprintf(ls_commande,"xcopy \"%s%s\\%s\" \"%s%s\"  /H /Y /K \n",racine,maillon_dossier->nom,fic_src->get_name(),DST->racine,maillon_dossier->nom);
                              p_logger->add(ls_commande);         
                            }
    
                     }//endif fic_dst!=NULL
                     //et on avance au maillon suivant
                     fic_src= lst_fic_src->get_next(false);                
                  }
             }//fin if lst_fic_src != NULL
         }
         //et on avance au maillon suivant
         maillon_dossier = liste_dossiers.get_next(false);                
      };       
}

void c_arbo::fic_en_trop(c_arbo *SRC)
{
 //parcourir les dossier destination
c_maillon_dossier *maillon_dossier;
c_fichier *fic_src,*fic_dst;
c_liste_chainee_fichier *lst_fic_src,*lst_fic_dst;
long li_copy;
char ls_commande[MAX_CHAINE];

      maillon_dossier = liste_dossiers.get_next(true);            
      while( maillon_dossier!=NULL)
      {
         //cherche le dossier en source
         lst_fic_src = SRC->liste_dossiers.chercher(maillon_dossier->nom);
         if(lst_fic_src == NULL)
         {
            //non trouvé            
            #ifdef DEBUG
            sprintf(ls_commande,"Echo Le répertoire %s%s n'existe plus.\n",racine,maillon_dossier->nom);
            p_logger->add(ls_commande);
            #endif
            sprintf(ls_commande,"RD /S /Q \"%s%s\" \n",racine,maillon_dossier->nom);
            p_logger->add(ls_commande);

         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             lst_fic_dst =     maillon_dossier->get_liste_fichier();
             if(lst_fic_dst != NULL)//normalement impossible car liste_fichiers n'est pas un pointeur mais un attribut en dur
             {
                 //maintenant on boucle sur la liste des fichiers sources
                 fic_dst= lst_fic_dst->get_next(true);            
                 while( fic_dst!=NULL)
                 {
                     //printf("recherche du fichier %s en destination\n",fic_src->get_name());   
                     fic_src=lst_fic_src->chercher(fic_dst->get_name());
                     if(fic_src==NULL)
                     {
                          #ifdef DEBUG            
                          sprintf(ls_commande,"Echo Le fichier %s%s\\%s n'existe plus.\n",racine,maillon_dossier->nom,fic_dst->get_name());
                          p_logger->add(ls_commande);
                          #endif
                          sprintf(ls_commande,"DEL \"%s%s\\%s\" /A \n",racine,maillon_dossier->nom,fic_dst->get_name());
                          p_logger->add(ls_commande);
                     }
                     else
                     {
                         //pas besoin de comparer on l'a fait précédemment!
                     }//endif fic_dst!=NULL
                     //et on avance au maillon suivant
                     fic_dst= lst_fic_dst->get_next(false);                
                  }
             }//fin if lst_fic_src != NULL
         }
         //et on avance au maillon suivant
         maillon_dossier = liste_dossiers.get_next(false);                
      };       
}


