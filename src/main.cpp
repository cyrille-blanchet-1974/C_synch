/*synch
synchronise deux dossier
analyse la source pour chaque fichier le cherche en cible
S'il n'existe pas il faut le copier
s'il existe on compare date, attributs et taille pour savoir si on doit écraser
ensuite on parcours le cible en cherchant chaques fichiers en source s'il n'y est pas on doit l'effacer de la cible
Version 1.0 10/2005 en procédurale
Version 1.1 11/2006 test de parcours de dossier seulement pour voir où améliorer
Version 2.0 11/2006 tentative de refonte en objet (but: lire les 2 arborescences puis comparer en mémoire pour diminuer lesI/O disques PB compile
Version 2.1 11/2006 tentative N°2 de refonte en objet compile Ok mais limitation du nombre de fichiers/dossiers
Version 3.0 06/2008 objet avec liste linéaire chainée pour stocker les fichiers et dossiers lecture du disque seulement pas finit comparaison
Version 3.1 06/2008 (idem ci-dessus+comparaisons) fonctionne mais lentement car 140 000 dossier = des milliards de strcmp// essai d'accélération avec un cache en tableau sans succes
Version 3.2 06/2008 essai d'amélioration en triant les liste sans succes
Version 4.0 06/2008 cette fois une liste chainée pour les dossier contenant pour chaque maillon le nom du dossier et une liste chainée des fichiers! (pas encore de comparaison)
synchronisation D:\ -> WD (140 000 dossiers)
26secondes en procédurale -> 6 secondes
*/
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "arbo.h"
#include "lib.h"
#include "logger.h"
#include "global.h"

using namespace std;

int main(int argc, char *argv[])
{
  c_arbo *source;
  c_arbo *cible;
  c_logger *p_logger;
  char ls_commande[1024];
  

  printf("Synch 4.0 (c) CBL 2008\n"); 
  if (argc == 4)
  {  
     p_logger=new c_logger(argv[3]);      
     
     p_logger->add("@echo off\n");
     
     sprintf(ls_commande,"Echo Synchronisation de %s vers %s\n",argv[1],argv[2]); 
     p_logger->add(ls_commande);   

     printf("Lecture source\n");   
     source = new c_arbo(argv[1]);
     source->set_logger(p_logger);
     
     printf("Lecture cible\n");
     //cible = new c_arbo("G:\\sauvegardes\\portable");
     cible = new c_arbo(argv[2]);
     cible->set_logger(p_logger);

     printf("Recherche fichiers manquants/modifiés\n");   
     source->fic_en_moins(cible);

     printf("Recherche fichiers en trop\n");    
     cible->fic_en_trop(source);

     //system("PAUSE");
     delete source;
     delete cible;
     delete p_logger;
     //system("PAUSE");
  }  
  else
  {
      printf("Syntaxe: Synch source cible fic.bat\n");
      printf("------------------------------------\n");
      printf("source: Dossier maitre\n");
      printf("cible: Dossier esclave (deviedra un clone de source)\n");
      printf("fic.bat: fichier bat qui recevra les commandes pour cloner source en cible\n");
      printf("---------------------------------------------------------------------------\n");
      system("PAUSE");
}
  return EXIT_SUCCESS;
}

