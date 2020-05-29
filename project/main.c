#include "game.h"
#include "player.h"
#include "UI.h"
#include "AI.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Game game;
    int option = 0;
    while ( 1 )
    {
        printTitle();
        scanf( "%d", &option );
        if( option == 1 )
        {
            initGame( &game );
            startGame( &game );
            system( "clear" );
            for( int i = 0; i < 10; i++ )
            {
                roundGame( &game );
            }
            endGame( &game );
            printEnd();
            scanf( "%d", &option );

            if( option == 2 )
            {
                break;
            }
            else if( option != 1 )
            {
                printf( "wrong option!!\n" );
                break;
            }
        }

        else if( option == 2 )
        {
            break;
        }
        
        else
        {
            printf( "wrong option!!\n" );
            break;
        }
    }
    
    return 0;
}