#include <QGridLayout>
#include <QDebug>

#include "qtboard.h"
#include "qtfield.h"

QtBoard::QtBoard(int rows, int cols) : _rows(rows), _cols(cols)
{
    QGridLayout *layout = new QGridLayout();

    _fields = QVector< QVector<QtField *> >(_rows, QVector<QtField *>(_cols));
    for (int row = 0; row < _rows; row++) {
        for (int col = 0; col < _cols; col++) {
            QtField *field = new QtField(*this, row, col);
            connect(field, &QtField::clicked, this, &QtBoard::handleFieldClick);
            layout->addWidget(field, row, col);
            _fields[row][col] = field;
        }
    }
    for (int row = 0; row < _rows; row++) {
        for (int col = 0; col < _cols; col++) {
            _fields[row][col]->setState(QtField::EMPTY);
        }
    }
    layout->setSpacing(0);
    layout->setSizeConstraint(QGridLayout::SetFixedSize);
    setLayout(layout);
}

QtBoard::~QtBoard()
{
}

QtField *QtBoard::field(int row, int col) {
    QtField *field = NULL;

    if (row >= 0 && row < _rows && col >= 0 && col < _cols) {
        field = _fields[row][col];
    }
    return field;
}

void QtBoard::handleFieldClick(QtField *field)
{
    qDebug() << "Clicked: " << field->row() << ", " << field->col();
}
