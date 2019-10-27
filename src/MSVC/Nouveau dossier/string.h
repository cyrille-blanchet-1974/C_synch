/***************************************************************************
* Copyright (C) 2004 by Bouard Eric *
* eric@bouard.org *
* wwww.bouard.org *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 2 of the License, or *
* (at your option) any later version. *
* *
* This program is distributed in the hope that it will be useful, *
* but WITHOUT ANY WARRANTY; without even the implied warranty of *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
* GNU General Public License for more details. *
* *
* You should have received a copy of the GNU General Public License *
* along with this program; if not, write to the *
* Free Software Foundation, Inc., *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. *
***************************************************************************/
#include <config.h>
#include <mcheck.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream.h>
#include <string.h>

#include <iostream>
#include <cstdlib>

#define TAB (char)0x09
#define EOT (char)0x04

/************
* Méthodes *
************/
class String
{
 private:
#define PROTECT_MEM 1
#define DATE_TAILLE_MAXIMUM 200
#define MALLOC 1
#define REALLOC 2
#define VERIFIEINDEXE 3
#define FICHIER_LOG "memory_error.log"
#define TAILLE_INITIALE 50
#define TAILLE_NOMBRE 70
#define MAX_ISTREAM_SIZE 2048
#define STRINGDEBUG 1
#if STRINGDEBUG==1
#define DEBUGMEMOIRE if (mcheck(0) != 0){sortie_sur_erreur(MALLOC);}
#else
#define DEBUGMEMOIRE
#endif

/*******************
* membres données *
*******************/
 String * _pszTemp;
 char * _pszChaine;
 int _piTaille;

 void * String::my_malloc(size_t Taille);
 void String::my_free(void * pString);
 char * String::my_realloc(char * pString, size_t sNewSize);
 void String::sortie_sur_erreur(int alloc_Type);
 void String::_verifieIndexe(unsigned long lParam);
 String::String(bool dummy,int iTaille);
 void String::_allocpTemp(int iTaille=0);
 void String::_allocpTemp(char * pTemp);
 void String::_str_cpy(char * szChaine);
 void String::_cat(char * szChaine);
 bool String::_cat(const String & RightParam);
 void String::_SansEspaceGauche();
 void String::_SansEspaceDroite();
 bool String::_EgaleA(const String & RightParam);
 bool String::_NonEgaleA(const String & RightParam);
 public:
 String::String();
 String(char * szChaine);
 String(int iEntier);
 String(char cChar);
 String(unsigned long ulLong);
 String(long lLong);
 String(float fFloat);
 String(double dDouble);
~String();
 char * val();
 int Taille();
 String Minuscule();
 String Majuscule();
 void SansEspaceGauche(bool dummy);
 String SansEspaceGauche();
 void SansEspaceDroite(bool dummy);
 String SansEspaceDroite();
 void SansEspace(bool dummy);
 String SansEspace();
 String Gauche(int iTaille = 0);
 String Droite(int iTaille = 0);
 String Milieu(int iDepart, int iLongueur = 0);
 String ExtraitChaine(int iTaille,char cSeperator=TAB);
 String Repete(String sChaine, int iTaille);
 String Complete(int iTaille,char cRemplissage=' ');
/******************
* les Opérateurs *
******************/
 String& operator= ( const String& RightParam );
 String operator+ (const String & RightParam);
 String& operator+= (const String & RightParam);
 bool operator== (const String & RightParam);
 bool operator!= (const String & RightParam);
 char & operator[] (unsigned long lParam);
 friend ostream & operator << (ostream & out, const String & RightParam);
 friend istream & operator >> (istream & in, String & RightParam);
};


