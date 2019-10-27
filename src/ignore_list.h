/*******************************************************************************
*
*                   Classe de stockage des dossier à ignorer (singleton)
*
*******************************************************************************/
#ifndef IGNORE_LIST_H
#define IGNORE_LIST_H
#include <string.h> //str*
#include "logger.h"
#include "global.h"
#include "strings.h"



class c_ignore_list
{
    private:	
        static class c_strings     cs_full_folder_to_ignore;    //TODO => tableau pour en gèrer plusieurs
		static class c_strings     cs_partial_folder_to_ignore; //TODO => tableau pour en gèrer plusieurs
		//TODO ignorer sources/cible séparément
		
	public:
		// class constructor
		c_ignore_list();
		// class destructor
		~c_ignore_list();
		//indiquer un dossier à ignorer (chemin complet) 
		void set_full_folder(class c_strings path); //TODO => Add quand tableau 
		//indiquer un nom générique de dossier à ignorer (chemin partiel)
	    void set_partial_folder(class c_strings path);//TODO => Add quand tableau 
		//indiquer si un dossier complet doit être ignorer
		bool is_full_folder_to_be_ignore(class c_strings path); 
		//indiquer si un dossier complet doit être ignorer
		bool is_full_folder_to_be_ignore(char* path); 
		//indiquer si un chemin partiel doit être ignorer 
	    bool is_partial_folder_to_be_ignore(class c_strings path); 
		//indiquer si un chemin partiel doit être ignorer 
	    bool is_partial_folder_to_be_ignore(char* path); 
};

#endif // IGNORE_LIST_H
