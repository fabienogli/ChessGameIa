#include "Case.h"

Case::Case(int x, int y)
{
	occupied = false;
    couleur=-1;
    id="";
	coordonnee = new Coordonnee(x, y);
}

char Case::getId(){
    return id;
}
void Case::setId(char id){
    this->id=id;
}
int Case::getCouleur(){
    return couleur;
}
void Case::setCouleur(int i){
    this->couleur=i;
}
Coordonnee Case::getCoordonee()
{
	return *coordonnee;
}

bool Case::isOccupied()
{
	return occupied;
}

void Case::setPiece()
{
	occupied = true;
}



void Case::removePiece()
{
	occupied = false;
}

void Case::setCoord(Coordonnee coord)
{
	*coordonnee = coord;
}


Case::~Case()
{
	delete coordonnee;
}

