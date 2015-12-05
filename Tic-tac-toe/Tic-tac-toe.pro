#-------------------------------------------------
#
# Project created by QtCreator 2015-11-29T07:58:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tic-tac-toe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GameLogic/gamefiled.cpp \
    GameLogic/game.cpp \
    GameLogic/Players/player.cpp \
    GameLogic/gameview.cpp \
    GameLogic/Players/humanplayer.cpp \
    GameLogic/Players/stupidaiplayer.cpp \
    GameLogic/Players/alphabetaai.cpp \
    GameLogic/Players/minimaxaiplayer.cpp

HEADERS  += mainwindow.h \
    GameLogic/gamefiled.h \
    GameLogic/game.h \
    GameLogic/Players/player.h \
    GameLogic/Players/enumplayer.h \
    GameLogic/gameview.h \
    GameLogic/Players/humanplayer.h \
    GameLogic/Players/stupidaiplayer.h \
    GameLogic/Players/alphabetaai.h \
    GameLogic/Players/minimaxaiplayer.h

FORMS    += mainwindow.ui
