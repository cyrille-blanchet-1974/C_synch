/*******************************************************************************
*
*                   Classe de gestion des chaînes
*
*******************************************************************************/
#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include "string.h"
#include "global.h"

class c_string
{
	public:  
        //copie une chaine 
        static char * copy_alloc(char *ap_chaine);
        //concataine 2 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2);
        //concataine 3 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2,char *ap_chaine3);
        //concataine 4 chaine dans une autre
        static char * concat_alloc(char*ap_chaine1,char *ap_chaine2,char *ap_chaine3,char *ap_chaine4);
};

#endif // STRING_H




