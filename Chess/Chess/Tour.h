#pragma once
#include "Piece.h"
#include <QVector>
class Tour : public Piece
{
public:
	Tour();
	~Tour();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);

};

