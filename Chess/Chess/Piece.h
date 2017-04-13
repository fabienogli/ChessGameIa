#pragma once
#include "Coordonnee.h"
#include <iostream>

class Piece
{
public:
	Piece();
	Coordonnee getCoordonne();
	void setCoordonnee(Coordonnee *coord);
	void kill(Piece& piece);
	bool isAlive();
	void afficher();
	virtual bool testDeplacement(Coordonnee coord);
	bool testDiagonal(Coordonnee coord);
	bool testVertical(Coordonnee coord);
	bool testHorizontal(Coordonnee coord);
	void move(Coordonnee coord, Coordonnee origin);
	~Piece();
private:
	Coordonnee *coordonnee;
	bool alive;

	
};

