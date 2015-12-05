#ifndef PLAYER_H
#define PLAYER_H

#include "GameLogic/Players/enumplayer.h"
#include <QObject>

class Game;
class GameField;

struct Move
{
    int row;
    int column;
};

class Player : public QObject
{
    Q_OBJECT
public:
    Player(Game *game, PlayerType playerType, QObject *parent = 0);
    Game *getGame();
    PlayerType getPlayerType();
    PlayerType computeOpositePlayer(PlayerType player);
    QVector<Move> generateAllMoves(const GameField &field);
    QVector<Move> generateOptimalMoves(const GameField &field);
    void makeMove(Move move, PlayerType player, GameField &field);
    void unMakeMove(Move move, GameField &field);
public slots:
    virtual void makeStep() = 0;
private:
    Game *m_game;
    PlayerType m_playerType;
};

#endif // PLAYER_H
