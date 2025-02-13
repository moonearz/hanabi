#include "defs.h"

void printBoard(const BOARD *board) {
    int i;
    for(i = 0; i < NUM_PLAYERS; i++) {
        printf("this is player %i's hand: \n", i + 1);
        printHand((board->players) + i);
    }
    printDeck(board->deck);
}

void initBoard(BOARD *board) {
    board->num_hints = NUM_HINTS;
    board->num_fuses = NUM_FUSES;
    board->move_counter = 0;
    board->num_cards = 50 + 10 * RAINBOW_MODE;
    initDeck(board->deck);
    initDiscard(board);
    shuffleDeck(board->deck);
    deal(board);
}

