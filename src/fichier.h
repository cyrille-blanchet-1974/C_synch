#ifndef FICHIER_H
#define FICHIER_H

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>


class fichier
{
    private:
    	unsigned	attrib;		
    	time_t		time_create;
    	time_t		time_access;
    	time_t		time_write;
    	_fsize_t	size;
    	char		name[FILENAME_MAX];	

	public:  
    	// class constructor
		fichier();
		// class destructor
		~fichier();
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

#endif // FICHIER_H
