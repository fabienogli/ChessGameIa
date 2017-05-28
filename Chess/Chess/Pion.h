#pragma once
#include "Piece.h"
#include "Plateau.h"
class Pion : public Piece
{
public:
    Pion(int i);
	~Pion();
    void move(Coordonnee *coord, Coordonnee origin, Plateau * plateau);
    virtual bool testDeplacement(Coordonnee coord, Plateau* Plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8]);
private:
    int nbCout;
    int wayToMove;
};

