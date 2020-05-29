#include "player.h"

int32_t AI_playCard( Player *AI, int32_t table[4][5] )
{
    int idx = 0;
    while( AI->cards[idx] == -1 )
    {
        idx++;
    }

    return AI->cards[idx];
}

int32_t AI_selectColumn( Player *AI, int32_t table[4][5] )
{
    return 0;
}