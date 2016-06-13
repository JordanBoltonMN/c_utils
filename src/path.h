#include <time.h>

typedef struct path {
    char * path;
    char * dirname;
    char * ext;
    time_t creation;
} path;

path create_path(char * path);
