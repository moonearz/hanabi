#include "defs.h"

void printCard(const CARD card) {
    char color;
    switch (card.color) {
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
    printf("%c%i", color, card.value);
}

bool validCard(const CARD card) {
    return card.color != NO_CARD && card.color != UNKNOWN && card.value < 6 && card.value > 0;
}

bool playableCard(const CARD card, const bool fireworks[][5]) {
    if(!validCard(card)) {
        return false;
    }

    int j;
    for(j = 0; j < card.value - 1; j++) {
        if(!fireworks[card.color][j]) {
            return false;
        }
    }

    return !(fireworks[card.color][card.value - 1]);
}