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
		delete [] p_buffer;
		p_buffer=NULL;
	}
	//réalloue
    p_buffer=new char[taille+1];
    if(p_buffer==NULL) erreur(1);    
	taille_buffer=taille+1;
	taille_chaine=0;
}

/***********************************************
* copie d'une chaîne à la suite de la chaine
************************************************/
int c_strings::copy(char *ap_chaine)
{
char * tmp;
    tmp=ap_chaine;
    while(*tmp)
    {
		p_buffer[taille_chaine]=tmp[0];
		tmp++;
		taille_chaine++;
		if(taille_chaine > taille_buffer) 
		{
			//pour ne pas aller trop loin
			erreur(2);
			return -1;
		}
	}
	//Zéro final
	p_buffer[taille_chaine]=0;
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
	taille_chaine=0;
	taille_buffer=0;
	p_buffer=NULL;
}

/***********************************************
* constructeur
************************************************/
c_strings::c_strings(char *ap_chaine)
{
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
	//libèrer la mémoire
	if(p_buffer!=NULL)
	{
		delete [] p_buffer;
		p_buffer=NULL;
	}
}

/***********************************************
* affectation
************************************************/
void c_strings::operator=(class c_strings  &chaine)
{
    realloc(chaine.len());
    copy(chaine.p_buffer);  
}

/***********************************************
* affectation
************************************************/
void c_strings::operator=(char * p_chaine)
{
	//Allouer la mémoire
	realloc(strlen(p_chaine));
	copy(p_chaine);
}

/***********************************************
* concaténation
************************************************/
class c_strings c_strings::operator+( class c_strings &  chaine)
{

     c_strings p_tmp;

 	 p_tmp.realloc(taille_chaine+chaine.len());
	 p_tmp.copy(p_buffer);
	 p_tmp.copy(chaine.get_pointer());
	 return p_tmp;
}

/***********************************************
* concaténation
************************************************/
class c_strings c_strings::operator+( char * chaine)
{

     c_strings p_tmp;

 	 p_tmp.realloc(taille_chaine+strlen(chaine));
	 p_tmp.copy(p_buffer);
	 p_tmp.copy(chaine);
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
     c_strings p_tmp(p_buffer);//sauve chaine locale

 	 realloc(p_tmp.len()+chaine.len()); //réalloue la mémoire de local + param (efface la chaine locale)
	 copy(p_tmp.get_pointer()); //remet la sauvegarde
	 copy(chaine.get_pointer()); // plus la chaine param
}

/***********************************************
* comparaison de chaines
************************************************/
bool c_strings::operator ==(const class c_strings & chaine)
{
     return (strcmp(p_buffer,(char *)chaine)==0);
}

/***********************************************
* comparaison de chaines
************************************************/
bool c_strings::operator ==(char * chaine)
{
     return (strcmp(p_buffer,chaine)==0);
}

/***********************************************
* ajoute une chaine
************************************************/
void c_strings::operator +=(char * chaine)
{
     c_strings p_tmp(p_buffer); //copie de locale
     c_strings p_tmp2(chaine); // c_strings de param

 	 realloc(p_tmp.len()+p_tmp2.len()); //aloue en locale taille des deux
	 copy(p_tmp.get_pointer()); //remet la sauvegarde
	 copy(p_tmp2.get_pointer()); // et param
}

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
/*int	c_strings::comp(char *ap_chaine)
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
         }    
    }
}    
*/
/***********************************************
* comparaison de chaîne
************************************************/
//trop long//
/*
int	c_strings::lcomp(class c_strings & chaine1,class c_strings & chaine2)
{
    bool fin=false;
    long pointeur=0;
    long cmp=0;
    char cbuffer1,cbuffer2;
    //return strcmp((char *)chaine1,(char*)chaine2);
     
    //printf("comparaison '%s' '%s' \n",(char *) chaine1,(char *) chaine2);
    while(fin == false)
    {
         //cbuffer1=chaine1[pointeur];
         //cbuffer2=chaine2[pointeur];
         //if(cbuffer1==cbuffer2)
         if(chaine1[pointeur]==chaine2[pointeur])
         {
             //if(cbuffer1==0) 
             if(chaine1[pointeur]==0)
             {
                  //printf("'%s'=='%s' \n",(char *) chaine1,(char *) chaine2);
                  return 0;//fin de chaîne -> chaînes identiques
             }
             pointeur++; //caractère suivant
         }
         else
         {
             //printf("'%s'<>'%s' \n",(char *) chaine1,(char *) chaine2);
             return -1; //caractère différent -> 
         }    
    }
}    
*/
/***********************************************
* comparaison avec une chaîne
************************************************/
//trop long//
/*
int	c_strings::comp(char *ap_chaine)
{
    class c_strings chaine1;
    class c_strings chaine2;
    
    chaine1 = p_buffer;
    chaine2 = ap_chaine;
    if(chaine1.len()!=chaine2.len())return -1;//si taille différente, inutile de continuer..    
    return lcomp(chaine1,chaine2);
}    
*/
/***********************************************
* comparaison avec une c_string
************************************************/
//trop long//
/*
int	c_strings::comp(class c_strings & chaine)
{
    class c_strings chaine1;
    class c_strings chaine2;
    
    chaine1 = p_buffer;
    chaine2 = chaine;
    if(chaine1.len()!=chaine2.len())return -1;//si taille différente, inutile de continuer..    
    return lcomp(chaine1,chaine2);
}    
*/
/***********************************************
* comparaison avec une chaîne sans se préoccuper de la casse
************************************************/
//trop long//
/*
int	c_strings::compnocase(char *ap_chaine)
{
    class c_strings chaine1;
    class c_strings chaine2;
    
    chaine1 = p_buffer;
    chaine2 = ap_chaine;
    if(chaine1.len()!=chaine2.len())return -1;//si taille différente, inutile de continuer..    
    chaine1.lower();
    chaine2.lower();
    return lcomp(chaine1,chaine2);
}    
*/

/***********************************************
* comparaison avec une c_string sans se préoccuper de la casse
************************************************/
//trop long
/*
int	c_strings::compnocase(class c_strings & chaine)
{
    class c_strings chaine1;
    class c_strings chaine2;
    
    chaine1 = p_buffer;
    chaine2 = chaine;
    if(chaine1.len()!=chaine2.len())return -1;//si taille différente, inutile de continuer..    
    chaine1.lower();
    chaine2.lower();
    return lcomp(chaine1,chaine2);
}    
*/
