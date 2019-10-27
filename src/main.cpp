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
*/

#include <cstdlib>
#include <iostream>
#include "arbo.h"

using namespace std;

int main(int argc, char *argv[])
{
  class c_arbo *source;
  class c_arbo *cible;

    source = new c_arbo("D:");
    cible = new c_arbo("M:");
    source->fic_en_moins(cible);
    cible->fic_en_trop(source);

    system("PAUSE");
    return EXIT_SUCCESS;
}


