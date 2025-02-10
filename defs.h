#include <stdbool.h>

#define NUM_PLAYERS 4
#define NUM_FUSES 3
#define NUM_HINTS 8
#define RAINBOW_MODE false

enum COLOR {RED, BLUE, YELLOW, GREEN, WHITE, RAINBOW};

struct card {
    enum COLOR color;
    int value;
};

struct deck {
    struct card cards[50 + 10 * RAINBOW_MODE];
    int index;
};

struct player {
    struct card hand[4];
    struct card knowledge[4];
};

struct board {
    struct player players[NUM_PLAYERS];
    struct deck deck;
    int num_hints;
    int num_fuses;
};

/* FUNCTIONS */
//board.c
//hand.c
//player.c

