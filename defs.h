#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) {\
printf("%s - Failed", #n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n ",__LINE__); \
exit(1);}
#endif

#define NUM_PLAYERS 4
#define HAND_SIZE 4 + (NUM_PLAYERS < 4)
#define NUM_FUSES 3
#define NUM_HINTS 8
#define RAINBOW_MODE false

enum COLOR {RED = 0, BLUE = 1, YELLOW = 2, GREEN = 3, WHITE = 4, RAINBOW = 5, NO_CARD = 6, UNKNOWN = 7};
enum MOVES {HINT = 1, PLAY = 2, DISCARD = 3};
enum HINT_TYPE{COLOR = 1, NUMBER = 2, NOHINT = 3};

typedef struct {
    enum MOVES move_type;
    int index; //index of card discarded or played, -1 for a hint?
    enum HINT_TYPE;
} MOVE;

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
    int knowledge[HAND_SIZE][5 + RAINBOW_MODE][5]; //represents knowledge the player has about their own hand, for each card
    int id;
} PLAYER;

typedef struct {
    PLAYER players[NUM_PLAYERS];
    DECK deck;
    DECK discard_pile;
    bool fireworks[5 + RAINBOW_MODE][5];
    int num_hints;
    int num_fuses;
    int move_counter;
    int num_cards;
} BOARD;

/* FUNCTIONS */
//board.c
extern void initBoard(BOARD *board);
extern int getScore(BOARD *board);
extern void initPlayers(BOARD *board);
extern void fillKnowledge(BOARD *board);
extern void printVisibleGameState(const BOARD *board);
extern void printFullGameState(const BOARD *board);
//player.c
extern void printHand(const PLAYER *player);
extern void discardCard(BOARD *board, PLAYER *player, int index);
extern void shiftHand(PLAYER *player, int index);
extern void drawCard(PLAYER *player, DECK *deck);
extern void printKnowledge(const PLAYER *player);
extern void initKnowledge(PLAYER *player);
extern void newKnowledge(PLAYER *player);
//deck.c
extern void printDeck(const DECK *deck);
extern void printDiscard(const DECK *discard);
extern void initDeck(DECK *deck);
extern void initDiscard(BOARD *board);
extern void pushDiscard(DECK *discard, CARD card);
extern void shuffleDeck(DECK *deck);
extern CARD pop(DECK *deck); 
extern void deal(BOARD *board);
extern void initFireworks(bool fireworks[][5]);
extern void printFireworks(bool fireworks[][5]);
//card.c
extern void printCard(const CARD card);
extern bool validCard(const CARD card);
extern bool playableCard(const CARD card, const bool fireworks[][5]);
//move.c
extern bool isLegalMove(const MOVE* move);
