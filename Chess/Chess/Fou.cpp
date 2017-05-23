#include "Fou.h"
#include "Plateau.h"


Fou::Fou() :Piece()
{
    id_piece = 'F';
}


Fou::~Fou()
{
}

bool Fou::testDeplacement(Coordonnee coord, Plateau * plateau)
{
    return Piece::testDiagonal(coord, plateau);
}
