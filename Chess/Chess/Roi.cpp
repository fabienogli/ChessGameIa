#include "Roi.h"
#include "Plateau.h"
#include "deplacements.h"
/**
Classe du roi
*/



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

QVector<QPoint> Roi::deplacementsPossible(int idJoueur,const int couleur[8][8],const char idPiece[8][8],QVector<QPoint> *coupPrec){
    return deplacements::deplacementRoi(idPiece,couleur,QPoint(this->getCoordonne()->getX(),this->getCoordonne()->getY()));
}


