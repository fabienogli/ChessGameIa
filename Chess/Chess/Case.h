#pragma once
#include "Coordonnee.h"
#include "Piece.h"
class Case
{
public:
	Case(int x, int y);
	void setCoord(Coordonnee coord);
	Coordonnee getCoordonee();
	bool isOccupied();
	void setPiece();
	void removePiece();
	~Case();
private:
	Coordonnee *coordonnee;
	bool occupied;
};

