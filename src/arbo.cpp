#include "arbo.h" 
#include "liste_chainee.h" 
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>

//#define TRACE

void print_oem(char * as_chaine)
{
char ls_oem[1024];     
   CharToOem(as_chaine,ls_oem);
   printf("%s",ls_oem);
   fflush(stdin);
}


// class constructor
c_arbo::c_arbo(char * nom)
{
    long taille;
    taille=strlen(nom)+1;
    racine=new char[taille];

	strcpy(racine,nom);
    c_arbo::parcourir(nom);   
    //liste.creer_cache();
               
}                

// class destructor
c_arbo::~c_arbo()
{
	// insert your code here
	delete racine;
	
}

int c_arbo::parcourir(char * chemin)
{
c_fichier *fichier;
struct _finddata_t lstr_find;
char ls_chemin[MAX_CHAINE];
char ls_nom[MAX_CHAINE];
char *cle;
long ll_handle;
	sprintf(ls_chemin,"%s\\*.*",chemin);
	//DEBUG
	//printf("%s\n",chemin);
	//DEBUG
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
              strcpy(ls_nom,chemin);
              strcat(ls_nom,"\\");
              strcat(ls_nom,lstr_find.name);
              cle=chemin;
              //enlever la racine de la clé (sinon on ne peut plus comparer entre source et cible!!!
              cle = cle+strlen(racine);
              fichier=new c_fichier(lstr_find,cle);
              liste.ajouter(fichier);
              //delete fichier;
              //si c'est un dossier
             if (lstr_find.attrib & _A_SUBDIR)
             {
                   parcourir(ls_nom);
             }
             
         }
    }
    while(_findnext(ll_handle, &lstr_find)==0);
    _findclose (ll_handle);
    return 0;
}



c_liste_chainee* c_arbo::get_liste()
{
   return &liste;
}

char* c_arbo::get_racine()
{
      return racine;
}

void c_arbo::fic_en_moins(c_arbo *DST)
{
     c_liste_chainee *lsrc,*ldst;
     c_fichier *fsrc,*fdst;
     char* fichier;
     char ls_commande[MAX_CHAINE];
     int  li_copy;
     
     lsrc=get_liste();
     ldst=DST->get_liste();
     //parcourir la liste src
     fichier=lsrc->get_next(true);
     if(fichier ==NULL) return;
     do
     {
        //chercher fichier dans dst:
        //fdst = ldst->chercher_cache(fichier);                              
        fdst = ldst->chercher(fichier);                              
        if(fdst==NULL) 
        {
           //fichier n'existe pas en destination
           //le copier
           //fsrc = lsrc->chercher_cache(fichier);                              
           fsrc = lsrc->chercher(fichier);                              
           if(fsrc==NULL) 
           {
                printf("Erreur normalement impossible (1)\n");          
                exit(-1);//erreur impossible
           }
           //si c'est un dossier
           if (fsrc->is_dir() )
           {
               #ifdef TRACE               
               sprintf(ls_commande,"Echo répertoire %s non trouvé !!!\n",fichier);
               print_oem(ls_commande);
               #endif
               sprintf(ls_commande,"MD \"%s%s\" \n",racine,fichier);
               print_oem(ls_commande);                   
           }
           else
           {
               //c'est un fichier
               //le copier
               #ifdef TRACE
               sprintf(ls_commande,"Echo fichier %s non trouvé !!!\n",fichier);
               print_oem(ls_commande);
               #endif
               sprintf(ls_commande,"copy \"%s%s\" \"%s%s\"\n",racine,fichier,DST->get_racine(),fsrc->get_chemin());
               print_oem(ls_commande);                   
           }

        }                         
        else
        {
            //le fichier existe des deux cotés
            //fsrc = lsrc->chercher_cache(fichier);                              
            fsrc = lsrc->chercher(fichier);                              
           if(fsrc==NULL) 
           {
                printf("Erreur normalement impossible (2)\n");          
                exit(-1);//erreur impossible
           }
            //si c'est un dossier
            if (fsrc->is_dir() )
            {
               //on ne fait rien!!!
            }
           else
           {
               //c'est un fichier
               //il faut voir s'il a bougé...
               li_copy=0;
               //le copier
               if (fsrc->get_size()        != fdst->get_size())        
               {
                  #ifdef TRACE                         
                  sprintf(ls_commande,"Echo Fichier %s taille différente!!!\n",fichier);
                  print_oem(ls_commande);             
                  #endif
                  li_copy=1;
                }
                //if (lstr_find_src.time_create != lstr_find_dst.time_create) printf("Fichier %s heure de création différente!!!\n",ls_fichier_dst);
                //if (lstr_find_src.time_access != lstr_find_dst.time_access) printf("Fichier %s heure de dernier accés différente!!!\n",ls_fichier_dst);
                if (fsrc->get_time_write()  != fdst->get_time_write())  
                {
                    #ifdef TRACE                        
                    sprintf(ls_commande,"Echo Fichier %s heure de modification différente!!!\n",fichier);
                    print_oem(ls_commande);
                    #endif
                    li_copy=1;
                }
                if (li_copy==1) 
                {
                  sprintf(ls_commande,"copy \"%s%s\" \"%S%s\"\n",racine,fichier,DST->get_racine(),fsrc->get_chemin());
                  print_oem(ls_commande);         
                }
           }
        }
        fichier=lsrc->get_next(false);
     }while (fichier != NULL);
}
void c_arbo::fic_en_trop(c_arbo *SRC)
{
     c_liste_chainee *lsrc,*ldst;
     c_fichier *fsrc,*fdst;
     char* fichier;
     char ls_commande[MAX_CHAINE];
     int  li_copy;
     
     ldst=get_liste();
     lsrc=SRC->get_liste();
     //parcourir la liste destination
     fichier=ldst->get_next(true);
     if(fichier ==NULL) return;
     do
     {
        //chercher fichier dans src:
        //fsrc = lsrc->chercher_cache(fichier);                              
        fsrc = lsrc->chercher(fichier);                              
        if(fsrc==NULL) 
        {
           //fichier n'existe pas en source
           //l'effacer
           //si c'est un dossier
           if (fdst->is_dir() )
           {
               #ifdef TRACE               
               sprintf(ls_commande,"echo Le répertoire %s n'existe plus dans %s. Il doit être effacer de %s \n",fichier,SRC->get_racine(),get_racine());
               print_oem(ls_commande);
               #endif
               sprintf(ls_commande,"RD /S /Q \"%s%s\" \n",get_racine(),fichier);
               print_oem(ls_commande);
           }
           else
           {
               //c'est un fichier
               #ifdef TRACE
               sprintf(ls_commande,"echo Fichier %s non trouvé!!! On doit l'effacer de %s \n",fichier,SRC->get_racine());
               print_oem(ls_commande);
               #endif
               sprintf(ls_commande,"DEL \"%s%s\" /A \n",get_racine(),fichier);
               print_oem(ls_commande);
           }
        }                         
        else
        {
            //le fichier existe des deux cotés
            //on ne fait rien (comparaison effectuée au dessus!
        }
        fichier=ldst->get_next(false);
     }while (fichier != NULL);
}


