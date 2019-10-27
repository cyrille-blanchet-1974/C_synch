/*synch
synchronise deux dossier
analyse la source pour chaque fichier le cherche en cible
S'il n'existe pas il faut le copier
s'il existe on compare date, attributs et taille pour savoir si on doit écraser
ensuite on parcours le cible en cherchant chaques fichiers en source s'il n'y est pas on doit l'effacer de la cible
Version 1.0 10/2005 en procédurale
Version 1.1 11/2006 test de parcours de dossier seulement pour voir où améliorer
Version 2.0 11/2006 tentative de refont en objet (but: lire les 2 arborescences puis comparer en mémoire pour diminuer lesI/O disques
*/
#include <stdio.h> //sprintf
//#include <stdlib.h>
#include <io.h> //file
#include <string.h> //strcpy
//#include <time.h>
//typedef char* va_list;
//#include <stdarg.h>
//#include <windef.h>
//#include <wingdi.h>
//#include <winuser.h>


/*
class c_fichier{
    private:
    	unsigned	attrib;		
    	time_t		time_create;
    	time_t		time_access;
    	time_t		time_write;
    	_fsize_t	size;
    	char		name[FILENAME_MAX];	

	public:  
    	// class constructor
		c_fichier();
		// class destructor
		~c_fichier();
		//initialisation
		void init(struct _finddata_t infos);
		//indique si c'est un répertoire
		int is_dir();
		//indique si c'est un fichier spécial (. .. recycler ...
		int is_special();
        //propriétés
        time_t get_time_create();
        time_t get_time_access();
        time_t get_time_write();
        _fsize_t get_size();
        void get_name(char * o_name);
        unsigned get_attrib();
};



struct arborescence
{
    char             name[FILENAME_MAX];
   	class c_fichier          * files;		
    arborescence     * repertoires;
};

class c_arbo
{
    private:
        //tableau de fichier
        struct  arborescence racine;
        char    name[FILENAME_MAX];
    
	public:
		// class constructor
		c_arbo( char *nom);
		// class destructor
		~c_arbo();
		int parcourir(char *chemin);
};



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

*/




/*
void print_oem(char * as_chaine)
{
char ls_oem[1024];     
   CharToOem(as_chaine,ls_oem);
   printf("%s",ls_oem);
   fflush(stdin);
}

int fic_en_moins(char* as_chemin_src,char* as_chemin_dst, char * as_chemin_relatif)
//parcours SRC et cherche les fichier différents dans dst ou absent
{
struct _finddata_t lstr_find_src,lstr_find_dst; 
long ll_handle_src,ll_handle_dst;
char ls_chemin_src[1024];
char ls_chemin_dst[1024];
char ls_fichier_dst[1024];
char ls_chemin_prochain[1024];
char ls_commande[1024];
int  li_copy;
     //créé les path de recherche
     //Source
    sprintf(ls_chemin_src,"%s%s*.*",as_chemin_src,as_chemin_relatif);
    //recherche dans source
    ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
    do 
    {     
          //ignorer les fichiers .  ..       et le volume du disque
         if( (strcmp(lstr_find_src.name,".")!=0) && 
             (strcmp(lstr_find_src.name,"..")!=0) && 
            !(lstr_find_src.attrib & _A_VOLID)  && 
             (strcmp(lstr_find_src.name,"System Volume Information")!=0) && 
             (strcmp(lstr_find_src.name,"RECYCLER")!=0) )
         {
             if (lstr_find_src.attrib & _A_SUBDIR)
             {
                  //c'est un répertoire 
                  //on le cherche en destination
                  sprintf(ls_chemin_dst,"%s%s%s\\*.*",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                  ll_handle_dst =  _findfirst (ls_chemin_dst, &lstr_find_dst);
                  if (ll_handle_dst ==-1)
                  {
                    //s'il n'existe pas on le copie
                     sprintf(ls_commande,"echo répertoire %s%s%s non trouvé !!!\n",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                     print_oem(ls_commande);
                     sprintf(ls_commande,"xcopy \"%s%s%s\\*.*\" \"%s%s%s\\\" /E /I /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                     print_oem(ls_commande);                   
                  }
                  else
                  {
                   //on 'récurse' dedans
                   _findclose (ll_handle_dst);
                   sprintf(ls_chemin_prochain,"%s%s\\",as_chemin_relatif,lstr_find_src.name);
                   fic_en_moins(as_chemin_src,as_chemin_dst,ls_chemin_prochain);
                   }
             }
             else
             {
                 //c'est un fichier?
                 sprintf(ls_fichier_dst,"%s%s%s",as_chemin_dst,as_chemin_relatif,lstr_find_src.name);
                         
                 //cherche ce fichier...
                 ll_handle_dst =  _findfirst (ls_fichier_dst, &lstr_find_dst);
                 if (ll_handle_dst == -1)
                 {
                     sprintf(ls_commande,"echo Fichier %s non trouvé!!!\n",ls_fichier_dst);
                     print_oem(ls_commande);
                     sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /E /I /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif);
                     print_oem(ls_commande);
                 }
                 else
                 {
                     _findclose (ll_handle_dst);
                     li_copy = 0;
                     //comparer lstr_find_src et lstr_find_dst
                     if (lstr_find_src.size        != lstr_find_dst.size)        
                     {
                         sprintf(ls_commande,"echo Fichier %s taille différente!!!\n",ls_fichier_dst);
                         print_oem(ls_commande);             
                         li_copy=1;
                     }
                     //if (lstr_find_src.time_create != lstr_find_dst.time_create) printf("Fichier %s heure de création différente!!!\n",ls_fichier_dst);
                     //if (lstr_find_src.time_access != lstr_find_dst.time_access) printf("Fichier %s heure de dernier accés différente!!!\n",ls_fichier_dst);
                     if (lstr_find_src.time_write  != lstr_find_dst.time_write)  
                     {
                         sprintf(ls_commande,"echo Fichier %s heure de modification différente!!!\n",ls_fichier_dst);
                         print_oem(ls_commande);
                         li_copy=1;
                     }
                     if (li_copy==1) 
                     {
                       sprintf(ls_commande,"xcopy \"%s%s%s\" \"%s%s\"  /E /I /H /Y /K \n",as_chemin_src,as_chemin_relatif,lstr_find_src.name,as_chemin_dst,as_chemin_relatif);
                       print_oem(ls_commande);         
                     }
                 }
             }
         }
    }          
    while(_findnext(ll_handle_src, &lstr_find_src)==0);
    _findclose (ll_handle_src);
    return 0;
}

int fic_en_trop(char* as_chemin_src,char* as_chemin_dst, char * as_chemin_relatif)
{
    //parcours destination à la recherche de fichier/répertoire qui ne seraient pas dans la source -> a effacer...
struct _finddata_t lstr_find_src,lstr_find_dst; 
long ll_handle_src,ll_handle_dst;
char ls_chemin_src[1024];
char ls_chemin_dst[1024];
char ls_fichier_dst[1024];
char ls_chemin_prochain[1024];
char ls_commande[1024];
     //créé les path de recherche
    //cible
    sprintf(ls_chemin_dst,"%s%s*.*",as_chemin_dst,as_chemin_relatif);
    //printf("REM Parcours de %s \n",ls_chemin_dst);
    //recherche dans source
    ll_handle_dst =  _findfirst (ls_chemin_dst, &lstr_find_dst);
    do 
    {     
          //ignorer les fichiers .  ..       et le volume du disque
         if( (strcmp(lstr_find_dst.name,".")!=0) && 
             (strcmp(lstr_find_dst.name,"..")!=0) && 
            !(lstr_find_dst.attrib & _A_VOLID) && 
             (strcmp(lstr_find_dst.name,"System Volume Information")!=0) && 
             (strcmp(lstr_find_dst.name,"RECYCLER")!=0))
         {
             if (lstr_find_dst.attrib & _A_SUBDIR)
             {
                  //c'est un répertoire 
                  //on le cherche en source
                  sprintf(ls_chemin_src,"%s%s%s\\*.*",as_chemin_src,as_chemin_relatif,lstr_find_dst.name);
                  ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
                  if (ll_handle_src == -1)
                  {
                       //n'exite plus en source -> a effacer
                       sprintf(ls_commande,"echo Le répertoire %s n'existe plus dans %s%s. Il doit être effacer de %s%s \n",lstr_find_dst.name,as_chemin_src,as_chemin_relatif,as_chemin_dst,as_chemin_relatif);
                       print_oem(ls_commande);
                       sprintf(ls_commande,"RD /S /Q \"%s%s%s\" \n",as_chemin_dst,as_chemin_relatif,lstr_find_dst.name);
                       print_oem(ls_commande);
                  }
                  else
                  {
                      _findclose (ll_handle_src);
                      //puis on 'récurse' dedans
                      sprintf(ls_chemin_prochain,"%s%s\\",as_chemin_relatif,lstr_find_dst.name);
                      fic_en_trop(as_chemin_src,as_chemin_dst,ls_chemin_prochain);
                      }
             }
             else
             {
                 //c'est un fichier?
                 sprintf(ls_chemin_src,"%s%s%s",as_chemin_src,as_chemin_relatif,lstr_find_dst.name);
                 //cherche ce fichier...
                 ll_handle_src =  _findfirst (ls_chemin_src, &lstr_find_src);
                 if (ll_handle_src == -1)
                 {
                     sprintf(ls_commande,"echo Fichier %s non trouvé!!! On doit l'effacer de %s%s \n",ls_chemin_src,as_chemin_dst,as_chemin_relatif);
                     print_oem(ls_commande);
                     sprintf(ls_commande,"DEL \"%s%s%s\" /A \n",as_chemin_dst,as_chemin_relatif,lstr_find_dst.name);
                     print_oem(ls_commande);
                 }
                 else
                 {
                     //comparer lstr_find_src et lstr_find_dst
                     if (lstr_find_src.size        != lstr_find_dst.size)        
                     {
                        sprintf(ls_commande,"echo Fichier %s taille différente!!!\n",ls_chemin_src);
                        print_oem(ls_commande);
                     }
                     //if (lstr_find_src.time_create != lstr_find_dst.time_create) printf("REM Fichier %s heure de création différente!!!\n",ls_fichier_dst);
                     //if (lstr_find_src.time_access != lstr_find_dst.time_access) printf("REM Fichier %s heure de dernier accés différente!!!\n",ls_fichier_dst);
                     if (lstr_find_src.time_write  != lstr_find_dst.time_write)  
                     {
                         sprintf(ls_commande,"echo Fichier %s heure de modification différente!!!\n",ls_chemin_src);
                         print_oem(ls_commande);
                     }
                     
                     _findclose (ll_handle_src);
                 }
             }
         }
    }          
    while(_findnext(ll_handle_dst, &lstr_find_dst)==0);
    _findclose (ll_handle_dst);
    return 0;
}
*/
class c_arbo
{
    private:
        char    name[FILENAME_MAX];
    
	public:
		// class constructor
		c_arbo( char *nom);
		// class destructor
		~c_arbo();
};

// class constructor
c_arbo::c_arbo(char * nom)
{
	strcpy(name,nom);
}                

// class destructor
c_arbo::~c_arbo()
{
	// insert your code here
}

int main(int argc, char *argv[])
{
    class c_arbo a("toto");
    char ls_commande[1024];
  if (argc == 3)
  {  
     sprintf(ls_commande,"@echo off\n",argv[1],argv[2]);
     //print_oem(ls_commande);
     //sprintf(ls_commande,"Echo Synchronisation de %s vers %s\n",argv[1],argv[2]); 
     //print_oem(ls_commande);
     //fic_en_trop(argv[1],argv[2],"\\");  
     //fic_en_moins(argv[1],argv[2],"\\"); 
  }
  //system("PAUSE");	
  return 0;
}
