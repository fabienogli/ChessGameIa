#include "Piece.h"

//Initialise la piece
Piece::Piece()
{
	alive = true;
}

//Retourne les coordonne de la piece
Coordonnee Piece::getCoordonne()
{
	return *coordonnee;
}

//Modifie les coordonne de la piece
void Piece::setCoordonnee(Coordonnee *coord)
{
	coordonnee = coord;
}

//Methode lorsqu une piece mange une autre
void Piece::kill(Piece & piece)
{
	piece.~Piece();
}

//Test pour voir si la piece est toujours en vie
bool Piece::isAlive()
{
	return alive;
}

//retourne son abscisse, son ordonnee et le nom de la piece
void Piece::afficher()
{
	std::cout <<"x= "<< getCoordonne().getX() << " et y= " << getCoordonne().getY() << " " << getId()<< std::endl;
}

//Methode pour tester un deplacement
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

//Methode de deplacement de la piece, si le test retourne vrai, la piece peut se deplacer
void Piece::move(Coordonnee coord, Coordonnee origin)
{
	Coordonnee test(origin.getX() - coord.getX(), origin.getY() - coord.getY());
	if (testDeplacement(test)) {
		setCoordonnee(&coord);
	}
}

//Destructeur de la piece
Piece::~Piece()
{
	alive = false;
	delete coordonnee;
}

char Piece::getId()
{
	return typeid(*this).name()[6];
}



