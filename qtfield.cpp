#include <QPixmap>
#include <QPainter>
#include <QDebug>

#include "qtfield.h"
#include "qtboard.h"

QtField::QtField(QtBoard &board, int row, int col)
    : _board(board), _row(row), _col(col), _state(UNKNOWN), _bgDirty(true)
{
}

QtField::~QtField()
{
}

QtField *QtField::left()
{
    return _board.field(_row, _col - 1);
}

QtField *QtField::right()
{
    return _board.field(_row, _col + 1);
}

QtField *QtField::above()
{
    return _board.field(_row - 1, _col);
}

QtField *QtField::below()
{
    return _board.field(_row + 1, _col);
}

void QtField::setState(QtField::State state)
{
    _state = state;
    _updatePixmap();
}

QtField::State QtField::setNextState()
{
    setState(_nextState(_state));
    return _state;
}

void QtField::mousePressEvent(QMouseEvent* /*event (unused)*/)
{
    setNextState();
    emit clicked(this);
}

QtField::State QtField::_nextState(QtField::State state)
{
    switch (state) {
        case EMPTY: return WATER;
        case WATER: return SHIP;
        case SHIP: return EMPTY;
        default: return UNKNOWN;
    }
}

void QtField::_updateBgPixmap()
{
    if (_bgDirty) {
        int width, height;
        QPainter painter;

        _bgPixmap.load(":images/fields/empty.png");
        width = _bgPixmap.width();
        height = _bgPixmap.height();
        painter.begin(&_bgPixmap);
        painter.drawLine(0, 0, 0, height);
        painter.drawLine(0, 0, width, 0);
        if (left() == NULL) {
            painter.drawLine(1, 0, 1, height - 1);
        }
        if (above() == NULL) {
            painter.drawLine(0, 1, width - 1, 1);
        }
        if (right() == NULL) {
            painter.drawLine(width - 1, 0, width - 1, height - 1);
            painter.drawLine(width - 2, 0, width - 2, height - 1);
        }
        if (below() == NULL) {
            painter.drawLine(0, height - 1, width - 1, height - 1);
            painter.drawLine(0, height - 2, width - 1, height - 2);
        }
        painter.end();
        _bgDirty = false;
    }
}

void QtField::_updatePixmap()
{
    QPainter painter;
    QPixmap pixmap, overlay;

    _updateBgPixmap();
    pixmap = QPixmap(_bgPixmap.width(), _bgPixmap.height());
    painter.begin(&pixmap);
    painter.drawPixmap(0, 0, _bgPixmap);
    switch (_state) {
        case WATER:
            overlay.load(":images/fields/water.png");
            break;
        case SHIP:
            overlay.load(":images/fields/boat.single.png");
            break;
        default:
            break;
    }
    painter.drawPixmap(0, 0, overlay);
    painter.end();
    setPixmap(pixmap);
}
