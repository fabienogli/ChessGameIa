#include "Joueur.h"



Joueur::Joueur(std::string nom)
{
	nomJoueur = nom;
}

std::string Joueur::getNomjoueur()
{
	return nomJoueur;
}

Piece Joueur::getPiece(Piece& pieceSelec)
{
	Coordonnee coord = pieceSelec.getCoordonne();
	bool found = false;
	int i = 0;
	while (found || i < deck.size())
	{
		if (coord.getX() == (*deck[i]).getCoordonne().getX()&& coord.getY() == (*deck[i]).getCoordonne().getY())
		{
			found = true;
		}
		i++;
	}
	return *deck[i];
}

void Joueur::generateDeck()
{
	for (int i = 0; i < 8; i++)
	{
		deck.push_back(new Pion());
	}
	deck.push_back(new Tour());
	deck.push_back(new Fou());
	deck.push_back(new Roi());
	deck.push_back(new Cavalier());

}

void Joueur::afficherPiece()
{
	for (int i = 0; i < deck.size(); i++)
	{
		std::cout << typeid(*deck[i]).name() << std::endl;
	}
}


Joueur::~Joueur()
{
	for (int i(0); i < deck.size(); ++i)
	{
		delete deck[i];
		deck[i] = 0;
	}
}
