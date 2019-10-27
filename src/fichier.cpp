#include <stdio.h>
#include <string.h>
#include "fichier.h"


    
/***********************************************
* constructeur 1 recoit un objet fichier en m�moire et copie ces donn�es en local
************************************************/
c_fichier::c_fichier(c_fichier *ap_fichier)
{
	attrib=ap_fichier->get_attrib();		
	time_write=ap_fichier->get_time_write();
	size=ap_fichier->get_size();

    p_name.set(ap_fichier->get_name());
}

/***********************************************
* constructeur 2 
*ne recoit rien on devra remplire avec la m�thode init
************************************************/
c_fichier::c_fichier()
{
}
/***********************************************
* initialise l'objet
* recoit une structure  fichier
************************************************/
void c_fichier::init(struct _finddata_t infos)
{
  
	attrib=infos.attrib;		
	time_write=infos.time_write;
	size=infos.size;

    p_name.set(infos.name);
}

/***********************************************
* destructeur lib�re la m�moire
************************************************/
c_fichier::~c_fichier()
{
}

/***********************************************
* indique si le fichier est un dossier
************************************************/
int c_fichier::is_dir()
{
     if (attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}

/***********************************************
* indique si le fichier est 'sp�cial'
* c-a-d si c'est . .. le nom du volume du disque ou la poubelle
************************************************/
int c_fichier::is_special()
{
char * p_local_name=NULL;
  p_local_name=p_name.get();
  if(strcmp(p_local_name,".")==0)                          return 1;
  if(strcmp(p_local_name,"..")==0)                         return 1;
  if(strcmp(p_local_name,"System Volume Information")==0)  return 1;
  if(strcmp(p_local_name,"RECYCLER")==0)                   return 1;
  if(strcmp(p_local_name,"$RECYCLE.BIN")==0)               return 1;
  //TODO: Ajouter les fichier system de windows vista/seven/8/2008...
  if(attrib & _A_VOLID)                                    return 1;
  return 0;
}

/***********************************************
*donne la date/heure de modification
************************************************/
time_t c_fichier::get_time_write()
{
       return time_write;
}

/***********************************************
* donne la taille
************************************************/
_fsize_t c_fichier::get_size()
{
         return size;
}

/***********************************************
*donne le nom
************************************************/
char* c_fichier::get_name()
{
     return p_name.get();
}

/***********************************************
*donne un pointeur sur le nom
************************************************/
class c_strings * c_fichier::get_pname()
{
	return &p_name;
}


/***********************************************
* donne les attributs
************************************************/
unsigned c_fichier::get_attrib()
{
     return attrib;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier::operator==(c_fichier &b)
{
 	if (b.size!=size) return false;		
	//si la taille est 0 alors on ne compare pas les dates 
	//(apparement si on lance un scopy d'un fichier de taille 0 mais existant d�j� 
	//en destination, la date du fichier de destination devient la date de la copie...)
	if(size !=0) {
	 	if (b.time_write!=time_write) return false;		
	}
    return true;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier::operator!=(c_fichier &b)
{
 	if (b.size!=size) return true;				
	//si la taille est 0 alors on ne compare pas les dates 
	//(apparement si on lance un scopy d'un fichier de taille 0 mais existant d�j� 
	//en destination, la date du fichier de destination devient la date de la copie...)
	if(size !=0) {
		if (b.time_write!=time_write) return true;		
	}
    return false;
}

/***********************************************
*affiche le fichier
************************************************/
void c_fichier::afficher()
{
   printf("   fichier:%s\n",p_name.get());
}

/***********************************************
*affiche le fichier
************************************************/
bool c_fichier::isDiffCrypt(c_fichier &src,c_fichier &dst){
 	//on est sur du cryptage
	//ma clef (source n'est pas crypt�e mais devrait th�oriquement l'�tre
	//du coup pour tout fichier de 4096octets ou plus le system me donne une taille inf�rieur de 4096 octets
	//car lors du cryptage un ent�te est ajout�
	if(dst.size >= 4096){ //on regarde la taille de destination qui est la seule qui soit ok
		//+ de 4096 alors on les soustrait � destination
		if ((src.size+4096) !=dst.size) return true;
	}else{
		//moins de 4096 octets le fichier n'est pas cryot� et donc on compare directement
 		if (src.size!=dst.size) return true;				
	}
	//si la taille est 0 alors on ne compare pas les dates 
	//(apparement si on lance un scopy d'un fichier de taille 0 mais existant d�j� 
	//en destination, la date du fichier de destination devient la date de la copie...)
	if(src.size !=0) {
		if (src.time_write!=dst.time_write) return true;		
	}
    return false;
}