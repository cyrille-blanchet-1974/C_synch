#include "arbo.h" 
#include "logger.h"
#include <stdio.h> //printf
#include <string.h> //str*
#include <windows.h>//GetCurrentThreadId
#include "synch.h"


/***********************************************
* constructeur de la classe
* Entrée: source,cible,sortie
************************************************/
c_synch::c_synch(char * a_source,char * a_cible,char * a_sortie,bool b_multithread,bool b_ecraser,bool b_verbose)
{   
c_strings ls_commande(1024);
    
    this->StateSource     = NOT_CREATE;
    this->StateCible      = NOT_CREATE;
    this->p_logger=new c_logger(a_sortie,b_ecraser);      
    
    this->p_logger->add("@echo off\n");
    ls_commande.set("Echo Synchronisation de ");
    ls_commande.add(a_source);
    ls_commande.add(" vers ");
    ls_commande.add(a_cible);
    ls_commande.add("\n");
    this->p_logger->add(ls_commande.get());   
      
    this->p_source = new c_arbo(a_source,this->p_logger,b_verbose);
    this->p_cible  = new c_arbo(a_cible ,this->p_logger,b_verbose);
    if(b_multithread)
    {
        run_multithread();
    }
    else
    {
        run_monothread();
    }    
}                

/***********************************************
* destructeur de la classe
************************************************/
c_synch::~c_synch()
{
    //nettoyage    
    if(this->p_source!=NULL)delete this->p_source;
    this->p_source=NULL;
    if(this->p_cible!=NULL)delete this->p_cible;
    this->p_cible=NULL;
    if(this->p_logger!=NULL)delete this->p_logger;
    this->p_logger=NULL;
}
                   
/***********************************************
* traiement séquentiel
************************************************/
void c_synch::run_monothread()
{
    printf("Thread(%li)-MODE MonoThread \n",GetCurrentThreadId()); 
    LireSource( ) ;
	ThreadStatus();
    LireCible ( ) ;
	ThreadStatus();
    EnMoins   ( ) ;
    EnTrop    ( ) ;
}     

/***********************************************
* traitement parallèle
************************************************/
// lance la synchro en monothread
void c_synch::run_multithread()
{
DWORD dwThreadId1,dwThreadId2,dwThreadId3,dwThreadId4,dwThrdParam = 1; 
HANDLE hThread1,hThread2,hThread3,hThread4; 

    printf("Thread(%li)-MODE MultiThread \n",GetCurrentThreadId()); 
    printf("Thread(%li)-CREATION DES THREADS SECONDAIRES DE LECTURE\n",GetCurrentThreadId()); 
    hThread1 = CreateThread( 
        NULL,               // attribut de securité par defaut         
        0,                  // taille de la pile par defaut
        ThreadLireSource,   // notre function
        this,            // l'argument pour la fonction
        0,                  // flag de creation par defaut
        &dwThreadId1);      // retourne l'id du thread
    // On check si le thread est ok 
    if (hThread1 == NULL) 
    {
      printf( "Thread(%li)-Probleme lors de la creation du thread 1 (%d)\n",GetCurrentThreadId(),GetLastError() ); 
      return ;
    }
    
    hThread2 = CreateThread(NULL,0,ThreadLireCible,this,0,&dwThreadId2);  
    // On check si le thread est ok 
    if (hThread2 == NULL) 
    {
      printf( "Thread(%li)-Probleme lors de la creation du thread 2 (%d)\n",GetCurrentThreadId(),GetLastError() ); 
      return ;
    }
    
    while( 0==0 )
    {
            Sleep(DELAI_ATTENTE);
            ThreadStatus();
            printf("Thread(%li)-ATTENTE THREADS SECONDAIRES DE LECTURE \n",GetCurrentThreadId()); 
            if( (this->StateSource == READED) && (this->StateCible == READED)  ) break;
    }       
	ThreadStatus();
    printf("Thread(%li)-CREATION DES THREADS SECONDAIRES DE COMPARAISON\n",GetCurrentThreadId()); 
    hThread3 = CreateThread(NULL,0,ThreadEnMoins,this,0,&dwThreadId3);
    // On check si le thread est ok 
    if (hThread3 == NULL) 
    {
      printf( "Thread(%li)-Probleme lors de la creation du thread 3 (%d)\n",GetCurrentThreadId(),GetLastError() ); 
      return;
    }

    hThread4 = CreateThread(NULL,0,ThreadEnTrop,this,0,&dwThreadId4);    
    // On check si le thread est ok 
    if (hThread4 == NULL) 
    {
      printf( "Thread(%li)-Probleme lors de la creation du thread 4 (%d)\n",GetCurrentThreadId(),GetLastError() ); 
      return;
    }
    
    while( 0==0 )
    {
            Sleep(DELAI_ATTENTE);
            printf("Thread(%li)-ATTENTES THREADS SECONDAIRES DE COMPARAISON \n",GetCurrentThreadId()); 
            if( (this->StateSource == COMPARED) && (this->StateCible == COMPARED)  ) break;
    }        
	printf("Thread(%li)-FIN NETTOYAGE\n",GetCurrentThreadId()); 
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);
    CloseHandle(hThread4); 
}
     
/***********************************************
* lecture arborescence source
************************************************/
void c_synch::LireSource( ) 
{ 
     printf("Thread(%li)-Lecture source : DEBUT \n",GetCurrentThreadId());   
     this->StateSource     = READING;     
     this->p_source->parcourir();
     this->StateSource     = READED;
     printf("Thread(%li)-Lecture source : FIN \n",GetCurrentThreadId());   
} 

/***********************************************
* lecture arborescence cible
************************************************/
void c_synch::LireCible( )
{ 
     printf("Thread(%li)-Lecture cible DEBUT\n",GetCurrentThreadId());
     this->StateCible     = READING;     
     this->p_cible->parcourir();
     this->StateCible     = READED;
     printf("Thread(%li)-Lecture cible FIN\n",GetCurrentThreadId());
} 

/***********************************************
* statut des objets
************************************************/
void c_synch::ThreadStatus( )
{
     if(this->p_source != NULL) this->p_source->get_status();
     if(this->p_cible != NULL)  this->p_cible->get_status();
}

/***********************************************
* recherche des fichier manquant en destination
************************************************/
void c_synch::EnMoins( )
{
     printf("Thread(%li)-Recherche fichiers manquants/modifiés DEBUT\n",GetCurrentThreadId());   
     this->StateSource     = COMPARING;     
     this->p_source->fic_en_moins(this->p_cible);
     this->StateSource     = COMPARED;
     printf("Thread(%li)-Recherche fichiers manquants/modifiés FIN\n",GetCurrentThreadId());        
}

/***********************************************
* recherche des fichier en destination
* ne devant plus y être
************************************************/
void c_synch::EnTrop( )
{
     printf("Thread(%li)-Recherche fichiers en trop DEBUT\n",GetCurrentThreadId());    
     this->StateCible     = COMPARING;     
     this->p_cible->fic_en_trop(this->p_source);
     this->StateCible     = COMPARED;     
     printf("Thread(%li)-Recherche fichiers en trop FIN\n",GetCurrentThreadId());    
}

/***********************************************
* lecture arborescence source
************************************************/
DWORD WINAPI c_synch::ThreadLireSource( LPVOID lpParam ) 
{ 
     ((c_synch*)lpParam)->LireSource();
     return 0;
} 

/***********************************************
* lecture arborescence cible
************************************************/
DWORD WINAPI c_synch::ThreadLireCible( LPVOID lpParam )
{ 
     ((c_synch*)lpParam)->LireCible();
     return 0;
} 
/***********************************************
* recherche des fichier manquant en destination
************************************************/
DWORD WINAPI c_synch::ThreadEnMoins( LPVOID lpParam )
{
     ((c_synch*)lpParam)->EnMoins();
     return 0;
}

/***********************************************
* recherche des fichier en destination
* ne devant plus y être
************************************************/
DWORD WINAPI c_synch::ThreadEnTrop( LPVOID lpParam )
{
     ((c_synch*)lpParam)->EnTrop();
     return 0;
}
