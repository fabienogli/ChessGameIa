#include "Piece.h"

Piece::Piece()
{
	alive = true;
}

Piece::~Piece()
{
	alive = false;
}

void Piece::kill(Piece& piece)
{
	piece.~Piece();
}

void Piece::setCoordonne(int x, int y)
{
	coordonnee = new Coordonnee(x, y);
}

void Piece::move(Coordonnee& coord)
{
	*coordonnee = coord;
}