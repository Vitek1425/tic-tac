#include "alphabetaai.h"
#include <GameLogic/game.h>
#include <QDebug>

AlphaBetaAi::AlphaBetaAi(Game *game, PlayerType playerType, QObject *parent) :
    Player(game, playerType, parent)
{

}

void AlphaBetaAi::makeStep()
{
	int depth = 5;

    GameField field = getGame()->getField();
    QVector<Move> moves = generateAllMoves(field);

	int alpha = -RAND_MAX;
	int beta = RAND_MAX;

	makeMove(moves.at(0), getPlayerType(), field);
	alpha = -alphaBeta(depth, computeOpositePlayer(getPlayerType()), -beta, -alpha, field);
	unMakeMove(moves.at(0), field);

	Move bestMove = moves.at(0);
	for(int i = 1; i < moves.size(); ++i)
    {
        makeMove(moves.at(i), getPlayerType(), field);
		int scoreMove = -alphaBeta(depth, computeOpositePlayer(getPlayerType()), -beta, -alpha, field);
        unMakeMove(moves.at(i), field);
        qDebug() << moves.at(i).row << moves.at(i).column << scoreMove ;
		if (scoreMove > alpha)
        {
			alpha = scoreMove;
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

	int max = -RAND_MAX;
    for(int i = 0; i < moves.size() && (alpha < beta); ++i)
    {
        makeMove(moves.at(i), player, field);
        int tmp = -alphaBeta(depth-1, opPlayer, -beta, -alpha, field);
        unMakeMove(moves.at(i), field);

		if( tmp > beta ) return -RAND_MAX;
		if( tmp > max ) max = tmp;
		if( max > alpha ) alpha = max;
    }
	return max;

}

int AlphaBetaAi::ratingField(PlayerType player, const GameField &field)
{
	// Где-то здесь ошибка. Всегда возращается 0.
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
