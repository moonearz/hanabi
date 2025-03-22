#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < 4; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void initKnowledge(PLAYER *player) {
    int i,j,k,value;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 5 + RAINBOW_MODE; j++) {
            for(k = 0; k < 5; k++) {
                if(k == 4) {
                    value = 1;
                }
                else if(k == 0) {
                    value = 3;
                }
                else {
                    value = 2;
                }
                player->knowledge[i][j][k] = value;
            }
        }
    }
}

//initializes no knowledges in index 3 for a draw
void newKnowledge(PLAYER *player) {
    int j,k,value;
    for(j = 0; j < 5 + RAINBOW_MODE; j++) {
        for(k = 0; k < 5; k++) {
            if(k == 4) {
                    value = 1;
                }
                else if(k == 0) {
                    value = 3;
                }
                else {
                    value = 2;
                }
                player->knowledge[3][j][k] = value;
        }
    }
}

void printKnowledge(const PLAYER *player) {
    int i,j, k;
    char colors[6][8] = {"RED", "BLUE", "YELLOW", "GREEN", "WHITE", "RAINBOW"};
    printf("Player %i could possibly have in their hand:\n", player->id);
    for(i = 0; i < 4; i++) {
        printf("for card index %i:\n", i);
        printf("          1 2 3 4 5\n");
        for(j = 0; j < 5 + RAINBOW_MODE; j++) {
            printf("%-8s: ", colors[j]);
            for(k = 0; k < 5; k++) {
                printf("%i ", player->knowledge[i][j][k]);
            }
            printf("\n");
        }
    }
}

//index is index of card to discard, also draws
void discardCard(BOARD *board, PLAYER *player, int index) {
    shiftHand(player, index);
    drawCard(player, &board->deck);
}

//index is index of the card that was removed
void shiftHand(PLAYER *player, int index) {
    int i,j,k;
    //index was the card that was "removed"
    for(i = index; i < 3; i++) {
        player->hand[i] = player->hand[i + 1];
        for(j = 0; j < 5 + RAINBOW_MODE; j++) {
            for(k = 0; k < 5; k++) {
                player->knowledge[i][j][k] = player->knowledge[i+1][j][k];
            }
        }
    }
}

void drawCard(PLAYER *player, DECK *deck) {
    player->hand[3] = pop(deck);
    newKnowledge(player);
}
