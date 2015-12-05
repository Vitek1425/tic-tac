#include "gamefiled.h"
#include <QDebug>
#include <iostream>

GameField::GameField() : GameField(0, 0)
{

}

GameField::GameField(int rowCount, int columnCount):
    m_rowCount(rowCount),
    m_columnCount(columnCount)
{
    m_fieldValues.resize(rowCount);
    m_fieldValues.reserve(rowCount);
    for(int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
    {
        QVector<CellValue> row(columnCount);
        for(int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
        {
            row[columnIndex] = empty;
        }
        m_fieldValues[rowIndex] = row;
    }
}

int GameField::getRowCount() const
{
    return m_rowCount;
}

int GameField::getColumnCount() const
{
    return m_columnCount;
}

void GameField::setValue(int row, int column, CellValue value)
{
    m_fieldValues[row][column] = value;
}

CellValue GameField::getValue(int row, int column) const
{
    bool isValidIndex = !((row < 0) || (row >= m_rowCount) ||
                        (column < 0) || (column >= m_columnCount));
    if(!isValidIndex)
    {
        return noField;
    }
    return m_fieldValues.at(row).at(column);
}

bool GameField::isSameCellRow(int beginColumn, int endColumn, int row, CellValue ceil) const
{
    for(int column = beginColumn; column < endColumn; ++column)
    {
        if (getValue(row, column) != ceil)
            return false;
    }
    return true;
}

bool GameField::isSameCellColumn(int beginRow, int endRow, int column, CellValue ceil) const
{
    for(int row = beginRow; row < endRow; ++row)
    {
        if (getValue(row, column) != ceil)
            return false;
    }
    return true;
}

bool GameField::isSameTopLeftToBottomRight(int beginRow, int beginColumn,
                                           int lenght, CellValue ceil) const
{
    for(int index = 0; index < lenght; ++index)
    {
        if (getValue(beginRow + index,
                     beginColumn + index) != ceil)
            return false;
    }
    return true;
}

bool GameField::isSameBottomLeftToTopRight(int beginRow, int beginColumn,
                                           int lenght, CellValue ceil) const
{
    for(int index = 0; index < lenght; ++index)
    {
        if (getValue(beginRow - index,
                     beginColumn + index) != ceil)
            return false;
    }
    return true;
}

void GameField::show()
{
    for(int i = 0; i < m_rowCount; ++i)
    {
        for(int j = 0; j < m_columnCount; ++j)
        {
            std::cout << cellValueToChar(getValue(i, j));
        }
    std::cout << std::endl;
    }
}

char GameField::cellValueToChar(CellValue value)
{
    switch (value) {
    case cross:
        return 'x';
    case naught:
        return 'o';
    default:
        return ' ';
    }
}

