#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include "string.h"
#include "global.h"

class c_string
{
	public:  
        static char * strcpy_alloc(char*dst,char *src);
        static char * strcat_alloc(char*dst,char *src);
};

#endif // STRING_H




