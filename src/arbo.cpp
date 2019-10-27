#include "arbo.h" 
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "logger.h"
#include <stdio.h> //printf
#include <string.h> //str*


/***********************************************
* constructeur de la classe
* Entrée: racine de l'arboresence
************************************************/
c_arbo::c_arbo(char *ap_nom,c_logger *logger)
{   
    //constantes
    G_SEPARATOR = "\\";;  
    G_WILDCHAR = "*.*";

    //nb_fichiers
    nb_fic=0;
	nb_fold=0;
    
    //init pointeur liste de dossier
    p_liste_dossier=NULL;   
    p_logger=logger;

    //sauve la racine
    cs_racine=ap_nom; 

}                

/***********************************************
* parcourir: parcours l'arborescence et stocke 
* les données 
************************************************/
void c_arbo::parcourir()
{
//char* p_tmp;    
c_strings p_tmp;
    p_tmp=cs_racine;
	p_tmp+="\\";
	
    //parcourir l'arborescence (RECURSIF)
    c_arbo::parcourir(p_tmp);   

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
	if(p_liste_dossier!=NULL)delete p_liste_dossier;
	p_liste_dossier=NULL;
	p_logger=NULL;	
}


/***********************************************
* parcourir: parcours l'arborescence et stocke 
* les données (FONCTION RECURSIVE
* Entrée: le nom du dossier à scanner
************************************************/
int c_arbo::parcourir(c_strings & acs_chemin)
{
c_lc_dossier *p_lst_dossier=NULL;//pointeur sur le maillon dossier actuel
c_lc_fichier *p_lst_fic_tete=NULL,*p_lst_fic_courant=NULL;
c_fichier fichier;
struct _finddata_t lstr_find;
c_strings cs_chemin;
c_strings cs_nom;
char* p_cle=NULL;
long ll_handle;

   p_cle=acs_chemin;
   //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
   p_cle = p_cle+cs_racine.len();
   //si pas encore de tête
   if(p_liste_dossier==NULL)
   {     //créer le premier maillon
         p_liste_dossier=new c_lc_dossier(p_cle);
         //pointeur actuel = tête
         p_lst_dossier=p_liste_dossier;
   }
   else
   {p_lst_dossier=p_liste_dossier->ajouter(p_cle);}//sinon ajouter un maillon et récupèrer un pointeur dessus       
   cs_chemin = acs_chemin;
   cs_chemin+=G_WILDCHAR;
   
   ll_handle =  _findfirst (cs_chemin, &lstr_find);
   if(ll_handle<0)
   {
        printf("erreur findfirst %s\n",(char*)cs_chemin);
        return -1;
   }   
    do
    {
         fichier.init(lstr_find);
         //ignorer les fichiers .  ..       et le volume du disque
         if(fichier.is_special()==0)
         {
             //si c'est un dossier
             if(fichier.is_dir())
             {
                   nb_fold++;

                   cs_nom=acs_chemin;
				   cs_nom+=lstr_find.name;
				   cs_nom+=G_SEPARATOR;
                   if(parcourir(cs_nom)==-1) return -1;
             }
             else
             {
                 nb_fic++;
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
c_strings ls_commande;
c_strings cs_source;
c_strings cs_cible;

      p_ldossier_src = p_liste_dossier;            
      while( p_ldossier_src!=NULL)
      {
         //cherche le dossier en destination    
         p_ldossier_dst = ap_DST->p_liste_dossier->chercher(p_ldossier_src->get_nom());
         if(p_ldossier_dst == NULL)
         {
            //non trouvé
            cs_source ="";            
            cs_source+=cs_racine;
            cs_source+=p_ldossier_src->get_nom();
            cs_source+=G_WILDCHAR;
            cs_cible ="";
            cs_cible+=ap_DST->cs_racine;
            cs_cible+=p_ldossier_src->get_nom();
            copie_dossier((char *)cs_source,(char *)cs_cible);
/*           
             ls_commande="xcopy \"";
             ls_commande+=cs_racine;
             ls_commande+=p_ldossier_src->get_nom();
             ls_commande+="*.*\" \"";
             ls_commande+=ap_DST->cs_racine;
             ls_commande+=p_ldossier_src->get_nom();
             ls_commande+="\" /E /I /H /Y /K \n";
             p_logger->add(ls_commande);*/
             
             //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
             ls_commande=p_ldossier_src->get_nom();
             len=strlen(ls_commande);
             p_ldossier_sav=p_ldossier_src;
             do
             {
                 p_ldossier_src = p_ldossier_src->get_next();     //on boucle
                 if(p_ldossier_src!=NULL)p_ldossier_sav=p_ldossier_src;
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
                      cs_source ="";
                      cs_source+=cs_racine;
                      cs_source+=p_ldossier_src->get_nom();              
                      cs_source+=p_fic_src->get_name();
                      cs_cible ="";
                      cs_cible+=ap_DST->cs_racine;
                      cs_cible+=+p_ldossier_src->get_nom();
                      copie_fichier((char *)cs_source,(char *)cs_cible);              
/*                      ls_commande="xcopy \"";
                      ls_commande+=cs_racine;
                      ls_commande+=p_ldossier_src->get_nom();
                      ls_commande+=p_fic_src->get_name();
                      ls_commande+="\" \"";
                      ls_commande+=ap_DST->cs_racine;
                      ls_commande+=p_ldossier_src->get_nom();
                      ls_commande+="\"  /H /Y /K \n";
                      p_logger->add(ls_commande);*/
                 }
                 else
                 {
                       li_copy=0;
                       //le copier
                       if (p_fic_src->get_size() != p_fic_dst->get_size())        
                       {
                          li_copy=1;
                        }
                        if (p_fic_src->get_time_write() != p_fic_dst->get_time_write())  
                        {
                            li_copy=1;
                        }
                        if (li_copy==1) 
                        {
                          cs_source ="";              
                          cs_source+=cs_racine;  
                          cs_source+=p_ldossier_src->get_nom();
                          cs_source+=p_fic_src->get_name();
                          cs_cible ="";
                          cs_cible+=ap_DST->cs_racine;
                          cs_cible+=p_ldossier_src->get_nom();
                          copie_fichier((char *)cs_source,(char *)cs_cible);              
                          /*ls_commande="xcopy \"";
                          ls_commande+=cs_racine;
                          ls_commande+=p_ldossier_src->get_nom();
                          ls_commande+=p_fic_src->get_name();
                          ls_commande+="\" \"";
                          ls_commande+=ap_DST->cs_racine;
                          ls_commande+=p_ldossier_src->get_nom();
                          ls_commande+="\"  /H /Y /K \n";                          
                          p_logger->add(ls_commande);         */
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
c_strings ls_commande;
c_strings cs_source;

      p_ldossier_dst = p_liste_dossier;            
      while( p_ldossier_dst!=NULL)
      {
         //cherche le dossier en source
         p_ldossier_src = ap_SRC->p_liste_dossier->chercher(p_ldossier_dst->get_nom());
         if(p_ldossier_src == NULL)
         {
            //non trouvé            
            cs_source ="";
            cs_source+=cs_racine;
            cs_source+=p_ldossier_dst->get_nom();
            supprime_dossier((char *)cs_source);
            /*
            ls_commande="RD /S /Q \"";
            ls_commande+=cs_racine;
            ls_commande+=p_ldossier_dst->get_nom();
            ls_commande+="\" \n";
            p_logger->add(ls_commande);
            */
            //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
			#ifdef _MSC_VER
				strcpy_s(ls_commande,strlen((char *)p_ldossier_dst->get_nom()),p_ldossier_dst->get_nom());
			#else
				strcpy(ls_commande,p_ldossier_dst->get_nom());
			#endif
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
                 if(p_lfichier_src==NULL)
                 {p_fic_src=NULL;}
                 else
                 {p_fic_src=p_lfichier_src->chercher(p_fic_dst->get_name());}
                 if(p_fic_src==NULL)
                 {
                      cs_source ="";
                      cs_source+= cs_racine;
                      cs_source+=p_ldossier_dst->get_nom();
                      cs_source+=p_fic_dst->get_name();             
                      supprime_fichier((char *)cs_source);
                      /*
                      ls_commande="DEL \"";
                      ls_commande+=cs_racine;
                      ls_commande+=p_ldossier_dst->get_nom();
                      ls_commande+=p_fic_dst->get_name();
                      ls_commande+="\" /F\n";
                      p_logger->add(ls_commande);*/
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

/***********************************************
* indique l'état de remplissage (nb fichiers et nb dossiers
*paramètres: long en référence pour envoyer les nombres
************************************************/
void c_arbo::get_status(long *nb_folders,long *nb_files)
{
	*nb_files=nb_fic;
	*nb_folders=nb_fold;
}

/***********************************************
* indique l'état de remplissage (nb fichiers et nb dossiers
************************************************/
void c_arbo::get_status()
{
	printf("Thread(%li)-Etat source %li dossier / %li fichiers\n",GetCurrentThreadId(),nb_fold,nb_fic);

}


/***********************************************
* copier un dossier
************************************************/
void c_arbo::copie_dossier(char * cs_source,char * cs_destination)
{
 c_strings ls_commande;     
        ls_commande="xcopy \"";
        ls_commande+=cs_source;
        ls_commande+="\" \"";
        ls_commande+=cs_destination;
        ls_commande+="\" /E /I /H /Y /K \n";
        p_logger->add(ls_commande);
 
}

/***********************************************
* copier un fichier
************************************************/
void c_arbo::copie_fichier(char * cs_source,char * cs_destination)
{
 c_strings ls_commande;     
        ls_commande="xcopy \"";
        ls_commande+=cs_source;
        ls_commande+="\" \"";
        ls_commande+=cs_destination;
        ls_commande+="\" /H /Y /K \n";
        p_logger->add(ls_commande);
 
}

/***********************************************
* indique l'état de remplissage (nb fichiers et nb dossiers
************************************************/
void c_arbo::supprime_fichier(char * cs_fichier)
{
 c_strings ls_commande;
           ls_commande="DEL \"";
           ls_commande+=cs_fichier;
           ls_commande+="\" /F\n";
           p_logger->add(ls_commande);
}

/***********************************************
* indique l'état de remplissage (nb fichiers et nb dossiers
************************************************/
void c_arbo::supprime_dossier(char * cs_dossier)
{
 c_strings ls_commande;     
           ls_commande="RD /S /Q \"";
           ls_commande+=cs_dossier;
           ls_commande+="\" \n";
           p_logger->add(ls_commande);
}
