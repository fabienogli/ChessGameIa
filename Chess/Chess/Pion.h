#pragma once
#include "Piece.h"
#include <vector>
#include <QVector>
class Pion : public Piece
{
public:
	Pion();
	~Pion();
	virtual bool testDeplacement(Coordonnee coord);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau plateau);
};

