#include <stdio.h>
#include <string.h>
#include "fichier.h"
#include "string.h"
#include "lib.h"
/*
#define	_A_NORMAL	0x00000000
#define	_A_RDONLY	0x00000001
#define	_A_HIDDEN	0x00000002
#define	_A_SYSTEM	0x00000004
#define	_A_VOLID	0x00000008
#define	_A_SUBDIR	0x00000010
#define	_A_ARCH		0x00000020
*/

    
// class constructor
c_fichier::c_fichier(c_fichier *fichier)
{
	attrib=fichier->get_attrib();		
	time_create=fichier->get_time_create();
	time_access=fichier->get_time_access();	
	time_write=fichier->get_time_write();
	size=fichier->get_size();
 
    name=c_string::strcpy_alloc(name,fichier->get_name());

}

// class constructor 3
c_fichier::c_fichier()
{
    name=NULL;
}

// changeùent du contenu 
int c_fichier::init(struct _finddata_t infos,char *achemin)
{
  
	attrib=infos.attrib;		
	time_create=infos.time_create;
	time_access=infos.time_access;	
	time_write=infos.time_write;
	size=infos.size;


    if (name !=NULL) delete name;
    name=c_string::strcpy_alloc(name,infos.name);
}

// class destructor
c_fichier::~c_fichier()
{
	// insert your code here
    if (name !=NULL) delete name;
}


int c_fichier::is_dir()
{
     if (attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}

int c_fichier::is_special()
{
     if( (strcmp(name,".")!=0) && 
         (strcmp(name,"..")!=0) && 
        !(attrib & _A_VOLID)  && 
         (strcmp(name,"System Volume Information")!=0) && 
         (strcmp(name,"RECYCLER")!=0) )
         return 0;
     else
         return 1;
}
    
time_t c_fichier::get_time_create()
{
       return time_create;
}
time_t c_fichier::get_time_access()
{
       return time_access;
}
time_t c_fichier::get_time_write()
{
       return time_write;
}
_fsize_t c_fichier::get_size()
{
         return size;
}
char* c_fichier::get_name()
{
     return name;
}

unsigned c_fichier::get_attrib()
{
     return attrib;
}
bool c_fichier::operator==(c_fichier b)
{
 	if (b.attrib!=attrib) return false;		
 	if (b.time_create!=time_create) return false;		
 	if (b.time_access!=time_access) return false;		
 	if (b.time_write!=time_write) return false;		
 	if (b.size!=size) return false;		
    if( strcmp(name,b.name)!=0 ) return false;
    
     return true;
}
void c_fichier::afficher()
{
   printf("   fichier:%s\n",name);
}
