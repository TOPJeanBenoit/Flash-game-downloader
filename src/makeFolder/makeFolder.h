#include <stdio.h>
#include <string.h>
#include <uv.h>

#define MAXCHARURL 200


//int makeDirectory(char * name);
//int mkTabDir(char ** tab, int nbChar);
//
//void make_dir(const char *path);

int uv_mkdir_p(const char *dir_path);
int create_parent_dirs_for_file_uv(const char *file_path);
int dir_exists_uv(const char *dir_path);
int parent_dir_exists_for_file_uv(const char *file_path);
int attendre_dossier_uv(uv_loop_t *loop, const char *path, int timeout_sec);