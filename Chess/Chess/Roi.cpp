#include "Roi.h"
#include "Plateau.h"
#include "deplacement.h"
/**
Classe du roi
*/

class deplacement;

Roi::Roi() :Piece()
{
    id_piece = 'R';
}


Roi::~Roi()
{
}

bool Roi::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    if (abs(coord.getX() - getCoordonne()->getX()) < 2 && abs(coord.getY() - getCoordonne()->getY()) < 2){
        return(testVertical(coord, plateau) || testHorizontal(coord, plateau));
    }
}

QVector<QPoint> Roi::deplacementsPossible(int idJoueur,int couleur[8][8],char idPiece[8][8]){
    int x = this->getCoordonne()->getX();
    int y= this->getCoordonne()->getY();
    return QVector<QPoint>();
    //deplacement::deplacementRoi(idPiece,couleur,QPoint(x,y));
}


