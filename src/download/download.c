#include "download.h"

// Fonction de rappel pour écrire les données reçues dans le fichier
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int download_file(char * outfilename ,char *url) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    //char *url = "https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png";
    //char outfilename[FILENAME_MAX] = "logo.png";

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");
        if (fp == NULL) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier local.\n");
            return 1;
        }

        // Configuration de libcurl
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        // Optionnel : Suivre les redirections (ex: http vers https)
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Exécution du téléchargement
        res = curl_easy_perform(curl);

        // Nettoyage
        if (res != CURLE_OK) {
            fprintf(stderr, "Erreur curl : %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        fclose(fp);
        printf("Téléchargement de %s terminé avec succès !\n", url);
        
    }
    return 0;
}

int download_from_main_url_and_relative_path(char * main_url, char * relative_path){
    //printf("download: %s ; %s\n", main_url, relative_path);

    int i = 0;
    int n = 0;

    char * absolute_file = malloc(sizeof(char) * MAX_URL);

    // Cherche le dernier '/' (ou '\\' sous Windows)
    char *filename = strrchr(relative_path, '/');
    
    if (filename == NULL) {
        // Pas de séparateur trouvé, le chemin est déjà le nom de fichier
        filename = relative_path;
    }else{
        filename++;
    }
    

    //get root of the game
    for(i=0; main_url[i] != '\0' ;i++){
        if(main_url[i] == '/'){
            n = i;
        }

    }
    strcpy(absolute_file , main_url);

    //printf("n:%d\n",n);

    
    absolute_file[n+1] = '\0';

    strcat(absolute_file, relative_path);
    
    //printf("absolute_file:%s\n", absolute_file);

    //printf("filename:%s\n", filename);



    return download_file(filename, absolute_file);
}

