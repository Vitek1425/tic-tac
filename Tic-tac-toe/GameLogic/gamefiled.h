#ifndef GAMEFILED_H
#define GAMEFILED_H

#include <QVector>

enum CellValue {cross, naught, empty, noField};

class GameField
{
public:
    GameField();
    GameField(int rowCount, int columnCount);
    int getRowCount() const;
    int getColumnCount() const;

    void setValue(int row, int column, CellValue value);
    CellValue getValue(int row, int column) const;

    bool isSameCellRow(int beginColumn, int endColumn, int row, CellValue ceil) const;
    bool isSameCellColumn(int beginRow, int endRow, int column, CellValue ceil) const;
    bool isSameTopLeftToBottomRight(int beginRow, int beginColumn,
                                    int lenght, CellValue ceil) const;
    bool isSameBottomLeftToTopRight(int beginRow, int beginColumn,
                                    int lenght, CellValue ceil) const;
    void show();
    char cellValueToChar(CellValue value);
private:
    int m_rowCount;
    int m_columnCount;
    QVector<QVector<CellValue> > m_fieldValues;
};

#endif // GAMEFILED_H
