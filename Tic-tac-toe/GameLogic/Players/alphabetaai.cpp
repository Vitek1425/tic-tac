#include "alphabetaai.h"
#include <GameLogic/game.h>
#include <QDebug>

AlphaBetaAi::AlphaBetaAi(Game *game, PlayerType playerType, QObject *parent) :
    Player(game, playerType, parent)
{

}

void AlphaBetaAi::makeStep()
{
    int depth = 2;
    GameField field = getGame()->getField();
    QVector<Move> moves = generateAllMoves(field);
    Move bestMove = moves.at(0);
    makeMove(moves.at(0), getPlayerType(), field);
    int scoreBestMove = -alphaBeta(depth, computeOpositePlayer(getPlayerType()), -RAND_MAX, RAND_MAX, field);
    unMakeMove(moves.at(0), field);
    for(int i = 0; i < moves.size(); ++i)
    {
        makeMove(moves.at(i), getPlayerType(), field);
        int scoreMove = -alphaBeta(depth, computeOpositePlayer(getPlayerType()), -RAND_MAX, RAND_MAX, field);
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

int AlphaBetaAi::alphaBeta(int depth, PlayerType player, int alpha, int beta, GameField &field)
{
    if((depth == 0) || (getGame()->computeGameState(field) != continues))
    {
        return ratingField(player, field);
    }

    QVector<Move> moves = generateOptimalMoves(field);
    PlayerType opPlayer = (player == playerOne ? playerTwo : playerOne);

    for(int i = 0; i < moves.size() && (alpha < beta); ++i)
    {
        makeMove(moves.at(i), player, field);
        int tmp = -alphaBeta(depth-1, opPlayer, -beta, -alpha, field);
        unMakeMove(moves.at(i), field);
        if(tmp > alpha) alpha = tmp;
    }
    return alpha;

}

int AlphaBetaAi::ratingField(PlayerType player, const GameField &field)
{
    GameState state = getGame()->computeGameState(field);
    if(state == playerOneWin)
    {
        if (player == playerOne)
            return 5;
        else
            return -5;
    }
    if(state == playerTwoWin)
    {
        if (player == playerTwo)
            return 5;
        else
            return -5;
    }
    if(state == draw)
        return 2;
    return 0;
}
