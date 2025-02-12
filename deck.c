#include "defs.h"

extern void printCard(const CARD card) {
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

void printDeck (const DECK *deck) {
    int i, j;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        for(j = 0; j < 10; j++) {
            if(10 * i + j >= (deck->index)) {
                printCard(deck->cards[10 * i + j]);
                printf(" ");
            }
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
    deck->index = 0;
}

void shuffleDeck(DECK *deck) //implements Fisher-Yates shuffling
{
    srand(142857); //seed for debuggging, remove this later
    int i,j;
    CARD temp;
    for(i = deck->index; i < 49 + 10 * RAINBOW_MODE; i++) {
        j = (rand() % (49 + 10 * RAINBOW_MODE - i)) + i;
        temp.color = deck->cards[i].color;
        temp.value = deck->cards[i].value;
        deck->cards[i].color = deck->cards[j].color;
        deck->cards[i].value = deck->cards[j].value;
        deck->cards[j].color = temp.color;
        deck->cards[j].value = temp.value;
    }
}

CARD pop(DECK *deck) {
    CARD top;
    top.color = deck->cards[deck->index].color;
    top.value = deck->cards[deck->index].value;
    (deck->index)++;
    return top;
}

void deal(BOARD *board) //deal 4 cards to every player -- MOST RECENTLY DEALT CARD GOES TO INDEX 3
{
    int i,j;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < NUM_PLAYERS; j++) {
            board->players[j].hand[i] = pop(board->deck);
        }
    }
}