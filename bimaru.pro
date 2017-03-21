TEMPLATE = app
VERSION = 1.0

CONFIG += debug

QT += widgets

HEADERS       = mainwindow.h \
                qtboard.h \
                qtfield.h

SOURCES       = bimaru.cpp \
                mainwindow.cpp \
                qtboard.cpp \
                qtfield.cpp

RESOURCES     = bimaru.qrc
