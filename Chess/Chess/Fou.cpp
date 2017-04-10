#include "Fou.h"



Fou::Fou()
{
}


Fou::~Fou()
{
}

bool Fou::testDeplacement(Coordonnee coord)
{
	return Piece::testDiagonal(coord);
}