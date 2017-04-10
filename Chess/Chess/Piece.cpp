#include "Piece.h"



Piece::Piece()
{
	alive = true;
}

Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}

void Piece::setCoordonnee(int x, int y)
{
	coordonnee = new Coordonnee(x, y);
}

void Piece::kill(Piece & piece)
{
	piece.~Piece();
}

bool Piece::isAlive()
{
	return alive;
}

void Piece::afficher()
{
	std::cout << getCoordonne().getX() << " " << getCoordonne().getY() << " " << isAlive() << std::endl;
}


Piece::~Piece()
{
	alive = false;
}
