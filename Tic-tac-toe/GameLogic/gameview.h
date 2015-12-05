#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <GameLogic/game.h>

class GameView : public QWidget
{
	Q_OBJECT
public:
	explicit GameView(QWidget *parent = 0);

signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
private slots:
    void showMessageWinner(PlayerType winnerPlayer);
private:
	void updateFieldRect();
	void drawFieldRect(QPainter *painter);
	void drawAxis(QPainter *painter);
	void drawCeils(QPainter *painter);
    void drawCeil(QPainter *painter, CellValue ceil, const QPointF &point, int size);

    Game *m_gameModel;

	QRectF m_fieldRect;
};

#endif // GAMEVIEW_H
