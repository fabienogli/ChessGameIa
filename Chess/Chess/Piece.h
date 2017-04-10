#include "Coordonee.h"
class Piece
{
public:
	Piece();
	~Piece();
	void kill(Piece& piece);
	void setCoordonne(int x, int y);
	void move(Coordonnee& coord);
	Coordonnee& getCoordonne();
	bool isAlive();
private:
	Coordonnee *coordonnee;
	bool alive;
};
