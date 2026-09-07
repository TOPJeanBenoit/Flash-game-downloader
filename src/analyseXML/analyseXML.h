#include <stdio.h> //FILE
#include <string.h> //strcmp
#include <stdlib.h> // malloc

#include <glib.h>//g_file_test

#define MAX_TAB_URL 100
#define MAX_STR_URL 200
#define MAX_STR_TEMP_CPY 100


/**
 * 
 * 
 * retour 1 si le fichier link n'existe pas
 * retour 0 sinon
 */
int get_file_from_xml(char * link, char **nomFListe, int * iListe);

/**
 * urlTexte: 
 *  -0 verifer toutes les extention
 *  -1: vérifier uniquement les extentions qui contiennent du texte
 * 
 * i_point: index du point dans ligne
 * 
 * retour 1: extention correcte
 * retour 0: extention incorrecte
 */
int correct_extention(char * ligne, int i_point, int urlTexte);

/**
 *
 * paramètre:
 *  -entrée: url (pointeur du texte à analyser)
 *  -point : index du point de l'url
 * 
 * sortie:
 *  -*debut : index du début de l'url
 *    
 *  -*fin : index de la fin de l'url
 */
void search_extention_with_dot(char * url, int *debut, int point, int *fin);

/**
 * Don't forget to deallocate the return char *
 * 
 */
char * get_filename(char * url);


/**
 * Don't forget to deallocate the return char *
 */
char * cut_url(char * url, int debut, int fin);

/**
 * 
 */
int file_exists(const char *filename); 

/**
 * return 1: extention correcte
 *        0: extention incorrecte
 */
int verifiy_extention_from_url(char * url);
