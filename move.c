#include "defs.h"

bool isLegalMove(const MOVE* move) {
    return true;
}

//index is index of card to discard, also draws
void discardCard(BOARD *board, PLAYER *player, int index) {
    pushDiscard(&board->discard_pile, player->hand[index]);
    shiftHand(player, index);
    drawCard(player, &board->deck);
    if((board->num_hints) < MAX_HINTS) {
        (board->num_hints)++;
    }
}

//index is index of the card that was removed
void shiftHand(PLAYER *player, int index) {
    int i,j,k;
    //index was the card that was "removed"
    for(i = index; i < HAND_SIZE - 1; i++) {
        player->hand[i] = player->hand[i + 1];
        for(j = 0; j < 5 + RAINBOW_MODE; j++) {
            for(k = 0; k < 5; k++) {
                player->knowledge[i][j][k] = player->knowledge[i+1][j][k];
            }
        }
    }
}

void drawCard(PLAYER *player, DECK *deck) {
    if(deck->index == (50 + 10 * RAINBOW_MODE)) {
        CARD empty = makeCard('N', 0);
        player->hand[HAND_SIZE - 1] = empty;
        newKnowledge(player); //is this the right choice? they know what card it is
        return;
    }
    player->hand[HAND_SIZE - 1] = pop(deck);  
    newKnowledge(player);
}

//check if card is valid? check if card is playable, if yes update fireworks, if no discard and remove fuse token
void playCard(BOARD *board, PLAYER *player, int index) {
    ASSERT(validCard(player->hand[index]));
    if(playableCard(player->hand[index], board->fireworks)) {
        CARD temp;
        temp.color = player->hand[index].color;
        temp.value = player->hand[index].value;
        board->fireworks[temp.color][temp.value - 1] = true;
        if(temp.value == 5 && (board->num_hints) < MAX_HINTS) {
            (board->num_hints)++;
        }
        shiftHand(player, index);
        drawCard(player, &board->deck);
    }
    else {
        pushDiscard(&board->discard_pile, player->hand[index]);
        shiftHand(player, index);
        drawCard(player, &board->deck);
        (board->num_fuses)--;
    }
}

//check id hinted is not the hint giver-- does this require knowing the hint giver? -> implicit in whose turn it is, player already decided
//color hint is true if hinting color, false if hinting number
//this should be made after thinking about knowledge a bit
void giveHint(BOARD *board, int id_hinted, int card_index, bool color_hint) {

}

bool canHint(const BOARD *board) {
    return (board->num_hints > 0);
}

bool canDiscard(const BOARD *board) {
    return (board->num_hints < MAX_HINTS);
}


//player is the player whose turn it is
MOVE generateRandomMove(const BOARD *board, const PLAYER *player) {
    MOVE output;
    int range = 3;
    if(!canHint(board))
        range--;
    if(!canDiscard(board))
        range--;
    
    int r = rand() % range;
    switch(r) {
        case 0:
            output.move_type = PLAY;
            break;
        case 1:
            if(!canHint(board)) {
                output.move_type = DISCARD;
            }
            else {
                output.move_type = HINT;
            }
            break;
        case 2:
            output.move_type = DISCARD;
            break;
    }
    //type of move is now determined, fill in details
    if(output.move_type == HINT) {
        output.hint_type = (enum HINT_TYPE)(rand() % 2 + 1);

        int player_index = player->id; //we need to hint someone who isn't this player
        while(player_index == player->id) {
            player_index = rand() % NUM_PLAYERS;
        }
        output.player_index = player_index;
        int range = HAND_SIZE;
        //there's an edge case at the end of the game where a player has fewer than three cards-- gotta check
        /* if(&board->players[player_index].hand[HAND_SIZE - 1].color == NO_CARD)
            range--; */
        output.index_of_card = rand() % range;
    }
    else {
        int index_choice = rand() % HAND_SIZE;
        output.index_of_card = index_choice;
        output.hint_type = NOHINT;
        output.player_index = 6; //6 as a nonsensical value for index that isn't used
    }
    
    return output;
}

MOVE createMove(char type, int card_index, int player_index, char hint_t) {
    MOVE out;
    ASSERT(type == 'H' || type == 'P' || type == 'D'); //type of move is hint, play, or discard
    ASSERT(card_index > -1 && card_index < HAND_SIZE);
    ASSERT(player_index > -1 && player_index < 7);
    ASSERT(hint_t == 'C' || hint_t == 'V' || hint_t == 'N'); //hint type is color, value, or no hint
    out.index_of_card = card_index;
    out.player_index = player_index;
    switch(type) {
        case 'H':
            out.move_type = HINT;
            out.hint_type = (hint_t == 'C') ? COLOR : VALUE;
            break;
        case 'P':
            out.move_type = PLAY;
            out.hint_type = NOHINT;
            break;
        default:
            out.move_type = DISCARD;
            out.hint_type = NOHINT;
            break;
    }
    return out;
}

void printMove(const MOVE move, const PLAYER *player) {
    if(move.move_type == HINT) {
        printf("Player %i is hinting player %i their card at index %i for %s\n", player->id + 1, move.player_index + 1, move.index_of_card, (move.hint_type == COLOR) ? "color" : "value");
    }
    else if(move.move_type == PLAY) {
        printf("Player %i is playing the card at index %i in their hand\n", player->id + 1, move.index_of_card);
    }
    else {
        printf("Player %i is discarding the card at index %i in their hand\n", player->id + 1, move.index_of_card);
    }
}

void printCompactMove(const MOVE move) {
    char out[5];
    switch(move.move_type) {
        case HINT:
            out[0] = 'H';
            out[2] = move.player_index + '0';
            out[3] = (move.hint_type == COLOR) ? 'C' : 'V';
            break;
        case PLAY:
            out[0] = 'P';
            out[2] = '6';
            out[3] = 'N';
            break;
        default:
            out[0] = 'D';
            out[2] = '6';
            out[3] = 'N';
            break;
    }
    out[1] = move.index_of_card + '0';
    out[4] = '\0';
    printf("%s\n", out);
}

//only internal knowledge needs to be updated, positive knowledge for hinted cards, negative knowledge for other cards
//things get zeroed out kind of "unnaturally", will need to check (externally) that values don't become less than 0
void updateKnowledgeHint(PLAYER *player, MOVE hint) {
    ASSERT(hint.hint_type != NOHINT);
    int i;
    //starting with positive knowledge
    if(hint.hint_type == COLOR) {
        enum COLOR hinted_color = player->hand[hint.index_of_card].color;
        for(i = 0; i  < HAND_SIZE; i++) { //apply the hint for all cards that have hinted color
            if(player->hand[i].color == hinted_color) {
                knownColor(player->knowledge, i, hinted_color);
            }
            else {
                knownNotColor(player->knowledge, i, hinted_color);
            }
        }   
    }
    else {
        int hinted_value = player->hand[hint.index_of_card].value;
         for(i = 0; i  < HAND_SIZE; i++) { //apply the hint for all cards that have hinted color
            if(player->hand[i].value == hinted_value) {
                knownValue(player->knowledge, i, hinted_value);
            }
            else {
                knownNotValue(player->knowledge, i, hinted_value);
            }
        }

    }
}

void knownColor(int knowledge[][5 + RAINBOW_MODE][5], int index, enum COLOR color) {
    int i,j;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) { //colors
        if(i == color)
            continue;
        for(j = 0; j < 5; j++) { //values
            knowledge[index][i][j] = 0;
        }
    }
}

void knownValue(int knowledge[][5 + RAINBOW_MODE][5], int index, int value) {
    int i,j;
    for(i = 0; i < 5; i++) { //values
        if(i == (value - 1))
            continue;
        for(j = 0; j < 5 + RAINBOW_MODE; j++) { //colors
            knowledge[index][j][i] = 0;
        }
    }
}

void knownNotColor(int knowledge[][5 + RAINBOW_MODE][5], int index, enum COLOR color) {
    int i;
    for(i = 0; i < 5; i++) {
        knowledge[index][color][i] = 0;
    }
}

void knownNotValue(int knowledge[][5 + RAINBOW_MODE][5], int index, int value) {
    int i;
    for(i = 0; i < 5 + RAINBOW_MODE; i++) {
        knowledge[index][i][value - 1] = 0;
    }
}
