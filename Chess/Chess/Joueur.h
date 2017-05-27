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
    Piece* getPiece2(int i);
    int isAnyPiece(Coordonnee coord);
    int isAnyPiece2(Coordonnee coord);
	void generateDeck();
	void afficherPiece();
	void setOrigin(int i);
    int getIdJoueur();
    std::vector<Piece*> getDeck();
	Piece getPiece(int i);
    Coordonnee getOrigin();
	int getDeckSize();
	~Joueur();
private:
	Coordonnee *origin;
	std::string nomJoueur;
    int id;
	static int const nombrePiece = 6;
    static int wayToMove;
    std::vector<Piece*> deck;
};

