#pragma once
#include "Piece.h"
class Fou : public Piece 
{
public:
	Fou();
	~Fou();
	virtual bool testDeplacement(Coordonnee coord);
};

