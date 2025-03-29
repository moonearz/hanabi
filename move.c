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

//check id hinted is not the hint giver-- does this require knowing the hint giver?
//color hint is true if hinting color, false if hinting number
void giveHint(BOARD *board, int id_hinted, int card_index, bool color_hint) {

}
