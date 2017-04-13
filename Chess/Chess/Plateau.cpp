#include "Plateau.h"


Plateau::Plateau()
{
	damier = new Grille();
	joueur1 = new Joueur("joueur 1");
	joueur2 = new Joueur("joueur 2");
}

void Plateau::afficher()
{
	for (int j = 0; (*damier).getHauteur(); j++) {
		for (int i = 0; (*damier).getLargeur(); i++) {
			if ((*damier).getCase(i, j).isOccupied())
				std::cout << typeid((*damier).getCase(i, j).getPiece()).name();
			else
			{
				std::cout << 0;
			}
		}
		std::cout << std::endl;
	}
}


Joueur & Plateau::getJoueur()
{
	return *joueurActif;
}

Plateau::~Plateau()
{
	delete damier;
	delete joueur1, joueur2, joueurActif;
}
