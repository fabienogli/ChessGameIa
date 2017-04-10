#pragma once
#include "Piece.h"
class Fou : public Piece 
{
public:
	Fou();
	~Fou();
	bool testDeplacement(Coordonnee coord);
};

