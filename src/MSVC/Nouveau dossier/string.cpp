    /***************************************************************************
 Copyright (C) 2004 by Bouard Eric *
 eric@bouard.org *
 wwww.bouard.org *
 This program is free software; you can redistribute it and/or modify *
 it under the terms of the GNU General Public License as published by *
 the Free Software Foundation; either version 2 of the License, or *
(at your option) any later version. *

 This program is distributed in the hope that it will be useful, *
 but WITHOUT ANY WARRANTY; without even the implied warranty of *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
 GNU General Public License for more details. *

 You should have received a copy of the GNU General Public License *
 along with this program; if not, write to the *
 Free Software Foundation, Inc., *
 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. *
**************************************************************************/
    #include "String.h"
    
    /**********************************************
 allocation de mémoire et sortie sur erreur *
*********************************************/
    
    /************************
 redinition de malloc *
***********************/
    
     void * String::my_malloc(size_t Taille)
    {
     void * pszTemp = NULL;
    
     DEBUGMEMOIRE
    
     pszTemp = (void *) malloc(Taille + PROTECT_MEM );
     if (pszTemp == NULL)
    {
     sortie_sur_erreur(MALLOC);
    }
    
     if (STRINGDEBUG==1)
     memset(pszTemp,205,Taille + PROTECT_MEM);
    
     return pszTemp;
    }
    
    /**********************
 redinition de free *
*********************/
     void String::my_free(void * pString)
    {
     DEBUGMEMOIRE
    
     if (pString == NULL)
    {
     return;
    }
     free(pString);
     pString = NULL;
    }
    
    /*************************
 redinition de realloc *
************************/
     char * String::my_realloc(char * pString, size_t sNewSize)
    {
    
     DEBUGMEMOIRE
    
     pString = (char *) realloc(pString, sizeof (char) *(sNewSize+ PROTECT_MEM));
     if (pString == NULL)
    {
     sortie_sur_erreur(REALLOC);
    }
    
     return pString;
    }
    
    /*********************
 Sortie sur Erreur *
********************/
     void String::sortie_sur_erreur(int alloc_Type)
    {
     char ptcDate[DATE_TAILLE_MAXIMUM + PROTECT_MEM];
     char ptcNomFichierLog[100+PROTECT_MEM];
     char ptcNomProgramme[200+PROTECT_MEM];
     char dtype[50+PROTECT_MEM];
     time_t pttTime;
     struct tm * ptmLocal = NULL;
     FILE * fFichierLog = NULL;
    
     pttTime = time(NULL);
     ptmLocal = localtime(&pttTime);
     if (ptmLocal == NULL)
    {
     fprintf(stdout, "\nAttention, impossible de convertir en temps local, localtime() a echoué\n");
     fprintf(stderr, "\nAttention, impossible de convertir en temps local, localtime() a echoué\n");
    }
     else
    {
     strftime(ptcDate, DATE_TAILLE_MAXIMUM , "%C", ptmLocal);
    }
    
     strcpy(ptcNomFichierLog, FICHIER_LOG);
     fFichierLog = fopen(ptcNomFichierLog, "a");
     if (fFichierLog == NULL)
    {
     fprintf(stdout, "\nAttention: impossible d'ouvrir le fichier %s\n", ptcNomFichierLog);
     fprintf(stderr, "\nAttention: impossible d'ouvrir le fichier %s\n", ptcNomFichierLog);
     exit(-1);
    }
    
    
     if (getenv("PROGRAM_NAME") == NULL)
    {
     fprintf(fFichierLog, "\n%sAttention: le nom du programme n'a pu etre trouvé. \n", ptcDate);
     ptcNomProgramme[0] = 0;
    }
     else
    {
     strncpy(ptcNomProgramme, getenv("PROGRAM_NAME"), 200);
    }
    
     switch (alloc_Type)
    {
     case MALLOC:
    {
     fprintf(stdout, "\nErreur Fatale : my_malloc() a echoué !!");
     fprintf(stderr, "\nErreur Fatale : my_malloc() a echoué !!");
     fprintf(fFichierLog, "\n%s: %s - Erreur Fatale : my_malloc() a echoué !!", ptcDate, ptcNomProgramme);
     break;
    }
     case REALLOC:
    {
     fprintf(stdout, "\nErreur Fatale: my_realloc() a echoué !!");
     fprintf(stderr, "\nErreur Fatale: my_realloc() a echoué !!");
     fprintf(fFichierLog, "\n%s %s - Erreur Fatale : realloc() a échoué !! ", ptcDate, ptcNomProgramme);
     break;
    }
     case VERIFIEINDEXE:
    {
     fprintf(stdout, "\nErreur Fatale: _verifieIndexe() a echoué !!");
     fprintf(stderr, "\nErreur Fatale: _verifieIndexe() a echoué !!");
     fprintf(fFichierLog, "\n%s %s - Erreur Fatale : _verifieIndexe() a échoué !! ", ptcDate, ptcNomProgramme);
     break;
    }
     default:
    {
     fprintf(stdout, "\nErreur Fatale: type inconnu!");
     fprintf(stderr, "\nErreur Fatale: type inconnu!");
     exit(-1);
    }
    }
    
     fprintf(fFichierLog, "\n%s %s - Erreur Fatale.Fin de l'application....", ptcDate, ptcNomProgramme);
     fclose(fFichierLog);
    
     exit(-1);
    }
    /****************************
 Vérification de l'indexe *
***************************/
     void String::_verifieIndexe(unsigned long lParam)
    {
     if (lParam < 0 || lParam > _piTaille )
    {
     sortie_sur_erreur(VERIFIEINDEXE);
    }
    }
    
    
    
    /**************************************
 Constructeur d'une longueur donnée *
*************************************/
     String::String(bool dummy,int iTaille)
    {
     _pszChaine = (char *) my_malloc(sizeof(char)* iTaille);
     _piTaille = 0;
     _pszChaine[_piTaille] = '\0';
     _pszTemp = NULL;
    }
    
    /*************************************
 Allocation d'un string temporaire *
*************************************/
     void String::_allocpTemp(int iTaille)
    {
     if (iTaille==0)
    {
     iTaille = _piTaille;
    }
     if (_pszTemp)
    {
 my_free(_pszTemp);
    }
 _pszTemp = new String(true,iTaille);
    }

    /***************************************************
 Allocation d'un string temporaire et affectation*
*************************************************/
 void String::_allocpTemp(char * pTemp)
    {
 if (_pszTemp)
    {
 my_free(_pszTemp);
 DEBUGMEMOIRE
    }
 _pszTemp = new String(this->_pszChaine);
    }



    /************************************************
 redinition de copie du chaine dans un String *
***********************************************/
 void String::_str_cpy(char * szChaine)
    {

 if (szChaine == NULL)
    {
 _pszChaine[0] = '\0';
 _piTaille = 0;
 return;
    }

 _piTaille = strlen(szChaine);
 if (_piTaille == 0)
    {
 _pszChaine[0] = '\0';
 _piTaille = 0;
 return;
    }

 _pszChaine = (char *) my_realloc(_pszChaine, _piTaille);
 strncpy(_pszChaine, szChaine, _piTaille);
 _pszChaine[_piTaille] = '\0';
    }

 void String::_cat(char * szChaine)
    {
 int iTaille = strlen(szChaine);
 _pszChaine = (char *) my_realloc(_pszChaine, _piTaille + iTaille);
 strncat(_pszChaine, szChaine, iTaille);
 _piTaille += iTaille;
    }
 bool String::_cat(const String & RightParam)
    {
 _pszChaine = (char *) my_realloc(_pszChaine, _piTaille + RightParam._piTaille);
 strncat(_pszChaine, RightParam._pszChaine, RightParam._piTaille);
 _piTaille +=RightParam._piTaille;
    }

    /*******************************
 Enleve les espaces a gauche *
******************************/
 void String::_SansEspaceGauche()
    {
 char *szChaine = _pszChaine;
 char *szChaineTemp = _pszChaine;

 while (isspace(*szChaine))
 szChaine++;

 if (szChaine != _pszChaine)
    {
 _piTaille=0;
 while (*szChaine)
    {
    *szChaineTemp++ = *szChaine++;
 _piTaille++;
    }
++szChaineTemp='\0';
    }
    }

    /*******************************
 Enleve les espaces a droite *
******************************/
 void String::_SansEspaceDroite()
    {
 char *szChaine = _pszChaine + _piTaille - 1;

 while (_piTaille>0)
    {
 if (isspace(*szChaine))
    {
    *szChaine = '\0';
 _piTaille--;
 szChaine--;
    }
 else
    {
 break;
    }
    }
    }
    /*******************************
 comparaison de 2 string *
******************************/
 bool String::_EgaleA(const String & RightParam)
    {
 if (_piTaille == RightParam._piTaille)
    {
 if (strcmp(RightParam._pszChaine, _pszChaine))
 return false;
 else
 return true;
    }
 else
 return false;
    }

 bool String::_NonEgaleA(const String & RightParam)
    {
 if (_piTaille == RightParam._piTaille)
    {
 if (strcmp(RightParam._pszChaine, _pszChaine))
 return true;
 else
 return false;
    }
 else
 return true;
    }

    /***************************
 Constructeur par défaut *
**************************/
 String::String()
    {
 _pszChaine = (char *) my_malloc(sizeof(char)* TAILLE_INITIALE);
 _piTaille = 0;
 _pszChaine[_piTaille] = '\0';
 _pszTemp = NULL;
    }

    /***********************************************
 Constructeur avec une chaine en affectation *
**********************************************/
 String::String(char * szChaine)
    {
 _piTaille = strlen(szChaine);
 _pszChaine = (char *) my_malloc(sizeof(char)* _piTaille);
 strncpy(_pszChaine, szChaine, _piTaille);
 _pszChaine[_piTaille] = '\0';
 _pszTemp = NULL;
    }

    /***********************************************
 Constructeur avec un entier en affectation *
**********************************************/
 String::String(int iEntier)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 sprintf(_pszChaine, "%d", iEntier);
 _piTaille = strlen(_pszChaine);
 _pszTemp = NULL;
    }
    /***********************************************
 Constructeur avec un char en affectation *
**********************************************/
 String::String(char cChar)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 _pszChaine[0]=cChar;
 _pszChaine[1]='\0';
 _piTaille = 1;
 _pszTemp = NULL;
    }

    /*******************************************************
 Constructeur avec un long non signé en affectation *
******************************************************/
 String::String(unsigned long ulLong)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 sprintf(_pszChaine, "%lu", ulLong);
 _piTaille = strlen(_pszChaine);
 _pszTemp = NULL;
    }

    /*********************************************
 Constructeur avec un long en affectation *
********************************************/
 String::String(long lLong)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 sprintf(_pszChaine, "%ld", lLong);
 _piTaille = strlen(_pszChaine);
 _pszTemp = NULL;
    }

    /**********************************************
 Constructeur avec un float en affectation *
*********************************************/
 String::String(float fFloat)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 sprintf(_pszChaine, "%f", fFloat);
 _piTaille = strlen(_pszChaine);
 _pszTemp = NULL;
    }

    /***********************************************
 Constructeur avec un double en affectation *
**********************************************/
 String::String(double dDouble)
    {
 _pszChaine = (char *) my_malloc(TAILLE_NOMBRE);
 sprintf(_pszChaine, "%f", dDouble);
 _piTaille = strlen(_pszChaine);
 _pszTemp = NULL;
    }


    /***************
 Destructeur *
**************/
 String::~String()
    {

 my_free(_pszChaine);
 _pszChaine = NULL;
 _piTaille=0;
 if (_pszTemp != NULL)
    {
 delete _pszTemp;
 _pszTemp = NULL;
    }
 DEBUGMEMOIRE;
    }

    /******************************
 permet l'acces a la chaine *
*****************************/
 char * String::val()
    {
 return _pszChaine;
    }

    /***********************************
 retourne la taille de la chaine *
**********************************/
 int String::Taille()
    {
 return _piTaille;
    }

    /**************************
 la chaine en minuscule *
*************************/
 String String::Minuscule()
    {
 long Iter;

 _allocpTemp();

 for (Iter = 0; Iter <= _piTaille; Iter++)
    {
 _pszTemp->_pszChaine[Iter] = tolower(_pszChaine[Iter]);
    }
 _pszTemp->_piTaille=_piTaille;
 return * _pszTemp; // return the object now
    }

    /**************************
 la chaine en majuscule *
*************************/
 String String::Majuscule()
    {
 long Iter;

 _allocpTemp();

 for (Iter = 0; Iter <= _piTaille; Iter++)
    {
 _pszTemp->_pszChaine[Iter] = toupper(_pszChaine[Iter]);
    }
 _pszTemp->_piTaille=_piTaille;
 return * _pszTemp; // return the object now
    }


    /***************************************************
 Enleve les espaces a gauche dans l'objet courant*
**************************************************/
 void String::SansEspaceGauche(bool dummy)
    {
 this->_SansEspaceGauche();
    }

    /*******************************
 Enleve les espaces a gauche *
******************************/
 String String::SansEspaceGauche()
    {
 _allocpTemp(_pszChaine);
    (*_pszTemp)._SansEspaceGauche();
 return *_pszTemp;
    }

    /***************************************************
 Enleve les espaces a droite dans l'objet courant*
**************************************************/
 void String::SansEspaceDroite(bool dummy)
    {
 this->_SansEspaceDroite();
    }


    /*******************************
 Enleve les espaces a droite *
******************************/
 String String::SansEspaceDroite()
    {
 _allocpTemp(_pszChaine);
    (*_pszTemp)._SansEspaceDroite();
 return *_pszTemp;
    }
    /***************************************************************
 Enleve les espaces a gauche et à droite dans l'objet courant*
**************************************************************/
 void String::SansEspace(bool dummy)
    {
 this->_SansEspaceGauche();
 this->_SansEspaceDroite();
    }

    /******************************************
 Enleve les espaces a gauche et a droite*
****************************************/
 String String::SansEspace()
    {
 _allocpTemp(_pszChaine);
    (*_pszTemp)._SansEspaceGauche();
    (*_pszTemp)._SansEspaceDroite();
 return *_pszTemp;
    }

    /*****************************************
 Extrait la partie gauche d'une chaîne *
****************************************/
 String String::Gauche(int iTaille)
    {
    // Par exemple -
    // Gauche() avec _pszChaine = "Ceci est un test " retourne "Ceci est un test"
    // Gauche(4) avec _pszChaine = "Ceci est un test " retourne "Ceci"
    // Gauche(50) avec _pszChaine = "Ceci est un test " retourne "Ceci est un test "
 _allocpTemp(_pszChaine);
 if (iTaille <=0)
    {
    (*_pszTemp)._SansEspaceDroite();
    }
 else
    {
 if (iTaille <= _piTaille)
    {
 _pszTemp->_pszChaine[iTaille] = '\0';
 _pszTemp->_piTaille=iTaille;
    }
    }

 return *_pszTemp;
    }

    /*****************************************
 Extrait la partie droite d'une chaîne *
****************************************/
 String String::Droite(int iTaille)
    {
    // Par exemple -
    // Droite() avec _pszChaine = " Ceci est un test" retourne "Ceci est un test"
    // Droite(4) avec _pszChaine = " Ceci est un test" retourne "test"
    // Droite(50) avec _pszChaine = " Ceci est un test" retourne " Ceci est un test"
 _allocpTemp(_pszChaine);
 if (iTaille <=0)
    {
    (*_pszTemp)._SansEspaceGauche();
    }
 else
    {
 if (iTaille <= _piTaille)
    {
 strncpy(_pszTemp->_pszChaine,_pszTemp->_pszChaine+_piTaille-iTaille,iTaille);
 _pszTemp->_pszChaine[iTaille] = '\0';
 _pszTemp->_piTaille=iTaille;
    }
    }

 return *_pszTemp;
    }
    /***********************************************************************
 Extrait une sous-chaîne d'une chaîne à partir d'une position donnée.*
**********************************************************************/
 String String::Milieu(int iDepart, int iLongueur)
    {
    // Par exemple - String Ch = "Ceci est un test"
    // Ch.Milieu(2, 3) Renvoie "eci"
    // Ch.Milieu(2) Renvoie "eci est un test"
    // Ch.Milieu(50) Renvoie ""
    // Ch.Milieu(2, 50) Renvoie "eci est un test"
 _allocpTemp(_pszChaine);
 if (iDepart<1)
    {
 iDepart=1;
    }

 if (iLongueur <=0 || iLongueur > (_piTaille-iDepart+1))
    {
 iLongueur = _piTaille-iDepart+1;
    }

 strncpy(_pszTemp->_pszChaine,_pszTemp->_pszChaine+iDepart-1,iLongueur);
 _pszTemp->_pszChaine[iLongueur] = '\0';
 _pszTemp->_piTaille=iLongueur;

 return *_pszTemp;
    }

    /**************************************************************************************************
 Extrait une sous-chaîne d'une chaîne de caractères en fonction d'un séparateur de chaîne donné *
*************************************************************************************************/
 String String::ExtraitChaine(int iTaille,char cSeperator)
    {
    // Par exemple - String Ch = "ABC" + TAB + "" + TAB + "" + TAB + "DEF"
    // Ch.ExtraitChaîne(1) Renvoie "ABC"
    // Ch.ExtraitChaîne(2) Renvoie ""
    // Ch.ExtraitChaîne(3) Renvoie ""
    // Ch.ExtraitChaîne(4) Renvoie "DEF"
    // Ch.ExtraitChaîne(5) Renvoie EOT
 int iter;
 int iCompteur = 1;
 int iDecalage=0;
 bool bFlag=false;

 _allocpTemp(_piTaille);

 for (int iter = 0; iter < _piTaille; iter++)
    {
 if (_pszChaine[iter] == cSeperator)
    {
 iCompteur++;
    }
 if (iCompteur==iTaille)
    {
 bFlag=true;
 if(_pszChaine[iter] != cSeperator)
    {
 _pszTemp->_pszChaine[iDecalage]= _pszChaine[iter];
 iDecalage++;
    }
    }
    }
 if (bFlag==true)
    {
 _pszTemp->_pszChaine[iDecalage]='\0';
    }
 else
    {
 _pszTemp->_pszChaine[0]= EOT;
 _pszTemp->_pszChaine[1]='\0';
    }
 return *_pszTemp;

    }

    /*******************************************************************************
 Repete : Concatène N répétitions d'une même chaîne de caractères. *
******************************************************************************/
 String String::Repete(String sChaine, int iTaille)
    {
    //Ch.Répète("x", 4) Renvoie "xxxx"
    //Ch.Répète("Boby", 2) Renvoie "BobyBoby"
    //Ch.Répète("", 2) Renvoie ""
    //Ch.Répète("", 0) Renvoie 0
 int Iter;
 if (iTaille <= 0 || sChaine._pszChaine=="")
    {
 _allocpTemp("");
 return *_pszTemp;
    }

 _allocpTemp(sChaine._piTaille * iTaille);

 for (Iter = 0; Iter < iTaille; Iter++)
    {
 strcat(_pszTemp->_pszChaine, sChaine._pszChaine);
    }
 _pszTemp->_piTaille = sChaine._piTaille * iTaille;
 return *_pszTemp;
    }
    /*******************************************************************************
 Complete une chaîne de caractères en fonction d'un caractere de remplissage *
******************************************************************************/
 String String::Complete(int iTaille,char cRemplissage)
    {
    // Par exemple - String Ch = "Ceci est un test"
    // Ch.Complete(20) Renvoie "Ceci est un test "
    // Ch.Complete(20, "X") Renvoie "Ceci est un testXXXX"
    // Ch.Complete(4) Renvoie "Ceci"
 char tcTemp[2];
 int Iter;
 tcTemp[0]=cRemplissage;
 tcTemp[1]='\0';
 _allocpTemp(_pszChaine);
 if (iTaille > 0 )
    {
 if (iTaille > _piTaille)
    {
 _pszTemp->_pszChaine = (char *) realloc(_pszTemp->_pszChaine, sizeof (char) *(iTaille + PROTECT_MEM));
 if (_pszTemp->_pszChaine == NULL)
    {
 sortie_sur_erreur(REALLOC);
    }
 for (Iter = 0; Iter < iTaille-_piTaille; Iter++)
    {
 strcat(_pszTemp->_pszChaine, tcTemp);
    }
 _pszTemp->_piTaille=iTaille;
    }
 else
    {
 _pszTemp->_pszChaine[iTaille]='\0';
 _pszTemp->_piTaille=iTaille;
    }
    }
 return *_pszTemp;
    }
    /****************************************************************************************************************************/
    /******************
 les Opérateurs *
*****************/
 String& String::operator= ( const String& RightParam )
    {
 if (&RightParam == this)
    {
 return *this;
    }

 this->_str_cpy(RightParam._pszChaine);

 return *this;
    }

 String String::operator+ (const String & RightParam)
    {
    /*******************************************************/
    // pour concaténer deux chaînes if faut caster la 1ere
    // en String comme ici :
    //aa = (String) "Ceci " + " est un test " ;
    /*******************************************************/
 String stringTemp(_pszChaine);
 stringTemp._cat(RightParam);

 return stringTemp;

    }

 String& String::operator+= (const String & RightParam)
    {
 this->_cat(RightParam);
 return *this;
    }

 bool String::operator== (const String & RightParam)
    {
 return(_EgaleA(RightParam));
    }

 bool String::operator!= (const String & RightParam)
    {
 return(_NonEgaleA(RightParam));
    }

 char & String::operator[] (unsigned long lParam)
    {
 _verifieIndexe(lParam);
 return _pszChaine[lParam];
    }
 ostream & operator << (ostream & out, const String & RightParam)
    {
 out << RightParam._pszChaine;
 return out;
    }
 istream & operator >> (istream & in, String & RightParam)
    {
 static char szTemp[MAX_ISTREAM_SIZE];

 in >> szTemp;
 RightParam = szTemp;
 return in;
    }



