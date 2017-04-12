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

}

void Joueur::generateDeck()
{
	Cavalier	*cavalier;
	Tour		*tour;
	Fou			*fou;
	Roi			*roi;
	for (int i = 0; i < 8; i++)
	{
		deck.push_back(new Pion());
	}
	deck.push_back(tour);
	deck.push_back(fou);
	deck.push_back(roi);
	deck.push_back(cavalier);

}


Joueur::~Joueur()
{
	for (int i(0); i < deck.size(); ++i)
	{
		delete deck[i];
		deck[i] = 0;
	}
}
