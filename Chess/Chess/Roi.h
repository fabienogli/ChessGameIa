#pragma once
#include "Piece.h"
class Roi : public Piece 
{
public:
	Roi();
	~Roi();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8]);
};

