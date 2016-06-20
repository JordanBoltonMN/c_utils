#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fnmatch.h>
#include <fts.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

#include "dbl_ll.h"

// used as an argument by fts_open
int path_cmp(const FTSENT **a, const FTSENT **b);

dbl_ll * path_search(char * const dir, const regex_t * pattern);
void free_path_search(dbl_ll * root);
