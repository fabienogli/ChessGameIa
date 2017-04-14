#include "Plateau.h"

//Constructeur du plateau
Plateau::Plateau()
{
	damier = new Grille();
	joueur1 = new Joueur("joueur 1",0);
	joueur2 = new Joueur("joueur 2",1);
	initiatePosInGrid();
}

//Positionne les pieces des differentes piece des joueurs dans le plateau
void Plateau::initiatePosInGrid()
{
	std::vector<Piece*> deck1= (*joueur1).getDeck();
	std::vector<Piece*> deck2 = (*joueur2).getDeck();

	for (int i=0; i < (*joueur1).getDeckSize(); i++)
	{
		(*damier).putPiece(deck1[i]);
		(*damier).putPiece(deck2[i]);
	}
}
//Affichage du plateau dans la console
void Plateau::afficher()
{
	for (int j = 0; j<(*damier).getHauteur(); j++) {
		for (int i = 0; i<(*damier).getLargeur(); i++) {
			if ((*damier).getCase(i, j).isOccupied())
				std::cout << (*damier).getCase(i, j).getPiece().getId();
			else
			{
				std::cout << 0;
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		std::cout << "-------------" << std::endl;
	}
}

//Retourne le pointeur du joueur actif
Joueur & Plateau::getJoueur()
{
	return *joueurActif;
}

//Destructeur du plateau
Plateau::~Plateau()
{
	delete damier;
	delete joueur1, joueur2, joueurActif;
}
