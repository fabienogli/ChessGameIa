#include "Grille.h"



Grille::Grille()
{
	for (int y = 0; y < hauteur; y++) {
		for (int x = 0; x < largeur; x++) {
			cases[x][y] = new Case(x, y);
		}
	}
}


Grille::~Grille()
{
	delete cases;
}

Case Grille::getCase(int x, int y)
{
	return *cases[x][y];
}

int Grille::getHauteur()
{
	return hauteur;
}

int Grille::getLargeur()
{
	return largeur;
}
