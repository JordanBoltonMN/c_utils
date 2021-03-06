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
        ptr = ptr->next;
    }

    ptr->next = node;
    node->prev = ptr;

    return root;
}

struct dbl_ll_del_result dbl_ll_del(dbl_ll * root, const void * key, dbl_ll_cmp_key cmp, dbl_ll_free release) {
    struct dbl_ll_del_result result;
    result.deleted = false;
    result.root = root;

    if (root == NULL) {
        result.root = root;
        result.deleted = false;
        return result;
    }

    dbl_ll * ptr = root;
    while (ptr != NULL) {
        int key_cmp = (*cmp)(key, ptr->key);
        // match found
        if (key_cmp == 0) {
            result.deleted = true;

            if (ptr->prev != NULL) {
                ptr->prev->next = ptr->next;
            }
            if (ptr->next != NULL) {
                ptr->next->prev = ptr->prev;
            }
            if (root == ptr) {
                result.root = NULL;
            }

            release(ptr);
            return result;
        }
        else if (key_cmp == -1) {
            ptr = ptr->prev;
        } else {
            ptr = ptr->next;
        }
    }

    return result;
}


bool dbl_ll_has(const dbl_ll * root, const void * key, dbl_ll_cmp_key cmp) {
    const dbl_ll * node = root;

    while (node != NULL) {
        if ( (*cmp)(node->key, key) == 0 ) {
            return true;
        }
        node = node->next;
    }

    return false;
}
