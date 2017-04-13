#include <iostream>
#include "Plateau.h"
#include "Joueur.h"

using namespace std;

int main()
{
	Joueur joueur("Christian");
	joueur.generateDeck();
	joueur.afficherPiece();
	cin.get();
	return 0;
}

