#include "Grille.h"

/*Classe Grille
Compose d objet de la classe case
*/

/**
 * @brief Grille::Grille
 * Constructeur de Grille
 */
Grille::Grille()
{
    for (int x = 0; x < hauteur; x++) {
        for (int y = 0; y < largeur; y++) {
			cases[x][y] = new Case(x, y);

		}
	}
}


/**
 * @brief Grille::~Grille
 * Destructeur de Grille
 */
Grille::~Grille()
{
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			delete cases[i][j];
}

/**
 * @brief Grille::getCase
 * Retourne la case a l abscisse x et a l ordonne y
 * @param x abscisse x
 * @param y ordonne y
 * @return un pointeur sur la pièce demandée
 */
Case* Grille::getCase(int x, int y)
{

   // std::cout << "dans getcase";std::cout << std::endl;
    return cases[x][y];

}

/**
 * @brief Grille::getHauteur
 * @return la hauteur de la grille
 */
int Grille::getHauteur()
{
	return hauteur;
}

/**
 * @brief Grille::getLargeur
 * @return la largeur de la grille
 */
int Grille::getLargeur()
{
	return largeur;
}

/**
 * @brief Grille::putPiece
 * fonction permettant de placer une pièce dans une case
 * @param piece pointeur sur la pièce à mettre dans la case
 */
void Grille::putPiece(Piece *piece)
{
    cases[piece->getCoordonne()->getX()][piece->getCoordonne()->getY()]->setPiece();
    cases[piece->getCoordonne()->getX()][piece->getCoordonne()->getY()]->setId(piece->getId());
    cases[piece->getCoordonne()->getX()][piece->getCoordonne()->getY()]->setCouleur(piece->getCouleur());
}

/**
 * @brief Grille::removePiece
 * fonction permettant d'enlever une pièce d'une case
 * @param coordOrigin pointeur sur les coordonnées de la pièce à enlever
 */
void Grille::removePiece(Coordonnee* coordOrigin){
    cases[coordOrigin->getX()][coordOrigin->getY()]->removePiece();
    cases[coordOrigin->getX()][coordOrigin->getY()]->setId('N');
    cases[coordOrigin->getX()][coordOrigin->getY()]->setCouleur(-1);
}
