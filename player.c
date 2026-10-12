#include "defs.h"

void printHand(const PLAYER *player) {
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        printCard(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void printHandString(const PLAYER *player) {
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        printCard(player->hand[i]);
    }
}

void initKnowledge(PLAYER *player) {
    int i, j, k, value;

    for (i = 0; i < HAND_SIZE; i++) {
        for (j = 0; j < 5 + RAINBOW_MODE; j++) {
            for (k = 0; k < 5; k++) {
                if (k == 4) {
                    value = 1;
                } else if (k == 0) {
                    value = 3;
                } else {
                    value = 2;
                }
                player->knowledge[i][j][k] = value;
            }
        }
    }
}

// initializes no knowledge in index hand size - 1 for a draw
void newKnowledge(PLAYER *player) {
    int j, k, value;
    for (j = 0; j < 5 + RAINBOW_MODE; j++) {
        for (k = 0; k < 5; k++) {
            if (k == 4) {
                value = 1;
            } else if (k == 0) {
                value = 3;
            } else {
                value = 2;
            }
            player->knowledge[HAND_SIZE - 1][j][k] = value;
        }
    }
}

// initializes the knowledge for a new draw based on the visible cards
void drawKnowledge(PLAYER *player, BOARD *board) {
    // do nothing if the card is not a card
    if (player->hand[HAND_SIZE - 1].color == NO_CARD)
        return;
    // need to iterate through hands, discard pile, board
    // actually, because of the way the deck is structured maybe I can just go
    // through all the "seen" cards double counts because the players hand is
    // included in that solution: add back cards in the players hand
    int i, j;
    int current_index = board->deck.index;
    CARD tmp;
    for (i = 0; i < current_index; i++) {
        tmp = board->deck.cards[i];
        (player->knowledge[HAND_SIZE - 1][tmp.color][tmp.value - 1])--;
    }
    for (j = 0; j < HAND_SIZE; j++) {
        tmp = player->hand[j];
        (player->knowledge[HAND_SIZE - 1][tmp.color][tmp.value - 1])++;
    }
}

void printKnowledge(const PLAYER *player) {
    int i, j, k;
    char colors[6][8] = {"RED", "BLUE", "YELLOW", "GREEN", "WHITE", "RAINBOW"};
    printf("Player %i could possibly have in their hand:\n", player->id + 1);
    for (i = 0; i < HAND_SIZE; i++) {
        printf("for card index %i:\n", i);
        printf("          1 2 3 4 5\n");
        for (j = 0; j < 5 + RAINBOW_MODE; j++) {
            printf("%-8s: ", colors[j]);
            for (k = 0; k < 5; k++) {
                printf("%i ", player->knowledge[i][j][k]);
            }
            printf("\n");
        }
    }
}

void printKnowledgeString(const PLAYER *player) {
    int i, j, k;
    for (i = 0; i < HAND_SIZE; i++) {
        for (j = 0; j < 5 + RAINBOW_MODE; j++) {
            for (k = 0; k < 5; k++) {
                printf("%i", player->knowledge[i][j][k]);
            }
        }
    }
}

// sets the knowledge of hand size - 1 to 0 in the case of no card
void zeroKnowledge(PLAYER *player) {
    int j, k, value;
    for (j = 0; j < 5 + RAINBOW_MODE; j++) {
        for (k = 0; k < 5; k++) {
            player->knowledge[HAND_SIZE - 1][j][k] = 0;
        }
    }
}

// return true if there is only one (or zero) possible value of the card at
// index index
bool cardKnown(PLAYER *player, int index) {
    int i, j;
    int num_candidates = 0;
    for (i = 0; i < 5 + RAINBOW_MODE; i++) {
        for (j = 0; j < 5; j++) {
            if ((player->knowledge[index][i][j]) > 0)
                num_candidates++;
        }
    }
    return (num_candidates < 2);
}
