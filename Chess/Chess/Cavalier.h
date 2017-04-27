#pragma once
#include "Piece.h"

#include <QVector>
class Cavalier :public Piece
{
public:
	Cavalier();
	~Cavalier();
	bool testDeplacement(Coordonnee coord);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);

};

