#include "Roi.h"
/**
Classe du roi
*/
Roi::Roi()
{
}


Roi::~Roi()
{
}

bool Roi::testDeplacement(Coordonnee coord)
{
    if (abs(coord.getX() - getCoordonne().getX()) < 2 && abs(coord.getY() - getCoordonne().getY()) < 2){
        return(testVertical(coord) || testHorizontal(coord));
    }
}
