#pragma once
#include "Piece.h"
class PieceDiagonale : public Piece
{
public:
	PieceDiagonale();
	~PieceDiagonale();
	bool testDeplacement(Coordonnee coord);
};

