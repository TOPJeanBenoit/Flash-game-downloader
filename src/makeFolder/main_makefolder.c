#include "makeFolder.h"

//fonctionne


int main(void) {
    const char *file_path = "export/logs/2026/data.json";


    if (parent_dir_exists_for_file_uv(file_path)) {
        printf("L'arborescence existe !\n");
    } else {
        printf("L'arborescence n'existe pas.\n");
    }

    if(create_parent_dirs_for_file_uv(file_path) == 0) {
        printf("Arborescence créé pour %s\n", file_path);
    }else{
        printf("Échec de la création de l'arborescence.\n");
    }

    return 0;

    //OLD:
    /*
    
    //char * url[50] = {"bonjour/test.txt", "test1.txt", "bonjour/aa/bb/test.txt"};


    //mkTabDir(url, 3);


    //makeDirectory("dossier");

    make_dir("bonjour/a/b/c");
    */
}
