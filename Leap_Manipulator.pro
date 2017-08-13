#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T16:30:14
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Leap_Manipulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    servospinner.cpp

HEADERS  += mainwindow.h \
    servospinner.h

FORMS    += mainwindow.ui

