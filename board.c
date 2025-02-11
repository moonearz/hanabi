#include "defs.h"

void printBoard(const BOARD *board) {
    int i;
    for(i = 0; i < NUM_PLAYERS; i++) {
        printf("this is player %i's hand: \n", i + 1);
        printHand((board->players) + i);
    }
    initDeck(board->deck);
    printDeck(board->deck);
}