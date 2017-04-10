#include "Case.h"



Case::Case(int x, int y)
{
	coordonnee = new Coordonnee(x, y);
}

Coordonnee Case::getCoordonee()
{
	return *coordonnee;
}

void Case::setCoord(Coordonnee coord)
{
	*coordonnee = coord;
}


Case::~Case()
{
}
