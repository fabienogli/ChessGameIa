#include "Case.h"
Case::Case(int x, int y)
{
	m_coord = new Coordonnee(x,y);
}

Coordonnee Case::getCoordonnee()
{
	return *m_coord;
}

Case::~Case()
{
	delete m_coord;
}

void Case::setPiece(Piece *piece)
{
	pieceCourante = piece;
}

Piece Case::getPiece()
{
	return *pieceCourante;
}