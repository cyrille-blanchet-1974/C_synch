#ifndef c_fichier_H
#define c_fichier_H

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>


class c_fichier
{
    private:
    	unsigned	attrib;		
    	time_t		time_create;
    	time_t		time_access;
    	time_t		time_write;
    	_fsize_t	size;
    	char		*name;	
    	char        *chemin;
    	char        *cle;

	public:  
    	// class constructor
		c_fichier(struct _finddata_t infos,char *achemin);
    	// class constructor
		c_fichier(c_fichier *fichier);//2nd constructor
		// class destructor
		~c_fichier();
		//indique si c'est un répertoire
		int is_dir();
		//indique si c'est un c_fichier spécial (. .. recycler ...
		int is_special();
        //propriétés
        time_t get_time_create();
        time_t get_time_access();
        time_t get_time_write();
        _fsize_t get_size();
        char* get_name();
        char* get_chemin();
        char* get_cle();
        unsigned get_attrib();
        bool operator==(c_fichier b);
};

#endif // c_fichier_H
