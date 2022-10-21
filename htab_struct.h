// htab_struct.h
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#ifndef __HTAB_STRUCT_H__
#define __HTAB_STRUCT_H__

#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **list;
};

struct htab_item {
    struct htab_pair *htabPair;
    struct htab_item *next;
};

#endif // __HTAB_STRUCT_H__
