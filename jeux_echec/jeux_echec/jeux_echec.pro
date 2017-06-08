#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T16:49:46
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jeux_echec
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fenetre_option.cpp \
    terrain.cpp \
    case_terrain.cpp \
    deplacements.cpp \
    ia.cpp

HEADERS  += mainwindow.h \
    fenetre_option.h \
    terrain.h \
    case_terrain.h \
    deplacements.h \
    Definement.h \
    ia.h

RESOURCES += \
    Image.qrc
