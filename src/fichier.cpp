#include <stdio.h>
#include <string.h>
#include "fichier.h"


    
/***********************************************
* constructeur 1 recoit un objet fichier en mémoire et copie ces données en local
************************************************/
c_fichier::c_fichier(c_fichier *ap_fichier)
{
	this->attrib=ap_fichier->get_attrib();		
	this->time_write=ap_fichier->get_time_write();
	this->size=ap_fichier->get_size();

    this->p_name.set(ap_fichier->get_name());

}

/***********************************************
* constructeur 2 
*ne recoit rien on devra remplire avec la méthode init
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
  
	this->attrib=infos.attrib;		
	this->time_write=infos.time_write;
	this->size=infos.size;

    this->p_name.set(infos.name);
}

/***********************************************
* destructeur libère la mémoire
************************************************/
c_fichier::~c_fichier()
{
}

/***********************************************
* indique si le fichier est un dossier
************************************************/
int c_fichier::is_dir()
{
     if (this->attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}

/***********************************************
* indique si le fichier est 'spécial'
* c-a-d si c'est . .. le nom du volume du disque ou la poubelle
************************************************/
int c_fichier::is_special()
{
char * p_local_name=NULL;
  p_local_name=this->p_name.get();
  if(strcmp(p_local_name,".")==0)                          return 1;
  if(strcmp(p_local_name,"..")==0)                         return 1;
  if(strcmp(p_local_name,"System Volume Information")==0)  return 1;
  if(strcmp(p_local_name,"RECYCLER")==0)                   return 1;
  if(this->attrib & _A_VOLID)                              return 1;
  return 0;
}

/***********************************************
*donne la date/heure de modification
************************************************/
time_t c_fichier::get_time_write()
{
       return this->time_write;
}

/***********************************************
* donne la taille
************************************************/
_fsize_t c_fichier::get_size()
{
         return this->size;
}

/***********************************************
*donne le nom
************************************************/
char* c_fichier::get_name()
{
     return this->p_name.get();
}

/***********************************************
*donne un pointeur sur le nom
************************************************/
class c_strings * c_fichier::get_pname()
{
	return &this->p_name;
}


/***********************************************
* donne les attributs
************************************************/
unsigned c_fichier::get_attrib()
{
     return this->attrib;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier::operator==(c_fichier &b)
{
 	if (b.time_write!=this->time_write) return false;		
 	//if (b.attrib!=attrib) return false;		
 	if (b.size!=this->size) return false;		
    //if( strcmp(p_name.get(),b.p_name.get())!=0 ) return false;
    
     return true;
}

/***********************************************
* compare deux fichiers
************************************************/
bool c_fichier::operator!=(c_fichier &b)
{
 	if (b.time_write!=this->time_write) return true;		
 	//if (b.attrib!=attrib) return true;		
 	if (b.size!=this->size) return true;		
    //if( strcmp(p_name.get(),b.p_name.get())!=0 ) return true;
    
     return false;
}

/***********************************************
*affiche le fichier
************************************************/
void c_fichier::afficher()
{
   printf("   fichier:%s\n",this->p_name.get());
}
