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
    taille = 1;
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
long c_strings::realloc(long taille)
{
char* sauvegarde_buffer;
long  sauvegarde_taille_chaine;
long  sauvegarde_taille_buffer;
long  return_code = 0;

//	printf("realloc TB:%li Nt:%li",this->taille_buffer,taille);
	//sauvegarde
	sauvegarde_buffer = this->p_buffer;
	sauvegarde_taille_chaine=this->taille_chaine;
	sauvegarde_taille_buffer=this->taille_buffer;
	//réalloue
    this->p_buffer=new char[taille+1];
    if(this->p_buffer==NULL) 
	{
		//erreur allocation
		this->erreur(1);
		//restauration...
		this->p_buffer=sauvegarde_buffer;
		this->taille_chaine=sauvegarde_taille_chaine;
		this->taille_buffer=sauvegarde_taille_buffer;
		//et retourne -1
		return_code = -1;
	}
	else
	{
		//alloc ok
		this->taille_chaine=0;// on vient de réallouer donc taille = 0
		this->taille_buffer=taille+1; //taille nouveau buffer
		memset(this->p_buffer,0,this->taille_buffer);//init
		//si sauvegarde de qqchose
		if(sauvegarde_buffer != NULL)
		{
			//on copie la chaine sauvée
			return_code = this->copy(sauvegarde_buffer);
			if (return_code == 0)
			{
				//ok
				//taille_chaine est mise à jour par copy
				//on libère donc la sauvegarde
				delete [] sauvegarde_buffer;
				//tout est ok
				return_code = 0;
			}
			else
			{
				//soucis??? on libère ce que l'on vient de réallouer
				delete [] this->p_buffer;
				//et on restaure
				this->p_buffer=sauvegarde_buffer;//resto...
				this->taille_chaine=sauvegarde_taille_chaine;
				this->taille_buffer=sauvegarde_taille_buffer;
				this->erreur(1);
				//indique a l'appelant le soucis
				return_code = -1;
			}
		}
	}
//	printf("rc:%li\n",return_code);
	return return_code;
}

/***********************************************
* copie d'une chaîne à la suite de la chaine
************************************************/
int c_strings::copy(char *ap_chaine)
{
char * tmp;

//    printf("copy avant:#%s# ajout:#%s#",this->p_buffer,ap_chaine);

	tmp=ap_chaine;
    while(*tmp)
    {
		this->p_buffer[this->taille_chaine]=tmp[0];
		tmp++;
		this->taille_chaine++;
		if(this->taille_chaine > this->taille_buffer) 
		{
			//pour ne pas aller trop loin
			p_buffer[taille_buffer - 1]=0;
			this->erreur(2);
			return -1;
		}
	}
	//Zéro final
	this->p_buffer[this->taille_chaine]=0;
//	printf(" apres:#%s#\n",this->p_buffer);
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
			printf("Erreur allocation : %s \n",this->p_buffer);
			break;
		case 2:
			printf("Erreur lors de la copie: mémoire allouée insuffisante pour la chaine : %s\n",this->p_buffer);
			break;
		//
	}
}

/***********************************************
* constructeur
************************************************/
c_strings::c_strings()
{
	this->taille_chaine=0;
	this->taille_buffer=0;
	this->p_buffer=NULL;
}

/***********************************************
* constructeur
************************************************/
c_strings::c_strings(char *ap_chaine)
{
	this->taille_chaine=0;
    this->taille_buffer=0;
	this->p_buffer=NULL;
	//Allouer la mémoire
	this->realloc(this->strlen(ap_chaine));
	this->copy(ap_chaine);//todo si erreur copye???
}


/***********************************************
* constructeur
************************************************/
c_strings::c_strings(long taille_prealloc)
{
	this->taille_chaine=0;
    this->taille_buffer=0;
	this->p_buffer=NULL;
	//Allouer la mémoire
	this->realloc(taille_prealloc);//todo si erreur copye???
}


/***********************************************
* destructeur
************************************************/
c_strings::~c_strings()
{
//	printf("destructor: #%s#\n",this->p_buffer);
	//libèrer la mémoire
	if(this->p_buffer!=NULL)
	{
		delete [] this->p_buffer;
		this->p_buffer=NULL;
	}
	this->taille_chaine=0;
    this->taille_buffer=0;
}

/***********************************************
* affectation
************************************************/
void c_strings::set(char *p_chaine)
{
	long len_param;
	len_param = this->strlen(p_chaine);
	if( len_param  >= this->taille_buffer)
		this->realloc(len_param );//todo test retour
	this->taille_chaine=0;
	this->copy(p_chaine);  //todo si erreur copye???
}
/***********************************************
* affectation
************************************************/
void c_strings::set(class c_strings & chaine)
{
	this->set(chaine.get());
}
/***********************************************
* concatenation
************************************************/
void c_strings::add(char *p_chaine)
{
	long len_param;
	len_param = this->strlen(p_chaine);
	if( len_param  > (this->taille_buffer - this->taille_chaine) )
	{
		this->realloc(this->taille_buffer + (len_param - this->taille_chaine));//todo test retour //todo sauver d'abord!!!
	}
	copy(p_chaine);//todo si erreur copye???

}
/***********************************************
* c_strings::
************************************************/
void c_strings::add(class c_strings & chaine)
{
	this->add(chaine.get());
}
/***********************************************
* RAZ
************************************************/
void c_strings::reset()
{
	this->taille_chaine=0;
	this->set("");
}
/***********************************************
* etteur
************************************************/
char * c_strings::get()
{
	return this->p_buffer;
}

/***********************************************
* affectation
************************************************/
/*unsedvoid c_strings::operator=(class c_strings  &chaine)
{
    realloc(chaine.len());//todo si erreur alloc???
    copy(chaine.get_pointer());  //todo si erreur copy???
}
*/
/***********************************************
* affectation
************************************************/
/*void c_strings::operator=(char * p_chaine)
{
	//Allouer la mémoire
	realloc(strlen(p_chaine));//todo si erreur alloc???
	copy(p_chaine);//todo si erreur copy???
}*/

/***********************************************
* concaténation
************************************************/
/*class c_strings c_strings::operator+( class c_strings &  chaine)
{

     c_strings p_tmp;

 	 p_tmp.realloc(taille_chaine+chaine.len());//todo si erreur alloc???
	 p_tmp.copy(p_buffer);//todo si erreur copy???
	 p_tmp.copy(chaine.get_pointer());//todo si erreur copy???
	 return p_tmp;
}*/

/***********************************************
* concaténation
************************************************/
/*class c_strings c_strings::operator+( char * chaine)
{

     c_strings p_tmp;

 	 p_tmp.realloc(taille_chaine+strlen(chaine));//todo si erreur realoc???
	 p_tmp.copy(p_buffer);//todo si erreur copy???
	 p_tmp.copy(chaine);//todo si erreur copy???
	 return p_tmp;
}*/

/***********************************************
* opérateur d'accès
************************************************/
/*char c_strings::operator [](int pointeur)
{
    //on retourne le caractère pointé par "pointeur" dans "buffer"
    return p_buffer[pointeur];

}*/

/***********************************************
* cast
************************************************/
c_strings::operator char*()
{
     return this->p_buffer;
}

/***********************************************
* cast
************************************************/
c_strings::operator char*() const
{
     return this->p_buffer;
}



/***********************************************
* ajoute une chaine
************************************************/
/*void c_strings::operator +=(class c_strings & chaine) //sans le & en quittant la fonction il appel le destructeur de chaine
{
     c_strings p_tmp(p_buffer);//sauve chaine locale

 	 realloc(p_tmp.len()+chaine.len()); //réalloue la mémoire de local + param (efface la chaine locale)    //todo si erreur realloc??? //todo ne perd plus les data
	 copy(p_tmp.get_pointer()); //remet la sauvegarde //todo si erreur copy???
	 copy(chaine.get_pointer()); // plus la chaine param //todo si erreur copy???
}*/

/***********************************************
* comparaison de chaines
************************************************/
bool c_strings::operator ==(const class c_strings & chaine)
{
     return (strcmp(this->p_buffer,(char*)chaine)==0);
}

/***********************************************
* comparaison de chaines
************************************************/
bool c_strings::operator ==(char * chaine)
{
     return (strcmp(this->p_buffer,chaine)==0);
}

/***********************************************
* ajoute une chaine
************************************************/
/*void c_strings::operator +=(char * chaine)
{
     c_strings p_tmp(p_buffer); //copie de locale
     c_strings p_tmp2(chaine); // c_strings de param

 	 realloc(p_tmp.len()+p_tmp2.len()); //aloue en locale taille des deux
	 copy(p_tmp.get_pointer()); //remet la sauvegarde
	 copy(p_tmp2.get_pointer()); // et param
}*/

/***********************************************
* récupère un pointeur sur la chaine
************************************************/
/*char * c_strings::get_pointer()
{
 return p_buffer;     
}*/
     
/***********************************************
* longueure de la chaine
************************************************/
long c_strings::len()
{
     return this->taille_chaine;
}

/***********************************************
* passage en minuscules
************************************************/
/*void	c_strings::lower()
{
char * tmp;
    tmp=p_buffer;
    while(*tmp)
    {
        if(tmp[0] > 'A' && tmp[0] < 'Z')
          tmp[0] += 'a'-'A';         
          
		tmp++;
	}
}*/

/***********************************************
* passage en majuscules
************************************************/
/*void	c_strings::upper()
{
char * tmp;
    tmp=p_buffer;
    while(*tmp)
    {
        if(tmp[0] > 'a' && tmp[0] < 'z')
          tmp[0] -= 'A'-'a';         
		tmp++;
	}
}*/

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


bool c_strings::endsWith(char * chaine)
{
char * tmp;
	tmp = this->p_buffer + this->taille_chaine - strlen(chaine) +1;
	if(strcmp(tmp,chaine)==0) return true;
	return false;
}

