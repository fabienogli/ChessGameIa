#pragma once
#include "Piece.h"
class Roi : public Piece 
{
public:
	Roi();
	~Roi();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);
};

