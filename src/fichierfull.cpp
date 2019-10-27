#include <stdio.h>
#include <string.h>
#include "fichier.h"


    
/***********************************************
* constructeur 1 recoit un objet fichier en mémoire et copie ces données en local
************************************************/
c_fichier_full::c_fichier_full(c_fichier_full *ap_fichier)
{
	attrib=ap_fichier->get_attrib();		
	time_create=ap_fichier->get_time_create();
	time_access=ap_fichier->get_time_access();	
	time_write=ap_fichier->get_time_write();
	size=ap_fichier->get_size();

    p_name.set(ap_fichier->get_name());

}

/***********************************************
* constructeur 2 
*ne recoit rien on devra remplire avec la méthode init
************************************************/
c_fichier_full::c_fichier_full()
{
}

/***********************************************
* initialise l'objet
* recoit une structure  fichier
************************************************/
void c_fichier_full::init(struct _finddata_t infos)
{
  
	attrib=infos.attrib;		
	time_create=infos.time_create;
	time_access=infos.time_access;	
	time_write=infos.time_write;
	size=infos.size;

    p_name.set(infos.name);
}

/***********************************************
* destructeur libère la mémoire
************************************************/
c_fichier_full::~c_fichier_full()
{
}

/***********************************************
* indique si le fichier est un dossier
************************************************/
int c_fichier_full::is_dir()
{
     if (attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}

/***********************************************
* indique si le fichier est 'spécial'
* c-a-d si c'est . .. le nom du volume du disque ou la poubelle
************************************************/
int c_fichier_full::is_special()
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
* donne la date/heure de création du fichier
************************************************/    
time_t c_fichier_full::get_time_create()
{
       return time_create;
}

/***********************************************
*donne la date/heure de dernier acces
************************************************/
time_t c_fichier_full::get_time_access()
{
       return time_access;
}

/***********************************************
*donne la date/heure de modification
************************************************/
time_t c_fichier_full::get_time_write()
{
       return time_write;
}

/***********************************************
* donne la taille
************************************************/
_fsize_t c_fichier_full::get_size()
{
         return size;
}

/***********************************************
*donne le nom
************************************************/
char* c_fichier_full::get_name()
{
     return p_name.get();
}

/***********************************************
*donne un pointeur sur le nom
************************************************/
class c_strings * c_fichier_full::get_pname()
{
	return &p_name;
}


/***********************************************
* donne les attributs
************************************************/
unsigned c_fichier_full::get_attrib()
{
     return attrib;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier_full::operator==(c_fichier_full &b)
{
 	if (b.attrib!=attrib) return false;		
 	if (b.time_create!=time_create) return false;		
 	if (b.time_access!=time_access) return false;		
 	if (b.time_write!=time_write) return false;		
 	if (b.size!=size) return false;		
    if( strcmp(p_name.get(),b.p_name.get())!=0 ) return false;
    
     return true;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier_full::operator!=(c_fichier_full &b)
{
 	if (b.attrib!=attrib) return true;		
 	if (b.time_create!=time_create) return true;		
 	if (b.time_access!=time_access) return true;		
 	if (b.time_write!=time_write) return true;		
 	if (b.size!=size) return true;		
    if( strcmp(p_name.get(),b.p_name.get())!=0 ) return true;
    
     return false;
}

/***********************************************
*affiche le fichier
************************************************/
void c_fichier_full::afficher()
{
   printf("   fichier:%s\n",p_name.get());
}
