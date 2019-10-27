/*******************************************************************************
*
*                   Classe de gestion des cha�nes
*
*******************************************************************************/
#ifndef STRINGS_H
#define STRINGS_H
#include "global.h"

class c_strings
{
/*************************************************
*   Attrubuts
*************************************************/
	private:
		//donn�es de la cha�ne
		char* p_buffer;
		//taille de la cha�ne
		long taille_chaine;
		//taille de la cha�ne
		long taille_buffer;


/*************************************************
*   m�thodes
*************************************************/
	private:
		//taille d'une chaine
		long strlen(char *ap_chaine);
		//allouer ou r�allouer la m�moire
		void realloc(long taille);
		//d�clencher une erreur
		void erreur(long CodeErreur);
		//copie d'une chaine
		int	copy(char *ap_chaine);
		//comparaison de deux classe c_string
        //trop long//int	c_strings::lcomp(class c_strings & chaine1,class c_strings & chaine2);
        
	public:  
    	// class constructor
		c_strings(char *ap_chaine);
    	// class constructor
		c_strings();
		// class destructor
		~c_strings();
        //affectation
        void            operator=(char * p_chaine);
        void            operator=(class c_strings  &  chaine);
        //concat�nation
        class c_strings operator+( class c_strings  & chaine);
        class c_strings operator+( char * chaine);
        //concat�nation/affectation
        void            operator +=(class c_strings & chaine);
        void            operator +=(char * chaine);
        //comparaison
        bool            operator ==(const class c_strings & chaine);
        bool            operator ==(char* chaine);
        
        //acc�s caract�re par caract�re
        char            operator [](int pointeur);         
        //cast
                        operator char*(); 
                        operator char*() const; 
        //longueure de la cha�ne                
        long len();
        //pointeur sur la cha�ne
        char * get_pointer();
		//passage en minuscules
		void	lower();
		//passage en majuscules
		void	upper();
		//comparaison avec une cha�ne
		//trop long//int	comp(char *ap_chaine);
		//comparaison avec une c_string
		//trop long//int	comp(class c_strings & chaine);
		//comparaison avec une cha�ne sans se pr�occuper de la casse
		//trop long//int	compnocase(char *ap_chaine);
		//comparaison avec une c_string sans se pr�occuper de la casse
		//trop long//int	compnocase(class c_strings & chaine);
};

#endif // STRINGS_H




