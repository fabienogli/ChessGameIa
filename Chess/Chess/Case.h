#pragma once
#include "Coordonnee.h"
class Case
{
public:
	Case(int x, int y);
	void setCoord(Coordonnee coord);
	Coordonnee getCoordonee();
	~Case();
private:
	Coordonnee *coordonnee;
};

