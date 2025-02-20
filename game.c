#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"

int main() {
    int i;
    /* printf("The number of players in this game is: %i\n", NUM_PLAYERS);
    printf("Rainbow mode is %s\n", RAINBOW_MODE ? "on" : "off"); */

    BOARD myboard;
    initBoard(&myboard);
    printBoard(&myboard);
    printf("the current score is: %i\n", getScore(&myboard));


    return 0;
}