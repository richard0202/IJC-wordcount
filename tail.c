// tail.c
// Řešení IJC-DU2, příklad a), 19.4.2022
// Autor: Richard Kocián, FIT
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 4095                     // Maximální velikost jednoho řádku
#define REAL_LINE_SIZE (MAX_LINE_SIZE+2)    // + '\0' a '\n'

/**
 * @brief               Zaslání errorové zprávy
 */
void tooManyArguments();

/**
 * @brief                       Zpracovávání argumentů
 *
 * @param argc                  Počet argumentů
 * @param argv                  Pole stringů s jednotlivými argumenty
 * @param fileName              Ukazatel na string fileName (název souboru)
 * @param lastLinesToPrint      Ukazatel na int lastLinesToPrint (počet posledních řádků)
 *
 * @return 0                    Zpracování argumentů proběhlov  pořádku
 * @return -1                   Při zpracovávání argumentů došlo k chybě
 */
int argumentsProcessing(int argc, char *argv[], char **fileName, long *lastLinesToPrint);

/**
 * @brief                       Tisk posledních n řádků
 *
 * @param bufferLine            Int od jakého řádku bufferu se má začíst tisknout
 * @param lastLinesToPrint      Počet posledních řádků k tisku
 * @param buffer                Buffer obsahující posledních n řádků k tisku
 */
void printTail(long bufferLine, long lastLinesToPrint, int (*buffer)[REAL_LINE_SIZE]);

int main(int argc, char *argv[]) {
    char *fileName = "stdin";       // default nastavení vstupu
    long lastLinesToPrint = 10;     // default nastavení řádků k tisku
    if (argc > 4) {
        tooManyArguments();
        return -1;
    }

    if (argc >= 2) {
        if (argumentsProcessing(argc, argv, &fileName, &lastLinesToPrint) == -1) {
            return -1;
        }
    }

    if (lastLinesToPrint < 0) {
        fprintf(stderr, "Počet řádků musí být 0 a více!\n");
        return -1;
    }

    FILE *file;
    if (strcmp(fileName, "stdin") == 0) {
        file = stdin;
    } else {
        file = fopen(fileName, "r");
    }
    if (file == NULL) {
        fprintf(stderr,
                "Soubor %s nebyl nalezen!\n", argv[1]);
        return -1;
    }

    if (lastLinesToPrint == 0) {      // Pokud je argumentem -n zadáno číslo 0, tak se po zadání vstupu nic nevytiskne
        while ((fgetc(file)) != EOF) {
        }
        return 0;
    }

    // Alokace kruhového bufferu
    int (*buffer)[REAL_LINE_SIZE] = calloc(1, sizeof(int[lastLinesToPrint][REAL_LINE_SIZE]));

    if (buffer == NULL) {
        fprintf(stderr, "Nepodařilo se alkovat místo v paměti!\n");
        return -1;
    }

    long linesCount = 0;
    int character;
    long bufferLine = 0;
    long i = 0;
    bool isErrorPrinted = false;

    // Čtení ze vstupu znak po znaku, ukládání do kruhového bufferu
    while ((character = fgetc(file)) != EOF) {
        if (i >= MAX_LINE_SIZE && character != '\n') {
            if (!isErrorPrinted) {
                fprintf(stderr, "Byl překročen limit řádku (%d znaků)! Všechny delší řádky budou zkráceny.\n",
                        MAX_LINE_SIZE);
                isErrorPrinted = true;
            }

            // ukončení řádku, co překročil limit maximální délky
            buffer[bufferLine][i] = '\n';
            buffer[bufferLine][i + 1] = '\0';

            while (fgetc(file) != '\n') {   // přeskočení znaků, které jsou delší než maximální délka řádku

            }
            linesCount++;
            bufferLine++;
            i = 0;

            if (bufferLine >= lastLinesToPrint) {
                bufferLine = 0;
            }
            continue;
        }
        buffer[bufferLine][i] = character;
        i++;

        if (character == '\n') {
            linesCount++;
            bufferLine++;
            i = 0;
        }
        if (bufferLine >= lastLinesToPrint) {
            bufferLine = 0;
        }
    }

    printTail(bufferLine, lastLinesToPrint, buffer);

    free(buffer);
    if (!(strcmp(fileName, "stdin") == 0)) {
        fclose(file);
    }
}


void tooManyArguments() {
    fprintf(stderr, "Chybné zadání argumentů! Použití: ./tail [-n číslo] [název souboru]\n");
}

int argumentsProcessing(int argc, char *argv[], char **fileName, long *lastLinesToPrint) {
    if (strcmp(argv[1], "-n") == 0) {
        if (argc >= 3) {
            *lastLinesToPrint = strtol(argv[2], NULL, 0);
        } else {
            fprintf(stderr, "Za argumentem -n je očekáváno číslo!\n");
            return -1;
        }
        if (argc == 4) {
            *fileName = argv[3];
        }
    } else if (argc == 2) {
        *fileName = argv[1];
    } else {
        tooManyArguments();
        return -1;
    }
    return 0;
}

void printTail(long bufferLine, long lastLinesToPrint, int (*buffer)[REAL_LINE_SIZE]) {

    for (long j = bufferLine; j < lastLinesToPrint; j++) {
        for (int k = 0; k < REAL_LINE_SIZE; k++) {
            if (buffer[j][k] == 0) {
                break;
            }
            if (buffer[j][k] == '\n') { // ošetření, když v bufferu zbylo minulé slovo
                printf("\n");
                break;
            }
            printf("%c", buffer[j][k]);
        }
    }

    for (long j = 0; j < bufferLine; j++) {
        for (int k = 0; k < REAL_LINE_SIZE; k++) {
            if (buffer[j][k] == 0) {
                break;
            }
            if (buffer[j][k] == '\n') { // ošetření, když v bufferu zbylo minulé slovo
                printf("\n");
                break;
            }
            printf("%c", buffer[j][k]);
        }
    }
}
