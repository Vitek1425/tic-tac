#include "mainwindow.h"
#include "GameLogic/gameview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameView w;
    w.show();

    return a.exec();
}
