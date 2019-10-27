#include <string.h>
#include <stdio.h>
#include <stdarg.h>//pour winuser.h
#include <windef.h>//pour winuser.h
#include <wingdi.h>//pour winuser.h
#include <winuser.h> //pour CharToOem
#include "logger.h"
#include "global.h"


// class constructor
c_logger::c_logger(char *nom)
{
    pFile = fopen (nom,"w");
}
// class destructor
c_logger::~c_logger()
{
    fclose (pFile);
}
void c_logger::add(char * as_chaine)
{
char ls_oem[MAX_CHAINE];     
   CharToOem(as_chaine,ls_oem);
   fprintf(pFile,"%s",ls_oem);
   fflush(pFile);
}
