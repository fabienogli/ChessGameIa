#pragma once
#include "Case.h"
class Grille
{
public:


	Grille();
	~Grille();
	Case getCase(int x, int y);
    Case* getCase2(int x, int y);
	int getHauteur();
	int getLargeur();
	void putPiece(Piece * piece);
    void removePiece(Coordonnee coord);
private:
	static int const hauteur = 8;
	static int const largeur = 8;
	Case *cases[largeur][hauteur];
};

