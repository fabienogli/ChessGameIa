#include "Cavalier.h"
#include "Plateau.h"
#include "deplacements.h"


Cavalier::Cavalier() :Piece()
{
    id_piece = 'C';
}


Cavalier::~Cavalier()
{
}
QVector<QPoint> Cavalier::deplacementsPossible(int idJoueur, const int couleur[][], const char idPiece[][]){
    return deplacements::deplacementCavalier(couleur,QPoint(this->getCoordonne()->getX(),this->getCoordonne()->getY()));
}

bool Cavalier::testDeplacement(Coordonnee coord, Plateau * plateau)
{
	int x = coord.getX();
	int y = coord.getY();
	bool moveAble = false;
    int i = getCoordonne()->getX();
    int j = getCoordonne()->getY();

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
