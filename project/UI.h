#include "game.h"
#pragma once

int32_t getPlayerNumber();
char *getPlayerName();
int32_t playCard();
int32_t selectColumn();

void printTitle();
void printOpenCard( Game *game, int32_t id[], int32_t highlight );
void printTable( Game *game, int32_t highlight );
void printRound( Game *game );
void printResult( Game *game );
void printEnd();
void stop();
void printScore( Player *player );
