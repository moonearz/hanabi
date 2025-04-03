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

  /*   MOVE test_move[10];
    for(i = 0; i < 10; i++) {
        test_move[i] = generateRandomMove(&myboard, &myboard.players[0]);
        printMove(test_move[i], &myboard.players[0]);
        printCompactMove(test_move[i]);
    } */
    /* MOVE hint = HINT(0, 0, 'V'); //card index, player index, char type
    MOVE hint2 = HINT(0, 0, 'C');
    MOVE hint3 = HINT(1, 0, 'C');
    MOVE hint4 = HINT(2, 0, 'C');
    MOVE hint6 = HINT(2, 0, 'V');
    MOVE hint5 = HINT(3, 0, 'C');
    PLAYER *hinted = &myboard.players[0];
    updateKnowledgeHint(hinted, hint);
    updateKnowledgeHint(hinted, hint2);
    updateKnowledgeHint(hinted, hint3);
    updateKnowledgeHint(hinted, hint4);
    updateKnowledgeHint(hinted, hint5);
    updateKnowledgeHint(hinted, hint6); */

    PLAYER *player_to_move;
    MOVE random_move;
    freopen("game_output.txt", "w", stdout);

    //TODO: drawing card needs to update players knowledge of their new card based on hands and discard pile
    //Trying out a full game
    while(!(myboard.game_over)) {
        player_to_move = &myboard.players[myboard.move_counter % NUM_PLAYERS];
        random_move = generateRandomMove(&myboard, player_to_move);
        printMove(random_move, player_to_move);
        makeMove(&myboard, player_to_move, random_move);
        printFullGameState(&myboard);
    }

    fclose(stdout);

    return 0;
}