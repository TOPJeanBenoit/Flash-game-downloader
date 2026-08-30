#include <stdio.h>
#include <string.h>
#include <uv.h>
#include "makeFolder.h"



//Gémini 3.6, 23/07/2026

// Crée récursivement les dossiers (équivalent de mkdir -p)
int uv_mkdir_p(const char *dir_path) {
    uv_loop_t *loop = uv_default_loop();
    uv_fs_t req;
    char temp[1024];
    size_t len = strlen(dir_path);

    if (len >= sizeof(temp) || len == 0) return -1;
    snprintf(temp, sizeof(temp), "%s", dir_path);

    // Normalisation des séparateurs pour le parcours
    for (size_t i = 0; i < len; i++) {
        if (temp[i] == '\\') temp[i] = '/';
    }

    // Parcourt le chemin et crée chaque dossier niveau par niveau
    for (char *p = temp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';

            // uv_fs_mkdir est 100% portable (le mode 0755 est ignoré sous Windows)
            int r = uv_fs_mkdir(loop, &req, temp, 0755, NULL);
            uv_fs_req_cleanup(&req);

            // Seules les erreurs autres que "dossier existe déjà" sont bloquantes
            if (r < 0 && r != UV_EEXIST) {
                fprintf(stderr, "Erreur uv_fs_mkdir (%s): %s\n", temp, uv_strerror(r));
                return r;
            }

            *p = '/';
        }
    }

    // Dernier sous-dossier
    int r = uv_fs_mkdir(loop, &req, temp, 0755, NULL);
    uv_fs_req_cleanup(&req);
    
    return (r == 0 || r == UV_EEXIST) ? 0 : r;
}

// Extrait le dossier parent du fichier et lance la création
int create_parent_dirs_for_file_uv(const char *file_path) {
    char temp[1024];
    if (strlen(file_path) >= sizeof(temp)) return -1;

    snprintf(temp, sizeof(temp), "%s", file_path);

    // Isolement du dossier parent
    char *last_slash = strrchr(temp, '/');
    char *last_backslash = strrchr(temp, '\\');
    char *last_sep = (last_slash > last_backslash) ? last_slash : last_backslash;

    // Fichier à la racine du projet -> aucun dossier à créer
    if (last_sep == NULL) {
        return 0;
    }

    *last_sep = '\0'; // Tronque le nom du fichier

    return uv_mkdir_p(temp);
}


// Vérifie si un chemin donné est un dossier existant
int dir_exists_uv(const char *dir_path) {
    uv_loop_t *loop = uv_default_loop();
    uv_fs_t req;

    int r = uv_fs_stat(loop, &req, dir_path, NULL);
    int is_dir = 0;

    if (r == 0) {
        // req.statbuf contient les infos du fichier/dossier
        is_dir = (req.statbuf.st_mode & S_IFDIR) != 0;
    }

    uv_fs_req_cleanup(&req);
    return is_dir; // 1 si le dossier existe, 0 sinon
}

// Extraction du dossier parent et vérification
int parent_dir_exists_for_file_uv(const char *file_path) {
    char temp[1024];
    if (strlen(file_path) >= sizeof(temp)) return 0;

    snprintf(temp, sizeof(temp), "%s", file_path);

    // Trouver le dernier séparateur
    char *last_slash = strrchr(temp, '/');
    char *last_backslash = strrchr(temp, '\\');
    char *last_sep = (last_slash > last_backslash) ? last_slash : last_backslash;

    // Fichier dans le répertoire courant (pas de sous-dossiers requis)
    if (last_sep == NULL) return 1;

    *last_sep = '\0'; // Conserve uniquement le dossier parent

    return dir_exists_uv(temp);
}
//Fin gémini



//Gémini 14/08/2026
/**
 * Attend que le chemin existe ET soit un dossier en utilisant libuv.
 * @param loop Pointeur vers la boucle libuv (ex: uv_default_loop())
 * @param path Chemin du dossier
 * @param timeout_sec Temps max d'attente (0 = infini)
 * @return 1 si le dossier est prêt, 0 si timeout ou erreur
 */
int attendre_dossier_uv(uv_loop_t *loop, const char *path, int timeout_sec) {
    uv_fs_t req;
    int elapsed_ms = 0;
    int interval_ms = 100;
    int max_ms = timeout_sec * 1000;

    while (1) {
        /* Vérification synchrone du chemin avec libuv */
        int res = uv_fs_stat(loop, &req, path, NULL);
        
        if (res == 0) {
            /* On vérifie que c'est bien un répertoire */
            int est_dossier = (req.statbuf.st_mode & S_IFDIR) != 0;
            uv_fs_req_cleanup(&req);
            
            if (est_dossier) {
                return 1; /* Le dossier existe ! */
            }
        } else {
            uv_fs_req_cleanup(&req);
        }

        if (timeout_sec > 0 && elapsed_ms >= max_ms) {
            return 0; /* Timeout */
        }

        /* Pause cross-platform native gérée par libuv */
        uv_sleep(interval_ms);
        elapsed_ms += interval_ms;
    }
}















//OLD:

/*


int makeDirectory(char * name){

    uv_loop_t *loop = uv_default_loop();      // Boucle par défaut
    uv_fs_t req;                              // Requête pour le système de fichiers

    int r = uv_fs_mkdir(loop, &req, name, 0755, NULL);  // Appel synchrone

    if (r == 0) {
        printf("Dossier '%s' créé avec succès.\n", name);
    } else if (r == UV_EEXIST) {
        printf("Dossier '%s' existe déjà.\n", name);
    } else {
        fprintf(stderr, "Erreur: %s\n", uv_strerror(r));
    }

    uv_fs_req_cleanup(&req);   // Nettoyage de la requête

    return 0;
}

void subString(char * subStr,char * str, int j){
    int i = 0;

    for(i=0; i<j; i++){
        subStr[i] = str[i];
    }
    subStr[i] = '\0';
    
}

int mkTabDir(char ** tab, int nbChar){

    int i = 0;
    int j = 0;

    char stringTemp[MAXCHARURL];

    for(i=0;i<nbChar; i++){

        for(j=0; tab[i][j] != '\0'; j++){
            if(tab[i][j] == '/'){
                subString(stringTemp, tab[i], j);
                //printf("%s\n",stringTemp);
                makeDirectory(stringTemp);
                


            }

        }

    }

}

*/

