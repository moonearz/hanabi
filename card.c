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

CARD makeCard(char color, int value) {
    CARD c;
    ASSERT(color == 'B' || color == 'R' || color == 'Y' || color == 'G' || color == 'W' || color == 'X' || color == 'N');
    ASSERT(value > 0 && value < 6);
    switch(color) {
        case 'R':
            c.color = RED;
            break;
        case 'B':
            c.color = BLUE;
            break;
        case 'G':
            c.color = GREEN;
            break;
        case 'Y':
            c.color = YELLOW;
            break;
        case 'W':
            c.color = WHITE;
            break;
        case 'X':
            c.color = RAINBOW;
            break;
        default:
            c.color = NO_CARD;
    }
    c.value = value;
    return c;
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