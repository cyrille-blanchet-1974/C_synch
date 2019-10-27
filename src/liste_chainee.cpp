#include "fichier.h"
#include "liste_chainee.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>

// class constructor
c_liste_chainee::c_liste_chainee()
{
    p_tete = NULL;
    p_queue = NULL;               
    p_courant = NULL;
    p_dernier_trouve=NULL;
    count=0;
    nb_strcmp=0;
    nb_strcmp_init=0;
}                

int c_liste_chainee::ajouter(c_fichier *fichier)
{
    c_maillon *p_maillon;
    //on cr�� le nouveau maillon et on l'ajoute � la liste
    p_maillon = new c_maillon(fichier);
    if(p_tete == NULL)
    {
        //pas encore de maillon?
        p_tete=p_maillon;
    }
    else
    {
        //sinon on ajoute le maillon en fin de chaine
        p_queue->p_suivant=p_maillon;
        p_maillon->p_precedent=p_queue;
    }
    //le maillon ajout� est la nouvelle queue
    p_queue=p_maillon;
    count++;
    return 0;
}

int c_liste_chainee::ajouter_trier(c_fichier *fichier)
{
    c_maillon *p_maillon;
    c_maillon *p_maillon2;
    bool trouve = false;
    //char *chainecourante = "\\a garder\\documents\\achats possibles\\2,5 dans 5,25_files\\bd_data_002\\flashwrite_1_2.js" ;
    //char *chainecherchee = "\\a garder\\documents\\achats possibles\\2,5 dans 5,25_files\\bd_data_002\\SAM_CMOS_120X600_30k_3.swf";
   

    //on cr�� le nouveau maillon et on l'ajoute � la liste
    p_maillon = new c_maillon(fichier);
    if(p_tete == NULL)
    {
        //pas encore de maillon?
        p_tete=p_maillon;
        //le maillon ajout� est la nouvelle queue
        p_queue=p_maillon;
        //printf("premier maillon %s \n",p_maillon->cle);
    }
    else
    {
        //sinon on cherche le premier maillon < � cette cl�e en commencant par la fin (il est tr�s probable que les cl� arrive tri�e
        p_maillon2 = p_queue;
        trouve = false;
        while(trouve==false)
        {
            //pas de maillon -> on stop          
            if(p_maillon2 == NULL) 
            {
              trouve = true;
            }
            else
            {
              //sinon on compare avec le maillon a inserer  
              //if(strcmp(p_maillon->cle,chainecherchee)==0)printf("comparaison %s %s %li \n",p_maillon->cle ,p_maillon2->cle,strcmp(p_maillon->cle ,p_maillon2->cle));
              //if(strcmp(p_maillon->cle,chainecourante)==0)printf("comparaison %s %s %li \n",p_maillon->cle ,p_maillon2->cle,strcmp(p_maillon->cle ,p_maillon2->cle));
              nb_strcmp_init++;
              if ((strcmp(p_maillon->cle ,p_maillon2->cle) >0) )
              {
                  //si maillon a inserer plus grand  alors on a trouv�                     
                  trouve=true;                  
              }
              else
              {
                  //sinon on avance (a reculon)
                  p_maillon2 = p_maillon2->p_precedent;             
              }       
            }         
        }
        //while( (p_maillon2 != NULL) && (strcmp(p_maillon->cle ,p_maillon2->cle) >0) )p_maillon2 = p_maillon2->p_precedent;
        //si on a trouv� un maillon <=
        //on ins�re juste avant.
        if (p_maillon2 != NULL)
        {
            if(p_maillon2 == p_queue)
            {
               //le premier maillon inf�rieur est la queue alors
               //le nouveau maillon est la queue
               p_queue->p_suivant=p_maillon;
               p_maillon->p_precedent=p_queue;
               //le maillon ajout� est la nouvelle queue
               p_queue=p_maillon;
              // if(strcmp(p_maillon->cle,chainecherchee)==0)printf("Ajout queue %s \n",p_maillon->cle);
               //if(strcmp(p_maillon->cle,chainecourante)==0)printf("Ajout queue %s \n",p_maillon->cle);

               //printf("Ajout queue %s \n",p_maillon->cle);
            }            
            else
            {
                //on insere le p_maillon apr�s p_maillon2
                //le pr�c�dent de maillon est maillon2
                p_maillon->p_precedent=p_maillon2;
                //le suivant de maillon est le suivant de maillon2
                p_maillon->p_suivant=p_maillon2->p_suivant;
                //le suivant de maillon2 est maillon
                p_maillon2->p_suivant=p_maillon;
                //indiquer dans l'ancien suivant de maillon2 que son pr�c�dent est maillon
                p_maillon->p_suivant->p_precedent=p_maillon;
                //if(strcmp(p_maillon->cle,chainecherchee)==0)printf("ajout centre %s \n",p_maillon->cle);
                //if(strcmp(p_maillon->cle,chainecourante)==0)printf("ajout centre %s \n",p_maillon->cle);

                //printf("ajout centre %s \n",p_maillon->cle);
            }
                                    
        }
        else
        {
            //sinon on ajoute le maillon en t�te
            p_tete->p_precedent=p_maillon;
            p_maillon->p_suivant=p_tete;
            //le maillon ajout� est la nouvelle tete
            p_tete=p_maillon;
            //if(strcmp(p_maillon->cle,chainecherchee)==0)printf("Ajout tete %s \n",p_maillon->cle);
            //if(strcmp(p_maillon->cle,chainecourante)==0)printf("Ajout tete %s \n",p_maillon->cle);
            //printf("Ajout tete %s \n",p_maillon->cle);
        }               
    }
    count++;
    return 0;
}

c_fichier* c_liste_chainee::chercher(char *cle)
{
    c_maillon *p_maillon;
    c_fichier *sortie;
    bool trouvee=false;
    
    sortie=NULL;
    p_maillon=p_tete;
	do
	{
              nb_strcmp++;                         
              if(strcmp(cle , p_maillon->cle)==0)
              {
                      trouvee = true;
                      sortie=p_maillon->data;
              }
              else
              {                      
                  //maillon suivant
                  p_maillon=p_maillon->p_suivant;
                  }                     
    }while(	!trouvee && p_maillon!=NULL);//on stoppe sur le dernier
    return sortie;
      
}
		
// class destructor
c_liste_chainee::~c_liste_chainee()
{
	//liberer les maillon
	c_maillon *p_maillon;
	do
	{
              //sauve la suite de la tete 
              p_maillon=p_tete->p_suivant;
              //efface la tete
              delete p_tete;
              //nouvelle tete= suivant
              p_tete=p_maillon;
                     
    }while(	p_maillon != NULL);//on stoppe sur le dernier
    //RAZ de tous les pointeurs
    p_maillon=NULL;
    p_tete=NULL;
    p_queue=NULL;	
    printf("nombre d'�l�ments : %li\n",count);
    printf("nombre d'appel � strcmp en recherche : %li\n",nb_strcmp);
    printf("nombre d'appel � strcmp pendant l'init : %li\n",nb_strcmp_init);
}

char* c_liste_chainee::get_next(bool restart)
{
      if(restart) 
      {
          p_courant=p_tete;
      }
      else
      {
          p_courant=p_courant->p_suivant;
      }
      if(p_courant == NULL) return NULL;
      return p_courant->cle;      
}

c_fichier* c_liste_chainee::chercher_trie(char *cle)
{
    c_maillon *p_maillon;
    c_fichier *sortie;
    bool trouvee=false;
    long cmp;
    
    //si on n'a rien encore trouv� on commence en t�te
    if(p_dernier_trouve==NULL) 
    {
       p_maillon=p_tete;
    }
    else
    {
        p_maillon=p_dernier_trouve;
    }

    sortie=NULL;
    //d�terminer le sens de la recherche...
    cmp=strcmp(p_maillon->cle,cle);
    nb_strcmp++; 
   // printf("d�but de la fonction \nchaine courante:%s \nchainecherch�e:%s r:%li\n",p_maillon->cle,cle,cmp);
    if (cmp <0)
    {
        //le dernier trouv� est plus petit que celui cherch�
        // on cherche en allans vers la fin
        //printf("Recherche vers la fin\n");   
    	do
    	{
                  nb_strcmp++;         
                  //on compare
                  cmp = strcmp(p_maillon->cle,cle);
                  //printf("Recherche en avan�ant \nchaine courante:%s \nchainecherch�e:%s r:%li\n",p_maillon->cle,cle,cmp);
                  if(cmp==0)
                  {
                    //trouv�         
                    trouvee = true;
                    sortie=p_maillon->data;
                     //printf("Trouv�\n");
                  }
                  else
                  {    
                      if(cmp>0)                   
                      {
                         //on est trop loin
                         trouvee = true;                         
                         //printf("Trop loin\n");
                      }
                      else
                      {
                         //maillon suivant       
                         p_maillon=p_maillon->p_suivant;
                         // printf("suivant\n");
                      }

                  }                     
        }while(	!trouvee && p_maillon!=NULL);//on stoppe sur le dernier ou si on trouve                                                
    }
    else
    {
        //le dernier trouv� est plus grand ou �gale  que celui cherch�
        if(cmp==0)
        { 
           //coup de bol on est tomb� pil...
           sortie=p_maillon->data;
           trouvee = true;
        //   printf("Coup de bol:trouv�\n");
        }
        else
        {
            // on cherche en allans vers la d�but
        //    printf("Recherche en revenant vers le d�but\n");   
        	do
        	{
                      nb_strcmp++;      
                      //on compare
                      cmp = strcmp(p_maillon->cle,cle);
                   //   printf("Recherche a reculons \nchaine courante:%s \nchainecherch�e:%s r:%li\n",p_maillon->cle,cle,cmp);
                      if(cmp==0)
                      {
                        //trouv�         
                        trouvee = true;
                        sortie=p_maillon->data;
                    //    printf("Trouv�\n");
                      }
                      else
                      {    
                          if(cmp<0)                   
                          {
                             //on est trop loin
                             trouvee = true;                         
                        //     printf("Trop loin\n");
                          }
                          else
                          {
                             //maillon suivant       
                             p_maillon=p_maillon->p_precedent;
                        //     printf("Pr�c�dent\n");
                          }
    
                      }                     
            }while(	!trouvee && p_maillon!=NULL);//on stoppe sur le dernier ou si on trouve
        }
    }
  //  printf("Fin de la recherche\n\n\n");
    //si on a trouv� le garder en m�mmoire
    if (sortie != NULL)  p_dernier_trouve=p_maillon;
    return sortie;
}

void c_liste_chainee::afficher()
{
	c_maillon *p_maillon;
	p_maillon=p_tete;
	do
	{
         printf("%s \n",p_maillon->cle);            
         p_maillon=p_maillon->p_suivant;
                     
    }while(	p_maillon != NULL);//on stoppe sur le dernier
}
