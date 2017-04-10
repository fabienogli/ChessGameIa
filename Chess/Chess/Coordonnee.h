#pragma once
class Coordonnee
{
public:
	Coordonnee(int a, int b);
	~Coordonnee();
	int getX();
	int getY();
private:
	int x;
	int y;
};

