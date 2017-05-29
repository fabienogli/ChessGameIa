#pragma once
#include "Piece.h"
#include <QVector>
class deplacement;
class Tour : public Piece
{
public:
	Tour();
	~Tour();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]);

};

