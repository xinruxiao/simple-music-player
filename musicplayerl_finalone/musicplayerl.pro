#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T10:05:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musicplayerl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylove.cpp \
    playtimer.cpp \
    pausetimer.cpp \
    playlist.cpp \
    controlvoice.cpp \
    mylrc.cpp

HEADERS  += mainwindow.h \
    mylove.h \
    playtimer.h \
    pausetimer.h \
    playlist.h \
    controlvoice.h \
    mylrc.h

FORMS    += mainwindow.ui \
    mylove.ui \
    playtimer.ui \
    pausetimer.ui \
    search.ui \
    playlist.ui \
    controlvoice.ui \
    mylrc.ui

RESOURCES += \
    resource.qrc

RC_ICONS =my.ico
QT +=multimedia