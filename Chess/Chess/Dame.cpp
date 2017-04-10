#include "Dame.h"



Dame::Dame()
{
}


Dame::~Dame()
{
}

bool Dame::testDeplacement(Coordonnee coord)
{
	return(Piece::testDiagonal(coord) || Piece::testHorizontal(coord) || Piece::testVertical(coord));
}
