#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fts.h>
#include<string.h>
#include<errno.h>

int compare (const FTSENT**, const FTSENT**);

typedef int (*MathOp)(int, int);

int add(int x, int y) {
    return x + y;
}

int multiply(int x, int y) {
    return x * y;
}

int math_op(int x, int y, MathOp op) {
    return (*op)(x, y);
}

int main(int argc, char* const argv[]) {
    int x = math_op(10, 10, &add);
    int y = math_op(10, 10, &multiply);
    printf("%d\n", x);
    printf("%d\n", y);
    return 0;
}


// int main(int argc, char* const argv[]) {
//     FTS* file_system = NULL;
//     FTSENT* child = NULL;
//     FTSENT* parent = NULL;

//     if (argc < 2) {
//         printf("Usage: %s <path-spec>\n", argv[0]);
//         exit(255);
//     }

//     file_system = fts_open(argv + 1, FTS_NOCHDIR, &compare);

//     if (NULL != file_system) {
//         while( (parent = fts_read(file_system)) != NULL) {
//             child = fts_children(file_system,0);

//             if (errno != 0) {
//                 perror("fts_children");
//             }

//             while ((NULL != child) && (NULL != child->fts_link)) {
//                 child = child->fts_link;
//                 printf("%s%s\n", child->fts_path, child->fts_name);
//             }
//         }

//         fts_close(file_system);
//     }

//     return 0;
// }

// int compare(const FTSENT** one, const FTSENT** two) {
//     return (strcmp((*one)->fts_name, (*two)->fts_name));
// }
