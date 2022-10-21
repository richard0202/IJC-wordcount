// io.c
// Řešení IJC-DU2, příklad b), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isErrorPrinted = false;

int read_word(char *s, int max, FILE *f) {
    if (f != NULL) {
        int character;
        int count = 0;
        while ((character = fgetc(f)) != EOF) {
            if (character != ' ' && character != '\t' && character != '\n' && character != '\0') {
                if (count < max) {
                    s[count] = (char) character;
                    count++;
                } else {
                    if (!isErrorPrinted) {
                        fprintf(stderr, "Slovo je delší než maximum (%d), toto a další slova budou zkráceny!\n", max);
                        isErrorPrinted = true;
                    }
                    s[count] = '\0';
                    return count;
                }
            } else {
                s[count] = '\0';
                return count;
            }
        }
        return EOF;
    }
    return -1;
}
