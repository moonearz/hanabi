#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < HAND_SIZE; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void printHandString(const PLAYER *player) {
    int i;
    for(i = 0; i < HAND_SIZE; i++) {
        printCard(player->hand[i]);
    }
}

void initKnowledge(PLAYER *player) {
    int i,j,k,value;

    for(i = 0; i < HAND_SIZE; i++) {
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

//initializes no knowledges in index hand size - 1 for a draw
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
                player->knowledge[HAND_SIZE - 1][j][k] = value;
        }
    }
}

void printKnowledge(const PLAYER *player) {
    int i,j, k;
    char colors[6][8] = {"RED", "BLUE", "YELLOW", "GREEN", "WHITE", "RAINBOW"};
    printf("Player %i could possibly have in their hand:\n", player->id + 1);
    for(i = 0; i < HAND_SIZE; i++) {
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

void printKnowledgeString(const PLAYER *player) {
    int i,j,k;
    for(i = 0; i < HAND_SIZE; i++) {
        for(j = 0; j < 5 + RAINBOW_MODE; j++) {
            for(k = 0; k < 5; k++) {
                printf("%i", player->knowledge[i][j][k]);
            }
        }
    }
}

//sets the knowledge of hand size - 1 to 0 in the case of no card
void zeroKnowledge(PLAYER *player) {
    int j,k,value;
    for(j = 0; j < 5 + RAINBOW_MODE; j++) {
        for(k = 0; k < 5; k++) {
            player->knowledge[HAND_SIZE - 1][j][k] = 0;
        }
    }
}

//return true if there is only one (or zero) possible value of the card at index index
bool cardKnown(PLAYER *player, int index) {
    int i, j;
    int num_candidates = 0;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        for(j = 0; j < 5; j++) {
            if((player->knowledge[index][i][j]) > 0)
                num_candidates++;
        }
    }
    return (num_candidates < 2);
}
