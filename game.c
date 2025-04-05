#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"

int main() {
    srand(142); //seed for debuggging, remove this later
    int i;
    /* printf("The number of players in this game is: %i\n", NUM_PLAYERS);
    printf("Rainbow mode is %s\n", RAINBOW_MODE ? "on" : "off"); */

    BOARD myboard;

    PLAYER *player_to_move;
    MOVE random_move;
    int game_counter = 0;
    freopen("game_output.txt", "w", stdout);

    //TODO: drawing card needs to update players knowledge of their new card based on hands and discard pile
    //Trying out a full game
    while(game_counter < 15) {
        initBoard(&myboard);
        while(!(myboard.game_over)) {
            player_to_move = &myboard.players[myboard.move_counter % NUM_PLAYERS];
            printStateString(&myboard, player_to_move);
            random_move = generateRandomMove(&myboard, player_to_move);
            //printMove(random_move, player_to_move);
            makeMove(&myboard, player_to_move, random_move);
            //printFullGameState(&myboard);
        }
        printf("The score of the game was %i\n", getScore(&myboard));
        game_counter++;
    }

    fclose(stdout);

    return 0;
}