#include "analyseXML.h"

char * cut_url(char * url, int debut, int fin){

    //TODO_3: Calculate the necessary memory allocation
    char *charTmp = malloc(MAX_STR_TEMP_CPY * sizeof(char));

    int i = debut;
    int j = 0;
    
    while(i < fin){
        charTmp[j] = url[i];

        i++;
        j++;
    }
    charTmp[j] = '\0';
  
    return charTmp;
}

void search_extention_with_dot(char * url, int *debut, int point, int *fin){

    int i = point;
    int j = point;
    for(i; i != 0;i--){
        if(url[i] == '"' || url[i] == '>'){
            (*debut) = i;
            break;
        }

    }

    for(j; url[j] != '\0';j++){
        if(url[j] == '"' || url[j] == '<'){
            (*fin) = j;
            break;
        }
    }


}
/**
*
*urlTexte = 0 : all extention
*urlTexte = 1 : file to the text extension
*/
int correct_extention(char * ligne, int i_point, int urlTexte){
    char ** extention;
    char * extentionAll[] = {".swf", ".xml", ".mp3", ".mp4" , "fin"};
    char * extentionText[] = {".xml",".json", "fin"};

    if(urlTexte == 0){
        extention = extentionAll;       

    }else{
        extention = extentionText;
    }




    int i = 0;
    int j = 0;
    int i_point_temp = i_point;

    int verif = 1;

    for(i=0; strcmp(extention[i], "fin") != 0 ;i++){
        for(j=0;extention[i][j] != '\0' && verif == 1 ; j++){
            
            //printf("extention:%c\n",extention[i][j]);
            //printf("ligne:%c\n", ligne[i_point_temp]);

            if(extention[i][j] != ligne[i_point_temp]){
                verif = 0;
            }

            i_point_temp++;
        }

        if(verif == 1){
            return 1;
        }
        verif = 1;
        i_point_temp = i_point;
    }
    return 0;
}

int verifiy_extention_from_url(char * url){

    int i = 0;

    int i_dot = 0;

    while (url[i] != '\0'){
        if(url[i] == '.')
            i_dot = i;

        i++;
    }

    return correct_extention(url, i_dot, 1);
}

/**
 * Adds to the "FListName" Arrey all the files indicated in the link file.
 * 
 */
int get_file_from_xml(char * link, char **nomFListe, int * iListe){

    if(!file_exists(link)){
        //printf("The %s file does not exist\n",link);
        return 1;
    }

    FILE *fXML;
    FILE *listeURL;
    
    int index_debut = 0;
    int index_point = 0;
    int index_fin = 0;

    int i = 0;

    char ligne[MAX_STR_URL] = "";
    char str_temp[MAX_STR_URL] = "";
    
    
    fXML = fopen(link, "r");
    
    while(fgets(ligne, MAX_STR_URL, fXML)){
                

        for(i=0;i<MAX_STR_URL && ligne[i] != '\n' && ligne[i] != '\0' ; i++){


            if(ligne[i] == '.'){
                //printf(".\n");
                index_point = i;

                if(correct_extention(ligne, index_point, 0)){
                    search_extention_with_dot(ligne, &index_debut, index_point, &index_fin);
                    //printf("index_debut:%d, point:%d, fin:%d, iListe:%d \n",index_debut,index_point,index_fin, *iListe);
                    
                    nomFListe[*iListe] = cut_url(ligne, index_debut + 1, index_fin);

                    //old: nomFListe[*iListe] = cut_url(ligne, str_temp, index_debut + 1, index_fin);

                    (*iListe)++;
                }

                index_debut = 0;
                index_point = 0;
                index_fin = 0;



            }
        }
    }
    //printf("iListe:%d\n",*iListe);
    fclose(fXML);
}


char * get_filename(char * url){
    if(url == NULL){
        return NULL;
    }
    int i = 0;    
    int iSlash = 0;

    //printf("url:%s\n",url);

    for(i=0; url[i] != '\0'; i++){
        if(url[i] == '/'){
            iSlash = i;
        }
    }

    //printf("iSlash:%d \n",iSlash);   

    return cut_url(url+1, iSlash, i);

}

int file_exists(const char *filename){
    return g_file_test(filename, G_FILE_TEST_EXISTS);
}
