#pragma once
#include "Coordonnee.h"
#include "Piece.h"
#include <QPixmap>

class Case
{

public:
	Case(int x, int y);
	void setCoord(Coordonnee coord);
	Coordonnee getCoordonee();
	bool isOccupied();
    char getId();
    void setId(char id);
    int getCouleur();
    void setCouleur(int i);
	void setPiece();
	void removePiece();
	~Case();
private:
	Coordonnee *coordonnee;
	bool occupied;
    int couleur;
    char id;



};

