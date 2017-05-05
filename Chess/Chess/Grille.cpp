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
Case* Grille::getCase(int x, int y)
{

    std::cout << "dans getcase";std::cout << std::endl;
    return cases[x][y];

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
    (*cases[(*piece).getCoordonne().getX()][(*piece).getCoordonne().getY()]).setId(piece->getId());
    (*cases[(*piece).getCoordonne().getX()][(*piece).getCoordonne().getY()]).setCouleur(piece->getCouleur());
}

void Grille::removePiece(Coordonnee* coordOrigin){
    cases[coordOrigin->getX()][coordOrigin->getY()]->removePiece();
    cases[coordOrigin->getX()][coordOrigin->getY()]->setId('N');
    cases[coordOrigin->getX()][coordOrigin->getY()]->setCouleur(-1);
}
