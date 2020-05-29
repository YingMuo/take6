#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"

#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define GRN_BOLD "\x1b[;32;1m"
#define RESET "\x1b[0;m"

int32_t getCardScore( int card_value )
{
    if( card_value == 55 )
        return 7;
    else if( card_value % 10 == card_value / 10 )
        return 5;
    else if( card_value % 10 == 0 )
        return 3;
    else if( card_value % 10 == 5 )
        return 2;
    else
        return 1;
}

int32_t getPlayerNumber()
{
    system( "clear" );
    int player_number = 0;
    printf( "\nplease input player number ( 2-10 ): " );
    scanf( "%d", &player_number );

    if( player_number < 2 || player_number > 10 )
    {
        printf( "wrong player number!!\n" );
        return -1;
    }

    return player_number;
}

char *getPlayerName()
{
    getchar();
    char *player_name = NULL;
    player_name = calloc( 12, sizeof( char ) );
    printf( "please input player name ( at most 10 character ): " );
    fgets( player_name, 11, stdin );
    if( player_name[strlen(player_name)-1] == '\n' );
        player_name[strlen(player_name)-1] = '\0';

    return player_name;
}
int32_t playCard()
{
    int card = 0;
    printf( "\nplease input the card's number ( 1-104 ) to play card: " );
    scanf( "%d", &card );
    getchar();

    if( card > 104 || card < 1 )
    {
        return -1;
    }

    return card;
}
int32_t selectColumn()
{
    int column = 0;
    printf( YEL_BOLD"\nplease select the column ( 0-3 ): " );
    printf( RESET"" );
    scanf( "%d", &column );
    getchar();

    if( column < 0 || column > 3 )
    {
        printf( "wrong column select!!\n" );
        return -1;
    }

    return column;
}

void printTitle()
{
    system( "clear" );
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );
    printf( "please input 1 or 2 to select option below\n\n" );
    printf( "1. start\n" );
    printf( "2. exit\n\n" );

    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );

    printf( "please input a option: " );
}

void printOpenCard( Game *game, int32_t id[], int32_t highlight )
{
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );
    printf( "open card:\n" );
    for( int i = 0; i < game->player_number; i++ )
    {
        if( highlight != -1 && game->get_cards[i] == highlight )
        {
            printf( BLU_BOLD"%s ", game->player[id[i]].name );
            printf( RESET": " );
            printf( RED_BOLD"%03d\n", game->get_cards[i] );
            printf( RESET"" );
        }
        else
        {
            printf( RESET"%s: %03d\n", game->player[id[i]].name, game->get_cards[i] );
        }
        
    }
    printf( "\n" );
}

void printTable( Game *game, int32_t highlight )
{
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );
    printf( GRN_BOLD"Game table:\n\n" );
    printf( RESET"" );
    for( int i = 0; i < 4; i++ )
    {
        printf( "column %02d: ", i );
        for( int o = 0; o < 5; o++ )
        {
            if( highlight != -1 && game->table[i][o] == highlight && game->table[i][o] != -1 )
            {
                printf( RED_BOLD" %02d-%03d", getCardScore( game->table[i][o] ), game->table[i][o] );
                printf( RESET"" );
            }
            else if( game->table[i][o] != -1 )
            {
                printf( RESET" %02d-%03d", getCardScore( game->table[i][o] ), game->table[i][o] );
            }
            
        }
        printf( "\n\n" );
    }
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n\n" );
}

void printRound( Game *game )
{
    // output score table
    printf( "------------------------------------------------------------------------------------\n\n" );
    printf( GRN_BOLD"score table:\n\n" );
    printf( RESET"" );
    for( int i = 0; i < game->player_number; i++ )
    {
        printf( "player: %s\n", game->player[i].name );
        printf( "score: %04d points\n\n", game->player[i].scores );
    }

    printf( "------------------------------------------------------------------------------------\n\n" );

    // output card
    int tmp = 0;
    for( int i = 0; i < 10; i++ )
    {
        for( int o = 0; o < 9; o++ )
        {
            if( game->player[0].cards[o] > game->player[0].cards[o+1] )
            {
                tmp = game->player[0].cards[o];
                game->player[0].cards[o] = game->player[0].cards[o+1];
                game->player[0].cards[o+1] = tmp;
            }
        }
    }

    printf( GRN_BOLD"card: \n\n" );
    printf( RESET"" );
    for( int i = 0; i < 10; i++ )
    {
        if( game->player[0].cards[i] != -1 )
            printf( "  %02d-%03d", getCardScore( game->player[0].cards[i] ), game->player[0].cards[i] );
    }
    printf( "\n\n------------------------------------------------------------------------------------\n\n" );
}

void printResult( Game *game )
{
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );
    for( int i = 0; i < game->player_number; i++ )
    {
        printf( "%s : %d points\n", game->player[i].name, game->player[i].scores );
    }
    printf( "\nwinner: %s!!\n\n", game->player[0].name );
    printf( "------------------------------------------------------------------------------------\n" );
}

void printEnd()
{
    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );
    printf( "please input 1 or 2 to select option below\n\n" );
    printf( "\t1. return to title\n" );
    printf( "\t2. exit\n\n" );

    printf( "------------------------------------------------------------------------------------\n" );
    printf( "\n" );

    printf( "please input a option: " );
}

void stop()
{
    printf( "press any key to continue.\n" );
    getchar();
    system( "clear" );
}

void printScore( Player *player )
{
    printf( BLU_BOLD"%s", player->name );
    printf( RESET"'s points increase!!\n" );
    printf( BLU_BOLD"%s", player->name );
    printf( RESET" has got " );
    printf( RED_BOLD"%04d", player->scores );
    printf( RESET" points!!\n\n" );
}