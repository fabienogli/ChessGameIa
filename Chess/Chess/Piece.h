#pragma once
#include "Coordonnee.h"
//#include "Plateau.h"
class Plateau;
#include <iostream>
#include <vector>

class Piece
{

public:
	Piece();
	Coordonnee getCoordonne();
	void setCoordonnee(Coordonnee *coord);
    void setCoordonne(int x,int y);
	void kill(Piece& piece);
	bool isAlive();
	void afficher();
	virtual bool testDeplacement(Coordonnee coord);
	bool testDiagonal(Coordonnee coord);
	bool testVertical(Coordonnee coord);
	bool testHorizontal(Coordonnee coord);
    bool move(Coordonnee *coord, Coordonnee origin);
    virtual std::vector<Coordonnee> deplacementsPossible(int idJoueur,Plateau plateau);
	~Piece();
	char getId();
private:
	Coordonnee *coordonnee;
	bool alive;	
};

