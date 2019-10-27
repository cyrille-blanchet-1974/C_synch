#include <string.h>
#include <stdio.h>
#include "strings.h"


/***********************************************
* longueur d'une chaîne
************************************************/
long c_strings::strlen(char *ap_chaine)
{
  long taille;              
  char * tmp;
  
    tmp=ap_chaine;

  //déterminer la taille de la chaine 
    taille = 0;
    while(*tmp)
    {
       tmp++;
       taille++;
    }
//printf("strlen(%s)->%li\n",ap_chaine,taille);
	return taille;
}

/***********************************************
* réallouer la mémoire
************************************************/
void c_strings::realloc(long taille)
{
	//libèrer éventuellement la mémoire
	if(p_buffer!=NULL)
	{
		//printf("realloc libère %li %s\n",p_buffer,p_buffer);
		delete [] p_buffer;
		p_buffer=NULL;
	}
	//réalloue
    p_buffer=new char[taille+1];
	//printf("realloc alloue %li\n",p_buffer);
    if(p_buffer==NULL) erreur(1);    
	taille_buffer=taille+1;
	taille_chaine=0;
//printf("realloc(%li)\n",taille);	
}

/***********************************************
* copie d'une chaîne à la suite de la chaine
************************************************/
int c_strings::copy(char *ap_chaine)
{
//printf("copy(%s) taille_chaine=%li taille_buffer=%li\n",ap_chaine,taille_chaine,taille_buffer);	
char * tmp;
    tmp=ap_chaine;
    while(*tmp)
    {
		p_buffer[taille_chaine]=tmp[0];
		tmp++;
		taille_chaine++;
		//printf(".");
		if(taille_chaine > taille_buffer) 
		{
			//pour ne pas aller trop loin
			erreur(2);
			return -1;
		}
	}
	//Zéro final
	p_buffer[taille_chaine]=0;
	//printf("copy %li %s\n",p_buffer,p_buffer);
	return 0;
}


/***********************************************
* Gestion des erreurs
************************************************/
void c_strings::erreur(long CodeErreur)
{
	switch(CodeErreur)
	{
		case 1:
			printf("Erreur allocation\n");
			break;
		case 2:
			printf("Erreur lors de la copie: mémoire allouée insuffisante pour la chaîne\n");
			break;
		//
	}
}

/***********************************************
* constructeur
************************************************/
c_strings::c_strings()
{
//printf("constructeur()\n");	
	taille_chaine=0;
	taille_buffer=0;
	p_buffer=NULL;
}

/***********************************************
* constructeur
************************************************/
c_strings::c_strings(char *ap_chaine)
{
//printf("constructeur(%s)\n",ap_chaine,taille_chaine,taille_buffer);	
	taille_chaine=0;
    taille_buffer=0;
	p_buffer=NULL;
	//Allouer la mémoire
	realloc(strlen(ap_chaine));
	copy(ap_chaine);
}

/***********************************************
* destructeur
************************************************/
c_strings::~c_strings()
{
//printf("destructeur()\n");	
	//libèrer la mémoire
	if(p_buffer!=NULL)
	{
		//printf("destructeur libère %li %s\n",p_buffer,p_buffer);
		delete [] p_buffer;
		p_buffer=NULL;
	}
}

/***********************************************
* affectation
************************************************/
void c_strings::operator=(class c_strings  &chaine)
{
//printf("operateur= %s \n",chaine.p_buffer);	     
    realloc(chaine.len());
    copy(chaine.p_buffer);  
}

/***********************************************
* affectation
************************************************/
void c_strings::operator=(char * p_chaine)
{
//printf("operateur = %s \n",p_chaine);	
	//Allouer la mémoire
	realloc(strlen(p_chaine));
	copy(p_chaine);
}

/***********************************************
* concaténation
************************************************/
class c_strings c_strings::operator+( class c_strings &  chaine)
{
//printf("operateur + (local:%s;chaine:%s) \n",p_buffer,chaine.get_pointer());	

     c_strings p_tmp;

     //printf("operateur + realloc(%li) \n",taille_chaine+chaine.len());	
 	 p_tmp.realloc(taille_chaine+chaine.len());
 	 //printf("operateur + copy(%s) \n",p_buffer);	
	 p_tmp.copy(p_buffer);
	 //printf("operateur + copy(%s) \n",chaine.get_pointer());	
	 p_tmp.copy(chaine.get_pointer());
	 //printf("operateur + résultat: (%s) \n",p_tmp.get_pointer());	
	 return p_tmp;
}

/***********************************************
* concaténation
************************************************/
class c_strings c_strings::operator+( char * chaine)
{
//printf("operateur + (local:%s;chaine:%s) \n",p_buffer,chaine.get_pointer());	

     c_strings p_tmp;

     //printf("operateur + realloc(%li) \n",taille_chaine+chaine.len());	
 	 p_tmp.realloc(taille_chaine+strlen(chaine));
 	 //printf("operateur + copy(%s) \n",p_buffer);	
	 p_tmp.copy(p_buffer);
	 //printf("operateur + copy(%s) \n",chaine.get_pointer());	
	 p_tmp.copy(chaine);
	 //printf("operateur + résultat: (%s) \n",p_tmp.get_pointer());	
	 return p_tmp;
}

/***********************************************
* opérateur d'accès
************************************************/
char c_strings::operator [](int pointeur)
{
    //on retourne le caractère pointé par "pointeur" dans "buffer"
    return p_buffer[pointeur];

}

/***********************************************
* cast
************************************************/
c_strings::operator char*()
{
     return p_buffer;
}

/***********************************************
* cast
************************************************/
c_strings::operator char*() const
{
     return p_buffer;
}



/***********************************************
* ajoute une chaine
************************************************/
void c_strings::operator +=(class c_strings & chaine) //sans le & en quittant la fonction il appel le destructeur de chaine
{
     c_strings p_tmp(p_buffer);

 	 realloc(p_tmp.len()+chaine.len());
	 copy(p_tmp.get_pointer());
	 copy(chaine.get_pointer());
}

/***********************************************
* ajoute une chaine
************************************************/
void c_strings::operator +=(char * chaine)
{
     c_strings p_tmp(p_buffer);
     c_strings p_tmp2(chaine);

 	 realloc(p_tmp.len()+p_tmp2.len());
	 copy(p_tmp.get_pointer());
	 copy(p_tmp2.get_pointer());
}

/*class c_strings operator +(class c_strings a , class c_strings b);
{
     c_strings p_tmp;

 	 p_tmp.realloc(a.taille_chaine+b.taille_chaine);
	 p_tmp.copy(a.get_pointer());
	 p_tmp.copy(b.get_pointer());
}*/

/***********************************************
* récupère un pointeur sur la chaine
************************************************/
char * c_strings::get_pointer()
{
 return p_buffer;     
}
     
/***********************************************
* longueure de la chaine
************************************************/
long c_strings::len()
{
     return taille_chaine;
}

/***********************************************
* passage en minuscules
************************************************/
void	c_strings::lower()
{
char * tmp;
    tmp=p_buffer;
    while(*tmp)
    {
        if(tmp[0] > 'A' && tmp[0] < 'Z')
          tmp[0] += 'a'-'A';         
          
		tmp++;
	}
}

/***********************************************
* passage en majuscules
************************************************/
void	c_strings::upper()
{
char * tmp;
    tmp=p_buffer;
    while(*tmp)
    {
        if(tmp[0] > 'a' && tmp[0] < 'z')
          tmp[0] -= 'A'-'a';         
		tmp++;
	}
}

/***********************************************
* comparaison de chaîne
************************************************/
int	c_strings::comp(char *ap_chaine)
{
    bool fin=false;
    long pointeur=0;
    long cmp=0;
    char cbuffer,cchaine;
    while(fin == false)
    {
         cbuffer=p_buffer[pointeur];
         cchaine= ap_chaine[pointeur];
         if(cbuffer==cchaine)
         {
             if(cbuffer==0) return 1;//fin de chaîne -> chaînes identiques
             pointeur++; //caractère suivant
         }
         else
         {
             return 0; //caractère différent -> 
             /*
             if( cbuffer == 0 ) return -1;
             if( cchaine == 0 ) return 1;
             if( cbuffer > cchaine ) return 1;
             if( cbuffer < cchaine ) return -1;
             */
         }    
    }
}    
