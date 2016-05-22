#include <stdlib.h>

#include "dbl_ll.h"


struct dbl_ll * dbl_ll_create(void * key, void * data, dbl_ll * prev, dbl_ll * next) {
    struct dbl_ll * node = (struct dbl_ll *) malloc(sizeof(struct dbl_ll));
    node->key = key;
    node->data = data;
    node->prev = prev;
    node->next = next;
    return node;
}


struct dbl_ll * dbl_ll_insert(dbl_ll * root, dbl_ll * node) {
    if (root == NULL) {
        return node;
    }

    dbl_ll * ptr = root;
    while (ptr->next != NULL) {
        ptr = ptr-> next;
    }

    ptr->next = node;
    node->prev = ptr;

    return root;
}


bool dbl_ll_delete(dbl_ll * root, void * key, dbl_ll_cmp_key cmp, dbl_ll_free release) {
    if (root == NULL) {
        return false;
    }

    dbl_ll * ptr = root;
    while (ptr->next != NULL) {
        if ( (*cmp)(key, ptr->key) == 0 ) {
            dbl_ll * old_prev = ptr->prev;
            dbl_ll * old_next = ptr->next;

            if (ptr->prev != NULL) {
                ptr->prev->next = old_next;
            }
            if (ptr->next != NULL) {
                ptr->next->prev = old_prev;
            }

            (*release)(ptr);

            return true;
        } else {
            ptr = ptr-> next;
        }
    }

    return false;
}
