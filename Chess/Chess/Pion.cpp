#include "Pion.h"



Pion::Pion()
{
}


Pion::~Pion()
{
}

bool Pion::testDeplacement(Coordonnee coord)
{
    bool verif = false;
   /* if (coord.getX() == getCoordonne().getX()  && coord.getY() == getCoordonne().getY() - 1)
        verif = true;*/
    std::cout << "test deplacement";std::cout << std::endl;
    std::cout <<coord.getX();std::cout << std::endl;
    std::cout <<getCoordonne().getX();std::cout << std::endl;
    std::cout <<abs(coord.getY()-getCoordonne().getY());std::cout << std::endl;
    if (coord.getX() == getCoordonne().getX()  && ((abs(coord.getY()-getCoordonne().getY()== 1)) || (abs(coord.getY()-getCoordonne().getY()== 2))))
            verif = true;
	return verif;
}
