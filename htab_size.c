// htab_size.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"

size_t htab_size(const htab_t *t) {
    if  (t != NULL) {
        return t->size;
    }
    return (size_t) NULL;
}
