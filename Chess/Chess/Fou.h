#pragma once
#include "Piece.h"
#include <QVector>
class Fou : public Piece 
{
public:
	Fou();
	~Fou();
	virtual bool testDeplacement(Coordonnee coord);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);

};

