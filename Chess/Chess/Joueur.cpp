#include "Joueur.h"



Joueur::Joueur(std::string nom, int i)
{
	nomJoueur = nom;
	setOrigin(i);
	generateDeck();
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
		Pion *pion = new Pion();
		int j = int(abs((*origin).getY() - (2 - i % 2)));
		(*pion).setCoordonnee(new Coordonnee(i,j));
		deck.push_back(pion);
	}

	Tour *tour = new Tour();
	int y = (*origin).getY();
	(*tour).setCoordonnee(new Coordonnee(0, y));
	deck.push_back(tour);

	Fou *fou = new Fou();
	(*fou).setCoordonnee(new Coordonnee(2, y));
	deck.push_back(fou);

	Roi *roi = new Roi();
	(*roi).setCoordonnee(new Coordonnee(4, y));
	deck.push_back(roi);

	Cavalier *cavalier = new Cavalier();
	(*cavalier).setCoordonnee(new Coordonnee(6, y));
	deck.push_back(cavalier);

}

void Joueur::afficherPiece()
{
	for (int i = 0; i < deck.size(); i++)
	{
		(*deck[i]).afficher();
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

void Joueur::setOrigin(int i)
{
	switch (i)
	{
	case 0:
		origin = new Coordonnee(0, 0);
		break;
	case 1:
		origin = new Coordonnee(7, 7);
		break;
	default:
		break;
	}
}
