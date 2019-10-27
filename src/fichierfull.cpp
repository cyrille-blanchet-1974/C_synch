#include <stdio.h>
#include <string.h>
#include "fichier.h"


    
/***********************************************
* constructeur 1 recoit un objet fichier en mémoire et copie ces données en local
************************************************/
c_fichier_full::c_fichier_full(c_fichier_full *ap_fichier)
{
	this->attrib=ap_fichier->get_attrib();		
	this->time_create=ap_fichier->get_time_create();
	this->time_access=ap_fichier->get_time_access();	
	this->time_write=ap_fichier->get_time_write();
	this->size=ap_fichier->get_size();

    this->p_name.set(ap_fichier->get_name());

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
  
	this->attrib=infos.attrib;		
	this->time_create=infos.time_create;
	this->time_access=infos.time_access;	
	this->time_write=infos.time_write;
	this->size=infos.size;

    this->p_name.set(infos.name);
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
/*int c_fichier_full::is_dir()
{
     if (this->attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}*/

/***********************************************
* indique si le fichier est 'spécial'
* c-a-d si c'est . .. le nom du volume du disque ou la poubelle
************************************************/
/*int c_fichier_full::is_special()
{
char * p_local_name=NULL;
long ll_idx;
  p_local_name=this->p_name.get();
  if(strcmp(p_local_name,".")==0)                          return 1;
  if(strcmp(p_local_name,"..")==0)                         return 1;
  if(strcmp(p_local_name,"System Volume Information")==0)  return 1;
  if(strcmp(p_local_name,"RECYCLER")==0)                   return 1;
  if(this->attrib & _A_VOLID)                              return 1;
  for(ll_idx=0;ll_idx<this->ll_ignore_count;ll_idx++){
	if(strcmp(p_local_name,this->ls_ignore[ll_idx])==0)          return 1;
  }

  return 0;
}idem fichier.cpp*/

/***********************************************
* donne la date/heure de création du fichier
************************************************/    
time_t c_fichier_full::get_time_create()
{
       return this->time_create;
}

/***********************************************
*donne la date/heure de dernier acces
************************************************/
time_t c_fichier_full::get_time_access()
{
       return this->time_access;
}

/***********************************************
*donne la date/heure de modification
************************************************/
/*time_t c_fichier_full::get_time_write()
{
       return this->time_write;
}*/

/***********************************************
* donne la taille
************************************************/
/*_fsize_t c_fichier_full::get_size()
{
         return this->size;
}*/

/***********************************************
*donne le nom
************************************************/
/*char* c_fichier_full::get_name()
{
     return this->p_name.get();
}*/

/***********************************************
*donne un pointeur sur le nom
************************************************/
/*class c_strings * c_fichier_full::get_pname()
{
	return &this->p_name;
}*/


/***********************************************
* donne les attributs
************************************************/
/*unsigned c_fichier_full::get_attrib()
{
     return this->attrib;
}*/

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier_full::operator==(c_fichier_full &b)
{
 	if (b.attrib!=this->attrib) return false;		
 	if (b.time_create!=this->time_create) return false;		
 	if (b.time_access!=this->time_access) return false;		
 	if (b.time_write!=this->time_write) return false;		
 	if (b.size!=this->size) return false;		
    if( strcmp(this->p_name.get(),b.p_name.get())!=0 ) return false;
    
     return true;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier_full::operator!=(c_fichier_full &b)
{
 	if (b.attrib!=this->attrib) return true;		
 	if (b.time_create!=this->time_create) return true;		
 	if (b.time_access!=this->time_access) return true;		
 	if (b.time_write!=this->time_write) return true;		
 	if (b.size!=this->size) return true;		
    if( strcmp(this->p_name.get(),b.p_name.get())!=0 ) return true;
    
     return false;
}

/***********************************************
*affiche le fichier
************************************************/
/*void c_fichier_full::afficher()
{
   printf("   fichier:%s\n",this->p_name.get());
}*/
