#include "Tour.h"



Tour::Tour()
{
}


Tour::~Tour()
{
}

bool Tour::testDeplacement(Coordonnee coord)
{
	return Piece::testHorizontal(coord) || Piece::testVertical(coord);
}