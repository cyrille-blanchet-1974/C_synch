/*******************************************************************************
*
*                   Classe de fichier contient les informations sur un fichier
*
*******************************************************************************/
#ifndef c_fichier_H
#define c_fichier_H
#include <io.h>
#include <time.h>
#include "global.h"
#include "strings.h"

class c_fichier
{
    private:
        //attributs (lecture seule, archive,caché...
    	unsigned	attrib;		
    	//heure de création
    	time_t		time_create;
    	//heure d'access 
    	time_t		time_access;
    	//heure de mise à jour
    	time_t		time_write;
    	//taille 
    	_fsize_t	size;
    	//nom    
    	//char		*p_name;	
    	c_strings p_name;


	public:  
    	// class constructor
		c_fichier(c_fichier *ap_fichier);
    	// class constructor
		c_fichier();
		// class destructor
		~c_fichier();
    	// changeùent du contenu 
		void init(struct _finddata_t infos);
		//indique si c'est un répertoire
		int is_dir();
		//indique si c'est un c_fichier spécial (. .. recycler ...
		int is_special();
        //heure de création
        time_t get_time_create();
        //heure d'acces
        time_t get_time_access();
        //heure de mise à jour
        time_t get_time_write();
        //taille du fichier
        _fsize_t get_size();
        //nom
        char* get_name();
        //attributs
        unsigned get_attrib();
        //comparaison de deux fichiers
        bool operator==(c_fichier b);
        //afficher le fichier
        void afficher();
};

#endif // c_fichier_H
