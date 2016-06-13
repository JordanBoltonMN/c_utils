#include <stdio.h>
#include <time.h>

#include "path.h"
#include "str.h"

path create_path(char * path) {
    struct path result;
    result.path = str_copy(path);
    result.dirname = NULL;
    result.ext = NULL;
    return result;
}
