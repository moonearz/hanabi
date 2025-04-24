#include "defs.h"

//visible game state consists of players hands, discard pile, tokens, played cards = board
void printVisibleGameState(const BOARD *board) {
    printf("The number of hint tokens available is: %i\n", board->num_hints);
    printf("The number of fuses left is: %i\n", board->num_fuses);
    printf("The discard pile looks like: ");
    printDiscard(&board->discard_pile);
    int i;
    for(i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %i's hand is: ", i + 1);
        printHand(&board->players[i]);
    }
    printf("The board looks like: \n");
    printFireworks(board->fireworks);
}

//includes deck, knowledge, move number
void printFullGameState(const BOARD *board) {
    printVisibleGameState(board);
    printPlayerKnowledge(board);
    printf("Here is the state of the deck: \n");
    printDeck(&board->deck);
    printf("The move number is now: %i\n", board->move_counter + 1);
}

//this occurs before a move, represents the board to a player who is about to move
//in no particular order, hands, tokens, discard pile, played cards, game knowledge
void printStateString(const BOARD *board, const PLAYER *player_to_move) {
    int i,j;
    printf("%i|", board->num_fuses);
    printf("%i|", board->num_hints);
    printDiscardString(&board->discard_pile);
    printf("|");
    printPlayedCardsString(board->fireworks);
    printf("|");
    for(i = 0; i < NUM_PLAYERS; i++) {
        printKnowledgeString(&board->players[i]);
        printf("|");
    }
    for(i = 0; i < NUM_PLAYERS; i++) {
        if(i != player_to_move->id) {
            printHandString(&board->players[i]);
        }
        if(i < NUM_PLAYERS - 1) {
            printf("|");
        }
    }
    printf("\n");
}

void printPlayerKnowledge(const BOARD *board) {
    int i;
    for(int i = 0; i < NUM_PLAYERS; i++) {
        //printf("Player %i's knowledge matrix looks like: \n", i);
        printKnowledge(&board->players[i]);
    }
}

void initBoard(BOARD *board) {
    board->num_hints = MAX_HINTS;
    board->num_fuses = MAX_FUSES;
    board->move_counter = 0;
    board->num_cards = 50 + 10 * RAINBOW_MODE;
    board->game_over = false;
    initPlayers(board);
    initDeck(&board->deck);
    initDiscard(board);
    initFireworks(board->fireworks);
    shuffleDeck(&board->deck);
    deal(board);
    gameStartKnowledge(board);
    board->countdown = NUM_PLAYERS;
    board->deck_empty = false;
}

void initPlayers(BOARD *board) {
    int i,j;
    for(i = 0; i < NUM_PLAYERS; i++) {
        board->players[i].id = i;
        initKnowledge(&board->players[i]);
    }
}

int getScore(BOARD *board) {
    int i,j,score = 0;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        for(j = 0; j < 5; j++) {
            if(board->fireworks[i][j])
                score++;
        }
    }
    return score;
}

//initialize knowledge after first cards have been dealt
//only need to look at players' hands
void gameStartKnowledge(BOARD *board) {
    int i,j,k,l;
    CARD tmp;
    for(i = 0; i < NUM_PLAYERS; i++) { //adjusting knowledge of player i
        for(l = 0; l < HAND_SIZE; l++) { //iterating through cards in player i's hand
            for(j = 0; j < NUM_PLAYERS; j++) { //comparing cards to player j
                if(j == i)
                    continue;
                for(k = 0; k < HAND_SIZE; k++) { //iterating through cards in player j's hand
                    tmp = board->players[j].hand[k];
                    (board->players[i].knowledge[l][tmp.color][tmp.value - 1])--;
                }
            }
        }
    }
}

//shifting is taken care of from the player side
//this function should only reduce the possibilites based on new information
//should not reset the knowledge arrays
//a player just discarded or played a card and drew a new one so:
//  every other player compares their current knowledge with the new card drawn
//  the current player learns what their card was (see discard pile) and updates their hand knowledge accordingly. Their new card's knowledge
//  is also initialized
//  drawer is the player who drew the card
void updateKnowledgeDraw(BOARD *board, PLAYER *drawer, CARD drawn_card) {
    int i, j, temp_int;
    CARD tmp;
    if(drawn_card.color == NO_CARD) {
        zeroKnowledge(drawer);
    }
    else {
        //updating knowledge for other players based on drawn card
        for(i = 0; i < NUM_PLAYERS; i++) {
            for(j = 0; j < HAND_SIZE; j++) {
                //writing into old knowledge for the drawer's new card but it's getting reset anyways
                temp_int = (board->players[i].knowledge[j][drawn_card.color][drawn_card.value - 1])--;
                if(temp_int < 0) {
                    (board->players[i].knowledge[j][drawn_card.color][drawn_card.value - 1]) = 0;
                }
            }
        }
        newKnowledge(drawer);
        //drawer compares their new card to every card that's visible to them
        //places to check: discard pile, other player's hands, their own hands if they know what a card is
        for(i = 0; i <  HAND_SIZE - 1; i++) {
            //cards in hand
            if(cardKnown(drawer, i)) {
                tmp = drawer->hand[i];
                (drawer->knowledge[HAND_SIZE - 1][tmp.color][tmp.value - 1])--;
            }
        }
        //other players hands
        for(i = 0; i < NUM_PLAYERS; i++) {
            if(i == drawer->id)
                continue;
            for(j = 0; j < HAND_SIZE; j++) {
                tmp = board->players[i].hand[j];
                (drawer->knowledge[HAND_SIZE - 1][tmp.color][tmp.value - 1])--;
            }
        }
        //discard pile
        for(i = 0; i < board->discard_pile.index; i++) {
            ASSERT((board->discard_pile.cards[i].color) != NO_CARD);
            tmp = board->discard_pile.cards[i];
            (drawer->knowledge[HAND_SIZE - 1][tmp.color][tmp.value - 1])--;
        }
    }
}

//controls the logic for actually moving the game forward when a move happens
//maybe need to know the player a priori? For generating a legal move?
void makeMove(BOARD *board, PLAYER *player, MOVE move) {
    //casework based on which type of move
    if(move.move_type == PLAY) {
        playCard(board, player, move.index_of_card);
        drawKnowledge(player, board);
        //check if num fuses becomes 0 -> set game over to true if so
        if(board->num_fuses == 0) {
            board->game_over = true;
        }
    }
    else if(move.move_type == DISCARD) {
        discardCard(board, player, move.index_of_card);
        drawKnowledge(player, board);
    }
    else {
        updateKnowledgeHint(&board->players[move.player_index], move);
        (board->num_hints)--;
    }
    if(board->deck_empty)
        (board->countdown)--;
    else if(board->deck.index == (50 + 10 * RAINBOW_MODE))
        board->deck_empty = true;
    (board->move_counter)++;
    //check if turns have elapsed and game is over
    if(board->countdown == 0)
        board->game_over = true;
    if(getScore(board) == MAX_SCORE)
        board->game_over = true;
}

bool isLegalMove(MOVE move, BOARD *board) {
    if(move.move_type == HINT) {
        return move.player_index != (board->move_counter % NUM_PLAYERS);
    }
    return true;
}