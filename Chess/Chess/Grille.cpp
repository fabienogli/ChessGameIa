#include "Grille.h"

Grille::Grille()
{
	
	for (int j; j < tailleY; j++) {
		for (int i; i < tailleX; i++) {
			cases[i][j] = new Case(i, j);
		}
	}
}

Grille::~Grille()
{
}