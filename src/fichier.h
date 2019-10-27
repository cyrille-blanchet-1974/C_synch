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



class c_fichier
{
    protected:
        //attributs (lecture seule, archive,caché...
    	unsigned	attrib;		
    	//heure de mise à jour
    	time_t		time_write;
    	//taille 
    	_fsize_t	size;
    	//nom    
    	c_strings p_name;

	public:  
    	// class constructor
		c_fichier(c_fichier *ap_fichier);
    	// class constructor
		c_fichier();
		// class destructor
		~c_fichier();
    	// changement du contenu 
		void init(struct _finddata_t infos);
		//indique si c'est un répertoire
		int is_dir();
		//indique si c'est un c_fichier spécial (. .. recycler ...
		int is_special();
        //heure de mise à jour
        time_t get_time_write();
        //taille du fichier
        _fsize_t get_size();
        //nom
        char* get_name();
		//pointeur sur le nom
        class c_strings * get_pname();
        //attributs
        unsigned get_attrib();
        //comparaison de deux fichiers
        bool operator==(c_fichier &b);
        //comparaison de deux fichiers
		bool operator!=(c_fichier &b);
        //afficher le fichier
        void afficher();
		//compare les fichiers si cryptage
		bool isDiffCrypt(c_fichier &src,c_fichier &dest);
};



class c_fichier_full : c_fichier
{
    private:
    	//heure de création
    	time_t		time_create;
    	//heure d'access 
    	time_t		time_access;

	public:  
    	// class constructor
		c_fichier_full(c_fichier_full *ap_fichier);
		// class destructor
		~c_fichier_full();
        //heure de création
        time_t get_time_create();
        //heure d'acces
        time_t get_time_access();
        //comparaison de deux fichiers
        bool operator==(c_fichier_full &b);
        //comparaison de deux fichiers
        bool operator!=(c_fichier_full &b);

//////reprises de fichier
    	// changement du contenu 
		void init(struct _finddata_t infos);
		//indique si c'est un répertoire
		int is_dir();
		//indique si c'est un c_fichier spécial (. .. recycler ...
		int is_special();
        //heure de mise à jour
        time_t get_time_write();
        //taille du fichier
        _fsize_t get_size();
        //nom
        char* get_name();
		//pointeur sur le nom
        class c_strings * get_pname();
        //attributs
        unsigned get_attrib();
        //afficher le fichier
        void afficher();
		//compare les fichiers si cryptage
		bool isDiffCrypt(c_fichier_full &src,c_fichier_full &dest);
};

#endif // c_fichier_H
