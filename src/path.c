#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fnmatch.h>
#include <fts.h>
#include <regex.h>

#include "path.h"
#include "dbl_ll.h"
#include "str.h"

void free_path_search(dbl_ll * root) {
    dbl_ll * current = root;
    dbl_ll * next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->data);
        free(current);
        current = next;
    }
}


dbl_ll * path_search(char * const dir, const regex_t * pattern) {
    FTS * tree;
    FTSENT * f;
    // acts as the required datatype 'char * const *' for fts_open
    char * const argv[] = { dir, NULL };

    // either FTS_LOGICAL or FTS_PHYSICAL must be provided
    // FTS_LOGICAL follows symbolic links to their destination
    tree = fts_open(argv, FTS_LOGICAL, path_cmp);
    if (tree == NULL) {
        err(1, "fts_open");
    }

    dbl_ll * root = NULL;
    while ((f = fts_read(tree))) {
        if (f->fts_info != FTS_F) {
            continue;
        }
        else if (regexec(pattern, f->fts_name, 0, NULL, 0) == REG_NOMATCH) {
            continue;
        }
        else {
            char * key = str_copy(f->fts_path);
            FTSENT * data = (FTSENT *) malloc(sizeof(FTSENT));
            *data = *f;
            dbl_ll * node = dbl_ll_create(
                (void *) key,
                (void *) data,
                NULL,
                NULL
            );
            root = dbl_ll_insert(root, node);
        }
    }

    if (errno != 0) {
        err(1, "fts_read");
    }

    if (fts_close(tree) < 0) {
        err(1, "fts_close");
    }

    return root;
}


int path_cmp(const FTSENT **a, const FTSENT **b) {
    return strcmp((*a)->fts_name, (*b)->fts_name);
}
