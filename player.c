#include "defs.h"

extern void printCard(const CARD *card) {
    char color;
    switch (card->color) {
        case RED:
            color = 'R';
            break;
        case BLUE:
            color = 'B';
            break;
        case YELLOW:
            color = 'Y';
            break;
        case GREEN:
            color = 'G';
            break;
        case WHITE:
            color = 'W';
            break;
        default:
            color = 'X';
            break;
    }
    printf("%c%i", color, card->value);
}

void printHand(const PLAYER *player) {
    int i;
    for(i = 0; i < 4; i++) {
        printCard((player->hand) + i);
        printf(" ");
    }
    printf("\n");
}