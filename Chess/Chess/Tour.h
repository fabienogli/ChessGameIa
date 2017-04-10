#pragma once
#include "Piece.h"
class Tour : public Piece
{
public:
	Tour();
	~Tour();
	bool testDeplacement(Coordonnee coord);
};

