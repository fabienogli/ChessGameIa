#pragma once
#include "Case.h"
class Grille
{
public:
	Grille();
	~Grille();
	Case getCase(int x, int y);
	int getHauteur();
	int getLargeur();
	void putPiece(Piece * piece);
private:
	static int const hauteur = 8;
	static int const largeur = 8;
	Case *cases[largeur][hauteur];
};

