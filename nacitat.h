#ifndef NACITAT_H
#define NACITAT_H

typedef struct {
    int id;
    char meno[50];
    int killy;
    int assisty;
    int smrte;
} Hrac;

typedef struct {
    Hrac cervenyT[3];  
    Hrac modryT[3]; 
    char vitaz[10];    
} Zapas;

extern Hrac *hraci;       
extern int pocetHracov;    

extern Zapas *zapasy;     
extern int pocetZapasov;     

void nacitat_zapasy(const char *sub_zapasy); 
void nacitat_hracov(const char *sub_hraci);  

#endif