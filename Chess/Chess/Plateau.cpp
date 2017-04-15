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
	for (int i=0; i < (*joueur1).getDeckSize(); i++)
	{
		(*damier).putPiece((*joueur1).getDeck()[i]);
		(*damier).putPiece((*joueur2).getDeck()[i]);
	}
}
//Affichage du plateau dans la console
void Plateau::afficher()
{
	for (int j = 0; j<(*damier).getHauteur(); j++) {
		for (int i = 0; i<(*damier).getLargeur(); i++) {
			if ((*damier).getCase(i, j).isOccupied()) {
				Coordonnee coord(i, j);
				double i1 = (*joueur1).isAnyPiece(coord);
				double i2 = (*joueur2).isAnyPiece(coord);
					if (i1 != -1)
					{
						std::cout << (*joueur1).getPiece(i1).getId();
					}
					else
					{
						std::cout << (*joueur2).getPiece(i2).getId();
					}
					coord.~Coordonnee();
			}
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
Joueur Plateau::getJoueur()
{
	return *joueur1;
}

//Destructeur du plateau
Plateau::~Plateau()
{
	delete damier;
	delete joueur1;
	delete joueur2;
}
