#include "Pion.h"



Pion::Pion()
{
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord)
{ bool verif = false;
    std::cout << "test deplacement";std::cout << std::endl;
    std::cout <<coord.getX();std::cout << std::endl;
    std::cout <<getCoordonne().getX();std::cout << std::endl;
    std::cout <<abs(coord.getY()-getCoordonne().getY());std::cout << std::endl;
    if (coord.getX() == getCoordonne().getX()  && ((abs(coord.getY()-getCoordonne().getY()) == 1) || (abs(coord.getY()-getCoordonne().getY())== 2)))
            verif = true;
    if(verif==true) {std::cout << "vrai";std::cout << std::endl;}
    else{ std::cout << "faux";std::cout << std::endl;}
	return verif;
}
