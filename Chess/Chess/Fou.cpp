#include "Fou.h"
#include "Plateau.h"
#include "deplacement.h"

Fou::Fou() :Piece()
{
    id_piece = 'F';
}


Fou::~Fou()
{
}
QVector<QPoint> Fou::deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]){
    int x = this->getCoordonne()->getX();
    int y=this->getCoordonne()->getY();
return QVector<QPoint>();
//deplacement::deplacementFou(couleur,QPoint(x,y));
}

bool Fou::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return Piece::testDiagonal(coord, plateau);
}
