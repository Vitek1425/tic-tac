#include "player.h"
#include <GameLogic/gamefiled.h>

Player::Player(Game *game, PlayerType playerType, QObject *parent):
    m_game(game),
    m_playerType(playerType),
    QObject(parent)
{

}

Game *Player::getGame()
{
    return m_game;
}

PlayerType Player::getPlayerType()
{
    return m_playerType;
}

PlayerType Player::computeOpositePlayer(PlayerType player)
{
    return (player == playerOne) ? playerTwo : playerOne;
}

QVector<Move> Player::generateAllMoves(const GameField &field)
{
    QVector<Move> moves;
    for(int i = 0; i < field.getRowCount(); ++i)
        for(int j = 0; j < field.getColumnCount(); ++j)
        {
            if (field.getValue(i, j) == empty)
            {
                Move move;
                move.row = i;
                move.column = j;
                moves.push_back(move);
            }
        }
    return moves;
}

QVector<Move> Player::generateOptimalMoves(const GameField &field)
{
    QVector<Move> moves;
    for(int row = 0; row < field.getRowCount(); ++row)
        for(int column = 0; column < field.getColumnCount(); ++column)
        {
            if ((field.getValue(row, column) == empty) &&
                ((field.getValue(row - 1, column - 1) == cross) || (field.getValue(row - 1, column - 1) == naught) ||
                (field.getValue(row - 1, column) == cross) || (field.getValue(row - 1, column) == naught) ||
                (field.getValue(row - 1, column + 1) == cross) || (field.getValue(row - 1, column + 1) == naught) ||
                (field.getValue(row, column - 1) == cross) || (field.getValue(row, column - 1) == naught) ||
                (field.getValue(row, column + 1) == cross) || (field.getValue(row, column + 1) == naught) ||
                (field.getValue(row + 1, column - 1) == cross) || (field.getValue(row - 1, column - 1) == naught) ||
                (field.getValue(row + 1, column) == cross) || (field.getValue(row - 1, column) == naught) ||
                (field.getValue(row + 1, column + 1) == cross) || (field.getValue(row - 1, column + 1) == naught))||
                (field.getValue(row + 2, column + 2) == cross) || (field.getValue(row - 2, column + 2) == naught)||
                (field.getValue(row + 2, column + 2) == cross) || (field.getValue(row + 2, column + 2) == naught)||
                (field.getValue(row - 2, column - 2) == cross) || (field.getValue(row + 2, column + 2) == naught)||
                (field.getValue(row - 2, column - 2) == cross) || (field.getValue(row - 2, column - 2) == naught))
            {
                Move move;
                move.row = row;
                move.column = column;
                moves.push_back(move);
            }
        }
    return moves;
}

void Player::makeMove(Move move, PlayerType player, GameField &field)
{
    field.setValue(move.row, move.column, (player == playerOne) ? cross : naught);
}

void Player::unMakeMove(Move move, GameField &field)
{
    field.setValue(move.row, move.column, empty);
}

