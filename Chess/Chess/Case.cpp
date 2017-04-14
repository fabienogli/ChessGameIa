#include "Case.h"



Case::Case(int x, int y)
{
	occupied = false;
	coordonnee = new Coordonnee(x, y);
}

Coordonnee Case::getCoordonee()
{
	return *coordonnee;
}

bool Case::isOccupied()
{
	return occupied;
}

void Case::setPiece(Piece *piece)
{
	occupied = true;
	pieceCourante = piece;
}

Piece Case::getPiece()
{
	return *pieceCourante;
}

void Case::removePiece()
{
	occupied = false;
}

void Case::setCoord(Coordonnee coord)
{
	*coordonnee = coord;
}


Case::~Case()
{
	delete coordonnee;
}
