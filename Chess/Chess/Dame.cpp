#include "Dame.h"


Dame::Dame()
{
}


Dame::~Dame()
{
}

bool Dame::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return(Piece::testDiagonal(coord, plateau) || Piece::testHorizontal(coord, plateau) || Piece::testVertical(coord, plateau));
}
