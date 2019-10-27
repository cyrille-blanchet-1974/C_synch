/***************************************************
****************************************************
** **
** **
** ent�te classe "sString" **
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

    // les donn�es "priv�es" (variables, fonctions...)
    private:
    
        char * buffer; //le "buffer" qui va contenir la cha�ne de carac�res
        long len_tmp; //longueur de la cha�ne
    
    
    // les donn�es publiques
    public:
    
        sString(); //le constructeur par d�faut lorsqu'il ne contient rien
        sString(const char a); //le constructeur lorsqu'il contient une donn�e de type "char"
        sString(const char * a); //le constructeur lorsqu'il contient un pointeur vers un type de donn�e "char"
        ~sString(); //le destructeur
        
        char operator [](int pointeur); //op�rateur d'acc�s
        
        void operator =(const char * a); //op�rateur d'assignement d'un pointeur de type "char"
        void operator =(const char &a); //op�rateur d'assignement d'un caract�re de type "char"
        void operator =(const sString &a); //op�rateur d'assignement d'une autre variable de type "sString"
        
        friend sString operator +(const sString a , const sString b); //op�rateur de concat�nation
        void operator +=(const sString a); //op�rateur de concat�nation (ajoute une cha�ne juste apr�s celle-ci)
        
        //operator char(); //op�rateur de convertion vers un type de donn�e "char"
        operator char*(); //op�rateur de convertion vers un pointeur de type "char"
        operator char*() const; //op�rateur de convertion vers un pointeur de type "char"
        
        long Len(); //retourne la longueur de la cha�ne
        int to_Int(); //converti la valeur du buffer en int


};



//
// 
// CONSTRUCTEURS 
// 

//constructeur par d�faut
sString::sString()
{
    
    //on alloue un buffer de taille 1
    buffer = new char[1];
    
    //on sp�cifie la taille de cette cha�ne
    len_tmp = 0;
    
    //on ins�re le caract�re null qui sp�cifie la fin de la cha�ne de caract�res
    buffer[0] = '\0';

}

//constructeur lorsqu'il contient une donn�e de type "char"
sString::sString(const char a)
{

    //on alloue un buffer de taille 2
    buffer = new char[2];
    
    //on sp�cifie la taille de cette cha�ne
    len_tmp = 1;
    
    //on place le caract�re qui a �t� sp�cifi� en tant que "a"
    buffer[0] = a;
    
    //on ins�re le caract�re null qui sp�cifie la fin de la cha�ne de caract�res
    buffer[1] = '\0';

}

//constructeur lorsqu'il contient un pointeur vers un type de donn�e "char"
sString::sString(const char * a)
{

    int i = 0;
    
    //taille de la cha�ne de caract�res donn�e en argument
    len_tmp = 0;
    
    //on incr�mente notre pointeur "a" (ainsi que "len_tmp") jusqu'� ce qu'il arrive � la fin, de ce fait "len_tmp"
    //est �gale � la taille de la cha�ne de caract�res vers laquelle pointe notre pointeur "a"
    while(*a)
    {
    a++;
    len_tmp++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_tmp;
    
    //la taille de notre buffer �quivaut � celle de la cha�ne de caract�res donn�e en argument (+ 1 pour le caract�re null)
    buffer = new char[len_tmp + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
    buffer[i] = a[i];
    
    //on place le caract�re de fin (null)
    buffer[len_tmp] = '\0';

}

//
// 
// DESTRUCTEUR 
// 

//destructeur par d�faut
sString::~sString()
{
//delete [] buffer;
}

//
// 
// FONCTIONS 
// 

//retourne la longeur de la cha�ne
long sString::Len()
{

     return len_tmp;

}

//converti la valeur du buffer en int
int sString::to_Int()
{

    int tmp_int=0; //la variable temporaire qui va contenir la valeur de la variable � convertir
    int i; //variable d'incr�mentation
    int i2; //variable d'incr�mentation
    int i3; //variable d'incr�mentation
    int multi_sz; //multiplicateur
    
    
    for(i2=0 , i=len_tmp-1 ; i>=0 ; i-- , i2++)
    {
    
    //on remet � 1 notre multiplicateur
    multi_sz = 1;
    
    //on calcule le multiplicateur
    for(i3=0 ; i3<i2 ; i3++)
        multi_sz *= 10;
    
    //m�thode plus rapide, le probl�me est que si les caract�res ne sont pas des chiffres, il peut se produire une erreur
    if( int(buffer[i]) == 45 )
    {
        tmp_int = -tmp_int;
        return tmp_int; //on retourne la valeur directement car le signe "-" se trouve toujours � la fin
    }
    
    tmp_int += ( int(buffer[i]) - 48 ) * multi_sz;
    
    /* m�thode moins rapide mais plus simple � comprendre et surtout �vite certaines erreurs
    switch( int(buffer[i]) )
    {
    
        case 45: //signe -
            tmp_int = -tmp_int;
            return tmp_int; //on retourne la valeur directement car le signe "-" se trouve toujours � la fin
        
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

//op�rateur d'acc�s
char sString::operator [](int pointeur)
{
    //on retourne le caract�re point� par "pointeur" dans "buffer"
    return buffer[pointeur];

}

//op�rateur d'assignement d'un pointeur de type "char" (ex: sString c = "toto";)
void sString::operator =(const char * a)
{

    int i = 0;
    
    //taille de la cha�ne de caract�res donn�e en argument
    len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_tmp;
    
    //on supprime les donn�es contenues dans le "buffer"
    delete [] buffer;
    
    //on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
    buffer = new char[len_tmp + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
        buffer[i] = a[i];
    
    //on place le caract�re de fin (null)
    buffer[len_tmp] = '\0';

}

//op�rateur d'assignement d'un caract�re de type "char"
void sString::operator =(const char &a)
{

    //on supprime les donn�es contenues dans le "buffer"
    delete [] buffer;
    
    //on alloue un buffer de taille 2
    buffer = new char[2];
    
    //on sp�cifie la taille de cette cha�ne
    len_tmp = 1;
    
    //on place le caract�re qui a �t� sp�cifi� en tant que "a"
    buffer[0] = a;
    
    //on ins�re le caract�re null qui sp�cifie la fin de la cha�ne de caract�res
    buffer[1] = '\0';
}

//op�rateur d'assignement d'une autre variable de type "sString" (ex: sString c,d; c = d;)
void sString::operator =(const sString &a)
{
    //taille de la cha�ne de caract�res donn�e en argument
    len_tmp = a.len_tmp;
    
    //on supprime les donn�es contenues dans le "buffer"
    delete [] buffer;
    
    //on copie les don�es dans le buffer
    buffer = a.buffer;

}

//op�rateur de concat�nation
sString operator +(const sString a , const sString b)
{

    /*
    int i = 0 , i2 = 0;
    long len_sz = 0;
    
    //taille des deux cha�nes additionn�es
    len_sz = a.len_tmp + b.len_tmp;
    
    //on cr�e une nouvelle cha�ne temporaire de type "sString" et de longueur len_sz + 1 (pour le caract�re null)
    sString Resultat;
    if(Resultat.buffer)
    delete[] Resultat.buffer;
    Resultat.buffer = new char[len_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < a.len_tmp ; i++)
    Resultat.buffer[i] = a.buffer[i];
    
    //ensuite on copie la cha�ne "b" � la suite
    for (i2=0 ; i < len_sz ; i++ , i2++)
    Resultat.buffer[i] = b.buffer[i2];
    
    //on place le caract�re de fin (null)
    Resultat.buffer[len_sz] = '\0';
    
    //on retourne la cha�ne
    return Resultat;
    */
    
    int i = 0 , i2 = 0;
    long len_sz = 0;
    char * buffer_sz;
    
    //taille des deux cha�nes additionn�es
    len_sz = a.len_tmp + b.len_tmp;
    
    //on alloue un buffer de la taille des deux cha�nes aditionn�es
    buffer_sz = new char[len_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < a.len_tmp ; i++)
        buffer_sz[i] = a.buffer[i];
    
    //ensuite on copie la cha�ne "b" � la suite
    for (i2=0 ; i < len_sz ; i++)
    {
        buffer_sz[i] = b.buffer[i2];
        i2++;
    }
    
    //on place le caract�re de fin (null)
    buffer_sz[len_sz] = '\0';
    
    //on cr�e une nouvelle cha�ne temporaire de type "sString"
    sString Resultat = buffer_sz;
    
    //on lib�re la m�moire
    delete [] buffer_sz;
    
    //on retourne la cha�ne
    return Resultat;
    

}

//op�rateur de concat�nation, il permet d'ajouter une cha�ne directement apr�s celle-ci
void sString::operator +=(const sString a)
{

    int i = 0 , i2 = 0;
    long len_sz = 0;
    char * buffer_sz = new char[len_tmp];
    
    //taille des deux cha�nes additionn�es
    len_sz = len_tmp + a.len_tmp;
    
    //on copie le buffer de la variable "locale" (pas celui de "a")
    for (i=0; i <= len_tmp ; i++)
    buffer_sz[i] = buffer[i];
    
    //on supprime les donn�es contenues dans le "buffer"
    delete [] buffer;
    
    //on d�fini la taille du buffer
    buffer = new char[len_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < len_tmp ; i++)
        buffer[i] = buffer_sz[i];
    
    //ensuite on copie la cha�ne "b" � la suite
    for (i2=0 ; i < len_sz ; i++)
    {
        buffer[i] = a.buffer[i2];
        i2++;
    }
    
    //on place le caract�re de fin (null)
    buffer[len_sz] = '\0';
    
    //on sp�cifie la taille de la nouvelle cha�ne
    len_tmp = len_sz;

}
/*
//op�rateur de convertion vers un type de donn�e "char"
sString::operator char()
{

return buffer[0];

}
*/
//op�rateur de convertion vers un pointeur de type "char"
sString::operator char*()
{

 return buffer;

}

//op�rateur de convertion vers un pointeur de type "char"
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

//les fonctions prennant comme arguments des variables de type "sString" ont �t� supprim�es �tant donn�
//que le type "sString" fait automatiquement la conversion en "*char" lorsque n�cessaire

//char * sLeft(sString a , int longueur_sz); //renvoie les "n" premiers caract�res d'une cha�ne
char* sLeft(char * a , int longueur_sz); //renvoie les "n" premiers caract�res d'une cha�ne

//char* sRight(sString a , int longueur_sz); //renvoie les "n" derniers caract�res d'une cha�ne (rem: voir sLeft)
char* sRight(char * a , int longueur_sz); //renvoie les "n" derniers caract�res d'une cha�ne

//char* sMid(sString a , int depart_sz , int longueur_sz); //renvoie une cha�ne de longueur "longueur_sz" commen�ant au caract�re d�termin� par "depart_sz" (rem: voir sLeft)
char* sMid(char * a , int depart_sz , int longueur_sz); //renvoie une cha�ne de longueur "longueur_sz" commen�ant au caract�re d�termin� par "depart_sz"

//bool sCompare(sString a , sString b); //compare les deux cha�nes de caract�res "a" et "b" et renvoie "true" si elles concordent
bool sCompare(char * a , char * b); //compare les deux cha�nes de caract�res "a" et "b" et renvoie "true" si elles concordent

//int sStrPos(sString a , sString b , int depart_sz); //renvoie la position du premier caract�re de "b" trouv� dans "a"
int sStrPos(char * a , char * b , int depart_sz); //renvoie la position du premier caract�re de "b" trouv� dans "a"

//char** sSplit(sString a , sString b , int limite_sz); //d�coupe la cha�ne "a" en plusieurs morceaux s�par�s par "b", "limite_sz" est le nombre de morceaux max � retourner (-1 = max)
/*
//renvoie les "n" premiers caract�res d'une cha�ne
char * sLeft(sString a , int longueur_sz)
{

//on v�rifie si la longueur sp�cifi�e est sup�rieur � z�ro
if( longueur_sz <= 0 )
return ""; //non, on ne retourne rien

int i = 0;

//on v�rifie si la longueur demand�e n'est pas sup�rieure ou �gale � celle de la cha�ne "a"
if( longueur_sz >= a.Len() )
return a; //oui, on retourne la cha�ne telle qu'elle �tait

//on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
char * buffer_tmp = new char[longueur_sz + 1];

//variable qui va contenir la cha�ne de caract�res de "a"
char * tmp_a = a;

//on copie la cha�ne "a" vers le buffer
for (i=0; i < longueur_sz ; i++)
buffer_tmp[i] = tmp_a[i];

//on place le caract�re de fin (null)
buffer_tmp[longueur_sz] = '\0';

//et on retourne le r�sultat final
return buffer_tmp;

}
*/
//renvoie les "n" premiers caract�res d'une cha�ne
char * sLeft(char * a , int longueur_sz)
{

    //on v�rifie si la longueur sp�cifi�e est sup�rieur � z�ro
    if( longueur_sz <= 0 )
        return ""; //non, on ne retourne rien
    
    int i = 0;
    
    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_tmp;
    
    //on v�rifie si la longueur demand�e n'est pas sup�rieure ou �gale � celle de la cha�ne "a"
    if( longueur_sz >= len_tmp )
        return a; //oui, on retourne la cha�ne telle qu'elle �tait
    
    //on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=0; i < longueur_sz ; i++)
        buffer_tmp[i] = a[i];
    
    //on place le caract�re de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le r�sultat final
    return buffer_tmp;

}
/*
//renvoie les "n" derniers caract�res d'une cha�ne
char * sRight(sString a , int longueur_sz)
{

//on v�rifie si la longueur sp�cifi�e est sup�rieur � z�ro
if( longueur_sz <= 0 )
return ""; //non, on ne retourne rien

int i = 0 , i2 = 0;

//on v�rifie si la longueur demand�e n'est pas sup�rieure ou �gale � celle de la cha�ne "a"
if( longueur_sz >= a.Len() )
return a; //oui, on retourne la cha�ne telle qu'elle �tait

//on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
char * buffer_tmp = new char[longueur_sz + 1];

//variable qui va contenir la cha�ne de caract�res de "a"
char * tmp_a = a;

//on copie la cha�ne "a" vers le buffer
for (i=(a.Len() - longueur_sz) ; i < a.Len() ; i++)
{
buffer_tmp[i2] = tmp_a[i];
i2++;
}

//on place le caract�re de fin (null)
buffer_tmp[longueur_sz] = '\0';

//et on retourne le r�sultat final
return buffer_tmp;

}
*/
//renvoie les "n" derniers caract�res d'une cha�ne
char * sRight(char * a , int longueur_sz)
{

    //on v�rifie si la longueur sp�cifi�e est sup�rieur � z�ro
    if( longueur_sz <= 0 )
        return ""; //non, on ne retourne rien
    
    int i = 0 , i2 = 0;
    
    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_tmp;
    
    //on v�rifie si la longueur demand�e n'est pas sup�rieure ou �gale � celle de la cha�ne "a"
    if( longueur_sz >= len_tmp )
        return a; //oui, on retourne la cha�ne telle qu'elle �tait
    
    //on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=(len_tmp - longueur_sz) ; i < len_tmp ; i++)
    {
        buffer_tmp[i2] = a[i];
        i2++;
    }
    
    //on place le caract�re de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le r�sultat final
    return buffer_tmp;

}

//renvoie une cha�ne de longueur "longueur_sz" commen�ant au caract�re d�termin� par "depart_sz"
char * sMid(sString a , int depart_sz , int longueur_sz)
{

    int i = 0 , i2 = 0;
    
    //on v�rifie si on ne d�passe pas la taille de la cha�ne
    if( (depart_sz + longueur_sz + 1) > a.Len() )
    longueur_sz = a.Len() - depart_sz; //on resp�cifie la longueur de la cha�ne � retourner
    
    //on v�rifie si la longueur de la cha�ne est sup�rieur � z�ro
    if( longueur_sz < 0 )
        return ""; //non, on ne retourne rien
    
    //on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //variable qui va contenir la cha�ne de caract�res de "a"
    char * tmp_a = a;
    
    //on copie la cha�ne "a" vers le buffer
    for (i=(depart_sz) ; i < (depart_sz + longueur_sz) ; i++)
    {
        buffer_tmp[i2] = tmp_a[i];
        i2++;
    }
    
    //on place le caract�re de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le r�sultat final
    return buffer_tmp;

}

//renvoie une cha�ne de longueur "longueur_sz" commen�ant au caract�re d�termin� par "depart_sz"
char * sMid(char * a , int depart_sz , int longueur_sz)
{

    int i = 0 , i2 = 0;
    
    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_tmp = 0;
    
    while(*a)
    {
        a++;
        len_tmp++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_tmp;
    
    //on v�rifie si on ne d�passe pas la taille de la cha�ne
    if( (depart_sz + longueur_sz + 1) > len_tmp )
        longueur_sz = len_tmp - depart_sz; //on resp�cifie la longueur de la cha�ne � retourner
    
    //on v�rifie si la longueur de la cha�ne est sup�rieur � z�ro
    if( longueur_sz < 0 )
        return ""; //non, on ne retourne rien
    
    //on alloue un buffer de la taille de la cha�ne de caract�res donn�e en argument + 1 pour le caract�re null
    char * buffer_tmp = new char[longueur_sz + 1];
    
    //on copie la cha�ne "a" vers le buffer
    for (i=(depart_sz) ; i < (depart_sz + longueur_sz) ; i++)
    {
        buffer_tmp[i2] = a[i];
        i2++;
    }
    
    //on place le caract�re de fin (null)
    buffer_tmp[longueur_sz] = '\0';
    
    //et on retourne le r�sultat final
    return buffer_tmp;

}
/*
//compare les deux cha�nes de caract�res "a" et "b" et renvoie "true" si elles concordent
bool sCompare(sString a , sString b)
{

//on v�rifie d'abords si la longueur des deux cha�ne est la m�me
if( a.Len() != b.Len() )
return false;

//on r�cup�re sous forme "char" "a" et "b"
char * tmp_a = new char[a.Len()] = a;
char * tmp_b = new char[b.Len()] = b;

//on compare chaque caract�re correspondant
for( int i=0 ; i<=a.Len() ; i++ )
{

if(tmp_a[i] != tmp_b[i])
return false;

}

//si on arrive jusqu'ici, c'est que les deux cha�nes sont identiques
return true;

}
*/
//compare les deux cha�nes de caract�res "a" et "b" et renvoie "true" si elles concordent
bool sCompare(char * a , char * b)
{

    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_a;
    
    //taille de la cha�ne de caract�res donn�e en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur � z�ro
    b -= len_b;
    
    //on v�rifie d'abords si la longueur des deux cha�ne est la m�me
    if( len_a != len_b )
        return false;
    
    //on compare chaque caract�re correspondant
    for( int i=0 ; i<=len_a ; i++ )
    {
    
        if(a[i] != b[i])
            return false;   

    }

    //si on arrive jusqu'ici, c'est que les deux cha�nes sont identiques
    return true;

}
/*
//renvoie la position du premier caract�re de la cha�ne "b" trouv�e dans "a"
int sStrPos(sString a , sString b , int depart_sz = 0)
{

//on v�rifie si la taille de la cha�ne � chercher n'est pas plus grande que la cha�ne dans laquelle il faut chercher
if( (b.Len() + depart_sz) > a.Len() )
return -1;

//on calcule le nombre d'it�rations � effectuer
int iterations_sz = a.Len() - (b.Len() + depart_sz);

//on fait une boucle
for(int i=depart_sz ; i <= iterations_sz ; i++ )
{

//on v�rifie si la cha�ne de caract�res (dans "b") de m�me taille que "a" et commen�ant au caract�re "i" n'est pas = � "a"
if( sCompare(sMid(a , i , b.Len()) , b) )
return i;

}

//si on arrive ici, c'est qu'on a rien trouv�
return -1;

}
*/
//renvoie la position du premier caract�re de la cha�ne "b" trouv�e dans "a"
int sStrPos(char * a , char * b , int depart_sz = 0)
{

    int i2=0;
    
    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_a;
    
    //taille de la cha�ne de caract�res donn�e en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur � z�ro
    b -= len_b;
    
    //on v�rifie si la taille de la cha�ne � chercher n'est pas plus grande que la cha�ne dans laquelle il faut chercher
    if( (len_b + depart_sz) > len_a )
        return -1;
    
    //on calcule le nombre d'it�rations � effectuer
    int iterations_sz = len_a - (len_b + depart_sz);
    
    //on fait une boucle
    for(int i=depart_sz ; i2 <= iterations_sz ; i++ )
    {
    
        //on v�rifie si la cha�ne de caract�res (dans "b") de m�me taille que "a" et commen�ant au caract�re "i" n'est pas = � "a"
        if( sCompare(sMid(a , i ,len_b) , b) )
        return i;
        
        i2++;
    
    }
    
    //si on arrive ici, c'est qu'on a rien trouv�
    return -1;

}


//d�coupe la cha�ne "a" en plusieurs morceaux s�par�s par "b", "limite_sz" est le nombre de morceaux max � retourner (-1 = max)
sString * sSplit(char * a , char * b , int limite_sz , int &taille_finale)
{

    int i=0 , pos=-1 , pos2=0 ;
    sString * tmp_res;
    
    //taille de la cha�ne de caract�res donn�e en argument ("a")
    int len_a = 0;
    
    while(*a)
    {
        a++;
        len_a++;
    }
    
    //on remet notre pointeur � z�ro
    a -= len_a;
    
    //taille de la cha�ne de caract�res donn�e en argument ("b")
    int len_b = 0;
    
    while(*b)
    {
        b++;
        len_b++;
    }
    
    //on remet notre pointeur � z�ro
    b -= len_b;
    
    //on parcourt la cha�ne "a" � la recherche de "b" autant de fois que "b" s'y trouve
    do
    {
        pos = sStrPos(a , b , pos + 1);
        i++;
    
    }while(pos > 0);
    
    //si la limite est � z�ro on renvoie un tableau avec une seule valeur
    if(limite_sz == 0)
    {
    //on quitte ici
        tmp_res = new sString[0];
        tmp_res[0] = "";
        return tmp_res;
    
    //si une limite est sp�cifi�e, on v�rifie s'il faut en tenir compte
    }else if(limite_sz > 0){
    
        if(i > limite_sz)
        {
                i = limite_sz;
        }
    
    }
    
    //on sp�cifie le nombre de r�sultats que le tableau va contenir
    taille_finale = i;
    
    //on cr�e un tableau de type "sString" de la taille indiqu�e par "i"
    tmp_res = new sString[i];
    
    //on d�cr�mente i
    i--;
    
    //on remet la position de d�part � -1 (on y ajoute 1 par la suite � chaque it�rations de la boucle for)
    pos = -1;
    
    //pos2 commence lui � z�ro et va prendre la valeur de pos avant que celui-ci ne change
    pos2 = 0;
    
    int i2;
    
    for(int i2=0 ; i2<i ; i2++ )
    {
    
        //on r�cup�re la position de la premi�re occurence de la cha�ne "b" dans la cha�ne "a"
        pos = sStrPos(a , b , pos + 1);
        
        //on r�cup�re la cha�ne de caract�res situ�e entre "pos2" et "pos" et on la place dans notre tableau
        tmp_res[i2] = sMid(a , pos2 , pos-pos2);
        
        pos2 = pos + len_b;
    
    }
    
    //on r�cup�re la fin de la cha�ne
    tmp_res[i2] = sMid(a , pos2 , len_a-pos2);
    
    return tmp_res;

} 
