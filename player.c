#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < 4; i++) {
        printCard((player->hand) + i);
        printf(" ");
    }
    printf("\n");
}