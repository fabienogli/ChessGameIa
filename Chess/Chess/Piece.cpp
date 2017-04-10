#include "Piece.h"



Piece::Piece()
{
	alive = true;
}

Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}

void Piece::setCoordonnee(Coordonnee coord)
{
	coordonnee = &coord;
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

bool Piece::testDeplacement(Coordonnee coord)
{
	return false;
}

bool Piece::testDiagonal(Coordonnee coord)
{
	int x = coord.getX();
	int y = coord.getY();

	unsigned i = getCoordonne().getX();
	unsigned j = getCoordonne().getY();

	if (x < i)
		i = -i;
	if (y < j)
		j = -j;
	bool moveAble = false;
	while (!moveAble || i < x&&j < y) {
		if (x == i && y == j)
			moveAble = true;
		else {
			i += 1;
			j += 1;
		}
	}
	return moveAble;
}

bool Piece::testVertical(Coordonnee coord)
{
	int y = getCoordonne().getY();
	unsigned j = coord.getY();
	if (j > y)
		j = -j;
	bool moveAble = false;
	while (!moveAble || j < y) {
		if (y == j)
			moveAble = true;
		else
			j++;
	}
}

bool Piece::testHorizontal(Coordonnee coord)
{
	int x = getCoordonne().getX();
	unsigned i = coord.getX();

	if (i > x)
		i = -i;
	bool moveAble = false;
	while (!moveAble || i < x) {
		if (x == i)
			moveAble = true;
		else
		{
			i += 1;
		}
	}
}

void Piece::move(Coordonnee coord)
{
	if (testDeplacement(coord)) {
		setCoordonnee(coord);
	}
}


Piece::~Piece()
{
	alive = false;
}
