#pragma once
#include "Piece.h"
#include "deplacement.h"
class deplacement;
class Cavalier :public Piece
{
public:
	Cavalier();
	~Cavalier();
    bool testDeplacement(Coordonnee coord, Plateau * plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]);

};

