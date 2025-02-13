#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"

int main() {
    int i;
    /* printf("The number of players in this game is: %i\n", NUM_PLAYERS);
    printf("Rainbow mode is %s\n", RAINBOW_MODE ? "on" : "off"); */

    BOARD myboard;
    myboard.deck = malloc(sizeof (DECK));
    myboard.discard_pile = malloc(sizeof (DECK));
    initBoard(&myboard);
    printBoard(&myboard);


    return 0;
}