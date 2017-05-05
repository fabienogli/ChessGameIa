#include "Dame.h"


Dame::Dame()
{
}


Dame::~Dame()
{
}

bool Dame::testDeplacement(Coordonnee coord, Plateau * plateau)
{
	return(Piece::testDiagonal(coord) || Piece::testHorizontal(coord) || Piece::testVertical(coord));
}
