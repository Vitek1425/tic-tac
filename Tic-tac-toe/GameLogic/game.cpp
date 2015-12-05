#include "game.h"
#include <QDebug>

Game::Game(int rowCount,
           int columnCount,
           int lengthWinningString,
           QObject *parent):
    m_rowCount(rowCount),
    m_columnCount(columnCount),
    m_lengthWinningString(lengthWinningString),
    m_field(rowCount, columnCount),
    QObject(parent)
{
    m_currentPlayer = playerOne;
}

GameField Game::getField()
{
    return m_field;
}

bool Game::makeStep(int row, int column)
{
    if(m_field.getValue(row, column) != empty)
    {
        return false;
    }
    if (m_currentPlayer == playerOne)
    {
        m_field.setValue(row, column, cross);
        if(isEndGame(row, column, m_field))
        {
            emit endGame(playerOne);
        }
        m_currentPlayer = playerTwo;
        emit waitingMovePlayerTwo();
    }
    else  //currentPlayer == playerTwo
    {
        m_field.setValue(row, column, naught);
        if(isEndGame(row, column, m_field))
        {
            emit endGame(playerTwo);
        }
        m_currentPlayer = playerOne;
        emit waitingMovePlayerOne();
    }
    emit fieldChanged();
    GameState gameState = computeGameState(m_field);
    switch (gameState)
    {
    case playerOneWin:
    {
        qDebug() << "Выиграл первый игрок";
        break;
    }
    case playerTwoWin:
    {
        qDebug() << "Выиграл второй игрок";
        break;
    }
    case continues:
    {
        qDebug() << "Игра продолжается";
        break;
    }
    case draw:
    {
        qDebug() << "Ничья";
        break;
    }
    }
    return true;
}

bool Game::isEndGame(int row, int column, const GameField &field) const
{
    CellValue currentCellValue = field.getValue(row, column);

    //проверка совпадений на строке
    for(int i = column - m_lengthWinningString;
        i < column + m_lengthWinningString;
        ++i)
    {
        if(field.isSameCellRow(i, i + m_lengthWinningString, row, currentCellValue))
            return true;
    }
    //проверка совпадений на столбце
    for(int i = row - m_lengthWinningString;
        i < row + m_lengthWinningString;
        ++i)
    {
        if(field.isSameCellColumn(i, i + m_lengthWinningString, column, currentCellValue))
            return true;
    }
    //проверка совпадений от слево-вверх -> справа-вниз
    for(int i = -m_lengthWinningString;
        i < m_lengthWinningString;
        ++i)
    {
        if(field.isSameTopLeftToBottomRight(row - i,
                                            column - i,
                                            m_lengthWinningString,
                                            currentCellValue))
            return true;
    }
    //проверка совпадений от слево-низ -> справа-вверх
    for(int i = -m_lengthWinningString;
        i < m_lengthWinningString;
        ++i)
    {
        if(field.isSameBottomLeftToTopRight(row + i,
                                            column - i,
                                            m_lengthWinningString,
                                            currentCellValue))
            return true;
    }


    return false;
}

int Game::columnCount() const
{
    return m_columnCount;
}

int Game::rowCount() const
{
    return m_rowCount;
}

GameState Game::computeGameState(const GameField &field)
{
    int emptyCellCount = 0;
    for(int i = 0; i < field.getRowCount(); ++i)
        for(int j = 0; j < field.getColumnCount(); ++j)
        {
            CellValue cellValue = field.getValue(i, j);
            if(cellValue == empty)
            {
                emptyCellCount++;
            }
            else if (cellValue == cross)
            {
                if(isEndGame(i, j, field))
                {
                    return playerOneWin;
                }
            }
            else if (cellValue == naught)
            {
                if(isEndGame(i, j, field))
                {
                    return playerTwoWin;
                }
            }
        }
    if(emptyCellCount > 0)
        return continues;
    return draw;
}
