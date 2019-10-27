
#include "arbo.h" 
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>


// class constructor
c_fichier::c_fichier()
{
	strcpy(name," ");

}

// class destructor
c_fichier::~c_fichier()
{
	// insert your code here
}

void c_fichier::init(struct _finddata_t infos)
{
	// insert your code here
	attrib=infos.attrib;		
	time_create=infos.time_create;
	time_access=infos.time_access;	
	time_write=infos.time_write;
	size=infos.size;
	strcpy(name,infos.name);
	
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
void c_fichier::get_name(char * o_name)
{
     strcpy(o_name,name);
}
unsigned c_fichier::get_attrib()
{
     return attrib;
}


// class constructor
c_arbo::c_arbo(char * nom)
{
	strcpy(name,nom);
    c_arbo::parcourir(nom);                
}                

int c_arbo::parcourir(char * nom)
{
struct _finddata_t lstr_find;
char ls_chemin[1024];
char ls_chemin_prochain[1024];
char ls_nom[1024];
long ll_handle;
class c_fichier *fic;                

	sprintf(ls_chemin,"%s\\*.*",nom);
    fic = new c_fichier();	
    ll_handle =  _findfirst (ls_chemin, &lstr_find);
    do 
    {     
          fic->init(lstr_find);
          //si pas spécial
          if( fic->is_special() == 0)
          {
              if( fic->is_dir() == 0)
              {
                   fic->get_name(ls_nom);
                   sprintf(ls_chemin_prochain,"%s%s\\",ls_chemin,ls_nom);
                   parcourir(ls_chemin_prochain);
              }
              else
              {
              //stocker
                  
              }
          }
    }          
    while(_findnext(ll_handle, &lstr_find)==0);
    delete fic;
    _findclose (ll_handle);
    return 0;          
}

// class destructor
c_arbo::~c_arbo()
{
	// insert your code here
}
