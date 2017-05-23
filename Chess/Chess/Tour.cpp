#include "Tour.h"
#include "Plateau.h"


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

