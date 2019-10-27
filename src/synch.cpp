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
c_synch::c_synch(char * a_source,char * a_cible,char * a_sortie,bool b_multithread,bool b_ecraser,bool b_verbose,bool b_crypt,bool b_ignore_err)
{   
c_strings ls_commande(1024);
    
    StateSource     = NOT_CREATE;
    StateCible      = NOT_CREATE;
    p_logger=new c_logger(a_sortie,b_ecraser);      
    
    p_logger->add("@echo off\n");
    ls_commande.set("Echo Synchronisation de ");
    ls_commande.add(a_source);
    ls_commande.add(" vers ");
    ls_commande.add(a_cible);
    ls_commande.add("\n");
    p_logger->add(ls_commande.get());   
      
    p_source = new c_arbo(a_source,p_logger,b_verbose,b_crypt,b_ignore_err);
    p_cible = new c_arbo(a_cible,p_logger,b_verbose,b_crypt,b_ignore_err);
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
    if(p_source!=NULL)delete p_source;
    p_source=NULL;
    if(p_cible!=NULL)delete p_cible;
    p_cible=NULL;
    if(p_logger!=NULL)delete p_logger;
    p_logger=NULL;
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
            if( (StateSource == READED) && (StateCible == READED)  ) break;
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
            if( (StateSource == COMPARED) && (StateCible == COMPARED)  ) break;
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
     StateSource     = READING;     
     p_source->parcourir();
     StateSource     = READED;
     printf("Thread(%li)-Lecture source : FIN \n",GetCurrentThreadId());   
} 

/***********************************************
* lecture arborescence cible
************************************************/
void c_synch::LireCible( )
{ 
     printf("Thread(%li)-Lecture cible DEBUT\n",GetCurrentThreadId());
     StateCible     = READING;     
     p_cible->parcourir();
     StateCible     = READED;
     printf("Thread(%li)-Lecture cible FIN\n",GetCurrentThreadId());
} 

/***********************************************
* statut des objets
************************************************/
void c_synch::ThreadStatus( )
{
/*long nb_fic,nb_fold;
     nb_fic=0;
     nb_fold=0;
     if(p_source != NULL) p_source->get_status(&nb_fold,&nb_fic);
     printf("Thread(%li)-Etat source %li dossier / %li fichiers\n",GetCurrentThreadId(),nb_fold,nb_fic);   
     nb_fic=0;
     nb_fold=0;
     if(p_cible != NULL) p_cible->get_status(&nb_fold,&nb_fic);
     printf("Thread(%li)-Etat cible %li dossier / %li fichiers\n",GetCurrentThreadId(),nb_fold,nb_fic);   */
     if(p_source != NULL) p_source->get_status();
     if(p_cible != NULL)  p_cible->get_status();
}

/***********************************************
* recherche des fichier manquant en destination
************************************************/
void c_synch::EnMoins( )
{
     printf("Thread(%li)-Recherche fichiers manquants/modifiés DEBUT\n",GetCurrentThreadId());   
     StateSource     = COMPARING;     
     p_source->fic_en_moins(p_cible);
     StateSource     = COMPARED;
     printf("Thread(%li)-Recherche fichiers manquants/modifiés FIN\n",GetCurrentThreadId());        
}

/***********************************************
* recherche des fichier en destination
* ne devant plus y être
************************************************/
void c_synch::EnTrop( )
{
     printf("Thread(%li)-Recherche fichiers en trop DEBUT\n",GetCurrentThreadId());    
     StateCible     = COMPARING;     
     p_cible->fic_en_trop(p_source);
     StateCible     = COMPARED;     
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
