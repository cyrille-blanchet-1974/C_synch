#ifndef c_fichier_H
#define c_fichier_H
#include <io.h>
#include <time.h>
#include "global.h"

class c_fichier
{
    private:
    	unsigned	attrib;		
    	time_t		time_create;
    	time_t		time_access;
    	time_t		time_write;
    	_fsize_t	size;
    	char		*name;	


	public:  
    	// class constructor
		c_fichier(c_fichier *fichier);
    	// class constructor
		c_fichier();
		// class destructor
		~c_fichier();
    	// changeùent du contenu 
		int init(struct _finddata_t infos);
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
        unsigned get_attrib();
        bool operator==(c_fichier b);
        void afficher();
};

#endif // c_fichier_H
