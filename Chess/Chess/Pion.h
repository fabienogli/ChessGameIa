#pragma once
#include "Piece.h"
#include "Plateau.h"
#include <vector>
#include <QVector>
class Pion : public Piece
{
public:
    Pion(int i);
	~Pion();
    void move(Coordonnee *coord, Coordonnee origin, Plateau * plateau);
    virtual bool testDeplacement(Coordonnee coord, Plateau* Plateau);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);
private:
    int nbCout;
    int wayToMove;
};

