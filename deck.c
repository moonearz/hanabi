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

void printDeck (const DECK *deck) {
    int i, j;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        for(j = 0; j < 10; j++) {
            printCard(&deck->cards[10 * i + j]);
            printf(" ");
        }
        printf("\n");
    }
}

void initDeck(DECK *deck) {
    int i,j;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        enum COLOR current = i;
        for(j = 0; j < 10; j++) {
            deck->cards[10 * i + j].color = current;
            if(j < 3) {
                deck->cards[10 * i + j].value = 1;
            }
            else if(j < 5) {
                deck->cards[10 * i + j].value = 2;
            }
            else if(j < 7) {
                deck->cards[10 * i + j].value = 3;
            }
            else if(j < 9) {
                deck->cards[10 * i + j].value = 4;
            }
            else {
                deck->cards[10 * i + j].value = 5;
            }
        }
    }
}
