#pragma once
#include "Coordonnee.h"
//#include "Plateau.h"
class Plateau;
#include <iostream>
#include <QVector>
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
    virtual QVector<QPoint> deplacementsPossible(int idJoueur,Plateau * plateau);
    int getCouleur();
    void setCouleur(int i);
	~Piece();
	char getId();
protected:
	Coordonnee *coordonnee;
	bool alive;	
    int couleur;
    /*
     * 100 pour un pion
     * 300 cavalier et fou
     * 500 tour
     * 900 reine
     * 0 roi
     * */
};


