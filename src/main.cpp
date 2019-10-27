/*synch
synchronise deux dossier
analyse la source pour chaque fichier le cherche en cible
S'il n'existe pas il faut le copier
s'il existe on compare date, attributs et taille pour savoir si on doit �craser
ensuite on parcours le cible en cherchant chaques fichiers en source s'il n'y est pas on doit l'effacer de la cible
Version 1.0  10/2005 en proc�durale
Version 1.1  11/2006 test de parcours de dossier seulement pour voir o� am�liorer
Version 2.0  11/2006 tentative de refonte en objet (but: lire les 2 arborescences puis comparer en m�moire pour diminuer lesI/O disques PB compile
Version 2.1  11/2006 tentative N�2 de refonte en objet compile Ok mais limitation du nombre de fichiers/dossiers
Version 3.0  06/2008 objet avec liste lin�aire chain�e pour stocker les fichiers et dossiers lecture du disque seulement pas finit comparaison
Version 3.1  06/2008 (idem ci-dessus+comparaisons) fonctionne mais lentement car 140 000 dossier = des milliards de strcmp// essai d'acc�l�ration avec un cache en tableau sans succes
Version 3.2  06/2008 essai d'am�lioration en triant les liste sans succes
Version 4.0  06/2008 cette fois une liste chain�e pour les dossier contenant pour chaque maillon le nom du dossier et une liste chain�e des fichiers! (pas encore de comparaison)
synchronisation D:\ -> WD (140 000 dossiers)
26secondes en proc�durale -> 6 secondes
Version 4.1  07/2008 plus qu'une seule classe pour la liste chain�e et non une classe liste et une lasse maillon
Version 4.2  07/2008 am�lioration c_string
                    enlever la sensibilit� � la casse (strcmp
Version 4.22 07/2008 d�but classe sstring et version compatible Msdev                                        
Version 4.23 07/2008 objet sstring
       bench synchro d: portable avec western digital
             lancement nouveau:3m29 puis ancien:30s  puis nouveau:15s puis ancien:27s
             reboot     ancien:3m57 puis nouveau:16s puis ancien:27s  puis nouveau:15s
             1ere exec = mise en cache donc toujours plus longue ancien =30s nouveau = 15s -> 2* plus rapide!!!
             DEL /F pour effacer les fichier en lecture seule
reste � impl�menter le strcmp et strcmpnoxcase dans c_strings
et � l'utiliser dans arbo/dossier/fichier
Version 4.24 08/2008 Ajout operator ==
Test de strcmp impl�ment� dans la classe c_strings
passe de 15s (strcmp standard) � .... + de 2 minutes!!!
-> impl�mentation de == qui fait un strcmp
++lors du stockage des donn�es un .lower pour pas �tre eb�t� par la casse

Version 4.26 07/2009 d�but passage en multithreading
Version 4.27 08/2009 visual C++ 2008
Version 4.28 08/2009 Simplification c_strings
Version 4.29 09/2009 option verbose
*/
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "global.h"
#include "synch.h"


using namespace std;

/* Fonction d'analyse des param�tres de la ligne de commande
   Si ok lance les op�rations
   Si Ko ou /? affiche l'aide
   Renvoie 
*/
int main(int argc, char *argv[])
{
bool b_multithread_mode = false;
char ls_source[1024];
char ls_cible[1024];
char ls_fic_sortie[1024];
bool b_ecraser=true;//par d�faut on �rase
bool b_verbose=false;//par d�faut on ne trace pas tut � l'�cran
bool lb_all_is_ok=true;
c_synch *lsynch=NULL;
long i;
char *tmp;
	memset(ls_source,0,1024);
	memset(ls_cible,0,1024);
	memset(ls_fic_sortie,0,1024);
    printf("Thread(%li)-Synch 4.29 (c) CBL 2009\n",GetCurrentThreadId()); 
	for(i=1;i<argc;i++)
	{
		//si chaine contient /? /help -? -help --help -> afficher l'aide donc mettre lb_all_is_ok � Faux 
		if(strcmp(argv[i],"/?"    )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"-?"    )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"/help" )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"--help")==0) lb_all_is_ok = false;
		if(lb_all_is_ok == false)break; //inutile de continuer dans ce cas...

		//cherche /src:
		tmp = strstr(argv[i],"/src:");
		//si trouv�
		if(tmp!=NULL)
		{
			tmp=tmp+5; //on saute le /src:
			if(tmp[0]=='"') //si on est sur une "
			{	//notre chaine commence r�ellement au caract�re suivant
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_source,tmp+1,1024);
				#else
					strncpy(ls_source,tmp+1,1024);
				#endif
			}
			else
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_source,tmp,1024);
				#else
					strncpy(ls_source,tmp,1024);
				#endif
			if(tmp[0]=='"')//si " au d�but
				if(ls_source[strlen(ls_source)] == '"') //et " � la fin
					ls_source[strlen(ls_source)] = '\0';
			continue; //pas � l'argument suivant
		}

		//cherche /dst:
		tmp = strstr(argv[i],"/dst:");
		//si trouv�
		if(tmp!=NULL)
		{
			tmp=tmp+5; //on saute le /dst:
			if(tmp[0]=='"') //si on est sur une "
			{	//notre chaine commence r�ellement au caract�re suivant
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_cible,tmp+1,1024);
				#else
					strncpy(ls_cible,tmp+1,1024);
				#endif
			}
			else
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_cible,tmp,1024);
				#else
					strncpy(ls_cible,tmp,1024);
				#endif
			if(tmp[0]=='"')//si " au d�but
				if(ls_cible[strlen(ls_cible)] == '"') //et " � la fin
					ls_cible[strlen(ls_cible)] = '\0';
			continue; //pas � l'argument suivant
		}

		//cherche /src:
		tmp = strstr(argv[i],"/fic:");
		//si trouv�
		if(tmp!=NULL)
		{
			tmp=tmp+5; //on saute le /fic:
			if(tmp[0]=='"') //si on est sur une "
			{	//notre chaine commence r�ellement au caract�re suivant
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_fic_sortie,tmp+1,1024);
				#else
					strncpy(ls_fic_sortie,tmp+1,1024);
				#endif
			}
			else
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(ls_fic_sortie,tmp,1024);
				#else
					strncpy(ls_fic_sortie,tmp,1024);
				#endif
			if(tmp[0]=='"')//si " au d�but
				if(ls_fic_sortie[strlen(ls_fic_sortie)] == '"') //et " � la fin
					ls_fic_sortie[strlen(ls_fic_sortie)] = '\0';
			continue; //pas � l'argument suivant
		}

		//cherche /multithread
		tmp = strstr(argv[i],"/multithread");
		//si trouv�
		if(tmp!=NULL)
		{
			b_multithread_mode=true;
			continue; //pas � l'argument suivant
		}

		//cherche /multithread
		tmp = strstr(argv[i],"/append");
		//si trouv�
		if(tmp!=NULL)
		{
			b_ecraser=false;
			continue; //pas � l'argument suivant
		}
		
		//cherche /multithread
		tmp = strstr(argv[i],"/verbose");
		//si trouv�
		if(tmp!=NULL)
		{
			b_verbose=true;
			continue; //pas � l'argument suivant
		}
		
		//arriv� ici c'est que aucun argument ne correspond a ce que l'on attends...
		lb_all_is_ok =false;
		break; //inutile de continuer dans ce cas...
		
	}
	if(strlen(ls_source)==0)lb_all_is_ok=false;
	if(strlen(ls_cible)==0)lb_all_is_ok=false;
	if(strlen(ls_fic_sortie)==0)lb_all_is_ok=false;
	if(lb_all_is_ok)
	{
		lsynch=new c_synch(ls_source,ls_cible,ls_fic_sortie,b_multithread_mode,b_ecraser,b_verbose);
		if(lsynch!=NULL)delete lsynch;
	}
	else
    {
		printf("Syntaxe: %s /src:dossier_source /des:dossier_cible /fic:fichier_sortie.bat [/append] [/multithread]\n",argv[0]);
        printf("------------------------------------\n");
        printf("dossier_source: Dossier maitre\n");
        printf("dossier_cible: Dossier esclave (deviedra un clone de source)\n");
        printf("fichier_sortie.bat: fichier bat qui recevra les commandes pour cloner source en cible\n");
        printf("/multithread: Option pour mode multithread\n");
		printf("/append: Indique si on ajoue le resulat u fichier de sortie (defaut = ecraser) \n");
		printf("/verbose: affiche a l'�cran les information indiquant les diff�rences sources/cible \n");
        printf("---------------------------------------------------------------------------\n");
        system("PAUSE");
    }        
    return EXIT_SUCCESS;
}

