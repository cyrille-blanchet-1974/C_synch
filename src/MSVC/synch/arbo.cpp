#include "arbo.h" 
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "string.h"
#include "logger.h"
#include <stdio.h> //printf
#include <string.h> //str*

/***********************************************
* constructeur de la classe
* Entrée: racine de l'arboresence
************************************************/
c_arbo::c_arbo(char *ap_nom)
{   
char* p_tmp;    
    //constantes
    G_SEPARATOR[0] = '\\';  
    G_SEPARATOR[1] = '\0';  
    G_WILDCHAR[0] = '*';
    G_WILDCHAR[1] = '.';
    G_WILDCHAR[2] = '*';
    G_WILDCHAR[3] = '\0';
    
    p_racine=NULL;
    //init pointeur liste de dossier
    p_liste_dossier=NULL;   
    p_logger=NULL;
    //sauve la racine
    p_racine=c_string::copy_alloc(ap_nom); 

    p_tmp=c_string::concat_alloc(p_racine,"\\");

    //parcourir l'arborescence
    c_arbo::parcourir(p_tmp);   
    delete [] p_tmp;
    #ifdef DEBUG
    //affichage
    p_liste_dossier->afficher();                 
    #endif
}                

/***********************************************
* destructeur de la classe
*
************************************************/
c_arbo::~c_arbo()
{                           
	// on libère la mémoire
	if(p_racine!=NULL) delete [] p_racine;
	p_racine=NULL;
	if(p_liste_dossier!=NULL)delete p_liste_dossier;
	p_liste_dossier=NULL;
	p_logger=NULL;	
}

/***********************************************
*  indique a la classe le logger
*  Entrée: la classe logger
************************************************/
void c_arbo::set_logger(c_logger *ap_logger)
{
     p_logger=ap_logger;
}

/***********************************************
* parcourir: parcours l'arborescence et stocke 
* les données (FONCTION RECURSIVE
* Entrée: le nom du dossier à scanner
************************************************/
int c_arbo::parcourir(char * ap_chemin)
{
c_lc_dossier *p_lst_dossier=NULL;//pointeur sur le maillon dossier actuel
c_lc_fichier *p_lst_fic_tete=NULL,*p_lst_fic_courant=NULL;
c_fichier fichier;
struct _finddata_t lstr_find;
char* p_chemin=NULL;
char* p_nom=NULL;
char* p_cle=NULL;
long ll_handle;
   #ifdef DEBUG
   printf("Parcours début: %s \n",ap_chemin);
   #endif
   
   p_cle=ap_chemin;
   //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
   p_cle = p_cle+strlen(p_racine);
   //si pas encore de tête
   if(p_liste_dossier==NULL)
   {     //créer le premier maillon
         p_liste_dossier=new c_lc_dossier(p_cle);
         //pointeur actuel = tête
         p_lst_dossier=p_liste_dossier;
   }
   else
   {p_lst_dossier=p_liste_dossier->ajouter(p_cle);}//sinon ajouter un maillon et récupèrer un pointeur dessus       
   p_chemin = c_string::concat_alloc(ap_chemin,G_WILDCHAR);
   if(p_chemin==NULL){printf("erreur allocation\n");return -1;}
   ll_handle =  _findfirst (p_chemin, &lstr_find);
   if(ll_handle<0)printf("erreur findfirst %s\n",p_chemin);
    do
    {
         fichier.init(lstr_find);
         //ignorer les fichiers .  ..       et le volume du disque
         if(fichier.is_special()==0)
         {
             //si c'est un dossier
             if(fichier.is_dir())
             {
                   p_nom=c_string::concat_alloc(ap_chemin,lstr_find.name,G_SEPARATOR);
                   if(p_nom==NULL){printf("erreur allocation\n");return -1;}
                   parcourir(p_nom);
                   if(p_nom!=NULL)delete [] p_nom;     
                   p_nom=NULL;
             }
             else
             {
                 if(p_lst_fic_tete==NULL)
                 {
                    p_lst_fic_courant = p_lst_dossier->ajouter(&fichier);
                    p_lst_fic_courant = p_lst_fic_tete;
                 }
                 else
                 {
                     p_lst_fic_courant = p_lst_fic_courant->ajouter(&fichier);
                 }   
             }
         }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    _findclose (ll_handle);
    if(p_chemin!=NULL)delete [] p_chemin;
    return 0;
}

/***********************************************
* cherche les fichiers manquant en destination
*Entrée: arboresence destination
************************************************/
void c_arbo::fic_en_moins(c_arbo *ap_DST)
{
 //parcourir les dossier sources
c_lc_dossier *p_ldossier_src,*p_ldossier_dst,*p_ldossier_sav;
c_lc_fichier *p_lfichier_src,*p_lfichier_dst;
c_fichier *p_fic_src,*p_fic_dst;
long li_copy,len;
char ls_commande[MAX_CHAINE];

      p_ldossier_src = p_liste_dossier;            
      while( p_ldossier_src!=NULL)
      {
         //cherche le dossier en destination    
         p_ldossier_dst = ap_DST->p_liste_dossier->chercher(p_ldossier_src->get_nom());
         //p_lfichier_dst = ap_DST->p_liste_dossier->chercher(p_ldossier_src->get_nom());
         //if(p_lfichier_dst == NULL)
         if(p_ldossier_dst == NULL)
         {
            //non trouvé            
             #ifdef VERBOSE
             sprintf(ls_commande,"Echo répertoire %s%s non trouvé !!!\n",ap_DST->p_racine,p_ldossier_src->get_nom());
             p_logger->add(ls_commande);
             #endif
             sprintf(ls_commande,"xcopy \"%s%s*.*\" \"%s%s\" /E /I /H /Y /K \n",p_racine,p_ldossier_src->get_nom(),ap_DST->p_racine,p_ldossier_src->get_nom());
             p_logger->add(ls_commande);
             //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
             strcpy(ls_commande,p_ldossier_src->get_nom());
             //strcat(ls_commande,"\\");
             len=strlen(ls_commande);
             p_ldossier_sav=p_ldossier_src;
             do
             {
                 p_ldossier_src = p_ldossier_src->get_next();     //on boucle
                 if(p_ldossier_src!=NULL)p_ldossier_sav=p_ldossier_src;
                 //printf("%s %s %di\n",ls_commande,p_ldossier_src->get_nom(),len);
             }while( (p_ldossier_src!=NULL) && (strncmp(ls_commande,p_ldossier_src->get_nom(),len)==0) ); //tant que même début et pas arrivé à la fin
             if(p_ldossier_src==NULL)
             {p_ldossier_src=p_ldossier_sav;}
             else
             {p_ldossier_src = p_ldossier_src->get_prev();} //on revient d'un cran car plus bas il y a un next...
             
         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             p_lfichier_dst = p_ldossier_dst->get_liste_fichier();//
             p_lfichier_src = p_ldossier_src->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers sources
             while( p_lfichier_src!=NULL)
             {
                 p_fic_src=p_lfichier_src->get_fichier();   
                 if(p_lfichier_dst==NULL)
                 {p_fic_dst=NULL;}
                 else
                 {p_fic_dst=p_lfichier_dst->chercher(p_fic_src->get_name());}
                 if(p_fic_dst==NULL)
                 {
                      #ifdef VERBOSE
                      sprintf(ls_commande,"echo Fichier %s%s\\%s non trouvé!!!\n",ap_DST->p_racine,p_ldossier_src->get_nom(),p_fic_src->get_name());
                      p_logger->add(ls_commande);
                      #endif
                      sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /H /Y /K \n",p_racine,p_ldossier_src->get_nom(),p_fic_src->get_name(),ap_DST->p_racine,p_ldossier_src->get_nom());
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                       li_copy=0;
                       //le copier
                       if (p_fic_src->get_size()        != p_fic_dst->get_size())        
                       {
                          #ifdef VERBOSE                            
                          sprintf(ls_commande,"Echo Fichier %s%s\\%s taille différente!!!\n",ap_DST->p_racine,p_ldossier_src->get_nom(),p_fic_src->get_name());
                          p_logger->add(ls_commande);
                          #endif
                          li_copy=1;
                        }
                        if (p_fic_src->get_time_write()  != p_fic_dst->get_time_write())  
                        {
                            #ifdef VERBOSE                           
                            sprintf(ls_commande,"Echo Fichier %s%s\\%s heure de modification différente!!!\n",ap_DST->p_racine,p_ldossier_src->get_nom(),p_fic_src->get_name());
                            p_logger->add(ls_commande);
                            #endif
                            li_copy=1;
                        }
                        if (li_copy==1) 
                        {
                          sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /H /Y /K \n",p_racine,p_ldossier_src->get_nom(),p_fic_src->get_name(),ap_DST->p_racine,p_ldossier_src->get_nom());
                          p_logger->add(ls_commande);         
                        }

                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 p_lfichier_src= p_lfichier_src->get_next();                
              }
           
         }
         //et on avance au maillon suivant
         p_ldossier_src = p_ldossier_src->get_next();            
      };       
}

/***********************************************
* cherche les fichiers en trop
*Entrée: arborecence source
************************************************/
void c_arbo::fic_en_trop(c_arbo *ap_SRC)
{
 //parcourir les dossier destination
c_lc_dossier *p_ldossier_src,*p_ldossier_dst,*p_ldossier_sav;
c_lc_fichier *p_lfichier_src,*p_lfichier_dst;
c_fichier *p_fic_src,*p_fic_dst;
long len;
char ls_commande[MAX_CHAINE];

      p_ldossier_dst = p_liste_dossier;            
      while( p_ldossier_dst!=NULL)
      {
         //cherche le dossier en source
         //p_lfichier_src = ap_SRC->p_liste_dossier->chercher(p_ldossier_dst->get_nom());
         p_ldossier_src = ap_SRC->p_liste_dossier->chercher(p_ldossier_dst->get_nom());
         if(p_ldossier_src == NULL)
         //if(p_lfichier_src == NULL)
         {
            //non trouvé            
            #ifdef VERBOSE
            sprintf(ls_commande,"Echo Le répertoire %s%s n'existe plus.\n",p_racine,p_ldossier_dst->get_nom());
            p_logger->add(ls_commande);
            #endif
            sprintf(ls_commande,"RD /S /Q \"%s%s\" \n",p_racine,p_ldossier_dst->get_nom());
            p_logger->add(ls_commande);

            //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
            strcpy(ls_commande,p_ldossier_dst->get_nom());
             len=strlen(ls_commande);
             p_ldossier_sav=p_ldossier_dst;
             do
             {
                 p_ldossier_dst = p_ldossier_dst->get_next();     //on boucle
                 if(p_ldossier_dst!=NULL)p_ldossier_sav=p_ldossier_dst;
             }while( (p_ldossier_dst!=NULL) && (strncmp(ls_commande,p_ldossier_dst->get_nom(),len)==0) ); //tant que même début et pas arrivé à la fin
             if(p_ldossier_dst==NULL)
             {p_ldossier_dst=p_ldossier_sav;}
             else
             {p_ldossier_dst = p_ldossier_dst->get_prev();} //on revient d'un cran car plus bas il y a un next...
         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             p_lfichier_src = p_ldossier_src->get_liste_fichier();//
             p_lfichier_dst = p_ldossier_dst->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers sources
             while( p_lfichier_dst!=NULL)
             {
                 p_fic_dst=p_lfichier_dst->get_fichier();   
                 //p_fic_src=p_lfichier_src->chercher(p_fic_dst->get_name());
                 if(p_lfichier_src==NULL)
                 {p_fic_src=NULL;}
                 else
                 {p_fic_src=p_lfichier_src->chercher(p_fic_dst->get_name());}
                 if(p_fic_src==NULL)
                 {
                      #ifdef VERBOSE            
                      sprintf(ls_commande,"Echo Le fichier %s%s\\%s n'existe plus.\n",p_racine,p_ldossier_dst->get_nom(),p_fic_dst->get_name());
                      p_logger->add(ls_commande);
                      #endif
                      sprintf(ls_commande,"DEL \"%s%s%s\" /A \n",p_racine,p_ldossier_dst->get_nom(),p_fic_dst->get_name());
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                     //pas besoin de comparer on l'a fait précédemment!
                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 p_lfichier_dst= p_lfichier_dst->get_next();                
              }

         }
         //et on avance au maillon suivant
         p_ldossier_dst = p_ldossier_dst->get_next();            
      };       
}


