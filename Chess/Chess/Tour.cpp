#include "Tour.h"
#include "Plateau.h"
#include "deplacements.h"


Tour::Tour() :Piece()
{
    id_piece = 'T';
}


Tour::~Tour()
{
}

bool Tour::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return (testHorizontal(coord,plateau) || testVertical(coord,plateau));
}

QVector<QPoint> Tour::deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8],QVector<QPoint> *coupPrec){
  return deplacements::deplacementTour(couleur,QPoint(this->getCoordonne()->getX(),this->getCoordonne()->getY()));
}
