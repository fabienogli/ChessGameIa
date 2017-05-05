#pragma once
#include "Piece.h"
#include <QVector>
class Plateau;
class Roi : public Piece 
{
public:
	Roi();
	~Roi();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);
};

