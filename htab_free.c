// htab_free.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    if (t != NULL) {
        htab_clear(t);
        free(t->list);
        free(t);
    }
}
