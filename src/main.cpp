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
Version 4.24 08/2008 Ajout operator ==
Test de strcmp implémenté dans la classe c_strings
passe de 15s (strcmp standard) à .... + de 2 minutes!!!
-> implémentation de == qui fait un strcmp
++lors du stockage des données un .lower pour pas être ebêté par la casse

Version 4.26 07/2009 début passage en multithreading

*/
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "global.h"
#include "strings.h"
#include "synch.h"


using namespace std;

int main(int argc, char *argv[])
{
c_strings ls_commande;
bool b_multithread_mode = false;
c_synch *lsynch=NULL;

    printf("Thread(%li)-Synch 4.26 (c) CBL 2009\n",GetCurrentThreadId()); 
    if (argc < 4)
    {
        printf("Syntaxe: Synch source cible fic.bat [thread]\n");
        printf("------------------------------------\n");
        printf("source: Dossier maitre\n");
        printf("cible: Dossier esclave (deviedra un clone de source)\n");
        printf("fic.bat: fichier bat qui recevra les commandes pour cloner source en cible\n");
        printf("thread: Option pour mode multithread\n");
        printf("---------------------------------------------------------------------------\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    }
    if(argc >4)
        if( !strcmp(argv[4],"thread") ) 
            b_multithread_mode = true;
            
    lsynch=new c_synch(argv[1],argv[2],argv[3],b_multithread_mode);
    
    if(lsynch!=NULL)delete lsynch;
    
        
    return EXIT_SUCCESS;
}

