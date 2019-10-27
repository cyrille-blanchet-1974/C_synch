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


*/

#include <cstdlib>
#include <iostream>
#include "arbo.h"

using namespace std;

int main(int argc, char *argv[])
{
  class c_arbo *source;
  class c_arbo *cible;
  
  char *chainecourante = "\\a garder\\documents\\achats possibles\\2,5 dans 5,25_files\\bd_data_002\\flashwrite_1_2.js" ;
  char *chainecherchee = "\\a garder\\documents\\achats possibles\\2,5 dans 5,25_files\\bd_data_002\\SAM_CMOS_120X600_30k_3.swf";
   
   printf("cmp %s %s %li\n",chainecourante,chainecherchee,strcmp(chainecourante,chainecherchee));
   
    printf("Lecture source\n");
    source = new c_arbo("D:");
    printf("Lecture cible\n");
    //cible = new c_arbo("G:\\sauvegardes\\portable");
    cible = new c_arbo("D:");
    printf("Recherche fichiers manquants/modifiés\n");
    source->fic_en_moins(cible);
    printf("Recherche fichiers en trop\n");
    cible->fic_en_trop(source);

    delete source;
    delete cible;
    system("PAUSE");
    return EXIT_SUCCESS;
}


