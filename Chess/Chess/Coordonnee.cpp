#include "Coordonnee.h"

Coordonnee::Coordonnee(int a, int b)
{
	x = a;
	y = b;
}
/*Coordonnee::Coordonnee(Coordonnee const& coord){
    x=coord.x;
    y=coord.y;
}*/

int Coordonnee::getX()
{
    return this->x;
}

int Coordonnee::getY()
{
    return this->y;
}
void Coordonnee::setX(int x){
    this->x=x;
}

void Coordonnee::setY(int y){
    this->y=y;
}
Coordonnee::~Coordonnee()
{
}
