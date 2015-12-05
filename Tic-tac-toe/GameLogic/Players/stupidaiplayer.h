#ifndef STUPIDAIPLAYER_H
#define STUPIDAIPLAYER_H

#include <GameLogic/Players/player.h>

class StupidAiPlayer : public Player
{
    Q_OBJECT
public:
    explicit StupidAiPlayer(Game *game, PlayerType playerType, QObject *parent = 0);
public slots:
    void makeStep();
};

#endif // STUPIDAIPLAYER_H
