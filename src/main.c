#include <stdio.h>
#include "main.h"


int main(int argc, char *argv[]){
    command_line_interface(argc, argv);
    return 0;
}



/**
 * EX : . /main -l -n "name" -m "https://exemple.com/main.swf" "file1" "file2" "file3" ...
 * 
 * -h: help
 * -l: Command line game download, file names passed as arguments
 * -n: name of the game / name of the folder that will contain the files
 * -m: Game’s main file/hand URL
 * without - : the following files to download (xml, mp3, ...)
 */
void command_line_interface(int argc, char *argv[]){

    int opt;
    char *nom = NULL;
    char *main_val = NULL;

    while ((opt = getopt(argc, argv, "ln:m:")) != -1) {
        switch (opt) {
            case 'l':
                break;
            case 'n':
                nom = optarg;
                break;
            case 'm':
                main_val = optarg;
                break;
            case 'h':
                printf("[press F1] for Help"); ////////////////////////////////////////// Help here
                break;
            
            default:
                fprintf(stderr, "Usage: %s [-l] [-n nom] [-m main] file1 [file2 ...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //"optind" contains the index of the first non-option argument
    /*
    printf("Remaining files (%d in total) :\n", argc - optind);
    for (int i = optind; i < argc; i++) {
        printf(" - %s\n", argv[i]);
    }
    printf("nb:%d\n", argc - optind);
    */

    get_game(nom, main_val, &(argv[optind]), argc - optind);

}


int get_game(char * game_name, char * url_main, char ** other, int n_other){
    int i = 0;

    char * arrey_files[MAX_ARRAY_FILES];

    //number of filenames in the Arrey
    int arrey_files_n = 0;

    //exit loop variable
    int return_get_file_from_xml = 0;

    //temporary string
    char * filename_temp;

    //Destination location for the "game_name/url_relative" file
    char * url_temp_full = malloc((MAXCHAR_URL) * sizeof(char));

    //display arguments:
    /*

    printf("name:%s\n",game_name);
    printf("main:%s\n",url_main);

    for(i=0 ; i < n_other ; i++){
        printf("other[%d]:%s\n", i , other[i]);
    }

    */




    //mettre tous les fichiers dans le tableaux arrey_files


    //Creating the game folder
    if(! parent_dir_exists_for_file_uv(url_temp_full)){
        printf("Création dossier du jeu \n");
        uv_mkdir_p(game_name);
    }



    //Copy other file names to the arrey
    for(i=0 ; i < n_other ; i++){
        arrey_files[i] = strdup(other[i]);
    }
    arrey_files_n = n_other;

    

    //display
    printf("[\n");

    for(i=0; i < arrey_files_n; i++){
        printf("%s\n",arrey_files[i]);
    }
    printf("]\n\n");
    


    //Download main file
    filename_temp = get_filename(url_main);

    printf("Download main:\n");
    download_file(filename_temp, url_main);
    printf("\n");


    free(filename_temp);


    
    //Loop: Browse files in the arrey and add subfiles in this arrey
    i = 0;

    while(i < arrey_files_n){
        return_get_file_from_xml = 0;

        download_from_main_url_and_relative_path(url_main, arrey_files[i]);

        printf("analyse:%s \n", arrey_files[i]);
        filename_temp = get_filename(arrey_files[i]);

        if(verifiy_extention_from_url(arrey_files[i])){
            return_get_file_from_xml = get_file_from_xml(filename_temp, arrey_files, &arrey_files_n);
        }

        if(return_get_file_from_xml == 1){
            printf("Error: the %s file does not exist (was not downloaded) \n", arrey_files[i]);
            i++;
            continue; //Sometimes the game can work if there is a file missing
        }


        //Concatenation of the name of the game and relative file location
        snprintf(url_temp_full, MAXCHAR_URL, "%s/%s", game_name, arrey_files[i]);
        printf("Destination du fichier:%s \n", url_temp_full);

        if(! parent_dir_exists_for_file_uv(url_temp_full)){
            printf("Créer le dossier pour %s\n", url_temp_full);
            create_parent_dirs_for_file_uv(url_temp_full);
        }
        
        //Moving the file
        //printf("move: %s => %s\n", filename_temp, url_temp_full);
        rename(filename_temp, url_temp_full);

        free(filename_temp);

        printf("\n");
        i++;

    }

    filename_temp = get_filename(url_main);

    snprintf(url_temp_full, MAXCHAR_URL, "%s/%s", game_name, filename_temp);
    printf("Déplacement du fichier:%s=>%s \n", filename_temp, url_temp_full);

    rename(filename_temp, url_temp_full);


    printf("List files in %s:\n%s \n",game_name , url_main);

    //affichage du tableau
    for(i=0; i < arrey_files_n ; i++){
        printf("%s\n", arrey_files[i]);
        free(arrey_files[i]);
    }


    //écrire le tableau dans un fichier

    return 0;

}
