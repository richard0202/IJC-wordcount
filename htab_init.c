// htab_init.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

htab_t *htab_init(size_t n) {
    if (n <= 0) {
        n = 1;
    }
    htab_t *t = malloc(sizeof(htab_t));

    if (t == NULL) {
        return NULL;
    }

    t->list = calloc(n,sizeof (struct htab_item));
    if (t->list == NULL) {
        free(t);
        return NULL;
    }


    t->arr_size = n;
    t->size = 0;
    for (unsigned i = 0; i < n; i++) {
        t->list[i] = NULL;
    }
    return t;
}
