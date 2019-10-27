/*synch
synchronise deux dossier
analyse la source pour chaque fichier le cherche en cible
S'il n'existe pas il faut le copier
s'il existe on compare date, attributs et taille pour savoir si on doit écraser
ensuite on parcours le cible en cherchant chaques fichiers en source s'il n'y est pas on doit l'effacer de la cible
Version 1.0  10/2005 en procédurale
Version 1.1  11/2006 test de parcours de dossier seulement pour voir où améliorer
Version 2.0  11/2006 tentative de refonte en objet (but: lire les 2 arborescences puis comparer en mémoire pour diminuer lesI/O disques PB compile
Version 2.1  11/2006 tentative N°2 de refonte en objet compile Ok mais limitation du nombre de fichiers/dossiers
Version 3.0  06/2008 objet avec liste linéaire chainée pour stocker les fichiers et dossiers lecture du disque seulement pas finit comparaison
Version 3.1  06/2008 (idem ci-dessus+comparaisons) fonctionne mais lentement car 140 000 dossier = des milliards de strcmp// essai d'accélération avec un cache en tableau sans succes
Version 3.2  06/2008 essai d'amélioration en triant les liste sans succes
Version 4.0  06/2008 cette fois une liste chainée pour les dossier contenant pour chaque maillon le nom du dossier et une liste chainée des fichiers! (pas encore de comparaison)
synchronisation D:\ -> WD (140 000 dossiers)
26secondes en procédurale -> 6 secondes
Version 4.1  07/2008 plus qu'une seule classe pour la liste chainée et non une classe liste et une lasse maillon
Version 4.2  07/2008 amélioration c_string
                    enlever la sensibilité à la casse (strcmp
Version 4.22 07/2008 début classe sstring et version compatible Msdev                                        
Version 4.23 07/2008 objet sstring
       bench synchro d: portable avec western digital
             lancement nouveau:3m29 puis ancien:30s  puis nouveau:15s puis ancien:27s
             reboot     ancien:3m57 puis nouveau:16s puis ancien:27s  puis nouveau:15s
             1ere exec = mise en cache donc toujours plus longue ancien =30s nouveau = 15s -> 2* plus rapide!!!
             DEL /F pour effacer les fichier en lecture seule
reste à implémenter le strcmp et strcmpnoxcase dans c_strings
et à l'utiliser dans arbo/dossier/fichier
*/
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "arbo.h"
#include "logger.h"
#include "global.h"
#include "strings.h"

using namespace std;

int main(int argc, char *argv[])
{
  c_arbo *p_source=NULL;
  c_arbo *p_cible=NULL;
  c_logger *p_logger=NULL;
  //char ls_commande[1024];
  c_strings ls_commande;
/*  
/////test c_strings
  c_strings tmp;
  printf("après variable tmp %s\n",(char *) tmp);
  c_strings tmp2("tmp2");
  printf("après variable tmp2 %s\n",(char *) tmp2);
  c_strings tmp3 = "tmp3";
  printf("après variable tmp3 %s\n",(char *) tmp3);
  
  tmp=tmp2+tmp3;
  printf("après variable addition %s \n",(char *) tmp);
  printf("tmp:%s\n",(char *) tmp);//.get_pointer());
  printf("tmp2:%s\n",(char *) tmp2);//.get_pointer());
  printf("tmp3:%s\n",(char *) tmp3); //.get_pointer());
  
  tmp+="quatre";
  printf("tmp:%s\n",(char *) tmp);//.get_pointer());
  printf("tmp2:%s\n",(char *) tmp2);//.get_pointer());
  printf("tmp3:%s\n",(char *) tmp3); //.get_pointer());

  tmp=tmp+"cinq";
  printf("tmp:%s\n",(char *) tmp);//.get_pointer());
  printf("tmp2:%s\n",(char *) tmp2);//.get_pointer());
  printf("tmp3:%s\n",(char *) tmp3); //.get_pointer());
  system("PAUSE"); 
/////test c_strings
*/
  printf("Synch 4.1 (c) CBL 2008\n"); 
  if (argc == 4)
  {  
     p_logger=new c_logger(argv[3]);      
     
     p_logger->add("@echo off\n");
     
     //sprintf(ls_commande,"Echo Synchronisation de %s vers %s\n",argv[1],argv[2]); 
     ls_commande="Echo Synchronisation de ";
     ls_commande+=argv[1];
     ls_commande+=" vers ";
     ls_commande+=argv[2];
     ls_commande+="\n";
     p_logger->add((char *)ls_commande);   

     printf("Lecture source\n");   
     p_source = new c_arbo(argv[1]);
     p_source->set_logger(p_logger);
     
     printf("Lecture cible\n");
     //cible = new c_arbo("G:\\sauvegardes\\portable");
     p_cible = new c_arbo(argv[2]);
     p_cible->set_logger(p_logger);

     printf("Recherche fichiers manquants/modifiés\n");   
     p_source->fic_en_moins(p_cible);

     printf("Recherche fichiers en trop\n");    
     p_cible->fic_en_trop(p_source);

     //system("PAUSE");
     if(p_source!=NULL)delete p_source;
     p_source=NULL;
     if(p_cible!=NULL)delete p_cible;
     p_cible=NULL;
     if(p_logger!=NULL)delete p_logger;
     p_logger=NULL;
//     system("PAUSE");
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

