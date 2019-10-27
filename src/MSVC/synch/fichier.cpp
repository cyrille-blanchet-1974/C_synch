#include <stdio.h>
#include <string.h>
#include "fichier.h"
#include "string.h"
/*
//DEVCPP
#define	_A_NORMAL	0x00000000
#define	_A_RDONLY	0x00000001
#define	_A_HIDDEN	0x00000002
#define	_A_SYSTEM	0x00000004
#define	_A_VOLID	0x00000008
#define	_A_SUBDIR	0x00000010
#define	_A_ARCH		0x00000020*/
//Visual C io.h
//#define _A_NORMAL       0x00    /* Normal file - No read/write restrictions */
//#define _A_RDONLY       0x01    /* Read only file */
//#define _A_HIDDEN       0x02    /* Hidden file */
//#define _A_SYSTEM       0x04    /* System file */
//#define _A_SUBDIR       0x10    /* Subdirectory */
//#define _A_ARCH         0x20    /* Archive file */
#ifdef  _MSC_VER
#ifndef _A_VOLID
#define	_A_VOLID	0x00000008
#endif  
#endif  


    
/***********************************************
* constructeur 1 recoit un objet fichier en mémoire et copie ces données en local
************************************************/
c_fichier::c_fichier(c_fichier *ap_fichier)
{
    //#ifdef DEBUG
    //printf("c_fichier constructeur(%s)\n",ap_fichier->get_name());
    //#endif                       
	attrib=ap_fichier->get_attrib();		
	time_create=ap_fichier->get_time_create();
	time_access=ap_fichier->get_time_access();	
	time_write=ap_fichier->get_time_write();
	size=ap_fichier->get_size();

    p_name=NULL; 
    p_name=c_string::copy_alloc(ap_fichier->get_name());

}

/***********************************************
* constructeur 2 
*ne recoit rien on devra remplire avec la méthode init
************************************************/
c_fichier::c_fichier()
{
    p_name=NULL;
}

/***********************************************
* initialise l'objet
* recoit une structure  fichier
************************************************/
void c_fichier::init(struct _finddata_t infos)
{
  
    //#ifdef DEBUG
    //printf("c_fichier init(%s)\n",infos.name);
    //#endif                       
	attrib=infos.attrib;		
	time_create=infos.time_create;
	time_access=infos.time_access;	
	time_write=infos.time_write;
	size=infos.size;

    //printf("réallocation p_name de fichier \n");
    if (p_name !=NULL) 
    {
        if(p_name!=NULL)delete [] p_name;
        //printf("p_name de fichier libéré \n");
        p_name=NULL;
    }    
    p_name=c_string::copy_alloc(infos.name);
}

/***********************************************
* destructeur libère la mémoire
************************************************/
c_fichier::~c_fichier()
{
	// insert your code here
    if (p_name !=NULL) delete p_name;
    p_name=NULL;
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
* indique si le fichier est 'spécial'
* c-a-d si c'est . .. le nom du volume du disque ou la poubelle
************************************************/
int c_fichier::is_special()
{
  if(strcmp(p_name,".")==0)   return 1;
  if(strcmp(p_name,"..")==0)  return 1;
  if(attrib & _A_VOLID)     return 1;
  if(strcmp(p_name,"System Volume Information")==0)  return 1;
  if(strcmp(p_name,"RECYCLER")==0)  return 1;
  return 0;
}

/***********************************************
* donne la date/heure de création du fichier
************************************************/    
time_t c_fichier::get_time_create()
{
       return time_create;
}

/***********************************************
*donne la date/heure de dernier acces
************************************************/
time_t c_fichier::get_time_access()
{
       return time_access;
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
     return p_name;
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
bool c_fichier::operator==(c_fichier b)
{
 	if (b.attrib!=attrib) return false;		
 	if (b.time_create!=time_create) return false;		
 	if (b.time_access!=time_access) return false;		
 	if (b.time_write!=time_write) return false;		
 	if (b.size!=size) return false;		
    if( strcmp(p_name,b.p_name)!=0 ) return false;
    
     return true;
}

/***********************************************
*affiche le fichier
************************************************/
void c_fichier::afficher()
{
   printf("   fichier:%s\n",p_name);
}
