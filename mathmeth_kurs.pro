#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T23:24:55
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = mathmeth_kurs
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    dialog.cpp \
    calc.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    dialog.h \
    calc.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog.ui

