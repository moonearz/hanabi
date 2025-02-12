#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"

int main() {
    int i;
    printf("The number of players in this game is: %i\n", NUM_PLAYERS);
    printf("Rainbow mode is %s\n", RAINBOW_MODE ? "on" : "off");

    BOARD myboard;
    initDeck(myboard.deck);
    shuffleDeck(myboard.deck);
    deal(&myboard);
    printBoard(&myboard);


    return 0;
}