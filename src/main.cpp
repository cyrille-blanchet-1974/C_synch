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
Version 4.29.1 12/2011 ++ $RECYCLE.BIN dans les ignor�s
Version 4,30 01/2011 option /ignore                -> annul�e car plante
Version 4.31 02/2011 Objets des dossier � ignorer  -> annul�e car plante 
Version 4.32 12/2011 ignorer $RECYCLE.BIN          -> annul�e car ne fait rien 

Version 4.4 bas� sur 4.29.1 Continuer si Erreur de findfirst (sous option)
							si fichier destination exactement 4096 ou plus petit concid�rer comme identique (sous option)
							simplification main
TODO: copy en place de xcopy -> non car ne fonctionne pas si attribut cach�
Version 4.5 remplacer les caract�res posant souci � msdos (% � - ) par un ? dans les commandes du script de sortie

Version 4.6 : si fichiers sources et cible de taille 0 ne pas comparer la date
Version 4.61: transforme le caract�re tiret (-) de word en ? car non support� par dos 

TODO: log avec les erreur si ignore_err
*/
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "global.h"
#include "synch.h"


using namespace std;
#define MAXSIZEPARM 1024

void title(){
    printf("Thread(%li)-Synch 4.61 (c) CBL 2015\n",GetCurrentThreadId()); 
}
void help(char* nomProg){
		printf("Syntaxe: %s /src:dossier_source /des:dossier_cible /fic:fichier_sortie.bat [/append] [/multithread] [/verbose] [/crypt] [/ignore_err]\n",nomProg);
        printf("------------------------------------\n");
        printf("dossier_source: Dossier maitre\n");
        printf("dossier_cible: Dossier esclave (deviedra un clone de source)\n");
        printf("fichier_sortie.bat: fichier bat qui recevra les commandes pour cloner source en cible\n");
        printf("/multithread: Option pour mode multithread\n");
		printf("/append: Indique si on ajoue le resulat u fichier de sortie (defaut = ecraser) \n");
		printf("/verbose: affiche a l'�cran les information indiquant les diff�rences sources/cible \n");
		printf("/crypt: Si la destination fait exactement 4096 octet de moins concid�rer comme identique \n");
		printf("/ignore_err: affiche a l'�cran les information indiquant les diff�rences sources/cible \n");
        printf("---------------------------------------------------------------------------\n");
}
bool dealWithStringParm(char* arg,char* name,char* receptacle){
char *tmp;
	   //on cherche le switch ("/src:")
		tmp = strstr(arg,name);
		//si trouv�
		if(tmp!=NULL)
		{
			tmp=tmp+strlen(name); //on saute le switch ("/src:")
			if(tmp[0]=='"') //si on est sur une "
			{	//notre chaine commence r�ellement au caract�re suivant
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(receptacle,MAXSIZEPARM,tmp+1,_TRUNCATE);
				#else
					strncpy(receptacle,tmp+1,MAXSIZEPARM);
				#endif
			}
			else
				#if defined(_MSC_VER)  &&  (_MSC_VER > 1200) 
					strncpy_s(receptacle,MAXSIZEPARM,tmp,_TRUNCATE);
				#else
					strncpy(receptacle,tmp,MAXSIZEPARM);
				#endif
			if(tmp[0]=='"')//si " au d�but
				if(receptacle[strlen(receptacle)] == '"') //et " � la fin
					receptacle[strlen(receptacle)] = '\0';
			return true; //pas � l'argument suivant
		}
		return false;
}

//renvoie si le param�tre est dans la cha�ne
bool contains(char* arg,char* name){
	//si trouv�
	if(strstr(arg,name)!=NULL){
		return true;
	}
	return false;
}

/* Fonction d'analyse des param�tres de la ligne de commande
   Si ok lance les op�rations
   Si Ko ou /? affiche l'aide
   Renvoie 
*/
int main(int argc, char *argv[])
{
bool b_multithread_mode = false;
char ls_source[MAXSIZEPARM];
char ls_cible[MAXSIZEPARM];
char ls_fic_sortie[MAXSIZEPARM];
bool b_ecraser=true;//par d�faut on �rase
bool b_verbose=false;//par d�faut on ne trace pas tut � l'�cran
bool b_crypt=false;
bool b_ignore_err=false;
bool lb_all_is_ok=true;
c_synch *lsynch=NULL;
long i;
	memset(ls_source,0,MAXSIZEPARM);
	memset(ls_cible,0,MAXSIZEPARM);
	memset(ls_fic_sortie,0,MAXSIZEPARM);
	title();
	for(i=1;i<argc;i++)
	{
		//si chaine contient /? /help -? -help --help -> afficher l'aide donc mettre lb_all_is_ok � Faux 
		if(strcmp(argv[i],"/?"    )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"-?"    )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"/help" )==0) lb_all_is_ok = false;
		if(strcmp(argv[i],"--help")==0) lb_all_is_ok = false;
		if(lb_all_is_ok == false)break; //inutile de continuer dans ce cas...

		//cherche /src:
		if(dealWithStringParm(argv[i],"/src:",ls_source)) continue;
		//cherche /dst:
		if(dealWithStringParm(argv[i],"/dst:",ls_cible)) continue;
		//cherche /fic:
		if(dealWithStringParm(argv[i],"/fic:",ls_fic_sortie)) continue;

		//cherche /multithread
		if( contains(argv[i],"/multithread")){
			b_multithread_mode=true;
			continue; //pas � l'argument suivant
		}
		//cherche /append
		if( contains(argv[i],"/append")){
			b_ecraser=false;
			continue; //pas � l'argument suivant
		}
		//cherche /verbose
		if( contains(argv[i],"/verbose")){
			b_verbose=true;
			continue; //pas � l'argument suivant
		}
		//cherche /crypt
		if( contains(argv[i],"/crypt")){
			b_crypt=true;
			continue; //pas � l'argument suivant
		}
		//cherche /ignore_err
		if( contains(argv[i],"/ignore_err")){
			b_ignore_err=true;
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
		lsynch=new c_synch(ls_source,ls_cible,ls_fic_sortie,b_multithread_mode,b_ecraser,b_verbose,b_crypt,b_ignore_err);
		if(lsynch!=NULL)delete lsynch;
	}
	else
    {
		help(argv[0]);
        system("PAUSE");
    }        
    return EXIT_SUCCESS;
}


