#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


/*
install curl for dev: lib curl
sudo apt install libcurl4-openssl-dev
*/

#define MAX_URL 200

int download_file(char * outfilename ,char *url);

int download_from_main_url_and_relative_path(char * main_url, char * relative_path);








