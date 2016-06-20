#ifndef DBL_LL_H
#define DBL_LL_H

#include <stdbool.h>

typedef struct dbl_ll {
    void * key;
    void * data;
    struct dbl_ll * prev;
    struct dbl_ll * next;
} dbl_ll;


typedef struct dbl_ll_del {
    bool deleted;
    struct dbl_ll * root;
} dbl_ll_del;


typedef int (*dbl_ll_cmp)(const dbl_ll *, const dbl_ll *);
typedef int (*dbl_ll_cmp_key)(const void *, const void *);
typedef void (*dbl_ll_free)(dbl_ll *);

struct dbl_ll * dbl_ll_create(void * key, void * data, dbl_ll * prev, dbl_ll * next);

struct dbl_ll * dbl_ll_insert(dbl_ll * root, dbl_ll * node);

struct dbl_ll_del dbl_ll_delete(dbl_ll * root, const void * key, dbl_ll_cmp_key cmp, dbl_ll_free release);

bool dbl_ll_contains(const dbl_ll * root, const void * key, dbl_ll_cmp cmp);

#endif
