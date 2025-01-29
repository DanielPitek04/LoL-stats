#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <math.h>
#include "html.h"
#include "nacitat.h"

int pocetOdohratych = 0; 
int killyHraca = 0;       
int asistHraca = 0;     
int smrteHraca = 0;

void vytvorenie_html(const char *vystupny) {
    FILE *vystup = fopen(vystupny, "w");
    if (vystup == NULL) {
        printf("Súbor nesprávne načítaný (%s).\n", vystupny);
        exit(1);
    }

    fprintf(vystup, "<!DOCTYPE html>\n<html lang=\"cs\">\n<head>\n<link rel=\"stylesheet\" href=\"style.css\">\n<meta charset=\"UTF-8\">\n<title>LoL Projekt</title>\n</head>\n<body>\n");
    fprintf(vystup, "<h1>League of Legends štatistiky</h1>\n");

    // 1. TABULKA      
    fprintf(vystup, "<h2>Stats hráčov ↓</h2>\n");
    fprintf(vystup, "<pre>\n");
    fprintf(vystup, "<table>\n");
    fprintf(vystup, "<tr>\n");
    fprintf(vystup, "<th>Meno hráča</th>\n");
    fprintf(vystup, "<th>Divizia</th>\n");
    fprintf(vystup, "<th>Počet K | A | S</th>\n");
    fprintf(vystup, "<th>Počet zápasov</th>\n");
    fprintf(vystup, "<th>Červený tím</th>\n");
    fprintf(vystup, "<th>Modrý tím</th>\n");
    fprintf(vystup, "<th>Počet výhier</th>\n");  
    fprintf(vystup, "<th>Počet prehier</th>\n");
    fprintf(vystup, "</tr>\n");

    float *ratingy = (float *)malloc(pocetHracov * sizeof(float));
    if (ratingy == NULL) {
        fprintf(stderr, "Chyba pri alokovani pamate pre ratingy.\n");
        exit(1);
    }
    for (int i = 0; i < pocetHracov; i++) {
        ratingy[i] = 1000.0;
    }

    for (int i = 0; i < pocetHracov; i++) {  
        pocetOdohratych = 0; 
        killyHraca = 0;       
        asistHraca = 0;     
        smrteHraca = 0;
        int cerveny = 0;
        int modry = 0;
        int vyhry = 0;          
        int prehry = 0; 

        // ELO premenne
        float ra = 1000;  
        float rb = 1000;
        float ea = 0;
        int sa = 0; 
        int k = 30;     
        char *rank;

        fprintf(vystup, "<tr>\n");  
        fprintf(vystup, "<td>%s</td>\n", hraci[i].meno);  

        for (int a = 0; a < pocetZapasov; a++) {
            int c1 = 0; 
            int m1 = 0;

            for (int j = 0; j < 3; j++) {
                if (zapasy[a].cervenyT[j].id == hraci[i].id) {
                    pocetOdohratych++;  
                    killyHraca += zapasy[a].cervenyT[j].killy;    
                    asistHraca += zapasy[a].cervenyT[j].assisty;  
                    smrteHraca += zapasy[a].cervenyT[j].smrte;
                    cerveny++;
                    c1 = 1;
                    break;  
                }
            }
            for (int j = 0; j < 3; j++) {
                if (zapasy[a].modryT[j].id == hraci[i].id) {
                    pocetOdohratych++;  
                    killyHraca += zapasy[a].modryT[j].killy;    
                    asistHraca += zapasy[a].modryT[j].assisty;  
                    smrteHraca += zapasy[a].modryT[j].smrte;
                    modry++;
                    m1 = 1;
                    break;  
                }
            }
            if (strcmp(zapasy[a].vitaz, "red") == 0 && c1 > 0){vyhry++; sa++;}
            else if (strcmp(zapasy[a].vitaz, "blue") == 0 && m1 > 0) {vyhry++; sa++;}
            else if (strcmp(zapasy[a].vitaz, "red") == 0 && m1 > 0) {prehry++;}
            else if (strcmp(zapasy[a].vitaz, "blue") == 0 && c1 > 0) {prehry++;}

            // elo matematika :)
            if (c1 > 0) {
                for (int j = 0; j < 3; j++) {rb += ratingy[j];}
                rb = rb / 3; 
            }
            if (m1 > 0) {
                for (int j = 0; j < 3; j++) {rb += ratingy[j];}
                rb = rb / 3;  
            }
            ea = 1 / (1 + pow(10, (rb - ra) / 400.0));
            int novy_rating = ra + k * (sa - ea);
            ra = novy_rating;

            if(novy_rating >= 0 && novy_rating <= 1149){rank = "Bronze";}
            else if(novy_rating >= 1150 && novy_rating <= 1499){rank = "Silver";}
            else if(novy_rating >= 1500  && novy_rating <= 1849){rank = "Gold";}
            else if(novy_rating >= 1850  && novy_rating <= 2199){rank = "Platinum";}
            else if(novy_rating >= 2200){rank = "Diamond";}

            ratingy[i] = novy_rating;
        }
        fprintf(vystup, "<td>%s</td>\n", rank);
        fprintf(vystup, "<td>%d | %d | %d</td>\n", killyHraca, asistHraca, smrteHraca);  
        fprintf(vystup, "<td>%d</td>\n", pocetOdohratych);  
        fprintf(vystup, "<td>%d</td>\n", cerveny);  
        fprintf(vystup, "<td>%d</td>\n", modry);  
        fprintf(vystup, "<td>%d</td>\n", vyhry);  
        fprintf(vystup, "<td>%d</td>\n", prehry);
        fprintf(vystup, "</tr>\n");
    }
    free(ratingy);
    fprintf(vystup, "</table>\n");
    fprintf(vystup, "</pre>\n");

    // 2. TABULKA
    fprintf(vystup, "<h2>Stats KDR ↓</h2>\n");
    fprintf(vystup, "<pre>\n");
    fprintf(vystup, "<table>\n");
    fprintf(vystup, "<tr>\n");
    fprintf(vystup, "<th>Meno hráča</th>\n");
    fprintf(vystup, "<th>Počet K | A | S</th>\n");
    fprintf(vystup, "<th>KDR</th>\n"); // Pocet zabiti na pocet umrti
    fprintf(vystup, "<th>KDA</th>\n"); // Pocet zabiti, umrti a asistencii
    fprintf(vystup, "<th>DF</th>\n"); // Faktor dominancie
    fprintf(vystup, "<th>DR</th>\n"); // Pomer dominancie
    fprintf(vystup, "</tr>\n");

    for (int i = 0; i < pocetHracov; i++) {
        killyHraca = 0;       
        asistHraca = 0;     
        smrteHraca = 0;
        double kdr = 0;
        double kda = 0;
        int df = 0;
        double dr = 0;

        fprintf(vystup, "<tr>\n");  
        fprintf(vystup, "<td>%s</td>\n", hraci[i].meno);  
        for (int a = 0; a < pocetZapasov; a++) {
            for (int j = 0; j < 3; j++) {
                if (zapasy[a].cervenyT[j].id == hraci[i].id) {
                    killyHraca += zapasy[a].cervenyT[j].killy;    
                    asistHraca += zapasy[a].cervenyT[j].assisty;  
                    smrteHraca += zapasy[a].cervenyT[j].smrte;
                    break;  
                }
            }
            for (int j = 0; j < 3; j++) {
                if (zapasy[a].modryT[j].id == hraci[i].id) {
                    killyHraca += zapasy[a].modryT[j].killy;    
                    asistHraca += zapasy[a].modryT[j].assisty;  
                    smrteHraca += zapasy[a].modryT[j].smrte;
                    break;  
                }
            }
        }
        kdr = (double)killyHraca / (double)smrteHraca;
        kda = ((double)killyHraca + (double)asistHraca) / (double)smrteHraca;
        dr = ((2 * (double)killyHraca) + (double)asistHraca) / (3 * (double)smrteHraca);
        df = (2 * killyHraca) + asistHraca - (3 * smrteHraca);

        fprintf(vystup, "<td>%d | %d | %d</td>\n", killyHraca, asistHraca, smrteHraca);   
        fprintf(vystup, "<td>%.2f</td>\n", kdr);  
        fprintf(vystup, "<td>%.2f</td>\n", kda);  
        fprintf(vystup, "<td>%d</td>\n", df);  
        fprintf(vystup, "<td>%.2f</td>\n", dr);  
        fprintf(vystup, "</tr>\n");  
    }
    fprintf(vystup, "</table>\n");
    fprintf(vystup, "</pre>\n");

    // 3. TABULKA 
    fprintf(vystup, "<h2>TOP 10 Killerov ↓</h2>\n");
    fprintf(vystup, "<pre>\n");
    fprintf(vystup, "<table>\n");
    fprintf(vystup, "<tr>\n");
    fprintf(vystup, "<th>Miesto hráča</th>");
    fprintf(vystup, "<th>Meno hráča</th>\n");
    fprintf(vystup, "<th>Počet killov</th>\n");
    fprintf(vystup, "</tr>\n");

    int* pocetKillov = (int*)malloc(pocetHracov * sizeof(int));
    if (pocetKillov == NULL) {
        fprintf(stderr, "Chyba pri alokovani pamate pre pocetKillov.\n");
        exit(1);  
    }

    for (int i = 0; i < pocetHracov; i++) {
        pocetKillov[i] = 0;  
        for (int a = 0; a < pocetZapasov; a++) {
            for (int j = 0; j < 3; j++) {
                if (zapasy[a].cervenyT[j].id == hraci[i].id) {
                    pocetKillov[i] += zapasy[a].cervenyT[j].killy;
                }
                if (zapasy[a].modryT[j].id == hraci[i].id) {
                    pocetKillov[i] += zapasy[a].modryT[j].killy;
                }
            }
        }
    }
    for (int i = 0; i < pocetHracov; i++) {
        for (int j = i+1; j < pocetHracov; j++) {
            if (pocetKillov[i] < pocetKillov[j]) {
                int tmp = pocetKillov[i];
                pocetKillov[i] = pocetKillov[j];
                pocetKillov[j] = tmp;
                
                Hrac temp = hraci[i];
                hraci[i] = hraci[j];
                hraci[j] = temp;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        fprintf(vystup, "<tr>\n");
        fprintf(vystup, "<td>%d.</td>\n", i+1);
        fprintf(vystup, "<td>%s</td>\n", hraci[i].meno);
        fprintf(vystup, "<td>%d</td>\n", pocetKillov[i]);
        fprintf(vystup, "</tr>\n");
    }
    fprintf(vystup, "</table>\n");
    fprintf(vystup, "</pre>\n");

    free(pocetKillov);

    // 4. TABULKA
    fprintf(vystup, "<h2>TOP 10 Winnerov ↓</h2>\n");
    fprintf(vystup, "<pre>\n");
    fprintf(vystup, "<table>\n");
    fprintf(vystup, "<tr>\n");
    fprintf(vystup, "<th>Miesto hráča</th>\n");
    fprintf(vystup, "<th>Meno hráča</th>\n");
    fprintf(vystup, "<th>Počet výhier</th>\n");
    fprintf(vystup, "</tr>\n");

    int* pocetVyhier = (int*)malloc(pocetHracov * sizeof(int));
    if (pocetVyhier == NULL) {
        fprintf(stderr, "Chyba pri alokovani pamate pre pocetVyhier.\n");
        exit(1);  
    }

    for (int i = 0; i < pocetHracov; i++) {
        pocetVyhier[i] = 0;
        for (int a = 0; a < pocetZapasov; a++) {
            for (int j = 0; j < 3; j++) {
                if (zapasy[a].cervenyT[j].id == hraci[i].id) {
                    if (strcmp(zapasy[a].vitaz, "red") == 0) {
                        pocetVyhier[i]++;  
                    }
                }
                if (zapasy[a].modryT[j].id == hraci[i].id) {
                    if (strcmp(zapasy[a].vitaz, "blue") == 0) {
                        pocetVyhier[i]++;  
                    }
                }
            }
        }
    }
    for (int i = 0; i < pocetHracov; i++) {
        for (int j = i+1; j < pocetHracov; j++) {
            if (pocetVyhier[i] < pocetVyhier[j]) {
                int tmp = pocetVyhier[i];
                pocetVyhier[i] = pocetVyhier[j];
                pocetVyhier[j] = tmp;

                Hrac temp = hraci[i];
                hraci[i] = hraci[j];
                hraci[j] = temp;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        fprintf(vystup, "<tr>\n");
        fprintf(vystup, "<td>%d.</td>\n", i+1);
        fprintf(vystup, "<td>%s</td>\n", hraci[i].meno);
        fprintf(vystup, "<td>%d</td>\n", pocetVyhier[i]);
        fprintf(vystup, "</tr>\n");
    }
    fprintf(vystup,"</table>\n");
    fprintf(vystup, "</pre>\n");

    free(pocetVyhier);

    // SVG Graf 
    fprintf(vystup, "<h2>Graf s celkovým počtom killov ↓</h2>\n");

    int poziciaX = 50; 
    int sirkaSVG = pocetZapasov * 50;
    fprintf(vystup, "<div class=\"zarovnat\">\n");
    fprintf(vystup, "<svg width=\"%d\" height=\"300\" fill=\"yellow\">\n", sirkaSVG+50);
    fprintf(vystup, "<line x1=\"50\" y1=\"250\" x2=\"%d\" y2=\"250\" class=\"axis\" />\n", sirkaSVG+50); 
    for (int i = 0; i < pocetZapasov; i++) {
        fprintf(vystup, "<text x=\"%d\" y=\"270\" class=\"axis-label\">%d.</text>\n", poziciaX, i + 1);
        poziciaX += 50;
    }
    fprintf(vystup, "<line x1=\"50\" y1=\"50\" x2=\"50\" y2=\"250\" class=\"axis\" />\n");
    fprintf(vystup, "<text x=\"30\" y=\"50\" class=\"axis-label\">100</text>\n");  
    fprintf(vystup, "<text x=\"30\" y=\"100\" class=\"axis-label\">75</text>\n");
    fprintf(vystup, "<text x=\"30\" y=\"150\" class=\"axis-label\">50</text>\n");
    fprintf(vystup, "<text x=\"30\" y=\"200\" class=\"axis-label\">25</text>\n");
    fprintf(vystup, "<text x=\"30\" y=\"250\" class=\"axis-label\">0</text>\n");

    poziciaX = 50; 
    for (int i = 0; i < pocetZapasov; i++) {
        int killsZapas = 0;

        for (int j = 0; j < 3; j++) {
            killsZapas += zapasy[i].cervenyT[j].killy;    
        }
        for (int j = 0; j < 3; j++) {
            killsZapas += zapasy[i].modryT[j].killy;    
        }
        int poziciaY = 250 - killsZapas * (250/100); 
        int height = killsZapas * (250/100); 
        fprintf(vystup, "<rect x=\"%d\" y=\"%d\" width=\"30\" height=\"%d\" class=\"bar\" />\n", poziciaX, poziciaY, height); 
        poziciaX += 50;  
    }
    fprintf(vystup, "</svg>\n");
    fprintf(vystup, "</div>\n");

    fprintf(vystup, "<footer>\n");
    fprintf(vystup, "UPR Projekt 2024/2025 • League of Legends Štatistiky | Daniel Pitek\n");
    fprintf(vystup, "</footer>\n");
    fprintf(vystup, "</body>\n</html>\n");

    fclose(vystup);
}