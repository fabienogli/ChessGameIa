#include "Tour.h"
#include <QVector>
#include "Plateau.h"


Tour::Tour()
{
}


Tour::~Tour()
{
}

bool Tour::testDeplacement(Coordonnee coord)
{
	return Piece::testHorizontal(coord) || Piece::testVertical(coord);
}

QVector<QPoint> Tour::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> tmp;
    return tmp;
}
