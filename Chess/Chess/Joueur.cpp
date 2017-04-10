#include "Joueur.h"



Joueur::Joueur(std::string nom)
{
	nomJoueur = nom;
}

std::string Joueur::getNomjoueur()
{
	return nomJoueur;
}

Piece Joueur::getPiece(int numPiece)
{
	if(deck[0][numPiece]>0)
		return Piece();
}


Joueur::~Joueur()
{
	delete deck;
}
