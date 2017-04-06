class Coordonnee
{
public:
	Coordonnee();
	Coordonnee(int i, int j);
	~Coordonnee();
	void setCoordonnee(int i, int j);
	int getX();
	int getY();
private:
	int x;
	int y;
};

