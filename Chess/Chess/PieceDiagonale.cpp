#include "PieceDiagonale.h"
#include "Plateau.h"


PieceDiagonale::PieceDiagonale()
{
}


PieceDiagonale::~PieceDiagonale()
{
}

bool PieceDiagonale::testDeplacement(Coordonnee coord, Plateau * plateau)
{
	int x = coord.getX();
	int y = coord.getY();

    int i = getCoordonne().getX();
    int j = getCoordonne().getY();

	if (x < i)
		i = -i;
	if (y < j)
		j = -j;
	bool moveAble = false;
    while (!moveAble && i < x&&j < y) {

        if (x == i && y == j){
            if(plateau->getGrille()->getCase(i,j)->getCouleur()!=couleur)
                moveAble = true;
            else{
                moveAble = false;
                i=x;
                j=y;
            }
        }

		else {
            if(plateau->caseAtOccupy(i,j))
            {
                moveAble =false;
                i= x;
                j= y;
            }
			i += 1;
			j += 1;
		}
	}
	return moveAble;
}
