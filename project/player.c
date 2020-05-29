#include "player.h"
#include <stdio.h>
#include <stdlib.h>

void initPlayer( Player *player )
{
    player->name = NULL;
    for( int i = 0; i < 10; i++ )
        player->cards[i] = -1;
    player->scores = 0;
    for( int i = 0; i < 104; i++ )
        player->eat_cards[i] = -1;
    return;
}

void setPlayerName( Player *player, char *name )
{
    player->name = name;
    return;
}

void deal( Player *player, int32_t cards[10] )
{
    for( int i = 0; i < 10; i++ )
    {
        player->cards[i] = cards[i];
    }
    return;
}

void eatCards( Player *player, int32_t table[4][5], int32_t colume )
{
    int begin = 0;
    while( player->eat_cards[begin++] != -1 );

    int idx = 0;
    while( table[colume][idx] != -1 && idx < 5 )
    {
        if( table[colume][idx] == 55 )
            player->scores += 7;
        else if( table[colume][idx] % 10 == table[colume][idx] / 10 )
            player->scores += 5;
        else if( table[colume][idx] % 10 == 0 )
            player->scores += 3;
        else if( table[colume][idx] % 10 == 5 )
            player->scores += 2;
        else
            player->scores += 1;
        
        player->eat_cards[begin] = table[colume][idx];
        begin++;
        idx++;
    }
    return;
}

void freePlayerName( Player *player )
{
    free( player->name );
    return;
}