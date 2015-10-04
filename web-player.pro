#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T02:09:23
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = web-player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    googlemusicplayer.cpp \
    playertrack.cpp

HEADERS  += mainwindow.h \
    googlemusicplayer.h \
    playertrack.h

FORMS    += mainwindow.ui
