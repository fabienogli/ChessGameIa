#include "Piece.h"


Piece::Piece()
{
	alive = true;
}


Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}

void Piece::setCoordonnee(Coordonnee *coord)
{
	coordonnee = coord;
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
	std::cout <<"x= "<< getCoordonne().getX() << " et y= " << getCoordonne().getY() << " " << isAlive() <<typeid(*this).name()<< std::endl;
}

bool Piece::testDeplacement(Coordonnee coord)
{
	return false;
}

bool Piece::testDiagonal(Coordonnee coord)
{
	int x = coord.getX();
	int y = coord.getY();

	float i = getCoordonne().getX();
	float j = getCoordonne().getY();

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
	float j = coord.getY();
	if (j > y)
		j = -j;
	bool moveAble = false;
	while (!moveAble || j < y) {
		if (y == j)
			moveAble = true;
		else
			j++;
	}
	return moveAble;
}

bool Piece::testHorizontal(Coordonnee coord)
{
	int x = getCoordonne().getX();
	float i = coord.getX();

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
	return moveAble;
}

void Piece::move(Coordonnee coord, Coordonnee origin)
{
	Coordonnee test(origin.getX() - coord.getX(), origin.getY() - coord.getY());
	if (testDeplacement(test)) {
		setCoordonnee(&coord);
	}
}


Piece::~Piece()
{
	alive = false;
}



