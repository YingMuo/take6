#pragma once
#include <stdint.h>

typedef struct player_
{
    char *name;
    int32_t cards[10];
    uint32_t scores;
    int32_t eat_cards[104];
} Player;

void initPlayer( Player *player );
void setPlayerName( Player *player, char *name );
void deal( Player *player, int32_t cards[10] );
void eatCards( Player *player, int32_t table[4][5], int32_t colume );
void freePlayerName( Player *player );