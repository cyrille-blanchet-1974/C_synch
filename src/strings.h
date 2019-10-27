/*******************************************************************************
*
*                   Classe de gestion des chaînes
*
*******************************************************************************/
#ifndef STRINGS_H
#define STRINGS_H


class c_strings
{
/*************************************************
*   Attrubuts
*************************************************/
	private:
		//données de la chaîne
		char* p_buffer;
		//taille de la chaîne
		long taille_chaine;
		//taille de la chaîne
		long taille_buffer;


/*************************************************
*   méthodes
*************************************************/
	private:
		//taille d'une chaine
		long strlen(char *ap_chaine);
		//allouer ou réallouer la mémoire
		void realloc(long taille);
		//déclencher une erreur
		void erreur(long CodeErreur);
		//copie d'une chaine
		int	copy(char *ap_chaine);
		//comparaison de chaîne
		int	comp(char *ap_chaine);

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
        //concaténation
        class c_strings operator+( class c_strings  & chaine);
        class c_strings operator+( char * chaine);
        //concaténation/affectation
        void            operator +=(class c_strings & chaine);
        void            operator +=(char * chaine);
        //accès caractère par caractère
        char            operator [](int pointeur);         
        //cast
                        operator char*(); 
                        operator char*() const; 
        //longueure de la chaîne                
        long len();
        //pointeur sur la chaîne
        char * get_pointer();
		//passage en minuscules
		void	lower();
		//passage en majuscules
		void	upper();

		//strcmp
		//strnocascmp
};

#endif // STRINGS_H




