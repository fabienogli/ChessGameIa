#include <iostream>
#include "Piece.h"
using namespace std;

int main()
{
	Piece piece;
	piece.setCoordonnee(0, 1);
	piece.afficher();
	cin.get();
	return 0;
}

