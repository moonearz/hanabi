#include "defs.h"

//visible game state consists of players hands, discard pile, tokens, played cards = board
void printVisibleGameState(const BOARD *board) {
    printf("The number of hint tokens available is: %i\n", board->num_hints);
    printf("The number of fuses left is: %i\n", board->num_fuses);
    printf("The discard pile looks like: ");
    printDiscard(&board->discard_pile);
    int i;
    for(i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %i's hand is: ", i + 1);
        printHand(&board->players[i]);
    }
    printf("The board looks like: \n");
    printFireworks(board->fireworks);
}

void printFullGameState(const BOARD *board) {

}

void initBoard(BOARD *board) {
    board->num_hints = NUM_HINTS;
    board->num_fuses = NUM_FUSES;
    board->move_counter = 0;
    board->num_cards = 50 + 10 * RAINBOW_MODE;
    initPlayers(board);
    initDeck(&board->deck);
    initDiscard(board);
    initFireworks(board->fireworks);
    shuffleDeck(&board->deck);
    deal(board);
}

void initPlayers(BOARD *board) {
    int i,j;
    for(i = 0; i < NUM_PLAYERS; i++) {
        board->players[i].id = i + 1;
        initKnowledge(&board->players[i]);
    }
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