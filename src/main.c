/*synch
synchronise deux dossier
analyse la source pour chaque fichier le cherche en cible
S'il n'existe pas il faut le copier
s'il existe on compare date, attributs et taille pour savoir si on doit écraser
ensuite on parcours le cible en cherchant chaques fichiers en source s'il n'y est pas on doit l'effacer de la cible
Version 1.0 10/2005 en procédurale
*/
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
//typedef char* va_list;
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

int fic_en_moins(char* as_chemin_src,char* as_chemin_dst, char * as_chemin_relatif)
//parcours SRC et cherche les fichier différents dans dst ou absent
{
struct _finddata_t lstr_find_src,lstr_find_dst; 
long ll_handle_src,ll_handle_dst;
char ls_chemin_src[1024];
char ls_chemin_dst[1024];
char ls_fichier_dst[1024];
char ls_chemin_prochain[1024];
char ls_commande[1024];
int  li_copy;
     //créé les path de recherche
     //Source
    sprintf(ls_chemin_src,"%s%s*.*",as_chemin_src,as_chemin_relatif);
    //recherche dans source
    ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
    do 
    {     
          //ignorer les fichiers .  ..       et le volume du disque
         if( (strcmp(lstr_find_src.name,".")!=0) && 
             (strcmp(lstr_find_src.name,"..")!=0) && 
            !(lstr_find_src.attrib & _A_VOLID)  && 
             (strcmp(lstr_find_src.name,"System Volume Information")!=0) && 
             (strcmp(lstr_find_src.name,"RECYCLER")!=0) )
         {
             if (lstr_find_src.attrib & _A_SUBDIR)
             {
                  //c'est un répertoire 
                  //on le cherche en destination
                  sprintf(ls_chemin_dst,"%s%s%s\\*.*",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                  ll_handle_dst =  _findfirst (ls_chemin_dst, &lstr_find_dst);
                  if (ll_handle_dst ==-1)
                  {
                    //s'il n'existe pas on le copie
                    #ifdef TRACE
                     sprintf(ls_commande,"echo répertoire %s%s%s non trouvé !!!\n",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                     print_oem(ls_commande);
                     #endif
                     sprintf(ls_commande,"xcopy \"%s%s%s\\*.*\" \"%s%s%s\\\" /E /I /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                     print_oem(ls_commande);                   
                  }
                  else
                  {
                   //on 'récurse' dedans
                   _findclose (ll_handle_dst);
                   sprintf(ls_chemin_prochain,"%s%s\\",as_chemin_relatif,lstr_find_src.name);
                   fic_en_moins(as_chemin_src,as_chemin_dst,ls_chemin_prochain);
                   }
             }
             else
             {
                 //c'est un fichier?
                 sprintf(ls_fichier_dst,"%s%s%s",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                         
                 //cherche ce fichier...
                 ll_handle_dst =  _findfirst (ls_fichier_dst, &lstr_find_dst);
                 if (ll_handle_dst == -1)
                 {
                     #ifdef TRACE
                     sprintf(ls_commande,"echo Fichier %s non trouvé!!!\n",ls_fichier_dst);
                     print_oem(ls_commande);
                     #endif
                     sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif);
                     print_oem(ls_commande);
                 }
                 else
                 {
                     _findclose (ll_handle_dst);
                     li_copy = 0;
                     //comparer lstr_find_src et lstr_find_dst
                     if (lstr_find_src.size        != lstr_find_dst.size)        
                     {
                         #ifdef TRACE                          
                         sprintf(ls_commande,"echo Fichier %s taille différente!!!\n",ls_fichier_dst);
                         print_oem(ls_commande);             
                         #endif
                         li_copy=1;
                     }
                     //if (lstr_find_src.time_create != lstr_find_dst.time_create) printf("Fichier %s heure de création différente!!!\n",ls_fichier_dst);
                     //if (lstr_find_src.time_access != lstr_find_dst.time_access) printf("Fichier %s heure de dernier accés différente!!!\n",ls_fichier_dst);
                     if (lstr_find_src.time_write  != lstr_find_dst.time_write)  
                     {
                         #ifdef TRACE                          
                         sprintf(ls_commande,"echo Fichier %s heure de modification différente!!!\n",ls_fichier_dst);
                         print_oem(ls_commande);
                         #endif
                         li_copy=1;
                     }
                     if (li_copy==1) 
                     {
                       sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif);
                       print_oem(ls_commande);         
                     }
                 }
             }
         }
    }          
    while(_findnext(ll_handle_src, &lstr_find_src)==0);
    _findclose (ll_handle_src);
    return 0;
}

int fic_en_trop(char* as_chemin_src,char* as_chemin_dst, char * as_chemin_relatif)
{
    //parcours destination à la recherche de fichier/répertoire qui ne seraient pas dans la source -> a effacer...
struct _finddata_t lstr_find_src,lstr_find_dst; 
long ll_handle_src,ll_handle_dst;
char ls_chemin_src[1024];
char ls_chemin_dst[1024];
char ls_fichier_dst[1024];
char ls_chemin_prochain[1024];
char ls_commande[1024];
     //créé les path de recherche
    //cible
    sprintf(ls_chemin_dst,"%s%s*.*",as_chemin_dst,as_chemin_relatif);
    //printf("REM Parcours de %s \n",ls_chemin_dst);
    //recherche dans source
    ll_handle_dst =  _findfirst (ls_chemin_dst, &lstr_find_dst);
    do 
    {     
          //ignorer les fichiers .  ..       et le volume du disque
         if( (strcmp(lstr_find_dst.name,".")!=0) && 
             (strcmp(lstr_find_dst.name,"..")!=0) && 
            !(lstr_find_dst.attrib & _A_VOLID) && 
             (strcmp(lstr_find_dst.name,"System Volume Information")!=0) && 
             (strcmp(lstr_find_dst.name,"RECYCLER")!=0))
         {
             if (lstr_find_dst.attrib & _A_SUBDIR)
             {
                  //c'est un répertoire 
                  //on le cherche en source
                  sprintf(ls_chemin_src,"%s%s%s\\*.*",as_chemin_src,as_chemin_relatif,lstr_find_dst.name);
                  ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
                  if (ll_handle_src == -1)
                  {
                       //n'exite plus en source -> a effacer
                       #ifdef TRACE
                       sprintf(ls_commande,"echo Le répertoire %s n'existe plus dans %s%s. Il doit être effacer de %s%s \n",lstr_find_dst.name,as_chemin_src,as_chemin_relatif,as_chemin_dst,as_chemin_relatif);
                       print_oem(ls_commande);
                       #endif
                       sprintf(ls_commande,"RD /S /Q \"%s%s%s\" \n",as_chemin_dst,as_chemin_relatif,lstr_find_dst.name);
                       print_oem(ls_commande);
                  }
                  else
                  {
                      _findclose (ll_handle_src);
                      //puis on 'récurse' dedans
                      sprintf(ls_chemin_prochain,"%s%s\\",as_chemin_relatif,lstr_find_dst.name);
                      fic_en_trop(as_chemin_src,as_chemin_dst,ls_chemin_prochain);
                      }
             }
             else
             {
                 //c'est un fichier?
                 sprintf(ls_chemin_src,"%s%s%s",as_chemin_src,as_chemin_relatif,lstr_find_dst.name);
                 //cherche ce fichier...
                 ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
                 if (ll_handle_src == -1)
                 {
                     #ifdef TRACE              
                     sprintf(ls_commande,"echo Fichier %s non trouvé!!! On doit l'effacer de %s%s \n",ls_chemin_src,as_chemin_dst,as_chemin_relatif);
                     print_oem(ls_commande);
                     #endif
                     sprintf(ls_commande,"DEL \"%s%s%s\" /A \n",as_chemin_dst,as_chemin_relatif,lstr_find_dst.name);
                     print_oem(ls_commande);
                 }
                 else
                 {
                     //comparer lstr_find_src et lstr_find_dst
                     if (lstr_find_src.size        != lstr_find_dst.size)        
                     {
                        #ifdef TRACE                           
                        sprintf(ls_commande,"echo Fichier %s taille différente!!!\n",ls_chemin_src);
                        //print_oem(ls_commande);
                        #endif
                     }
                     //if (lstr_find_src.time_create != lstr_find_dst.time_create) printf("REM Fichier %s heure de création différente!!!\n",ls_fichier_dst);
                     //if (lstr_find_src.time_access != lstr_find_dst.time_access) printf("REM Fichier %s heure de dernier accés différente!!!\n",ls_fichier_dst);
                     if (lstr_find_src.time_write  != lstr_find_dst.time_write)  
                     {
                         #ifdef TRACE                          
                         sprintf(ls_commande,"echo Fichier %s heure de modification différente!!!\n",ls_chemin_src);
                         //print_oem(ls_commande);
                         #endif
                     }
                     
                     _findclose (ll_handle_src);
                 }
             }
         }
    }          
    while(_findnext(ll_handle_dst, &lstr_find_dst)==0);
    _findclose (ll_handle_dst);
    return 0;
}

int main(int argc, char *argv[])
{
    char ls_commande[1024];
  if (argc == 3)
  {  
     sprintf(ls_commande,"@echo off\n",argv[1],argv[2]);
     print_oem(ls_commande);
     sprintf(ls_commande,"Echo Synchronisation de %s vers %s\n",argv[1],argv[2]); 
     print_oem(ls_commande);
     fic_en_trop(argv[1],argv[2],"\\");  
     fic_en_moins(argv[1],argv[2],"\\"); 
  }
  //system("PAUSE");	
  return 0;
}
