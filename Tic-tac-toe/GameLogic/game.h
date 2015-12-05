#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <GameLogic/gamefiled.h>
#include <GameLogic/Players/enumplayer.h>

enum GameState {draw, playerOneWin, playerTwoWin, continues};

class Player;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(int rowCount,
                  int columnCount,
                  int lengthWinningString,
                  QObject *parent = 0);
    GameField getField();
    bool makeStep(int row, int column);
    bool isEndGame(int row, int column, const GameField &field) const;
    int columnCount() const;
    int rowCount() const;

    GameState computeGameState(const GameField &field);
signals:
    void fieldChanged();
    void endGame(PlayerType player);
    void waitingMovePlayerOne();
    void waitingMovePlayerTwo();
public slots:

private:
    int m_rowCount;
    int m_columnCount;
    int m_lengthWinningString;
    GameField m_field;
    PlayerType m_currentPlayer;
};

#endif // GAME_H
