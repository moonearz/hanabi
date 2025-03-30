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

    //printVisibleGameState(&myboard);
    //playCard(&myboard, &myboard.players[0], 2);
    //playCard(&myboard, &myboard.players[1], 1);
    //playCard(&myboard, &myboard.players[1], 1);
    //playCard(&myboard, &myboard.players[1], 1);

    //I don't currently understand why it needs to be knowledge[0]
    /* knownColor(&myboard.players[0].knowledge, 0, RED);
    knownNotColor(&myboard.players[1].knowledge, 0, RED);
    knownValue(&myboard.players[2].knowledge, 0, 4);
    knownNotValue(&myboard.players[3].knowledge, 0, 4); */

    MOVE test_move[10];
    for(i = 0; i < 10; i++) {
        test_move[i] = generateRandomMove(&myboard, &myboard.players[0]);
        printMove(test_move[i], &myboard.players[0]);
        printCompactMove(test_move[i]);
    }

    //printFullGameState(&myboard);

    return 0;
}