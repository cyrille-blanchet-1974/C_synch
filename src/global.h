/*******************************************************************************
*
*                   constantes globales
*
*******************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

//taille max des chînes
#define MAX_CHAINE 8192
//mode débug
#define DEBUG
#undef DEBUG
//afficher toutes les infos en fichier sortie
#define VERBOSE
#undef VERBOSE

#define G_SEPARATOR "\\"
#define G_WILDCHAR  "*.*"
#define G_QUOTE     "\""

#ifdef  _MSC_VER
#define strcasecmp _stricmp
#endif



#endif // GLOBAL_H




