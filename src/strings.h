/*******************************************************************************
*
*                   Classe de gestion des cha�nes
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

	public:  
    	// class constructor
		c_strings(char *ap_chaine);
    	// class constructor
		c_strings();
		// class destructor
		~c_strings();
        //affectation
        //friend 
        //class c_strings& operator=(class c_strings & chaine);
        void operator=(char * p_chaine);
        void operator=(class c_strings  &  chaine);
        class c_strings operator+( class c_strings  & chaine);
        //friend class c_strings operator+(class c_strings a , class c_strings b);
        void operator +=(class c_strings chaine);
        void operator +=(char * chaine);
        char operator [](int pointeur);         
        operator char*(); 
        operator char*() const; 

        long len();
        char * get_pointer();

//void operator =(const char * a); //op�rateur d'assignement d'un pointeur de type "char"
//void operator =(const char &a); //op�rateur d'assignement d'un caract�re de type "char"
//void operator =(const sString &a); //op�rateur d'assignement d'une autre variable de type "sString"
		//strcmp
		//strnocascmp
        //copie une chaine 
        static char * copy_alloc(char *ap_chaine);
        //concataine 2 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2);
        //concataine 3 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2,char *ap_chaine3);
        //concataine 4 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2,char *ap_chaine3,char *ap_chaine4);
};

#endif // STRINGS_H




