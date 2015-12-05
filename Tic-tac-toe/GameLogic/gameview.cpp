#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <qmath.h>
#include <QMessageBox>
#include "GameLogic/gameview.h"
#include "GameLogic/Players/player.h"
#include "GameLogic/Players/stupidaiplayer.h"
#include "GameLogic/Players/minimaxaiplayer.h"
#include "GameLogic/Players/alphabetaai.h"

GameView::GameView(QWidget *parent) :
	QWidget(parent)
{
    m_gameModel = new Game(10, 10, 5, this);
   Player *player = new AlphaBetaAi(m_gameModel, playerTwo, this);

  //  Player *player = new MinimaxAiPlayer(m_gameModel, playerOne, this);

	updateFieldRect();
    connect(m_gameModel, SIGNAL(endGame(PlayerType)), SLOT(showMessageWinner(PlayerType)));
    connect(m_gameModel, SIGNAL(fieldChanged()), SLOT(update()));

     connect(m_gameModel, SIGNAL(waitingMovePlayerTwo()), player, SLOT(makeStep()));
 //   connect(m_gameModel, SIGNAL(waitingMovePlayerOne()), player, SLOT(makeStep()));
//   player->makeStep();
}

void GameView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	drawFieldRect(&painter);
	drawAxis(&painter);
	drawCeils(&painter);
}

void GameView::resizeEvent(QResizeEvent *event)
{
	updateFieldRect();
}

void GameView::mousePressEvent(QMouseEvent *event)
{
	QPointF point = event->pos();
	if(!m_fieldRect.contains(point))
		return;

	float x = point.x() - m_fieldRect.x();
	float y = point.y() - m_fieldRect.y();

    int column = qCeil(x/m_fieldRect.width() * m_gameModel->columnCount()) - 1;
	int row = qCeil(y/m_fieldRect.height()* m_gameModel->rowCount()) - 1;

	m_gameModel->makeStep(row, column);
	update();
}

void GameView::showMessageWinner(PlayerType winnerPlayer)
{
	QMessageBox::information(this, "Ура!!!",
							 QString("Игрок %1 выиграл").arg(
                                 winnerPlayer == playerOne ? "1" : "2"));
}

void GameView::updateFieldRect()
{
	int minSize = qMin(width(), height());
	m_fieldRect = QRectF(width()/2 - minSize/2,
						 height()/2 - minSize/2,
						 minSize, minSize);
}

void GameView::drawFieldRect(QPainter *painter)
{
	painter->save();
	painter->drawRect(m_fieldRect);
	painter->restore();
}

void GameView::drawAxis(QPainter *painter)
{
	float stepX = m_fieldRect.width() / m_gameModel->columnCount();
	float stepY = m_fieldRect.height() / m_gameModel->rowCount();
//	painter->save();
	for(int row = 1; row < m_gameModel->rowCount(); ++row)
	{
		painter->drawLine(QLineF(QPointF(m_fieldRect.x(), m_fieldRect.y() + row * stepY),
							  QPointF(m_fieldRect.topRight().x(), m_fieldRect.y() + row * stepY)));
	}
	for(int column = 1; column < m_gameModel->columnCount(); ++column)
	{
		painter->drawLine(QLineF(QPointF(m_fieldRect.x() + column * stepX, m_fieldRect.y()),
								 QPointF(m_fieldRect.x() + column * stepX, m_fieldRect.bottomRight().y())));
	}
//	painter->restore();
}

void GameView::drawCeils(QPainter *painter)
{
//	painter->save();

	float stepX = m_fieldRect.width() / m_gameModel->columnCount();
	float stepY = m_fieldRect.height() / m_gameModel->rowCount();

	for(int row = 0; row < m_gameModel->rowCount(); ++row)
	{
		for(int column = 0; column < m_gameModel->columnCount(); ++column)
		{
			drawCeil(painter,
                     m_gameModel->getField().getValue(row, column),
					 QPointF(m_fieldRect.x() + stepX/2 + column * stepX,
							 m_fieldRect.y() + stepY/2 + row * stepY), 1);
		}
	}

//	painter->restore();
}

void GameView::drawCeil(QPainter *painter, CellValue ceil, const QPointF &point, int size)
{
//	painter->save();

	switch (ceil) {
    case cross:
		painter->drawText(point, QString("X"));
		return;
    case naught:
		painter->drawText(point, QString("0"));
		return;
    case empty:
		return;
	}

//	painter->restore();
}
