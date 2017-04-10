#pragma once
#include "Piece.h"
class Dame : public Piece
{
public:
	Dame();
	~Dame();
	bool testDeplacement(Coordonnee coord);
};

