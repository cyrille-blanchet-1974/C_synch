#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include "logger.h"
#include "global.h"

class c_logger
{
    private:
    	FILE *pFile;		

	public:  
    	// class constructor
		c_logger(char *nom);
		// class destructor
		~c_logger();
        void add(char * as_chaine);
};

#endif // LOGGER_H




