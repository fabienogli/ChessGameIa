#pragma once
#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Dame.h"
#include "Pion.h"
#include "Fou.h"
#include "Tour.h"
#include <vector>

class Joueur
{
public:
	Joueur(std::string nom);
	std::string getNomjoueur();
	Piece getPiece(Piece& pieceSelec);
	void generateDeck();
	void afficherPiece();
	~Joueur();
private:
	std::string nomJoueur;
	static int const nombrePiece = 6;
	std::vector<Piece*> deck;
};

