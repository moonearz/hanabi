#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < 4; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void discardCard(BOARD *board, PLAYER *player, int index) {

}

void shiftHand(PLAYER *player, int index) {

}

void drawCard(PLAYER *player, DECK *deck) {

}