#include "Coordonnee.h"



Coordonnee::Coordonnee(int a, int b)
{
	x = a;
	y = b;
}

int Coordonnee::getX()
{
	return x;
}

int Coordonnee::getY()
{
	return y;
}

Coordonnee::~Coordonnee()
{
}
