#include "Pion.h"



Pion::Pion()
{
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord)
{
	bool verif = false;
	if (coord.getX() == getCoordonne().getX()&& coord.getY() == getCoordonne().getY() - 1)
		verif = true;
	return verif;
}