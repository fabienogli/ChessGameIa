#pragma once
#include "Piece.h"
#include <vector>
class Pion : public Piece
{
public:
	Pion();
	~Pion();
	virtual bool testDeplacement(Coordonnee coord);
    virtual std::vector<Coordonnee> deplacementsPossible(int idJoueur,Plateau plateau);
};

