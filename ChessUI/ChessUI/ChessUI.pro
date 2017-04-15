#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T10:34:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Chess/Chess/Case.cpp \
    ../../Chess/Chess/Cavalier.cpp \
    ../../Chess/Chess/Coordonnee.cpp \
    ../../Chess/Chess/Dame.cpp \
    ../../Chess/Chess/Fou.cpp \
    ../../Chess/Chess/Grille.cpp \
    ../../Chess/Chess/Joueur.cpp \
    ../../Chess/Chess/main.cpp \
    ../../Chess/Chess/Piece.cpp \
    ../../Chess/Chess/PieceDiagonale.cpp \
    ../../Chess/Chess/Pion.cpp \
    ../../Chess/Chess/Plateau.cpp \
    ../../Chess/Chess/Roi.cpp \
    ../../Chess/Chess/Tour.cpp \
    ../../Chess/Chess/TypePiece.cpp

HEADERS  += mainwindow.h \
    ../../Chess/Chess/Case.h \
    ../../Chess/Chess/Cavalier.h \
    ../../Chess/Chess/Coordonnee.h \
    ../../Chess/Chess/Dame.h \
    ../../Chess/Chess/Fou.h \
    ../../Chess/Chess/Grille.h \
    ../../Chess/Chess/Joueur.h \
    ../../Chess/Chess/Piece.h \
    ../../Chess/Chess/PieceDiagonale.h \
    ../../Chess/Chess/Pion.h \
    ../../Chess/Chess/Plateau.h \
    ../../Chess/Chess/Roi.h \
    ../../Chess/Chess/Tour.h

FORMS    += mainwindow.ui
