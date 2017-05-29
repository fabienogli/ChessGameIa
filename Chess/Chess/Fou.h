#pragma once
#include "Piece.h"
class deplacement;
class Fou : public Piece
{
public:
	Fou();
	~Fou();
    virtual bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]);

};

