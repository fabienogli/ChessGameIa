#include "Coordonee.h"
#include "Piece.h"
class Case
{
public:
	Case(int x, int y);
	Coordonnee getCoordonnee();
	void setPiece(Piece *piece);
	Piece getPiece();
	~Case();
private:
	Coordonnee *m_coord;
	Piece *pieceCourante;
};

