// htab_clear.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

bool eraseItemWithoutResize(htab_t *t, htab_key_t key);

void htab_clear(htab_t *t) {
    if  (t != NULL) {
        for (unsigned i = 0; i < t->arr_size; i++) {
            if (t->list[i] != NULL) {
                struct htab_item *currentItem = t->list[i];
                while (currentItem->next != NULL) {
                    struct htab_item *nextItem = currentItem->next;
                    eraseItemWithoutResize(t, currentItem->htabPair->key);
                    currentItem = nextItem;
                }
                eraseItemWithoutResize(t, t->list[i]->htabPair->key);
            }
        }
    }
}

bool eraseItemWithoutResize(htab_t *t, htab_key_t key) {
    if (t != NULL) {
        for (unsigned i = 0; i < t->arr_size; ++i) {
            if (t->list[i] != NULL) {
                if (strcmp(t->list[i]->htabPair->key,key) == 0) { // odebrání položky v seznamu ukazatelů na záznamy
                    struct htab_item *nexItem = t->list[i]->next;
                    free((void *) t->list[i]->htabPair->key);
                    free(t->list[i]->htabPair);
                    free(t->list[i]);
                    t->list[i] = nexItem;
                    t->size--;
                    return true;
                }

                struct htab_item *currentItem = t->list[i];
                while (currentItem->next != NULL) {
                    if (strcmp(currentItem->next->htabPair->key, key) == 0) {  // odebrání záznamu
                        struct htab_item *nextItem = currentItem->next->next;
                        free((void *) currentItem->next->htabPair->key);
                        free(currentItem->next->htabPair);
                        free(currentItem->next);
                        currentItem->next = nextItem;
                        t->size--;
                        return true;
                    }
                    currentItem = currentItem->next;
                }
            }
        }
        return false;
    }
    return false;
}
