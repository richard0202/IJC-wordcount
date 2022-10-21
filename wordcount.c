// wordcount.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include <stdio.h>
#include "io.c"

void print(htab_pair_t *htabPair) {
    printf("%s\t%d\n", htabPair->key, htabPair->value);
}

int main() {
    // 2150, jelikož tato hodnota by mohla stačit pro většinu průměrně dlouhých souborů.
    // Nechceme zase moc malé číslo, jelikož by se muselo několikrát realokovat.
    // Zároveň ale nechceme zase moc velké, abychom při čtení malých souborů nealokovaly zbytečně hodně paměti.
    htab_t *t = htab_init(2150);
    if (t == NULL) {
        fprintf(stderr,"Chyba při inicializaci hash mapy!\n");
        return -1;
    }
    char word[127] = {0,};
    int wordLength = 0;

    while ((wordLength = read_word(word, 127, stdin)) != EOF) {
        if (wordLength != 0) {
            htab_pair_t *htabPair = htab_lookup_add(t, word);
            if (htabPair == NULL) {
                fprintf(stderr, "Chyba při přidávání prvku do hash mapy (NULL)!\n");
                htab_free(t);
                return -1;
            }
            htabPair->value++;
        }
        word[0] = '\0';
    }
    htab_for_each(t,&print);

    htab_free(t);
    return 0;
}
