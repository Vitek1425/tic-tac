#ifndef MINIMAXAIPLAYER_H
#define MINIMAXAIPLAYER_H

#include "GameLogic/Players/player.h"
#include <GameLogic/gamefiled.h>

class MinimaxAiPlayer : public Player
{
public:
    MinimaxAiPlayer(Game *game, PlayerType playerType, QObject *parent = 0);
public slots:
    virtual void makeStep();
private:
    int searchBestMove(int depth, PlayerType player, GameField &field);
    int ratingField(const GameField &field);
    int m_depthSearch;
};

#endif // MINIMAXAIPLAYER_H
