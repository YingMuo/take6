#pragma once
#include <stdint.h>
#include "player.h"

typedef struct game_
{
    int32_t player_number;
    int32_t table[4][5];
    int32_t get_cards[10];
    Player *player;
} Game;

void clearColume( Game *game, int32_t colume );
void initGame( Game *game );
void startGame( Game *game );
void getCards( Game *game, int32_t id, int32_t card );
void putCards( Game *game );
void cannotPut( Game *game, int32_t id, int32_t column, int32_t card_idx );
void overFive( Game *game, int32_t id, int32_t colume, int32_t card_idx );
void roundGame( Game *game );
void endGame( Game *game );