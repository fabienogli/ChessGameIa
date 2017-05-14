#pragma once
class Coordonnee
{
public:
	Coordonnee(int a, int b);
    //Coordonnee( Coordonnee const& coord);
	~Coordonnee();
	int getX();
	int getY();
    void setX(int x);
    void setY(int y);
private:
    int x;
    int y;
};

