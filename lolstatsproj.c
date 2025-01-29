#include <stdio.h>
#include <stdlib.h>
#include "nacitat.h"
#include "html.h"

int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr,"Zle zadane parametry.\n");
        return 1;
    }

    nacitat_zapasy(argv[1]);
    nacitat_hracov(argv[2]);
    vytvorenie_html(argv[3]);

    free(hraci); 
    free(zapasy);  

    return 0;
}
