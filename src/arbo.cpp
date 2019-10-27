#include "arbo.h" 
#include "lc_dossier.h"
#include "lc_fichier.h"
#include "logger.h"
#include <stdio.h> //printf
#include <string.h> //str*

/***********************************************
* constructeur de la classe
* Entr�e: racine de l'arboresence
************************************************/
c_arbo::c_arbo(char *ap_nom)
{   
//char* p_tmp;    
c_strings p_tmp;
    //constantes
    G_SEPARATOR = "\\";;  
    G_WILDCHAR = "*.*";
    
    //init pointeur liste de dossier
    p_liste_dossier=NULL;   
    p_logger=NULL;
    //sauve la racine
    p_racine=ap_nom; 

    p_tmp=p_racine;
	p_tmp+="\\";
	
    //parcourir l'arborescence
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
	// on lib�re la m�moire
	if(p_liste_dossier!=NULL)delete p_liste_dossier;
	p_liste_dossier=NULL;
	p_logger=NULL;	
}

/***********************************************
*  indique a la classe le logger
*  Entr�e: la classe logger
************************************************/
void c_arbo::set_logger(c_logger *ap_logger)
{
     p_logger=ap_logger;
}

/***********************************************
* parcourir: parcours l'arborescence et stocke 
* les donn�es (FONCTION RECURSIVE
* Entr�e: le nom du dossier � scanner
************************************************/
int c_arbo::parcourir(c_strings & ap_chemin)
{
c_lc_dossier *p_lst_dossier=NULL;//pointeur sur le maillon dossier actuel
c_lc_fichier *p_lst_fic_tete=NULL,*p_lst_fic_courant=NULL;
c_fichier fichier;
struct _finddata_t lstr_find;
c_strings p_chemin;
c_strings p_nom;
char* p_cle=NULL;
long ll_handle;
   #ifdef DEBUG
   printf("Parcours d�but: %s \n",ap_chemin);
   #endif
   
   p_cle=ap_chemin;
   //enlever la racine de la cl� (sinon on ne peut plus comparer entre source et cible!!!
   p_cle = p_cle+p_racine.len();
   //si pas encore de t�te
   if(p_liste_dossier==NULL)
   {     //cr�er le premier maillon
         p_liste_dossier=new c_lc_dossier(p_cle);
         //pointeur actuel = t�te
         p_lst_dossier=p_liste_dossier;
   }
   else
   {p_lst_dossier=p_liste_dossier->ajouter(p_cle);}//sinon ajouter un maillon et r�cup�rer un pointeur dessus       
   p_chemin = ap_chemin;
   p_chemin+=G_WILDCHAR;
   
   ll_handle =  _findfirst (p_chemin, &lstr_find);
   if(ll_handle<0)printf("erreur findfirst %s\n",(char*)p_chemin);
    do
    {
         fichier.init(lstr_find);
         //ignorer les fichiers .  ..       et le volume du disque
         if(fichier.is_special()==0)
         {
             //si c'est un dossier
             if(fichier.is_dir())
             {
                   p_nom=ap_chemin;
				   p_nom+=lstr_find.name;
				   p_nom+=G_SEPARATOR;
                   parcourir(p_nom);
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
    return 0;
}

/***********************************************
* cherche les fichiers manquant en destination
*Entr�e: arboresence destination
************************************************/
void c_arbo::fic_en_moins(c_arbo *ap_DST)
{
 //parcourir les dossier sources
c_lc_dossier *p_ldossier_src,*p_ldossier_dst,*p_ldossier_sav;
c_lc_fichier *p_lfichier_src,*p_lfichier_dst;
c_fichier *p_fic_src,*p_fic_dst;
long li_copy,len;
c_strings ls_commande;

      p_ldossier_src = p_liste_dossier;            
      while( p_ldossier_src!=NULL)
      {
         //cherche le dossier en destination    
         p_ldossier_dst = ap_DST->p_liste_dossier->chercher(p_ldossier_src->get_nom());
         if(p_ldossier_dst == NULL)
         {
            //non trouv�            
             #ifdef VERBOSE
             ls_commande="Echo r�pertoire ";
             ls_commande+=ap_DST->p_racine;
             ls_commande+=p_ldossier_src->get_nom();
             ls_commande+=" non trouv� !!!\n";
             p_logger->add(ls_commande);
             #endif
             ls_commande="xcopy \"";
             ls_commande+=p_racine;
             ls_commande+=p_ldossier_src->get_nom();
             ls_commande+="*.*\" \"";
             ls_commande+=ap_DST->p_racine;
             ls_commande+=p_ldossier_src->get_nom();
             ls_commande+="\" /E /I /H /Y /K \n";
             p_logger->add(ls_commande);
             //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
             strcpy(ls_commande,p_ldossier_src->get_nom());
             len=strlen(ls_commande);
             p_ldossier_sav=p_ldossier_src;
             do
             {
                 p_ldossier_src = p_ldossier_src->get_next();     //on boucle
                 if(p_ldossier_src!=NULL)p_ldossier_sav=p_ldossier_src;
             }while( (p_ldossier_src!=NULL) && (strncmp(ls_commande,p_ldossier_src->get_nom(),len)==0) ); //tant que m�me d�but et pas arriv� � la fin
             if(p_ldossier_src==NULL)
             {p_ldossier_src=p_ldossier_sav;}
             else
             {p_ldossier_src = p_ldossier_src->get_prev();} //on revient d'un cran car plus bas il y a un next...
             
         }   
         else
         {
             //trouv� -> comparer les listes de fichiers
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
                      ls_command= "echo Fichier ";
                      ls_command+=ap_DST->p_racine;
                      ls_command+=p_ldossier_src->get_nom();
                      ls_command+="\\";
                      ls_command+=p_fic_src->get_name();
                      ls_command+=" non trouv�!!!\n";
                      p_logger->add(ls_commande);
                      #endif
                      ls_commande="xcopy \"";
                      ls_commande+=p_racine;
                      ls_commande+=p_ldossier_src->get_nom();
                      ls_commande+=p_fic_src->get_name();
                      ls_commande+="\" \"";
                      ls_commande+=ap_DST->p_racine;
                      ls_commande+=p_ldossier_src->get_nom();
                      ls_commande+="\"  /H /Y /K \n";
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                       li_copy=0;
                       //le copier
                       if (p_fic_src->get_size()        != p_fic_dst->get_size())        
                       {
                          #ifdef VERBOSE                            
                          ls_commande="Echo Fichier ";                          
                          ls_commande+=ap_DST->p_racine;
                          ls_commande+=p_ldossier_src->get_nom();
                          ls_commande+="\\";
                          ls_commande+=p_fic_src->get_name();
                          ls_commande+=" taille diff�rente!!!\n";
                          p_logger->add(ls_commande);
                          #endif
                          li_copy=1;
                        }
                        if (p_fic_src->get_time_write()  != p_fic_dst->get_time_write())  
                        {
                            #ifdef VERBOSE                           
                            ls_commande="Echo Fichier ";
                            ls_commande+=ap_DST->p_racine;
                            ls_commande+=p_ldossier_src->get_nom();
                            ls_commande+="\\";
                            ls_commande+=p_fic_src->get_name();
                            ls_commande+=" heure de modification diff�rente!!!\n";
                            p_logger->add(ls_commande);
                            #endif
                            li_copy=1;
                        }
                        if (li_copy==1) 
                        {
                          ls_commande="xcopy \"";
                          ls_commande+=p_racine;
                          ls_commande+=p_ldossier_src->get_nom();
                          ls_commande+=p_fic_src->get_name();
                          ls_commande+="\" \"";
                          ls_commande+=ap_DST->p_racine;
                          ls_commande+=p_ldossier_src->get_nom();
                          ls_commande+="\"  /H /Y /K \n";                          
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
*Entr�e: arborecence source
************************************************/
void c_arbo::fic_en_trop(c_arbo *ap_SRC)
{
 //parcourir les dossier destination
c_lc_dossier *p_ldossier_src,*p_ldossier_dst,*p_ldossier_sav;
c_lc_fichier *p_lfichier_src,*p_lfichier_dst;
c_fichier *p_fic_src,*p_fic_dst;
long len;
c_strings ls_commande;

      p_ldossier_dst = p_liste_dossier;            
      while( p_ldossier_dst!=NULL)
      {
         //cherche le dossier en source
         p_ldossier_src = ap_SRC->p_liste_dossier->chercher(p_ldossier_dst->get_nom());
         if(p_ldossier_src == NULL)
         {
            //non trouv�            
            #ifdef VERBOSE
            ls_commande="Echo Le r�pertoire ";
            ls_commande+=p_racine;
            ls_commande+=p_ldossier_dst->get_nom();
            ls_commande+=" n'existe plus.\n";
            p_logger->add(ls_commande);
            #endif
            ls_commande="RD /S /Q \"";
            ls_commande+=p_racine;
            ls_commande+=p_ldossier_dst->get_nom();
            ls_commande+="\" \n";
            p_logger->add(ls_commande);

            //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
            strcpy(ls_commande,p_ldossier_dst->get_nom());
             len=strlen(ls_commande);
             p_ldossier_sav=p_ldossier_dst;
             do
             {
                 p_ldossier_dst = p_ldossier_dst->get_next();     //on boucle
                 if(p_ldossier_dst!=NULL)p_ldossier_sav=p_ldossier_dst;
             }while( (p_ldossier_dst!=NULL) && (strncmp(ls_commande,p_ldossier_dst->get_nom(),len)==0) ); //tant que m�me d�but et pas arriv� � la fin
             if(p_ldossier_dst==NULL)
             {p_ldossier_dst=p_ldossier_sav;}
             else
             {p_ldossier_dst = p_ldossier_dst->get_prev();} //on revient d'un cran car plus bas il y a un next...
         }   
         else
         {
             //trouv� -> comparer les listes de fichiers
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
                      #ifdef VERBOSE            
                      ls_commande="Echo Le fichier ";
                      ls_commande+=p_racine;
                      ls_commande+=p_ldossier_dst->get_nom();
                      ls_commande+="\\";
                      ls_commande+=p_fic_dst->get_name();
                      ls_commande+=" n'existe plus.\n";
                      p_logger->add(ls_commande);
                      #endif
                      ls_commande="DEL \"";
                      ls_commande+=p_racine;
                      ls_commande+=p_ldossier_dst->get_nom();
                      ls_commande+=p_fic_dst->get_name();
                      ls_commande+="\" /F\n";
                      p_logger->add(ls_commande);
                 }
                 else
                 {
                     //pas besoin de comparer on l'a fait pr�c�demment!
                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 p_lfichier_dst= p_lfichier_dst->get_next();                
              }

         }
         //et on avance au maillon suivant
         p_ldossier_dst = p_ldossier_dst->get_next();            
      };       
}


