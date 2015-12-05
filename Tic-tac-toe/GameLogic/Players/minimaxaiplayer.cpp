#include "minimaxaiplayer.h"
#include <GameLogic/game.h>
#include <QDebug>
#include <iostream>

MinimaxAiPlayer::MinimaxAiPlayer(Game *game, PlayerType playerType, QObject *parent) :
    Player(game, playerType, parent)
{
    m_depthSearch = 5;
}

void MinimaxAiPlayer::makeStep()
{
    GameField field = getGame()->getField();
    QVector<Move> moves = generateAllMoves(field);
    Move bestMove = moves.at(0);
    makeMove(moves.at(0), computeOpositePlayer(getPlayerType()), field);
    int scoreBestMove = searchBestMove(m_depthSearch, computeOpositePlayer(getPlayerType()), field);
    unMakeMove(moves.at(0), field);
    for(int i = 1; i < moves.size(); ++i)
    {
        makeMove(moves.at(i), getPlayerType(), field);
        int scoreMove = searchBestMove(m_depthSearch, computeOpositePlayer(getPlayerType()), field);
        unMakeMove(moves.at(i), field);
        qDebug() << moves.at(i).row << moves.at(i).column << scoreMove ;
        if (scoreMove > scoreBestMove)
        {
            scoreBestMove = scoreMove;
            bestMove = moves.at(i);
        }
    }
    qDebug() << "konec";
    getGame()->makeStep(bestMove.row, bestMove.column);
}

int MinimaxAiPlayer::searchBestMove(int depth, PlayerType player, GameField &field)
{
    if((depth == 0) || (getGame()->computeGameState(field) != continues))
    {
       // field.show();
        return ratingField(field);
    }

    int score = RAND_MAX * (player == getPlayerType() ? -1 : 1);
    PlayerType opPlayer = (player == playerOne ? playerTwo : playerOne);
    QVector<Move> moves = generateAllMoves(field);
    for(int i = 0; i < moves.size(); ++i)
    {
        makeMove(moves.at(i), player, field);
        int scoreMove = searchBestMove(depth - 1, opPlayer, field);
        if (player != getPlayerType())
        {
            if (scoreMove < score)
                score = scoreMove;
        }
        else //player == getPlayerType()
        {
            if (scoreMove > score)
                score = scoreMove;
        }
        unMakeMove(moves.at(i), field);
    }
    return score;
}

int MinimaxAiPlayer::ratingField(const GameField &field)
{

    GameState state = getGame()->computeGameState(field);
    if(state == playerOneWin)
    {
        if (getPlayerType() == playerOne)
            return 5;
        else
            return -5;
    }
    if(state == playerTwoWin)
    {
        if (getPlayerType() == playerTwo)
            return 5;
        else
            return -5;
    }
    if(state == draw)
        return 2;
    return 0;

}


