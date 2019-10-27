#include <string.h>
#include <stdio.h>
#include "strings.h"


/***********************************************
* longueur d'une cha�ne
************************************************/
long c_strings::strlen(char *ap_chaine)
{
  long taille;              

  //d�terminer la taille de la chaine 
    taille = 0;
    while(*ap_chaine)
    {
       ap_chaine++;
       taille++;
    }
    //on remet notre pointeur � z�ro
    ap_chaine -= taille; 
	return taille;
}

/***********************************************
* longueur d'une cha�ne
************************************************/
void c_strings::realloc(long taille)
{
	//lib�rer �ventuellement la m�moire
	if(p_buffer!=NULL)
	{
		delete [] p_buffer;
		p_buffer=NULL;
	}
	//r�alloue
    p_buffer=new char[taille+1];
    if(p_buffer==NULL) erreur(1);    
	taille_buffer=taille+1;
	taille_chaine=0;
}

/***********************************************
* copie d'une cha�ne � la suite de la chaine
************************************************/
int c_strings::copy(char *ap_chaine)
{
    while(*ap_chaine)
    {
		p_buffer[taille_chaine]=ap_chaine[0];
		taille_chaine++;
		if(taille_chaine > taille_buffer) 
		{
			//pour ne pas aller trop loin
			erreur(2);
			return -1;
		}
	}
	//Z�ro final
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
			printf("Erreur lors de la copie: m�moire allou�e insuffisante pour la cha�ne\n");
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
	//Allouer la m�moire
	realloc(strlen(ap_chaine));
	copy(ap_chaine);
}

/***********************************************
* destructeur
************************************************/
c_strings::~c_strings()
{
	//lib�rer la m�moire
	if(p_buffer!=NULL)
	{
		delete [] p_buffer;
		p_buffer=NULL;
	}
}



/***********************************************
* affectation
************************************************/
//class c_strings& c_strings::operator=(class c_strings  &chaine)
//{
 //   c_strings tmp(chaine.get_pointer());  
 //   return tmp;
//}

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
	//Allouer la m�moire
	realloc(strlen(p_chaine));
	copy(p_chaine);
}

//class c_strings operator=(class c_strings  chaine);
class c_strings c_strings::operator+(class c_strings chaine)
{
     c_strings p_tmp;

 	 p_tmp.realloc(p_tmp.len()+chaine.len());
	 copy(p_tmp.get_pointer());
	 copy(chaine.get_pointer());
	 return p_tmp;
}
//op�rateur d'acc�s
char c_strings::operator [](int pointeur)
{
    //on retourne le caract�re point� par "pointeur" dans "buffer"
    return p_buffer[pointeur];

}

c_strings::operator char*()
{
     return p_buffer;
}
c_strings::operator char*() const
{
     return p_buffer;
}



/***********************************************
* ajoute une chaine
************************************************/
void c_strings::operator +=(class c_strings chaine)
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

/*class c_strings c_strings::operator +(class c_strings a , class c_strings b);
{
     c_strings p_tmp;

 	 realloc(p_tmp.len()+p_tmp2.len());
	 copy(p_tmp.get_pointer());
	 copy(p_tmp2.get_pointer());
}*/

/***********************************************
* r�cup�re un pointeur sur la chaine
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
* copy une chaine dans une autre
* alloue la m�moire
************************************************/
char* c_strings::copy_alloc(char *ap_chaine)
{
 long taille,i;              
  char* p_tmp=NULL;

    //d�terminer la taille de la chaine a copier
    taille = 0;
    while(*ap_chaine)
    {
       ap_chaine++;
       taille++;
    }
    //on remet notre pointeur � z�ro
    ap_chaine -= taille; 
    //allouer la m�moire
    p_tmp=new char[taille+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la cha�ne src vers p_tmp
    for (i=0; i < taille ; i++)
        p_tmp[i] = ap_chaine[i];
    //on place le caract�re de fin (null)
    p_tmp[taille] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

/***********************************************
* concataine deux cha�nes
************************************************/
char* c_strings::concat_alloc(char *ap_chaine1,char *ap_chaine2)
{
  long taille1,taille2,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    //taille2=strlen(ap_chaine2);
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

/***********************************************
* concataine trois cha�nes
************************************************/
char* c_strings::concat_alloc(char *ap_chaine1,char *ap_chaine2,char * ap_chaine3)
{
  long taille1,taille2,taille3,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    taille3 = 0;
    while(*ap_chaine3)
    {
       ap_chaine3++;
       taille3++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine3 -= taille3;         
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+taille3+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la seconde cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on copie la troisi�me cha�ne src vers p_tmp
    for (i=0; i < taille3 ; i++,j++)
        p_tmp[j] = ap_chaine3[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2+taille3] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

char* c_strings::concat_alloc(char *ap_chaine1,char *ap_chaine2,char * ap_chaine3,char * ap_chaine4)
{
  long taille1,taille2,taille3,taille4,i,j;
  char* p_tmp=NULL;
    //d�terminer la taille des chaines a copier 
    taille1 = 0;
    while(*ap_chaine1)
    {
       ap_chaine1++;
       taille1++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine1 -= taille1; 
    taille2 = 0;
    while(*ap_chaine2)
    {
       ap_chaine2++;
       taille2++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine2 -= taille2;     
    taille3 = 0;
    while(*ap_chaine3)
    {
       ap_chaine3++;
       taille3++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine3 -= taille3;         
    taille4 = 0;
    while(*ap_chaine4)
    {
       ap_chaine4++;
       taille4++;
    }    
    //on remet notre pointeur � z�ro
    ap_chaine4 -= taille4;         
    //alloue la m�moire
    p_tmp=new char[taille1+taille2+taille3+taille4+1];
    if(p_tmp==NULL) printf("erreur allocation\n");
    //on copie la premiere cha�ne src vers p_tmp
    for (i=0,j=0; i < taille1 ; i++,j++)
        p_tmp[j] = ap_chaine1[i];
    //on copie la seconde cha�ne src vers p_tmp
    for (i=0; i < taille2 ; i++,j++)
        p_tmp[j] = ap_chaine2[i];
    //on copie la troisi�me cha�ne src vers p_tmp
    for (i=0; i < taille3 ; i++,j++)
        p_tmp[j] = ap_chaine3[i];
    //on copie la quitri�me cha�ne src vers p_tmp
    for (i=0; i < taille4 ; i++,j++)
        p_tmp[j] = ap_chaine4[i];
    //on place le caract�re de fin (null)
    p_tmp[taille1+taille2+taille3+taille4] = '\0';
    //on retourne le pointeur vers la copie
    return p_tmp;
}

