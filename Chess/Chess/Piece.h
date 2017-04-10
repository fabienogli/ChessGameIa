#pragma once
#include "Coordonnee.h"
#include <iostream>

class Piece
{
public:
	Piece();
	Coordonnee getCoordonne();
	void setCoordonnee(int x, int y);
	void kill(Piece& piece);
	bool isAlive();
	void afficher();
	~Piece();
private:
	Coordonnee *coordonnee;
	bool alive;
};

