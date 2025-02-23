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

    CARD testCards[4];
    testCards[0].color = RED;
    testCards[0].value = 1;
    testCards[1].color = BLUE;
    testCards[1].value = 3;
    testCards[2].color = NO_CARD;
    testCards[2].value = 2;
    testCards[3].color = GREEN;
    testCards[3].value = 6;

    for(i = 0; i < 4; i++) {
        printf("the card ");
        printCard(testCards[i]);
        printf(" is %s\n", playableCard(testCards[i], myboard.fireworks) ? "playable" : "not playable");
    }


    return 0;
}