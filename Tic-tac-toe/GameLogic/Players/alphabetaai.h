#ifndef ALPHABETAAI_H
#define ALPHABETAAI_H

#include "GameLogic/Players/player.h"
#include <GameLogic/gamefiled.h>

class AlphaBetaAi : public Player
{
public:
    AlphaBetaAi(Game *game, PlayerType playerType, QObject *parent = 0);
public slots:
    void makeStep();
private:
    int alphaBeta(int depth, PlayerType player, int alpha, int beta, GameField &field);
    int ratingField(PlayerType player, const GameField &field);
};

#endif // ALPHABETAAI_H
