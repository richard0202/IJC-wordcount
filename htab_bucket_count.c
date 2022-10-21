// htab_bucket_count.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_struct.h"

size_t htab_bucket_count(const htab_t *t) {
    if  (t != NULL) {
        return t->arr_size;
    }
    return (size_t) NULL;
}
