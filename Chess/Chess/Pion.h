#pragma once
#include "Piece.h"
#include <vector>
#include <QVector>
class Pion : public Piece
{
public:
	Pion();
	~Pion();
    void move(Coordonnee *coord, Coordonnee origin);
	virtual bool testDeplacement(Coordonnee coord);
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);
private:
    int nbCout;
};

