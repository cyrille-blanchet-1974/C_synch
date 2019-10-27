#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include "fichier.h"
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
fichier::fichier()
{
	strcpy(name," ");

}

// class destructor
fichier::~fichier()
{
	// insert your code here
}

void fichier::init(struct _finddata_t infos)
{
	// insert your code here
	attrib=infos.attrib;		
	time_create=infos.time_create;
	time_access=infos.time_access;	
	time_write=infos.time_write;
	size=infos.size;
	strcpy(name,infos.name);
	
}

int fichier::is_dir()
{
     if (attrib & _A_SUBDIR)
        return 1;
     else
        return 0;
}

int fichier::is_special()
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
    
time_t fichier::get_time_create()
{
       return time_create;
}
time_t fichier::get_time_access()
{
       return time_access;
}
time_t fichier::get_time_write()
{
       return time_write;
}
_fsize_t fichier::get_size()
{
         return size;
}
void fichier::get_name(char * o_name)
{
     strcpy(o_name,name);
}
unsigned fichier::get_attrib()
{
     return attrib;
}
