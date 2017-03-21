#ifndef QTFIELD_H
#define QTFIELD_H

#include <QLabel>
#include <QPixmap>

class QtBoard;

class QtField : public QLabel
{
    Q_OBJECT

public:
    enum State
    {
        UNKNOWN,
        EMPTY,
        WATER,
        SHIP,
        MARKED
    };

public:
    QtField(QtBoard &board, int row, int col);
    ~QtField();

    int row() { return _row; };
    int col() { return _col; };

    QtField *left();
    QtField *right();
    QtField *above();
    QtField *below();

    QtField::State state() { return _state; };
    void setState(QtField::State state);
    QtField::State setNextState();

signals:
    void clicked(QtField *field);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    QtField::State _nextState(QtField::State state);
    void _updateBgPixmap();
    void _updatePixmap();

private:
    QtBoard &_board;
    int _row;
    int _col;
    QtField::State _state;
    bool _bgDirty;
    QPixmap _bgPixmap;
};

#endif /* QTFIELD_H */
