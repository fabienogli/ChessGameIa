#include "Coordonee.h"
Coordonnee::Coordonnee()
{
	x = 0;
	y = 0;
}

Coordonnee::Coordonnee(int i, int j)
{
	x = i;
	y = j;
}

int Coordonnee::getX()
{
	return x;
}

int Coordonnee::getY()
{
	return y;
}

void Coordonnee::setCoordonnee(int i, int j)
{
	x = i;
	y = j;
}
Coordonnee::~Coordonnee()
{
}