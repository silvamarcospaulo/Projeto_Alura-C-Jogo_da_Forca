#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tad.h"

int main() {
    int menuOption = 0;
    int continu = 1;

    lineBreak();

    opening();

    do {
        menu();
        scanf("%d", &menuOption);

        switch (menuOption){
        
        case (1):
            newGame();
            break;

        case (2):
            rules();
            break;

        case (3):
            credits();
            break;

        case (4):
            shutDown();
            continu--;
            break;
        
        default:
            lineBreak();
            printf("OPCAO INVALIDA!\nEscolha uma opcao entre 1 e 4!\n");
            break;
        }

        }while(continu);

    return 0;
}