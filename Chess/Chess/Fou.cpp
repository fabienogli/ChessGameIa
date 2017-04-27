#include "Fou.h"
#include <QVector>
#include "Plateau.h"


Fou::Fou()
{
}


Fou::~Fou()
{
}
QVector<QPoint> Fou::deplacementsPossible(int idJoueur,Plateau * plateau){
    QVector<QPoint> tmp;
    return tmp;
}

bool Fou::testDeplacement(Coordonnee coord)
{
	return Piece::testDiagonal(coord);
}
