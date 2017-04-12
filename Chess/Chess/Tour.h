#pragma once
#include "Piece.h"
class Tour : public Piece
{
public:
	Tour();
	~Tour();
	virtual bool testDeplacement(Coordonnee coord);
};

