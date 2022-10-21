// htab_lookup_add.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (t != NULL) {
        htab_pair_t *htabPair = htab_find(t, key);
        if (htabPair == NULL) {

            size_t index = (htab_hash_function(key) % t->arr_size);
            if (t->list[index] == NULL) {
                t->list[index] = malloc(
                        sizeof(struct htab_item)); // přidání nové položky seznamu ukazatelů se záznamem
                if (t->list[index] == NULL) {
                    return NULL;
                }

                t->list[index]->htabPair = malloc(sizeof(htab_pair_t));
                if (t->list[index]->htabPair == NULL) {
                    free(t->list[index]);
                    t->list[index] = NULL;
                    return NULL;
                }

                t->list[index]->htabPair->key = malloc(sizeof(char) * (strlen(key) + 1));
                if (t->list[index]->htabPair->key == NULL) {
                    free(t->list[index]->htabPair);
                    free(t->list[index]);
                    t->list[index] = NULL;
                    return NULL;
                }

                strcpy((char *) t->list[index]->htabPair->key, key);

                t->list[index]->htabPair->value = 0;
                t->size++;
                t->list[index]->next = NULL;
                if ((t->size / t->arr_size) > AVG_LEN_MAX) {
                    htab_resize(t, t->size * 2);
                }

                return htab_find(t,key);

            } else {
                struct htab_item *currentItem = t->list[index];
                while (currentItem->next != NULL) {
                    currentItem = currentItem->next;
                }
                currentItem->next = malloc(sizeof(struct htab_item)); // přidání záznamu
                if (currentItem->next == NULL) {
                    return NULL;
                }

                currentItem->next->htabPair = malloc(sizeof(htab_pair_t));
                if (currentItem->next->htabPair == NULL) {
                    free(currentItem->next);
                    currentItem->next = NULL;
                    return NULL;
                }

                currentItem->next->htabPair->key = malloc(sizeof(char) * (strlen(key) + 1));
                if (currentItem->next->htabPair->key == NULL) {
                    free(currentItem->next->htabPair);
                    free(currentItem->next);
                    currentItem->next = NULL;
                    return NULL;
                }

                strcpy((char *) currentItem->next->htabPair->key, key);
                currentItem->next->htabPair->value = 0;
                t->size++;

                currentItem->next->next = NULL;
                if ((t->size / t->arr_size) > AVG_LEN_MAX) {
                    htab_resize(t, t->size * 2);
                }
                return htab_find(t,key);
            }
        } else {
            return htabPair;
        }
    }

    return NULL;
}
