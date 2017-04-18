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
	Joueur(std::string nom, int i);
    Joueur();
	std::string getNomjoueur();
	Piece getPiece(Coordonnee * coord);
	double isAnyPiece(Coordonnee coord);
	void generateDeck();
	void afficherPiece();
	void setOrigin(int i);
    int getIdJoueur();
	std::vector<Piece*> getDeck();
	Piece getPiece(int i);
	int getDeckSize();
	~Joueur();
private:
	Coordonnee *origin;
	std::string nomJoueur;
    int id;
	static int const nombrePiece = 6;
	std::vector<Piece*> deck;
};

