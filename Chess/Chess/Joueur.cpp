#include "Joueur.h"


//Methode constructeur de la classe joueur
//prend en parametre le nom du joueur et un int qui determine la position du joueur sur le plateau
Joueur::Joueur(std::string nom, int i)
{
	nomJoueur = nom;
	setOrigin(i);
	generateDeck();
}

//Retourne le nom du joueur
std::string Joueur::getNomjoueur()
{
	return nomJoueur;
}

//Retourne la piece selectionne
Piece Joueur::getPiece(Coordonnee *coord)
{
	bool found = false;
	int i = 0;
	while (found || i < deck.size())
	{
		if ((*coord).getX() == (*deck[i]).getCoordonne().getX()&& (*coord).getY() == (*deck[i]).getCoordonne().getY())
		{
			found = true;
		}
		i++;
	}
	return *deck[i];
}

//Genere les differentes pieces dans un vecteur
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

//Affiche pour chaque piece ses coordonne et le nom de la piece
void Joueur::afficherPiece()
{
	for (int i = 0; i < deck.size(); i++)
	{
		(*deck[i]).afficher();
	}
}

//Destructeur du joueur 
Joueur::~Joueur()
{
	for (int i(0); i < deck.size(); ++i)
	{
		delete deck[i];
	}
	delete origin;
}

//Definie la position du joueur dans le plateau
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

std::vector<Piece*> Joueur::getDeck()
{
	return deck;
}

Piece Joueur::getPiece(int i)
{
	return *deck[i];
}

int Joueur::getDeckSize()
{
	return deck.size();
}


