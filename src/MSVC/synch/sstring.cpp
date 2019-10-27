/***************************************************
****************************************************
** **
** **
** entête classe "sString" **
** **
** Thomas John **
** thomas.john@open-design.be **
** **
** http://www.open-design.be **
** **
****************************************************
***************************************************/
#include <stdio.h>
class sString
{

    // les données "privées" (variables, fonctions...)
    private:
    
        char * buffer; //le "buffer" qui va contenir la chaîne de caracères
        long len_tmp; //longueur de la chaîne
    
    
    // les données publiques
    public:
    
        sString(); //le constructeur par défaut lorsqu'il ne contient rien
        sString(const char a); //le constructeur lorsqu'il contient une donnée de type "char"
        sString(const char * a); //le constructeur lorsqu'il contient un pointeur vers un type de donnée "char"
        ~sString(); //le destructeur
        
        char operator [](int pointeur); //opérateur d'accès
        
        void operator =(const char * a); //opérateur d'assignement d'un pointeur de type "char"
        void operator =(const char &a); //opérateur d'assignement d'un caractère de type "char"
        void operator =(const sString &a); //opérateur d'assignement d'une autre variable de type "sString"
        
        friend sString operator +(const sString a , const sString b); //opérateur de concaténation
        void operator +=(const sString a); //opérateur de concaténation (ajoute une chaîne juste après celle-ci)
        
        //operator char(); //opérateur de convertion vers un type de donnée "char"
        operator char*(); //opérateur de convertion vers un pointeur de type "char"
        operator char*() const; //opérateur de convertion vers un pointeur de type "char"
        
        long Len(); //retourne la longueur de la chaîne
        int to_Int(); //converti la valeur du buffer en int


};



//
// 
// CONSTRUCTEURS 
// 

//constructeur par défaut
sString::sString()
{
    
    //on alloue un buffer de taille 1
    buffer = new char[1];
    
    //on spécifie la taille de cette chaîne
    len_tmp = 0;
    
    //on insère le caractère null qui spécifie la fin de la chaîne de caractères
    buffer[0] = '\0';

}

//constructeur lorsqu'il contient une donnée de type "char"
sString::sString(const char a)
{

    //on alloue un buffer de taille 2
    buffer = new char[2];
    
    //on spécifie la taille de cette chaîne
    len_tmp = 1;
    
    //on place le caractère qui a été spécifié en tant que "a"
    buffer[0] = a;
    
    //on insère le caractère null qui spécifie la fin de la chaîne de caractères
    buffer[1] = '\0';

}

//constructeur lorsqu'il contient un pointeur vers un type de donnée "char"
sString::sString(const char * a)
{

    int i = 0;
    
    //taille de la chaîne de caractères donnée en argument
    len_tmp = 0;
    
    //on incrémente notre pointeur "a" (ainsi que "len_tmp") jusqu'à ce qu'il arrive à la fin, de ce fait "len_tmp"
    //est égale à la taille de la chaîne de caractères vers laquelle pointe notre pointeur "a"
    while(*a)
    {
    a++;
    len_tmp++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_tmp;
    
    //la taille de notre buffer équivaut à celle de la chaîne de caractères donnée en argument (+ 1 pour le caractère null)
    buffer = new char[len_tmp + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
    buffer[i] = a[i];
    
    //on place le caractère de fin (null)
    buffer[len_tmp] = '\0';

}

//
// 
// DESTRUCTEUR 
// 

//destructeur par défaut
sString::~sString()
{
//delete [] buffer;
}

//
// 
// FONCTIONS 
// 

//retourne la longeur de la chaîne
long sString::Len()
{

     return len_tmp;

}

//converti la valeur du buffer en int
int sString::to_Int()
{

    int tmp_int=0; //la variable temporaire qui va contenir la valeur de la variable à convertir
    int i; //variable d'incrémentation
    int i2; //variable d'incrémentation
    int i3; //variable d'incrémentation
    int multi_sz; //multiplicateur
    
    
    for(i2=0 , i=len_tmp-1 ; i>=0 ; i-- , i2++)
    {
    
    //on remet à 1 notre multiplicateur
    multi_sz = 1;
    
    //on calcule le multiplicateur
    for(i3=0 ; i3<i2 ; i3++)
        multi_sz *= 10;
    
    //méthode plus rapide, le problème est que si les caractères ne sont pas des chiffres, il peut se produire une erreur
    if( int(buffer[i]) == 45 )
    {
        tmp_int = -tmp_int;
        return tmp_int; //on retourne la valeur directement car le signe "-" se trouve toujours à la fin
    }
    
    tmp_int += ( int(buffer[i]) - 48 ) * multi_sz;
    
    /* méthode moins rapide mais plus simple à comprendre et surtout évite certaines erreurs
    switch( int(buffer[i]) )
    {
    
        case 45: //signe -
            tmp_int = -tmp_int;
            return tmp_int; //on retourne la valeur directement car le signe "-" se trouve toujours à la fin
        
        case 49: //1
            tmp_int += 1 * multi_sz;
            break;
        
        case 50: //2
            tmp_int += 2 * multi_sz;
            break;
        
        case 51: //3
            tmp_int += 3 * multi_sz;
            break;
        
        case 52: //4
            tmp_int += 4 * multi_sz;
            break;
        
        case 53: //5
            tmp_int += 5 * multi_sz;
            break;
        
        case 54: //6
            tmp_int += 6 * multi_sz;
            break;
        
        case 55: //7
            tmp_int += 7 * multi_sz;
            break;
        
        case 56: //8
            tmp_int += 8 * multi_sz;
            break;
        
        case 57: //9
            tmp_int += 9 * multi_sz;
            break;
    
    }
    */
    
    }
    
    return tmp_int;

}

//
// 
// OPERATEURS 
// 

//opérateur d'accès
char sString::operator [](int pointeur)
{
    //on retourne le caractère pointé par "pointeur" dans "buffer"
    return buffer[pointeur];

}

//opérateur d'assignement d'un pointeur de type "char" (ex: sString c = "toto";)
void sString::operator =(const char * a)
{

    int i = 0;
    
    //taille de la chaîne de caractères donnée en argument
    len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_tmp;
    
    //on supprime les données contenues dans le "buffer"
    delete [] buffer;
    
    //on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
    buffer = new char[len_tmp + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
        buffer[i] = a[i];
    
    //on place le caractère de fin (null)
    buffer[len_tmp] = '\0';

}

//opérateur d'assignement d'un caractère de type "char"
void sString::operator =(const char &a)
{

    //on supprime les données contenues dans le "buffer"
    delete [] buffer;
    
    //on alloue un buffer de taille 2
    buffer = new char[2];
    
    //on spécifie la taille de cette chaîne
    len_tmp = 1;
    
    //on place le caractère qui a été spécifié en tant que "a"
    buffer[0] = a;
    
    //on insère le caractère null qui spécifie la fin de la chaîne de caractères
    buffer[1] = '\0';
}

//opérateur d'assignement d'une autre variable de type "sString" (ex: sString c,d; c = d;)
void sString::operator =(const sString &a)
{
    //taille de la chaîne de caractères donnée en argument
    len_tmp = a.len_tmp;
    
    //on supprime les données contenues dans le "buffer"
    delete [] buffer;
    
    //on copie les donées dans le buffer
    buffer = a.buffer;

}

//opérateur de concaténation
sString operator +(const sString a , const sString b)
{

    /*
    int i = 0 , i2 = 0;
    long len_sz = 0;
    
    //taille des deux chaînes additionnées
    len_sz = a.len_tmp + b.len_tmp;
    
    //on crée une nouvelle chaîne temporaire de type "sString" et de longueur len_sz + 1 (pour le caractère null)
    sString Resultat;
    if(Resultat.buffer)
    delete[] Resultat.buffer;
    Resultat.buffer = new char[len_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < a.len_tmp ; i++)
    Resultat.buffer[i] = a.buffer[i];
    
    //ensuite on copie la chaîne "b" à la suite
    for (i2=0 ; i < len_sz ; i++ , i2++)
    Resultat.buffer[i] = b.buffer[i2];
    
    //on place le caractère de fin (null)
    Resultat.buffer[len_sz] = '\0';
    
    //on retourne la chaîne
    return Resultat;
    */
    
    int i = 0 , i2 = 0;
    long len_sz = 0;
    char * buffer_sz;
    
    //taille des deux chaînes additionnées
    len_sz = a.len_tmp + b.len_tmp;
    
    //on alloue un buffer de la taille des deux chaînes aditionnées
    buffer_sz = new char[len_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < a.len_tmp ; i++)
        buffer_sz[i] = a.buffer[i];
    
    //ensuite on copie la chaîne "b" à la suite
    for (i2=0 ; i < len_sz ; i++)
    {
        buffer_sz[i] = b.buffer[i2];
        i2++;
    }
    
    //on place le caractère de fin (null)
    buffer_sz[len_sz] = '\0';
    
    //on crée une nouvelle chaîne temporaire de type "sString"
    sString Resultat = buffer_sz;
    
    //on libère la mémoire
    delete [] buffer_sz;
    
    //on retourne la chaîne
    return Resultat;
    

}

//opérateur de concaténation, il permet d'ajouter une chaîne directement après celle-ci
void sString::operator +=(const sString a)
{

    int i = 0 , i2 = 0;
    long len_sz = 0;
    char * buffer_sz = new char[len_tmp];
    
    //taille des deux chaînes additionnées
    len_sz = len_tmp + a.len_tmp;
    
    //on copie le buffer de la variable "locale" (pas celui de "a")
    for (i=0; i <= len_tmp ; i++)
    buffer_sz[i] = buffer[i];
    
    //on supprime les données contenues dans le "buffer"
    delete [] buffer;
    
    //on défini la taille du buffer
    buffer = new char[len_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
        buffer[i] = buffer_sz[i];
    
    //ensuite on copie la chaîne "b" à la suite
    for (i2=0 ; i < len_sz ; i++)
    {
        buffer[i] = a.buffer[i2];
        i2++;
    }
    
    //on place le caractère de fin (null)
    buffer[len_sz] = '\0';
    
    //on spécifie la taille de la nouvelle chaîne
    len_tmp = len_sz;

}
/*
//opérateur de convertion vers un type de donnée "char"
sString::operator char()
{

return buffer[0];

}
*/
//opérateur de convertion vers un pointeur de type "char"
sString::operator char*()
{

 return buffer;

}

//opérateur de convertion vers un pointeur de type "char"
sString::operator char*() const
{

 return buffer;

}

//
// 
// FONCTIONS 
// INDEPENDANTES 
// DE LA CLASSE 
// 

//les fonctions prennant comme arguments des variables de type "sString" ont été supprimées étant donné
//que le type "sString" fait automatiquement la conversion en "*char" lorsque nécessaire

//char * sLeft(sString a , int longueur_sz); //renvoie les "n" premiers caractères d'une chaîne
char* sLeft(char * a , int longueur_sz); //renvoie les "n" premiers caractères d'une chaîne

//char* sRight(sString a , int longueur_sz); //renvoie les "n" derniers caractères d'une chaîne (rem: voir sLeft)
char* sRight(char * a , int longueur_sz); //renvoie les "n" derniers caractères d'une chaîne

//char* sMid(sString a , int depart_sz , int longueur_sz); //renvoie une chaîne de longueur "longueur_sz" commençant au caractère déterminé par "depart_sz" (rem: voir sLeft)
char* sMid(char * a , int depart_sz , int longueur_sz); //renvoie une chaîne de longueur "longueur_sz" commençant au caractère déterminé par "depart_sz"

//bool sCompare(sString a , sString b); //compare les deux chaînes de caractères "a" et "b" et renvoie "true" si elles concordent
bool sCompare(char * a , char * b); //compare les deux chaînes de caractères "a" et "b" et renvoie "true" si elles concordent

//int sStrPos(sString a , sString b , int depart_sz); //renvoie la position du premier caractère de "b" trouvé dans "a"
int sStrPos(char * a , char * b , int depart_sz); //renvoie la position du premier caractère de "b" trouvé dans "a"

//char** sSplit(sString a , sString b , int limite_sz); //découpe la chaîne "a" en plusieurs morceaux séparés par "b", "limite_sz" est le nombre de morceaux max à retourner (-1 = max)
/*
//renvoie les "n" premiers caractères d'une chaîne
char * sLeft(sString a , int longueur_sz)
{

//on vérifie si la longueur spécifiée est supérieur à zéro
if( longueur_sz <= 0 )
return ""; //non, on ne retourne rien

int i = 0;

//on vérifie si la longueur demandée n'est pas supérieure ou égale à celle de la chaîne "a"
if( longueur_sz >= a.Len() )
return a; //oui, on retourne la chaîne telle qu'elle était

//on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
char * buffer_tmp = new char[longueur_sz + 1];

//variable qui va contenir la chaîne de caractères de "a"
char * tmp_a = a;

//on copie la chaîne "a" vers le buffer
for (i=0; i < longueur_sz ; i++)
buffer_tmp[i] = tmp_a[i];

//on place le caractère de fin (null)
buffer_tmp[longueur_sz] = '\0';

//et on retourne le résultat final
return buffer_tmp;

}
*/
//renvoie les "n" premiers caractères d'une chaîne
char * sLeft(char * a , int longueur_sz)
{

    //on vérifie si la longueur spécifiée est supérieur à zéro
    if( longueur_sz <= 0 )
        return ""; //non, on ne retourne rien
    
    int i = 0;
    
    //taille de la chaîne de caractères donnée en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_tmp;
    
    //on vérifie si la longueur demandée n'est pas supérieure ou égale à celle de la chaîne "a"
    if( longueur_sz >= len_tmp )
        return a; //oui, on retourne la chaîne telle qu'elle était
    
    //on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=0; i < longueur_sz ; i++)
        buffer_tmp[i] = a[i];
    
    //on place le caractère de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le résultat final
    return buffer_tmp;

}
/*
//renvoie les "n" derniers caractères d'une chaîne
char * sRight(sString a , int longueur_sz)
{

//on vérifie si la longueur spécifiée est supérieur à zéro
if( longueur_sz <= 0 )
return ""; //non, on ne retourne rien

int i = 0 , i2 = 0;

//on vérifie si la longueur demandée n'est pas supérieure ou égale à celle de la chaîne "a"
if( longueur_sz >= a.Len() )
return a; //oui, on retourne la chaîne telle qu'elle était

//on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
char * buffer_tmp = new char[longueur_sz + 1];

//variable qui va contenir la chaîne de caractères de "a"
char * tmp_a = a;

//on copie la chaîne "a" vers le buffer
for (i=(a.Len() - longueur_sz) ; i < a.Len() ; i++)
{
buffer_tmp[i2] = tmp_a[i];
i2++;
}

//on place le caractère de fin (null)
buffer_tmp[longueur_sz] = '\0';

//et on retourne le résultat final
return buffer_tmp;

}
*/
//renvoie les "n" derniers caractères d'une chaîne
char * sRight(char * a , int longueur_sz)
{

    //on vérifie si la longueur spécifiée est supérieur à zéro
    if( longueur_sz <= 0 )
        return ""; //non, on ne retourne rien
    
    int i = 0 , i2 = 0;
    
    //taille de la chaîne de caractères donnée en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_tmp;
    
    //on vérifie si la longueur demandée n'est pas supérieure ou égale à celle de la chaîne "a"
    if( longueur_sz >= len_tmp )
        return a; //oui, on retourne la chaîne telle qu'elle était
    
    //on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=(len_tmp - longueur_sz) ; i < len_tmp ; i++)
    {
        buffer_tmp[i2] = a[i];
        i2++;
    }
    
    //on place le caractère de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le résultat final
    return buffer_tmp;

}

//renvoie une chaîne de longueur "longueur_sz" commençant au caractère déterminé par "depart_sz"
char * sMid(sString a , int depart_sz , int longueur_sz)
{

    int i = 0 , i2 = 0;
    
    //on vérifie si on ne dépasse pas la taille de la chaîne
    if( (depart_sz + longueur_sz + 1) > a.Len() )
    longueur_sz = a.Len() - depart_sz; //on respécifie la longueur de la chaîne à retourner
    
    //on vérifie si la longueur de la chaîne est supérieur à zéro
    if( longueur_sz < 0 )
        return ""; //non, on ne retourne rien
    
    //on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //variable qui va contenir la chaîne de caractères de "a"
    char * tmp_a = a;
    
    //on copie la chaîne "a" vers le buffer
    for (i=(depart_sz) ; i < (depart_sz + longueur_sz) ; i++)
    {
        buffer_tmp[i2] = tmp_a[i];
        i2++;
    }
    
    //on place le caractère de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le résultat final
    return buffer_tmp;

}

//renvoie une chaîne de longueur "longueur_sz" commençant au caractère déterminé par "depart_sz"
char * sMid(char * a , int depart_sz , int longueur_sz)
{

    int i = 0 , i2 = 0;
    
    //taille de la chaîne de caractères donnée en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_tmp;
    
    //on vérifie si on ne dépasse pas la taille de la chaîne
    if( (depart_sz + longueur_sz + 1) > len_tmp )
        longueur_sz = len_tmp - depart_sz; //on respécifie la longueur de la chaîne à retourner
    
    //on vérifie si la longueur de la chaîne est supérieur à zéro
    if( longueur_sz < 0 )
        return ""; //non, on ne retourne rien
    
    //on alloue un buffer de la taille de la chaîne de caractères donnée en argument + 1 pour le caractère null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la chaîne "a" vers le buffer
    for (i=(depart_sz) ; i < (depart_sz + longueur_sz) ; i++)
    {
        buffer_tmp[i2] = a[i];
        i2++;
    }
    
    //on place le caractère de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le résultat final
    return buffer_tmp;

}
/*
//compare les deux chaînes de caractères "a" et "b" et renvoie "true" si elles concordent
bool sCompare(sString a , sString b)
{

//on vérifie d'abords si la longueur des deux chaîne est la même
if( a.Len() != b.Len() )
return false;

//on récupère sous forme "char" "a" et "b"
char * tmp_a = new char[a.Len()] = a;
char * tmp_b = new char[b.Len()] = b;

//on compare chaque caractère correspondant
for( int i=0 ; i<=a.Len() ; i++ )
{

if(tmp_a[i] != tmp_b[i])
return false;

}

//si on arrive jusqu'ici, c'est que les deux chaînes sont identiques
return true;

}
*/
//compare les deux chaînes de caractères "a" et "b" et renvoie "true" si elles concordent
bool sCompare(char * a , char * b)
{

    //taille de la chaîne de caractères donnée en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_a;
    
    //taille de la chaîne de caractères donnée en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur à zéro
    b -= len_b;
    
    //on vérifie d'abords si la longueur des deux chaîne est la même
    if( len_a != len_b )
        return false;
    
    //on compare chaque caractère correspondant
    for( int i=0 ; i<=len_a ; i++ )
    {
    
        if(a[i] != b[i])
            return false;   

    }

    //si on arrive jusqu'ici, c'est que les deux chaînes sont identiques
    return true;

}
/*
//renvoie la position du premier caractère de la chaîne "b" trouvée dans "a"
int sStrPos(sString a , sString b , int depart_sz = 0)
{

//on vérifie si la taille de la chaîne à chercher n'est pas plus grande que la chaîne dans laquelle il faut chercher
if( (b.Len() + depart_sz) > a.Len() )
return -1;

//on calcule le nombre d'itérations à effectuer
int iterations_sz = a.Len() - (b.Len() + depart_sz);

//on fait une boucle
for(int i=depart_sz ; i <= iterations_sz ; i++ )
{

//on vérifie si la chaîne de caractères (dans "b") de même taille que "a" et commençant au caractère "i" n'est pas = à "a"
if( sCompare(sMid(a , i , b.Len()) , b) )
return i;

}

//si on arrive ici, c'est qu'on a rien trouvé
return -1;

}
*/
//renvoie la position du premier caractère de la chaîne "b" trouvée dans "a"
int sStrPos(char * a , char * b , int depart_sz = 0)
{

    int i2=0;
    
    //taille de la chaîne de caractères donnée en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_a;
    
    //taille de la chaîne de caractères donnée en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur à zéro
    b -= len_b;
    
    //on vérifie si la taille de la chaîne à chercher n'est pas plus grande que la chaîne dans laquelle il faut chercher
    if( (len_b + depart_sz) > len_a )
        return -1;
    
    //on calcule le nombre d'itérations à effectuer
    int iterations_sz = len_a - (len_b + depart_sz);
    
    //on fait une boucle
    for(int i=depart_sz ; i2 <= iterations_sz ; i++ )
    {
    
        //on vérifie si la chaîne de caractères (dans "b") de même taille que "a" et commençant au caractère "i" n'est pas = à "a"
        if( sCompare(sMid(a , i ,len_b) , b) )
        return i;
        
        i2++;
    
    }
    
    //si on arrive ici, c'est qu'on a rien trouvé
    return -1;

}


//découpe la chaîne "a" en plusieurs morceaux séparés par "b", "limite_sz" est le nombre de morceaux max à retourner (-1 = max)
sString * sSplit(char * a , char * b , int limite_sz , int &taille_finale)
{

    int i=0 , pos=-1 , pos2=0 ;
    sString * tmp_res;
    
    //taille de la chaîne de caractères donnée en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur à zéro
    a -= len_a;
    
    //taille de la chaîne de caractères donnée en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur à zéro
    b -= len_b;
    
    //on parcourt la chaîne "a" à la recherche de "b" autant de fois que "b" s'y trouve
    do
    {
        pos = sStrPos(a , b , pos + 1);
        i++;
    
    }while(pos > 0);
    
    //si la limite est à zéro on renvoie un tableau avec une seule valeur
    if(limite_sz == 0)
    {
    //on quitte ici
        tmp_res = new sString[0];
        tmp_res[0] = "";
        return tmp_res;
    
    //si une limite est spécifiée, on vérifie s'il faut en tenir compte
    }else if(limite_sz > 0){
    
        if(i > limite_sz)
        {
                i = limite_sz;
        }
    
    }
    
    //on spécifie le nombre de résultats que le tableau va contenir
    taille_finale = i;
    
    //on crée un tableau de type "sString" de la taille indiquée par "i"
    tmp_res = new sString[i];
    
    //on décrémente i
    i--;
    
    //on remet la position de départ à -1 (on y ajoute 1 par la suite à chaque itérations de la boucle for)
    pos = -1;
    
    //pos2 commence lui à zéro et va prendre la valeur de pos avant que celui-ci ne change
    pos2 = 0;
    
    int i2;
    
    for(int i2=0 ; i2<i ; i2++ )
    {
    
        //on récupère la position de la première occurence de la chaîne "b" dans la chaîne "a"
        pos = sStrPos(a , b , pos + 1);
        
        //on récupère la chaîne de caractères située entre "pos2" et "pos" et on la place dans notre tableau
        tmp_res[i2] = sMid(a , pos2 , pos-pos2);
        
        pos2 = pos + len_b;
    
    }
    
    //on récupère la fin de la chaîne
    tmp_res[i2] = sMid(a , pos2 , len_a-pos2);
    
    return tmp_res;

} 
