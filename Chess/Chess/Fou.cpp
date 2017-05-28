#include "Fou.h"
#include "Plateau.h"
#include "deplacements.h"

Fou::Fou() :Piece()
{
    id_piece = 'F';
}


Fou::~Fou()
{
}
QVector<QPoint> Fou::deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8]){
return deplacements::deplacementFou(couleur,QPoint(this->getCoordonne()->getX(),this->getCoordonne()->getY()));
}

bool Fou::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return Piece::testDiagonal(coord, plateau);
}
