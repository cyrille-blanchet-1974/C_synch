#include "ignore_list.h" 

class c_strings     c_ignore_list::cs_full_folder_to_ignore;    
class c_strings     c_ignore_list::cs_partial_folder_to_ignore; 

/***********************************************
* constructeur de la classe
************************************************/
c_ignore_list::c_ignore_list()
{   
    //this->cs_full_folder_to_ignore.set(""); 
	//this->cs_partial_folder_to_ignore.set(""); 
}                

/***********************************************
* destructeur de la classe
*
************************************************/
c_ignore_list::~c_ignore_list()
{                           
}

/***********************************************
* setteurs de la classe
************************************************/
//indiquer un dossier à ignorer (chemin complet) 
void c_ignore_list::set_full_folder(class c_strings path)
{
   this->cs_full_folder_to_ignore.set(path); 
   if(!this->cs_full_folder_to_ignore.endsWith(G_SEPARATOR) ) this->cs_full_folder_to_ignore.add(G_SEPARATOR);
}
//indiquer un nom générique de dossier à ignorer (chemin partiel)
void c_ignore_list::set_partial_folder(class c_strings path)
{
	this->cs_partial_folder_to_ignore.set(path); 
	if(!this->cs_partial_folder_to_ignore.endsWith(G_SEPARATOR) ) this->cs_partial_folder_to_ignore.add(G_SEPARATOR);
}

/*************************************************
* indiquer si un dossier complet doit être ignorer
**************************************************/
bool c_ignore_list::is_full_folder_to_be_ignore(class c_strings path)
{
	if(strcasecmp(this->cs_full_folder_to_ignore.get(),path.get())==0) return true;
	return false;
}
/*************************************************
* indiquer si un dossier complet doit être ignorer
**************************************************/
bool c_ignore_list::is_full_folder_to_be_ignore(char* path)
{
	if(strcasecmp(this->cs_full_folder_to_ignore.get(),path)==0) return true;
	return false;
}

/*************************************************
* indiquer si un chemin partiel doit être ignorer 
**************************************************/
bool c_ignore_list::is_partial_folder_to_be_ignore(class c_strings path)
{
	if(strcasecmp(this->cs_partial_folder_to_ignore.get(),path.get())==0) return true;
	return false;
}

/*************************************************
* indiquer si un chemin partiel doit être ignorer 
**************************************************/
bool c_ignore_list::is_partial_folder_to_be_ignore(char* path)
{
	if(strcasecmp(this->cs_partial_folder_to_ignore.get(),path)==0) return true;
	return false;
}
