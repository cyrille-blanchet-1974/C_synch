/*******************************************************************************
*
*                   Classe de synchronisation
*
*******************************************************************************/
#ifndef SYNCH_H
#define SYNCH_H
#include <stdio.h>
#include <windows.h> //mutex+threads
#include "logger.h"
#include "global.h"
#include "strings.h"
#include "arbo.h"

#define DELAI_ATTENTE 2000
//état des arboresenes
#define NOT_CREATE 0
#define READING    2
#define READED     3
#define COMPARING  4
#define COMPARED   5


class c_synch
{
    private:
        //objets arborescences cible et source
        c_arbo *p_source;
        c_arbo *p_cible;
        //écriture du fichier de sortie
        c_logger *p_logger;
        //état des arboresenes
        int StateSource;
        int StateCible;
        void ThreadStatus( ); 
        void LireSource( ) ;
        void LireCible( ); 
        void EnMoins( ); 
        void EnTrop( ); 

	public:  
    	// class constructor 
		c_synch(char * a_source,char * a_cible,char * a_sortie,bool b_multithread,bool b_ecraser,bool b_verbose);
		// class destructor 
		~c_synch();
		// lance la synchro en monothread
        void run_monothread();
		// lance la synchro en monothread
        void run_multithread();
        static DWORD WINAPI ThreadLireSource( LPVOID lpParam ) ;
        static DWORD WINAPI ThreadLireCible( LPVOID lpParam ); 
        static DWORD WINAPI ThreadEnMoins( LPVOID lpParam ); 
        static DWORD WINAPI ThreadEnTrop( LPVOID lpParam ); 
};

#endif // SYNCH_H




