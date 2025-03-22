#include "defs.h"

void printBoard(const BOARD *board) {
    int i;
    for(i = 0; i < NUM_PLAYERS; i++) {
        printf("this is player %i's hand: \n", i + 1);
        printHand((board->players) + i);
    }
    printDeck(&board->deck);
}

void initBoard(BOARD *board) {
    board->num_hints = NUM_HINTS;
    board->num_fuses = NUM_FUSES;
    board->move_counter = 0;
    board->num_cards = 50 + 10 * RAINBOW_MODE;
    initDeck(&board->deck);
    initDiscard(board);
    initFireworks(board->fireworks);
    shuffleDeck(&board->deck);
    deal(board);
}

int getScore(BOARD *board) {
    int i,j,score = 0;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        for(j = 0; j < 5; j++) {
            if(board->fireworks[i][j])
                score++;
        }
    }
    return score;
}

//shifting is taken care of from the player side
//this function should only reduce the possibilites based on new information
//should not reset the knowledge arrays
void fillKnowledge(BOARD *board) {

}