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
	void setPiece(Piece * piece);
	Piece getPiece();
	void removePiece();
	~Case();
private:
	Coordonnee *coordonnee;
	Piece *pieceCourante;
	bool occupied;
};

