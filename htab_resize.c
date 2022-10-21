// htab_resize.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

void htab_resize(htab_t *t, size_t newn) {
    if (t == NULL) {
        return;
    }

    htab_t *new_table = htab_init(newn);
    if (new_table == NULL) {
        htab_free(new_table);
        return;
    }

    new_table->size = t->size;
    new_table->arr_size =newn;
    if (new_table->arr_size == 0) {
        new_table->arr_size++;
    }

    for (unsigned i = 0; i < t->arr_size; i++) {
        if (t->list[i] != NULL) {
            struct htab_item *currentItem = t->list[i];
            while (currentItem != NULL) {
                size_t index = (htab_hash_function(currentItem->htabPair->key) % new_table->arr_size);

                if (new_table->list[index] == NULL) {
                    new_table->list[index] = malloc(
                            sizeof(struct htab_item)); // přidání nové položky seznamu ukazatelů se záznamem
                    if (new_table->list[index] == NULL) {
                        htab_free(new_table);
                        return;
                    }

                    new_table->list[index]->htabPair = malloc(sizeof(htab_pair_t));
                    if (new_table->list[index]->htabPair == NULL) {
                        free(new_table->list[index]);
                        new_table->list[index] = NULL;
                        htab_free(new_table);
                        return;
                    }

                    new_table->list[index]->htabPair->key = malloc(sizeof(char) * (strlen(currentItem->htabPair->key) + 1));
                    if (new_table->list[index]->htabPair->key == NULL) {
                        free(new_table->list[index]->htabPair);
                        free(new_table->list[index]);
                        new_table->list[index] = NULL;
                        htab_free(new_table);
                        return;
                    }

                    strcpy((char *) new_table->list[index]->htabPair->key, currentItem->htabPair->key);

                    new_table->list[index]->htabPair->value = currentItem->htabPair->value;
                    new_table->list[index]->next = NULL;


                } else {

                    struct htab_item *currentNewItem = new_table->list[index];
                    while (currentNewItem->next != NULL) {
                        currentNewItem = currentNewItem->next;
                    }
                    currentNewItem->next = malloc(sizeof(struct htab_item)); // přidání záznamu
                    if (currentNewItem->next == NULL) {
                        htab_free(new_table);
                        return;
                    }

                    currentNewItem->next->htabPair = malloc(sizeof(htab_pair_t));
                    if (currentNewItem->next->htabPair == NULL) {
                        free(currentNewItem->next);
                        currentNewItem->next = NULL;
                        htab_free(new_table);
                        return;
                    }

                    currentNewItem->next->htabPair->key = malloc(sizeof(char) * (strlen(currentItem->htabPair->key) + 1));
                    if (currentNewItem->next->htabPair->key == NULL) {
                        free(currentNewItem->next->htabPair);
                        free(currentNewItem->next);
                        currentNewItem->next = NULL;
                        htab_free(new_table);
                        return;
                    }

                    strcpy((char *) currentNewItem->next->htabPair->key, currentItem->htabPair->key);
                    currentNewItem->next->htabPair->value = currentItem->htabPair->value;

                    currentNewItem->next->next = NULL;

                }

                currentItem = currentItem->next;
            }
        }
    }
    htab_clear(t);
    free(t->list);
    t->list = new_table->list;
    t->arr_size = new_table->arr_size;
    free(new_table);
}
