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
c_arbo::c_arbo(char *ap_nom,c_logger *logger,bool b_verbose,bool b_crypt,bool b_ignore_err)
{   
    //nb_fichiers
    nb_fic=0;
	nb_fold=0;

	this->b_verbose = b_verbose;
	this->b_ignore_err = b_ignore_err;
	this->b_crypt = b_crypt;
    
    //init pointeur liste de dossier
    p_liste_dossier=NULL;   
    p_logger=logger;

    //sauve la racine
    cs_racine.set(ap_nom); 

}                

/***********************************************
* parcourir: parcours l'arborescence et stocke 
* les données 
************************************************/
void c_arbo::parcourir()
{
//char* p_tmp;    
c_strings *p_tmp;

	p_tmp = new c_strings(cs_racine.len() +1);
    p_tmp->set(cs_racine.get());
	p_tmp->add(G_SEPARATOR);
	
    //parcourir l'arborescence (RECURSIF)
    c_arbo::parcourir(p_tmp->get());   

    #ifdef DEBUG
    //affichage
    p_liste_dossier->afficher();                 
    #endif
	delete p_tmp;
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
int c_arbo::parcourir(char *a_chemin)
{
c_lc_dossier *lc_dossier_actuel=NULL;//pointeur sur le maillon dossier actuel
c_lc_fichier *lp_lst_fic_courant=NULL;//pointeur sur le dernier fichier ajouté
c_fichier lfichier;
struct _finddata_t lstr_find;
c_strings lcs_chemin(4096);
c_strings lcs_nom(4096);
char* p_cle=NULL;
#if defined(_MSC_VER) && (_MSC_VER > 1200) 
	intptr_t ll_handle;
#else
	long ll_handle;
#endif

   p_cle=a_chemin;
   //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
   p_cle = p_cle+cs_racine.len();
   //si pas encore de tête
   if(p_liste_dossier==NULL)
   {     //créer le premier maillon
         p_liste_dossier=new c_lc_dossier(p_cle);
         //pointeur actuel = tête
         lc_dossier_actuel=p_liste_dossier;
   }
   else
   {
	     //sinon ajouter un maillon et récupèrer un pointeur dessus       
	     lc_dossier_actuel=p_liste_dossier->ajouter_dossier(p_cle);
   }
   lcs_chemin.set(a_chemin);
   lcs_chemin.add(G_WILDCHAR);
   
   ll_handle =  _findfirst (lcs_chemin.get(), &lstr_find);
   if(ll_handle<0)
   {
        printf("erreur findfirst %s\n",lcs_chemin.get());
		if(b_ignore_err){
			return 0;
		}else{
	        return -1;
		}
   }   
    do
    {
         lfichier.init(lstr_find);
         //ignorer les fichiers .  .. volume du disque poubelles dossier de récup...
         if(lfichier.is_special()==0)
         {
             //si c'est un dossier
             if(lfichier.is_dir())
             {
                   nb_fold++;

                   lcs_nom.set(a_chemin);
				   lcs_nom.add(lstr_find.name);
				   lcs_nom.add(G_SEPARATOR);
                   if(parcourir(lcs_nom)==-1) return -1;
             }
             else
             {
                 nb_fic++;
                 if(lp_lst_fic_courant==NULL)
                 {
                    lp_lst_fic_courant = lc_dossier_actuel->ajouter_fichier(&lfichier);
                 }
                 else
                 {
                     lp_lst_fic_courant = lp_lst_fic_courant->ajouter(&lfichier);
                 }   
             }
         }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    _findclose (ll_handle);
    return 0;
}

/* générer la copie récursive d'un dossier*/
void c_arbo::generer_copie_recursive(char * nom_dossier,char *racine_destination){
	c_strings ls_commande(2048);
         ls_commande.set("xcopy ");
		 ls_commande.add(G_QUOTE);
         ls_commande.add(cs_racine.get());
         ls_commande.add(nom_dossier);
         ls_commande.add("*.*");
		 ls_commande.add(G_QUOTE);
		 ls_commande.add(" ");
		 ls_commande.add(G_QUOTE);
         ls_commande.add(racine_destination);
         ls_commande.add(nom_dossier);
		 ls_commande.add(G_QUOTE);
         ls_commande.add(" /E /I /H /Y /K /R \n"); 
		 // /E   copie les sous-dossiers vides
		 // /I   destination = répertoire si plusieurs fichiers en sources
		 // /H   copie aussi les fichiers cachés
		 // /Y   pas de demande de confirmation
		 // /K   copie aussi les attributs
		 // /R   remplace les fichiers lecture seule
		 ls_commande.DOSify();
		 p_logger->add(ls_commande.get());
}

/* générer la copie d'un fichier*/
void c_arbo::generer_copie(char* nom_fichier,char * nom_dossier,char *racine_destination){
	c_strings ls_commande(2048);
          ls_commande.set("xcopy ");
		  ls_commande.add(G_QUOTE);
          ls_commande.add(cs_racine.get());
          ls_commande.add(nom_dossier);
          ls_commande.add(nom_fichier);
		  ls_commande.add(G_QUOTE);
		  ls_commande.add(" ");
		  ls_commande.add(G_QUOTE);
          ls_commande.add(racine_destination);
          ls_commande.add(nom_dossier);
		  ls_commande.add(G_QUOTE);
          ls_commande.add("  /H /Y /K /R \n");
		  // /H   copie aussi les fichiers cachés
		  // /Y   pas de demande de confirmation
		  // /K   copie aussi les attributs
		  // /R   remplace les fichiers lecture seule
		  ls_commande.DOSify();
          p_logger->add(ls_commande.get());
}

/***********************************************
* cherche les fichiers manquant en destination
*Entrée: arboresence destination
************************************************/
void c_arbo::fic_en_moins(c_arbo *ap_DST)
{
 //parcourir les dossier sources
c_lc_dossier *LocalPointeurListeDossierSource,*LocalPointeurListeDossierDestination,*lp_ldossier_sav;
c_lc_fichier *LocalPointeurListeFichierSource,*LocalPointeurListeFichierDestination;
c_fichier *LocalPointeurDonneesFichierSource,*LocalPointeurDonneesFichierDestination;
long len;
c_strings ls_tmp(2048);

      LocalPointeurListeDossierSource = this->p_liste_dossier;            
      while( LocalPointeurListeDossierSource!=NULL)
      {
         //cherche le dossier en destination    
         LocalPointeurListeDossierDestination = ap_DST->p_liste_dossier->chercher(LocalPointeurListeDossierSource->get_nom());
         if(LocalPointeurListeDossierDestination == NULL)
         {
            //non trouvé            
			 //on copie le dossier et tout ce qu'il contient
			 generer_copie_recursive(LocalPointeurListeDossierSource->get_nom(),ap_DST->cs_racine.get());
			 //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
			 //les fichier c'est simple on ne parcours pas la liste
			 //pour les dossier il faut éliminer tous les dossier commençant
			 //de la même façon (dans le nom on stock le \ final donc pas de risque d'éliminter c:\tmp2 lors du traitement de c:\)
			 ls_tmp.set(LocalPointeurListeDossierSource->get_nom());
             len=ls_tmp.len();
             lp_ldossier_sav=LocalPointeurListeDossierSource;
             do
			 {
                 LocalPointeurListeDossierSource = LocalPointeurListeDossierSource->get_next();     //on boucle
                 if(LocalPointeurListeDossierSource!=NULL)
					  lp_ldossier_sav=LocalPointeurListeDossierSource;
             }while( (LocalPointeurListeDossierSource!=NULL) && 
				     (strncmp(ls_tmp.get(),LocalPointeurListeDossierSource->get_nom(),len)==0) ); //tant que même début et pas arrivé à la fin
             if(LocalPointeurListeDossierSource==NULL)
             {	 
				 //rendu trop loin
				 //ouf on a une sauveagrde du précédent...
				 LocalPointeurListeDossierSource=lp_ldossier_sav;                 
			 }
             else
             { 
				 //on revient d'un cran car plus bas il y a un next...
				 LocalPointeurListeDossierSource = LocalPointeurListeDossierSource->get_prev();   
			 } 
             
         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             LocalPointeurListeFichierDestination = LocalPointeurListeDossierDestination->get_liste_fichier();
             LocalPointeurListeFichierSource = LocalPointeurListeDossierSource->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers sources
             while( LocalPointeurListeFichierSource!=NULL)
             {
                 LocalPointeurDonneesFichierSource=LocalPointeurListeFichierSource->get_fichier();   
                 if(LocalPointeurListeFichierDestination==NULL)
                 {LocalPointeurDonneesFichierDestination=NULL;}
                 else
                 {LocalPointeurDonneesFichierDestination=LocalPointeurListeFichierDestination->chercher(LocalPointeurDonneesFichierSource->get_name());}
                 if(LocalPointeurDonneesFichierDestination==NULL)
                 {
					 //le fichier n'est pas en destination
					 //on le copie
					 generer_copie(LocalPointeurDonneesFichierSource->get_name(),LocalPointeurListeDossierSource->get_nom(),ap_DST->cs_racine.get());
                 }
                 else
                 {
					 //le fichier existe des deux cotés, on compare
					 bool diff = true;
					 if(this->b_crypt){
						 //on est sur un systeme avec cryptage tout pourri
						 //le soft fait +4096 octets sur la taille indiquée de tout fichier non crypté et de taille > 4096 octets
						 //il faut donc en tenir compte
						 diff = LocalPointeurDonneesFichierSource->isDiffCrypt(*LocalPointeurDonneesFichierSource,*LocalPointeurDonneesFichierDestination);
					 }else{
						 diff = ( *LocalPointeurDonneesFichierSource != *LocalPointeurDonneesFichierDestination);
					 }
						if( diff)
                        {
						  if(this->b_verbose)
						  {
							  if(LocalPointeurDonneesFichierSource->get_time_write() != LocalPointeurDonneesFichierDestination->get_time_write())
								  printf("heures d'écritures différentes (%s  %s)\n",LocalPointeurDonneesFichierSource->get_name(),LocalPointeurDonneesFichierDestination->get_name());
							  if(LocalPointeurDonneesFichierSource->get_size() != LocalPointeurDonneesFichierDestination->get_size())
								  printf("Tailles différentes (%s:%li  %s:%li)\n",LocalPointeurDonneesFichierSource->get_name(),LocalPointeurDonneesFichierSource->get_size(),LocalPointeurDonneesFichierDestination->get_name(),LocalPointeurDonneesFichierDestination->get_size());
						  }
						  //différent on copie
						  generer_copie(LocalPointeurDonneesFichierSource->get_name(),LocalPointeurListeDossierSource->get_nom(),ap_DST->cs_racine.get());
                        }

                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 LocalPointeurListeFichierSource= LocalPointeurListeFichierSource->get_next();                
              }
           
         }
         //et on avance au maillon suivant
         LocalPointeurListeDossierSource = LocalPointeurListeDossierSource->get_next();            
      };       
}

/* suppression recursive d'un dossier */
void c_arbo::generer_suppression_dossier(char* nom_dossier){
	c_strings ls_commande(2048);
		ls_commande.set("RD /S /Q ");
		ls_commande.add(G_QUOTE);
		ls_commande.add(cs_racine.get());
		ls_commande.add(nom_dossier);
		ls_commande.add(G_QUOTE);
		ls_commande.add(" \n");
		ls_commande.DOSify();
		p_logger->add(ls_commande.get());
}

/* supprimer un fichier */
void c_arbo::generer_suppression_fichier(char * nom_dossier,char * nom_fichier){
	c_strings ls_commande(2048);
      ls_commande.set("DEL ");
	  ls_commande.add(G_QUOTE);
      ls_commande.add(cs_racine.get());
      ls_commande.add(nom_dossier);
      ls_commande.add(nom_fichier);
	  ls_commande.add(G_QUOTE);
      ls_commande.add(" /F /A \n"); 
	  //   /F   force effacement lecture seule   
	  //   /A   efface quemque soit les attributs
	  ls_commande.DOSify();
      p_logger->add(ls_commande.get());
}

/***********************************************
* cherche les fichiers en trop
*Entrée: arborecence source
************************************************/
void c_arbo::fic_en_trop(c_arbo *ap_SRC)
{
 //parcourir les dossier destination
c_lc_dossier *LocalPointeurListeDossierSource,*LocalPointeurListeDossierDestination,*lp_ldossier_sav;
c_lc_fichier *LocalPointeurListeFichierSource,*LocalPointeurListeFichierDestination;
c_fichier *LocalPointeurDonneesFichierSource,*LocalPointeurDonneesFichierDestination;
long len;
c_strings ls_temp(2048);

      LocalPointeurListeDossierDestination = this->p_liste_dossier;            
      while( LocalPointeurListeDossierDestination!=NULL)
      {
         //cherche le dossier en source
         LocalPointeurListeDossierSource = ap_SRC->p_liste_dossier->chercher(LocalPointeurListeDossierDestination->get_nom());
         if(LocalPointeurListeDossierSource == NULL)
         {
            //non trouvé en source -> le supprimer de destination           
			 generer_suppression_dossier(LocalPointeurListeDossierDestination->get_nom()),
            //comme on copie un dossier entier, on saute tous ces fichiers et sous-dossiers
			ls_temp.set(LocalPointeurListeDossierDestination->get_nom());
             len=ls_temp.len();
             lp_ldossier_sav=LocalPointeurListeDossierDestination;
             do
             {
                 LocalPointeurListeDossierDestination = LocalPointeurListeDossierDestination->get_next();     //on boucle
                 if(LocalPointeurListeDossierDestination!=NULL)lp_ldossier_sav=LocalPointeurListeDossierDestination;
             }while( (LocalPointeurListeDossierDestination!=NULL) && 
				     (strncmp(ls_temp.get(),LocalPointeurListeDossierDestination->get_nom(),len)==0) ); //tant que même début et pas arrivé à la fin
             if(LocalPointeurListeDossierDestination==NULL)
             {
				 //rendu trop loin
				 //ouf on a une sauveagrde du précédent...
				 LocalPointeurListeDossierDestination=lp_ldossier_sav;
			 }
             else
             {
				 //on revient d'un cran car plus bas il y a un next...
				 LocalPointeurListeDossierDestination = LocalPointeurListeDossierDestination->get_prev();
			 } 
         }   
         else
         {
             //trouvé -> comparer les listes de fichiers
             LocalPointeurListeFichierSource = LocalPointeurListeDossierSource->get_liste_fichier();//
             LocalPointeurListeFichierDestination = LocalPointeurListeDossierDestination->get_liste_fichier();
             //maintenant on boucle sur la liste des fichiers destinations
             while( LocalPointeurListeFichierDestination!=NULL)
             {
                 LocalPointeurDonneesFichierDestination=LocalPointeurListeFichierDestination->get_fichier();   
                 if(LocalPointeurListeFichierSource==NULL)
                 {
					 LocalPointeurDonneesFichierSource=NULL;
				 }
                 else
                 {
					 LocalPointeurDonneesFichierSource=LocalPointeurListeFichierSource->chercher(LocalPointeurDonneesFichierDestination->get_name());
				 }
                 if(LocalPointeurDonneesFichierSource==NULL)
                 {
					  generer_suppression_fichier(LocalPointeurListeDossierDestination->get_nom(),LocalPointeurDonneesFichierDestination->get_name());
                 }
                 else
                 {
                     //pas besoin de comparer on l'a fait précédemment!
                 }//endif fic_dst!=NULL
                 //et on avance au maillon suivant
                 LocalPointeurListeFichierDestination= LocalPointeurListeFichierDestination->get_next();                
              }

         }
         //et on avance au maillon suivant
         LocalPointeurListeDossierDestination = LocalPointeurListeDossierDestination->get_next();            
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
*paramètres: long en référence pour envoyer les nombres
************************************************/
void c_arbo::get_status()
{
     printf("Thread(%li)-Etat '%s' %li dossier / %li fichiers\n",GetCurrentThreadId(),cs_racine.get(),nb_fold,nb_fic);   
}

