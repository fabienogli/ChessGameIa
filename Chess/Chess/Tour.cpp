#include "Tour.h"
#include "Plateau.h"
#include "deplacement.h"


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

QVector<QPoint> Tour::deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]){
    int x = this->getCoordonne()->getX();
    int y=this->getCoordonne()->getY();
    return QVector<QPoint>();
    //deplacement::deplacementTour(couleur,QPoint(x,y));
}
