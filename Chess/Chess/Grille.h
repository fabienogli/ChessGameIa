#include "Case.h"
#include <vector>
class Grille
{
public:
	Grille();
	~Grille();
	Case& getCase();
private:
	static int const tailleX =8;
	static int const tailleY = 8;
	Case *cases[tailleX][tailleY];
};
