#pragma once
#include "Piece.h"
class Cavalier :public Piece
{
public:
	Cavalier();
	~Cavalier();
	bool testDeplacement(Coordonnee coord);
};

