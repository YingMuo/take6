#include "game.h"
#include "UI.h"
#include "AI.h"
#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

void clearColume( Game *game, int32_t colume )
{
    for( int i = 0; i < 5; i++ )
    {
        game->table[colume][i] = -1;
    }
}

void initGame( Game *game )
{
    game->player_number = -1;
    game->player = NULL;
    for( int i = 0; i < 10; i++ )
        game->get_cards[i] = -1;
    for( int i = 0; i < 4; i++ )
        clearColume( game, i );
}

void startGame( Game *game )
{
    // get player number
    int32_t player_number = 0;
    player_number = getPlayerNumber();

    // get player name
    char *player_name;
    player_name = getPlayerName();

    // randomize card
    int32_t random_cards[104];
    for( int i = 0; i < 104; i++ )
        random_cards[i] = i+1;

    int random = 0;
    srand( time(0) );
    int tmp = 0;
    for( int p = 0; p < 10; p++ )
    {
        for( int i = 0; i < 104; i++ )
        {
            for( int o = 0; o < 104; o++ )
            {
                random = rand() % 4;
                if( random != 0 )
                {
                    tmp = random_cards[o];
                    random_cards[o] = random_cards[i];
                    random_cards[i] = tmp;
                }
            }
        }
    }

    // set player number
    game->player_number = player_number;

    // init player
    game->player = calloc( player_number, sizeof( Player ) );

    initPlayer( &(game->player[0]) );
    setPlayerName( &(game->player[0]), player_name );

    for( int i = 1; i < player_number; i++ )
    {
        char *name = NULL;
        name = calloc( 10, sizeof( char ) );
        strcpy( name, "NPC" );
        name[3] = 0x30+i;
        initPlayer( &(game->player[i]) );
        setPlayerName( &(game->player[i]), name );
    }

    // deal card to player
    int32_t player_cards[10] = {0};
    for( int i = 0; i < player_number; i++ )
    {
        for( int o = 0; o < 10; o++ )
        {
            player_cards[o] = random_cards[i*10+o];
        }
        deal( &(game->player[i]), player_cards );
    }

    // deal card to table
    for( int i = 0; i < 4; i++ )
    {
        for( int o = 0; o < 3; o++ )
        {
            if( random_cards[10*player_number+o] > random_cards[10*player_number+o+1] )
            {
                tmp = random_cards[10*player_number+o];
                random_cards[10*player_number+o] = random_cards[10*player_number+o+1];
                random_cards[10*player_number+o+1] = tmp;
            }
        }
    }

    for( int i = 0; i < 4; i++ )
    {
        game->table[i][0] = random_cards[10*player_number+i];
    }

    return;
}

void getCards( Game *game, int32_t id, int32_t card )
{
    game->get_cards[id] = card;
    for( int i = 0; i < 10; i++ )
    {
        if( game->player[id].cards[i] == card )
        {
            game->player[id].cards[i] = -1;
            break;
        }
    }
    return;
}

void sort( int arr1[], int arr2[], int n )
{
    int tmp = 0;
    for( int i = 0; i < n; i++ )
    {
        for( int o = 0; o < n-1; o++ )
        {
            if( arr1[o] > arr1[o+1] )
            {
                tmp = arr1[o];
                arr1[o] = arr1[o+1];
                arr1[o+1] = tmp;

                tmp = arr2[o];
                arr2[o] = arr2[o+1];
                arr2[o+1] = tmp;
            }
        }
    }
    return;
}

void cannotPut( Game *game, int32_t id, int32_t column, int32_t card_idx )
{
    eatCards( &(game->player[id]), game->table, column );
    clearColume( game, column );
    game->table[column][0] = game->get_cards[card_idx];
    return;
}

void overFive( Game *game, int32_t id, int32_t column, int32_t card_idx )
{
    eatCards( &(game->player[id]), game->table, column );
    clearColume( game, column );
    game->table[column][0] = game->get_cards[card_idx];
    return;
}

void putCards( Game *game )
{
    // create id to record the player order
    int32_t id[game->player_number];
    for( int i = 0; i < game->player_number; i++ )
        id[i] = i;
    sort( game->get_cards, id, game->player_number );
    
    // output some information
    printOpenCard( game, id, -1 );
    printTable( game, -1 );
    stop();

    // put cards
    for( int i = 0; i < game->player_number; i++ )
    {
        int isPut = 0;
        int need_print_score = 0;
        int column = -1;
        for( int o = 3; o >= 0; o-- )
        {
            int idx = 0;
            int full = 0;
            if( game->table[o][4] != -1 )
            {
                full = 1;
                idx = 5;
            }
            else
            {
                while( game->table[o][idx] != -1 )
                {
                    idx++;
                }
            }
            
            if( game->get_cards[i] > game->table[o][idx-1] )
            {
                if( full == 0 )
                {
                    game->table[o][idx] = game->get_cards[i];
                    isPut = 1;
                    break;
                }
                else
                {
                    column = o;
                    overFive( game, id[i], column, i );
                    isPut = 1;
                    need_print_score = 1;
                    break;
                }
            }
        }
        if( isPut == 0 )
        {
            if( id[i] == 0 )
            {
                printOpenCard( game, id, game->get_cards[i] );
                printTable( game, -1 );
                while( column == -1 )
                {
                    column = selectColumn();
                }
                system( "clear" );
            }
            else
            {
                // TODO: AI input column
                column = AI_selectColumn( &(game->player[id[i]]), game->table );
            }

            cannotPut( game, id[i], column, i );
            need_print_score = 1;

            int tmp = 0;
            for( int o = column-1; o >= 0; o-- )
            {
                for( int p = 0; p < 5; p++ )
                {
                    tmp = game->table[o][p];
                    game->table[o][p] = game->table[o+1][p];
                    game->table[o+1][p] = tmp;
                }
            }
        }

        // output some information
        printOpenCard( game, id, game->get_cards[i] );
        printTable( game, game->get_cards[i] );
        if( need_print_score )
        {
            printScore( &(game->player[id[i]]) );
        }
        stop();
    }

    return;
}

void roundGame( Game *game )
{
    // initial get_gards
    for( int i = 0; i < 10; i++ )
        game->get_cards[i] = -1;

    // output some information
    printTable( game, -1 );
    printRound( game );

    // get play card
    int card = -1;
    int have_card = 0;
    while( 1 )
    {
        card = playCard();
        for( int i = 0; i < 10; i++ )
        {
            if( game->player[0].cards[i] == card && card != -1 )
            {
                getCards( game, 0, card );
                have_card = 1;
                break;
            }
        }

        if( have_card == 1 )
            break;
        printf( "wrong card's number input!!\n" );
    }
    for( int i = 1; i < game->player_number; i++ )
    {
        //TODO: AI playcard
        card = AI_playCard( &(game->player[i]), game->table );
        getCards( game, i, card );
    }

    system( "clear" );

    // put cards
    putCards( game );
    return;
}

void endGame( Game *game )
{
    Player tmp;
    for( int i = 0; i < game->player_number; i++ )
    {
        for( int o = 0; o < game->player_number-1; o++ )
        {
            if( game->player[o].scores > game->player[o+1].scores )
            {
                tmp = game->player[o];
                game->player[o] = game->player[o+1];
                game->player[o+1] = tmp;
            }
        }
    }
    printResult( game );

    for( int i = 0; i < game->player_number; i++ )
    {
        freePlayerName( &(game->player[i]) );
    }

    free( game->player );

    return;
}