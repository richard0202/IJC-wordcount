// htab_for_each.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    if (t != NULL) {
        for (unsigned i = 0; i < t->arr_size; i++) {
            if (t->list[i] != NULL) {
                struct htab_item *currentItem = t->list[i];
                while (currentItem != NULL) {
                    f(currentItem->htabPair);
                    currentItem = currentItem->next;
                }
            }
        }
    }
}
