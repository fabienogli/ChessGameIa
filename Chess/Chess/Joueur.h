#pragma once
#include "Piece.h"
class Joueur
{
public:
	Joueur(std::string nom);
	std::string getNomjoueur();
	Piece getPiece(int numPiece);
	~Joueur();
private:
	std::string nomJoueur;
	static int const nombrePiece = 6;
	Piece *deck[2][nombrePiece];
};

