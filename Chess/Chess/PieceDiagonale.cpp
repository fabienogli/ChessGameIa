#include "PieceDiagonale.h"



PieceDiagonale::PieceDiagonale()
{
}


PieceDiagonale::~PieceDiagonale()
{
}

bool PieceDiagonale::testDeplacement(Coordonnee coord, Plateau * plateau)
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
