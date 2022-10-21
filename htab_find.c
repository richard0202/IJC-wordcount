// htab_find.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key) {
    if (t != NULL) {
        for (unsigned i = 0; i < t->arr_size; ++i) {
            if (t->list[i] != NULL) {
                struct htab_item *currentItem = t->list[i];
                while (currentItem != NULL) {
                    if (strcmp(currentItem->htabPair->key, key) == 0) {
                        return currentItem->htabPair;
                    }
                    currentItem = currentItem->next;
                }
            }
        }
    }
    return NULL;
}
