#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T02:09:23
#
#-------------------------------------------------

QT       += core gui webenginewidgets KGlobalAccel KNotifications

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kweb-player
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    googlemusicplayer.cpp \
    mprisplayerobject.cpp \
    amarok/DBusAbstractAdaptor.cpp \
    playerstatus.cpp \
    trayicon.cpp

HEADERS  += mainwindow.h \
    googlemusicplayer.h \
    mprisplayerobject.h \
    amarok/DBusAbstractAdaptor.h \
    playerstatus.h \
    trayicon.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    jsscripts.qrc

DISTFILES += \
    kweb-player.notifyrc
