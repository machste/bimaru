#include <QPushButton>
#include <QBoxLayout>

#include "mainwindow.h"
#include "qtboard.h"

MainWindow::MainWindow()
{
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    QtBoard *board = new QtBoard(9, 9);

    setWindowTitle(tr("Bimaru Solver"));

    layout->addWidget(board);
    setLayout(layout);
}
