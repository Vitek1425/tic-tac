#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "GameLogic/Players/player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(Game *game, PlayerType playerType, QObject *parent = 0);

};

#endif // HUMANPLAYER_H
