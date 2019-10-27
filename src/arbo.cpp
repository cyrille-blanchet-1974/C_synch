#include "arbo.h" 
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "string.h"
#include "logger.h"
#include <stdio.h> //printf
#include <string.h> //str*



// class constructor
c_arbo::c_arbo(char * nom)
{   
    racine=c_string::strcpy_alloc(racine,nom); 
    liste_dossier=NULL;
    c_arbo::parcourir(nom);   
    #ifdef DEBUG
    liste_dossier->afficher();                 
    #endif
}                

// class destructor
c_arbo::~c_arbo()
{                           
	// insert your code here
	delete racine;
	delete liste_dossier;
	
}

void c_arbo::set_logger(c_logger *ap_logger)
{
     p_logger=ap_logger;
}


int c_arbo::parcourir(char * chemin)
{
c_lc_fichier *lst_fic;
c_fichier fichier;
struct _finddata_t lstr_find;
char* ls_chemin;
char* ls_nom;
char *cle;
long ll_handle;
   #ifdef DEBUG
   printf("Parcours %s \n",chemin);
   #endif
   lst_fic=NULL;
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

              //si c'est un dossier
             if (lstr_find.attrib & _A_SUBDIR)
             {
                   parcourir(ls_nom);
             }
             else
             {
                  fichier.init(lstr_find);
                  if(lst_fic==NULL)
                  {lst_fic=new c_lc_fichier(&fichier);}
                  else
                  {lst_fic->ajouter(&fichier);}
             }
             delete ls_nom;     
         }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    cle=chemin;
    //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
    cle = cle+strlen(racine);
    if(liste_dossier==NULL)
    {liste_dossier=new c_lc_dossier(cle,lst_fic);}
    else
    {liste_dossier->ajouter(cle,lst_fic);}
    _findclose (ll_handle);
    delete ls_chemin;
    return 0;
}



void c_arbo::fic_en_moins(c_arbo *DST)
{
 //parcourir les dossier sources
c_lc_dossier *dossier_src,*dossier_dst,*dossier_sav;
c_lc_fichier *fichier_src,*fichier_dst;
c_fichier *fic_src,*fic_dst;
long li_copy,len;
char ls_commande[MAX_CHAINE];

      dossier_src = liste_dossier;            
      while( dossier_src!=NULL)
      {
         //cherche le dossier en destination    
         fichier_dst = DST->liste_dossier->chercher(dossier_src->get_nom());
         if(fichier_dst == NULL)
         {
            //non trouvé            
             #ifdef DEBUG
             sprintf(ls_commande,"Echo répertoire %s%s non trouvé !!!\n",DST->racine,dossier_src->get_nom());
             p_logger->add(ls_commande);
             #endif
             sprintf(ls_commande,"xcopy \"%s%s\\*.*\" \"%s%s\\\" /E /I /H /Y /K \n",racine,dossier_src->get_nom(),DST->racine,dossier_src->get_nom());
             p_logger->add(ls_commande);
             //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
             strcpy(ls_commande,dossier_src->get_nom());
             strcat(ls_commande,"\\");
             len=strlen(ls_commande);
             dossier_sav=dossier_src;
             do
             {
                 dossier_src = dossier_src->get_next();                        //on boucle
                 if(dossier_src!=NULL)dossier_sav=dossier_src;
             }while( (dossier_src!=NULL) && (strncmp(ls_commande,dossier_src->get_nom(),len)==0) ); //tant que même début et pas arrivé à la fin
             if(dossier_src==NULL)
             {dossier_src=dossier_sav;}
             else
             {dossier_src = dossier_src->get_prev();} //on revien d'un cran car plus bas il y a un next...
             
         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             fichier_src = dossier_src->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers sources
             while( fichier_src!=NULL)
             {
                 fic_src=fichier_src->get_fichier();   
                 fic_dst=fichier_dst->chercher(fic_src->get_name());
                 if(fic_dst==NULL)
                 {
                      #ifdef DEBUG
                      sprintf(ls_commande,"echo Fichier %s%s\\%s non trouvé!!!\n",DST->racine,dossier_src->get_nom(),fic_src->get_name());
                      p_logger->add(ls_commande);
                      #endif
                      sprintf(ls_commande,"xcopy \"%s%s\\%s\" \"%s%s\"  /H /Y /K \n",racine,dossier_src->get_nom(),fic_src->get_name(),DST->racine,dossier_src->get_nom());
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                       li_copy=0;
                       //le copier
                       if (fic_src->get_size()        != fic_dst->get_size())        
                       {
                          #ifdef DEBUG                            
                          sprintf(ls_commande,"Echo Fichier %s%s\\%s taille différente!!!\n",DST->racine,dossier_src->get_nom(),fic_src->get_name());
                          p_logger->add(ls_commande);
                          #endif
                          li_copy=1;
                        }
                        if (fic_src->get_time_write()  != fic_dst->get_time_write())  
                        {
                            #ifdef DEBUG                           
                            sprintf(ls_commande,"Echo Fichier %s%s\\%s heure de modification différente!!!\n",DST->racine,dossier_src->get_nom(),fic_src->get_name());
                            p_logger->add(ls_commande);
                            #endif
                            li_copy=1;
                        }
                        if (li_copy==1) 
                        {
                          sprintf(ls_commande,"xcopy \"%s%s\\%s\" \"%s%s\"  /H /Y /K \n",racine,dossier_src->get_nom(),fic_src->get_name(),DST->racine,dossier_src->get_nom());
                          p_logger->add(ls_commande);         
                        }

                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 fichier_src= fichier_src->get_next();                
              }
           
         }
         //et on avance au maillon suivant
         dossier_src = dossier_src->get_next();            
      };       
}

void c_arbo::fic_en_trop(c_arbo *SRC)
{

 //parcourir les dossier destination
c_lc_dossier *dossier_src,*dossier_dst;
c_lc_fichier *fichier_src,*fichier_dst;
c_fichier *fic_src,*fic_dst;
long li_copy;
char ls_commande[MAX_CHAINE];

      dossier_dst = liste_dossier;            
      while( dossier_dst!=NULL)
      {
         //cherche le dossier en source
         fichier_src = SRC->liste_dossier->chercher(dossier_dst->get_nom());
         if(fichier_src == NULL)
         {
            //non trouvé            
            #ifdef DEBUG
            sprintf(ls_commande,"Echo Le répertoire %s%s n'existe plus.\n",racine,dossier_dst->get_nom());
            p_logger->add(ls_commande);
            #endif
            sprintf(ls_commande,"RD /S /Q \"%s%s\" \n",racine,dossier_dst->get_nom());
            p_logger->add(ls_commande);

         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             fichier_dst = dossier_dst->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers sources
             while( fichier_dst!=NULL)
             {
                 fic_dst=fichier_dst->get_fichier();   
                 fic_src=fichier_src->chercher(fic_dst->get_name());
                 if(fic_src==NULL)
                 {
                      #ifdef DEBUG            
                      sprintf(ls_commande,"Echo Le fichier %s%s\\%s n'existe plus.\n",racine,dossier_dst->get_nom(),fic_dst->get_name());
                      p_logger->add(ls_commande);
                      #endif
                      sprintf(ls_commande,"DEL \"%s%s\\%s\" /A \n",racine,dossier_dst->get_nom(),fic_dst->get_name());
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                     //pas besoin de comparer on l'a fait précédemment!
                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 fichier_dst= fichier_dst->get_next();                
              }

         }
         //et on avance au maillon suivant
         dossier_dst = dossier_dst->get_next();            
      };       
}


