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
    return x;
}

int Coordonnee::getY()
{
    return y;
}
void Coordonnee::setX(int x1){
    x=x1;
}

void Coordonnee::setY(int y1){
    y=y1;
}
Coordonnee::~Coordonnee()
{
}
