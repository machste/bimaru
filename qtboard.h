#ifndef QTBOARD_H
#define QTBOARD_H

#include <QWidget>
#include <QVector>

class QtField;

class QtBoard : public QWidget
{
    Q_OBJECT

public:
    QtBoard(int rows, int cols);
    ~QtBoard();

    QtField *field(int row, int col);

private slots:
    void handleFieldClick(QtField *field);

private:
    int _rows;
    int _cols;
    QVector< QVector<QtField *> > _fields;
};

#endif /* QTBOARD_H */
