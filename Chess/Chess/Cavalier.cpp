#include "Cavalier.h"
#include <QVector>
#include "Plateau.h"


Cavalier::Cavalier()
{
}


Cavalier::~Cavalier()
{
}

QVector<QPoint> Cavalier::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> tmp;
    return tmp;
}

bool Cavalier::testDeplacement(Coordonnee coord)
{
	int x = coord.getX();
	int y = coord.getY();
	bool moveAble = false;
	int i = getCoordonne().getX();
	int j = getCoordonne().getY();

	if (x == i + 2 || x == i - 2)
	{
		if (y == j - 1 || y == j + 1)
			moveAble = true;
	}
	else if (y == j - 2 || y == j + 2)
	{
		if (x == i + 1 || x == i - 1)
			moveAble = true;
	}
	return moveAble;

}
