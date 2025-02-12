#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_PLAYERS 4
#define NUM_FUSES 3
#define NUM_HINTS 8
#define RAINBOW_MODE false

enum COLOR {RED = 0, BLUE = 1, YELLOW = 2, GREEN = 3, WHITE = 4, RAINBOW = 5, NO_CARD = 6, UNKNOWN = 7};

typedef struct {
    enum COLOR color;
    int value;
} CARD;

typedef struct {
    CARD cards[50 + 10 * RAINBOW_MODE];
    int index;
} DECK;

typedef struct {
    CARD hand[4];
    CARD knowledge[4 * NUM_PLAYERS];
} PLAYER;

typedef struct {
    PLAYER players[NUM_PLAYERS];
    DECK *deck;
    DECK *discard_pile;
    int num_hints;
    int num_fuses;
    int move_counter;
    int num_cards;
} BOARD;

/* FUNCTIONS */
//board.c
extern void printBoard(const BOARD *board);
//player.c
extern void printHand(const PLAYER *player);
//deck.c
extern void printCard(const CARD card);
extern void printDeck(const DECK *deck);
extern void initDeck(DECK *deck);
extern void shuffleDeck(DECK *deck);
extern CARD pop(DECK *deck); 
void deal(BOARD *board);

