#include "Grille.h"

/*Classe Grille
Compose d objet de la classe case
*/

//Constructeur de Grille
Grille::Grille()
{
	for (int y = 0; y < hauteur; y++) {
		for (int x = 0; x < largeur; x++) {
			cases[x][y] = new Case(x, y);
		}
	}
}

//Destructeur de Grille
Grille::~Grille()
{
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			delete cases[i][j];
}

//Retourne la case a l abscisse x et a l ordonne y
Case Grille::getCase(int x, int y)
{
	return *cases[x][y];
}

//Retourne la hauteur de la grille
int Grille::getHauteur()
{
	return hauteur;
}

//Retourne la largeur de la grille
int Grille::getLargeur()
{
	return largeur;
}

void Grille::putPiece(Piece *piece)
{
	(*cases[(*piece).getCoordonne().getX()][(*piece).getCoordonne().getY()]).setPiece();
}
