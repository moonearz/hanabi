#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"

#define INTERACTIVE_MODE true

void flush_input() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    srand(142); //seed for debuggging, remove this later
    int i;
    /* printf("The number of players in this game is: %i\n", NUM_PLAYERS);
    printf("Rainbow mode is %s\n", RAINBOW_MODE ? "on" : "off"); */

    BOARD myboard;

    PLAYER *player_to_move;
    MOVE random_move;
    int game_counter = 0;
    char buffer[5];

    if(INTERACTIVE_MODE) {
        MOVE user_move;
        initBoard(&myboard);
        while(!(myboard.game_over)) {
            player_to_move = &myboard.players[myboard.move_counter % NUM_PLAYERS];
            printStateString(&myboard, player_to_move);
            //get user input
            printf("Enter a move: ");
            if (fgets(buffer, sizeof(buffer), stdin)) {
                // remove newline if present
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len - 1] == '\n') {
                    buffer[len - 1] = '\0';
                }
                else {
                    flush_input();
                }
            }
            if (strcmp(buffer, "quit") == 0) {
                exit(0);
            }
            else {
                user_move = MOVE(buffer[0], buffer[1] - '0', buffer[2] - '0', buffer[3]);
                if(!isLegalMove(user_move, &myboard)) {
                    printf("Invalid move!\n");
                    continue;
                }
            }
            printMove(user_move, player_to_move);
            makeMove(&myboard, player_to_move, user_move);
            //printFullGameState(&myboard);
        }
        printf("The score of the game was %i\n", getScore(&myboard));
    }
    else {
        freopen("game_output.txt", "w", stdout);
        //TODO: drawing card needs to update players knowledge of their new card based on hands and discard pile
        //Trying out a full game
        //DRAW KNOWLEDGE NEEDS TO BE TESTED
        //we can test by going the other way, starting with zeros and adding cards back in from the deck (plus player's hand)
        while(game_counter < 15) {
            initBoard(&myboard);
            while(!(myboard.game_over)) {
                player_to_move = &myboard.players[myboard.move_counter % NUM_PLAYERS];
                printStateString(&myboard, player_to_move);
                random_move = generateRandomMove(&myboard, player_to_move);
                printMove(random_move, player_to_move);
                makeMove(&myboard, player_to_move, random_move);
                printFullGameState(&myboard);
            }
            printf("The score of the game was %i\n", getScore(&myboard));
            game_counter++;
        }

        fclose(stdout);
    }

    return 0;
}