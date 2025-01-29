#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  
#include "nacitat.h"

Hrac *hraci = NULL;  
int pocetHracov = 0;

Zapas *zapasy = NULL;  
int pocetZapasov = 0;

char *token; 
char buffer[256];

void nacitat_hracov(const char *sb_hraci) {
    FILE *sub_hraci = fopen(sb_hraci, "r");
    if (sub_hraci == NULL) {
        printf("Súbor nesprávne načítaný (%s).\n", sb_hraci);
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), sub_hraci)) {
        buffer[strcspn(buffer, "\n")] = 0;

        hraci = realloc(hraci, (pocetHracov + 1) * sizeof(Hrac));
        if (hraci == NULL) {
            printf("Chyba pri alokovani pamate pre hracov.\n");
            exit(1);
        }

        token = strtok(buffer, ",");
        hraci[pocetHracov].id = atoi(token);  

        if (hraci[pocetHracov].id == 0) {
            printf("Nezadane ID pre hráča.\n");
            exit(1);  
        }

        token = strtok(NULL, ",");
        if (token == NULL || sscanf(token, "%49s", hraci[pocetHracov].meno) != 1) {
            printf("Nezadane meno pre hráča.\n");
            exit(1);  
        }

        for (int i = 0; i < pocetHracov; i++) {
            if (hraci[i].id == hraci[pocetHracov].id) {
                printf("Hráč pod rovnakým ID už existuje\n");
                exit(1);  
            }
        }
        pocetHracov++;
    }
    fclose(sub_hraci);
}

void nacitat_zapasy(const char *sb_zapasy) {
    FILE *sub_zapasy = fopen(sb_zapasy, "r");
    if (sub_zapasy == NULL) {
        printf("Súbor nesprávne načítaný (%s).\n", sb_zapasy);
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), sub_zapasy)) {
        buffer[strcspn(buffer, "\n")] = 0;  
        if (strncmp(buffer, "match", 5) == 0) {  
            
            zapasy = realloc(zapasy, (pocetZapasov + 1) * sizeof(Zapas));
            if (zapasy == NULL) {
                printf("Chyba pri alokovani pamäte pre zápasy.\n");
                exit(1);
            }

            fgets(buffer, sizeof(buffer), sub_zapasy);
            token = strtok(buffer, ",");
            for (int i = 0; i < 3; i++) {
                if (token == NULL || atoi(token) == 0) {
                    printf("Nezadane ID pre hráča červeného tímu.\n");
                    exit(1);  
                }
                zapasy[pocetZapasov].cervenyT[i].id = atoi(token);

                for (int j = 0; j < i; j++) {
                    if (zapasy[pocetZapasov].cervenyT[i].id == zapasy[pocetZapasov].cervenyT[j].id) {
                        printf("Hráči v červenom tíme nemôžu hrať pod rovnakým ID.\n");
                        exit(1);
                    }
                }
                token = strtok(NULL, ",");
            }

            fgets(buffer, sizeof(buffer), sub_zapasy);
            token = strtok(buffer, ",");
            for (int i = 0; i < 3; i++) {
                if (sscanf(token, "%d;%d;%d", &zapasy[pocetZapasov].cervenyT[i].killy,
                           &zapasy[pocetZapasov].cervenyT[i].assisty, &zapasy[pocetZapasov].cervenyT[i].smrte) != 3) {
                    printf("Nezadane štatistiky pre hráča červeného tímu.\n");
                    exit(1);
                }
                token = strtok(NULL, ",");
            }

            fgets(buffer, sizeof(buffer), sub_zapasy);
            token = strtok(buffer, ",");
            for (int i = 0; i < 3; i++) {
                if (token == NULL || atoi(token) == 0) {
                    printf("Nezadane ID pre hráča modrého tímu.\n");
                    exit(1);  
                }
                zapasy[pocetZapasov].modryT[i].id = atoi(token);

                for (int j = 0; j < i; j++) {
                    if (zapasy[pocetZapasov].modryT[i].id == zapasy[pocetZapasov].modryT[j].id) {
                        printf("Hráči v modrom tíme nemôžu hrať pod rovnakým ID.\n");
                        exit(1);
                    }
                }
                token = strtok(NULL, ",");
            }

            fgets(buffer, sizeof(buffer), sub_zapasy);
            token = strtok(buffer, ",");
            for (int i = 0; i < 3; i++) {
                if (sscanf(token, "%d;%d;%d", &zapasy[pocetZapasov].modryT[i].killy,
                           &zapasy[pocetZapasov].modryT[i].assisty, &zapasy[pocetZapasov].modryT[i].smrte) != 3) {
                    printf("Nezadane štatistiky pre hráča modrého tímu.\n");
                    exit(1);
                }
                token = strtok(NULL, ",");
            }

            fgets(buffer, sizeof(buffer), sub_zapasy);
            if (sscanf(buffer, "%s", zapasy[pocetZapasov].vitaz) != 1 || (strcmp(zapasy[pocetZapasov].vitaz, "red") != 0 && strcmp(zapasy[pocetZapasov].vitaz, "blue") != 0)) {
                printf("Nezadaný/Zlý formát víťazového tímu.\n");
                exit(1);
            } 
            
            pocetZapasov++;
        }
    }
    fclose(sub_zapasy);
}

