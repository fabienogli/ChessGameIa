#pragma once
#include "Piece.h"
class Dame : public Piece
{
public:
	Dame();
	~Dame();
	virtual bool testDeplacement(Coordonnee coord);
};

