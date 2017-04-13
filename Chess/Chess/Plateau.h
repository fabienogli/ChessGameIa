#pragma once
#include "Grille.h"
#include "Joueur.h"
class Plateau
{
public:
	Plateau();
	void afficher();
	Joueur& getJoueur();
	~Plateau();
private:
	Grille *damier;
	Joueur *joueurActif;
	Joueur *joueur1,*joueur2;
};

