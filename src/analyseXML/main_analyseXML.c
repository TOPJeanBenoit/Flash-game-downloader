#include "analyseXML.h"


int main(){

    //char * url = "abc/abc.c";
    //printf("cut:%s\n", get_filename(url));


    char * tab[MAX_STR_URL];
    int i = 0;
    int j = 0;
    FILE *returnFile;
     
    char filename[50] = "retour.txt";

    //printf("retour.txt existe:%d",file_exists(filename));
    
    printf("verifiy extention:%d\n", verifiy_extention_from_url(filename));
    
    //return 0;

    
    
    get_file_from_xml("config.xml", tab, &i);
    
    for(j; j < i ;j++){
        printf("url:%s\n", tab[j]);
    }
    
    returnFile = fopen(filename, "w");
    
    if (returnFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    
    for (j = 0; j < i; j++) {
        fprintf(returnFile, "%s\n", tab[j]);
    }
    
    printf("Fin écriture fichier \n");
    
    return 0;
    
    
}