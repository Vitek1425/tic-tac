#include "stupidaiplayer.h"
#include "GameLogic/game.h"

StupidAiPlayer::StupidAiPlayer(Game *game, PlayerType playerType, QObject *parent) :
    Player(game, playerType, parent)
{

}

void StupidAiPlayer::makeStep()
{
    Game *game = getGame();
    while(true)
    {
        int row = rand() % game->rowCount();
        int column = rand() % game->columnCount();
        if (game->makeStep(row, column))
        {
            return;
        }
    }

}

