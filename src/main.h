#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#include "analyseXML/analyseXML.h"
#include "download/download.h"
#include "makeFolder/makeFolder.h"

#define MAX_ARRAY_FILES 200
#define MAXCHAR_URL 500

int get_game(char * game_name, char * url_main, char ** other, int n_other);
void command_line_interface(int argc, char *argv[]);
