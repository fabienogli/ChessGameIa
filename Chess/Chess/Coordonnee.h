#pragma once
class Coordonnee
{
public:
	Coordonnee(int a, int b);
    //Coordonnee( Coordonnee const& coord);
	~Coordonnee();
	int getX();
	int getY();
    void setX(int x1);
    void setY(int y1);
private:
    int x;
    int y;
};

