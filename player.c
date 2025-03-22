#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < 4; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void printKnowledge(const PLAYER *player) {
    
}

//index is index of card to discard, also draws
void discardCard(BOARD *board, PLAYER *player, int index) {
    shiftHand(player, index);
    drawCard(player, &board->deck);
}

//index is index of the card that was removed
void shiftHand(PLAYER *player, int index) {
    int i;
    //index was the card that was "removed"
    for(i = index; i < 3; i++) {
        player->hand[i] = player->hand[i + 1];
    }
}

void drawCard(PLAYER *player, DECK *deck) {
    player->hand[3] = pop(deck);
}
