#pragma once
#include "Piece.h"

class Cavalier :public Piece
{
public:
	Cavalier();
	~Cavalier();
    bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8],QVector<QPoint> *coupPrec);

};

