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
 	if (b.time_write!=time_write) return false;		
 	//if (b.attrib!=attrib) return false;		
 	if (b.size!=size) return false;		
    //if( strcmp(p_name.get(),b.p_name.get())!=0 ) return false;
    
     return true;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier::operator!=(c_fichier &b)
{
 	if (b.time_write!=time_write) return true;		
 	//if (b.attrib!=attrib) return true;		
 	if (b.size!=size) return true;		
    //if( strcmp(p_name.get(),b.p_name.get())!=0 ) return true;
    
     return false;
}

/***********************************************
*affiche le fichier
************************************************/
void c_fichier::afficher()
{
   printf("   fichier:%s\n",p_name.get());
}
