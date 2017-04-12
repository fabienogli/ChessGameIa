#include <iostream>
#include "Pion.h"

using namespace std;

int main()
{
	Pion piece;
	Coordonnee coord(0, 1);
	piece.setCoordonnee(coord);
	piece.afficher();
	cout << typeid(piece).name() << endl;
	cin.get();
	return 0;
}

